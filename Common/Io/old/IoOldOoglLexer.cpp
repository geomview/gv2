#include "IoOldOoglLexer.h"
#include "IoDataStream.h"
#include "IoOldOoglToken.h"
#include "UtString.h"           // mbp-purify
//#include "GeomOldOoglParser.h"

#include <stdlib.h>
#include <string.h>
//#include <ctype.h>


IoOldOoglLexer::IoOldOoglLexer(IoDataStream* in_stream)
{
//  mpStream = in_stream ? in_stream : new IoDataStream();
//  We must record whether this variable is dynamically created so that
//  We can delete it if necessary in the destructor.
//  jcm-purify 12/3/97
    if (in_stream)
    {
        mpStream = in_stream;
        mStreamDynCreated = UtFALSE;
    }
    else
    {
        mpStream = new IoDataStream();
        mStreamDynCreated = UtTRUE;
    }
    DataTypeASCII();

    mpPrev = new IoOldOoglToken();
    mpCurrent = new IoOldOoglToken();
    mpNext = NULL;

    mpFName = NULL;
}

IoOldOoglLexer::~IoOldOoglLexer()
{
  if (mpPrev)    delete mpPrev;
  if (mpCurrent) delete mpCurrent;
  if (mpNext)    delete mpNext;

// jcm-purify 12/3/97
  if (mpFName)   delete mpFName;

// jcm-purify 12/3/97
  if (mStreamDynCreated) delete mpStream;
}

int IoOldOoglLexer::Open(const char *fname)
{
  if (fname == NULL) return 0;

  if (mpFName) delete mpFName;
  mpFName = UtString::Strdup(fname);
  return mpStream->FOpen(fname, "r");
}

int IoOldOoglLexer::Close()
{
  if (mpFName) { delete mpFName; mpFName = NULL; }
  return mpStream->FClose();
}


char *IoOldOoglLexer::GetNext()
{
  // Look in "mpNext" for the next token.  "mpNext" is only full if we
  // previously did an Unget or a LookAhead.
  if (mpNext != NULL)
  {
    SwapForward();
    return mpCurrent->mpCValue;
  }

  // Swap the previous token with the current token.  (think about the strings!)
  SwapForward();

  ReadToken(mpCurrent);
  return mpCurrent->mpCValue;
}

void IoOldOoglLexer::UngetCurrent()
{
  if (mpNext != NULL)
  {
        /* ERROR.  Cannot unget more than one token. */
//      GeomOldOoglParser::ParseError(this,
//          "Cannot unget more than one token.  Please report this error to software@geom.umn.edu");
  }

  // Slide tokens back.
  mpNext = mpCurrent;
  mpCurrent = mpPrev;
  mpPrev = NULL;
}

char *IoOldOoglLexer::LookAhead()
{
  if (mpNext == NULL)
  {
    mpNext = mpPrev;
    mpPrev = NULL;
    ReadToken(mpNext);
  }
  return mpNext->mpCValue;
}

void IoOldOoglLexer::ReadToken(IoOldOoglToken* token)
{
#define DELIMS "{}()<:@="
  // Get the next token from the input.
  char *string = mpStream->fdelimtok(DELIMS, IoDataStream::SIG_NONE);

  // First assume it is a string type token, then check later.
  token->mType = IoOldOoglToken::STRING;
  token->mpCValue = string;
        // OOPS!  Can't use this string.  It is reused all the time.

  // If we've reached the end of the file, return NULL.
  if (string == NULL)
    return;

  // See if the token is a number.
  char *s = *string == '-' ? string+1 : string;
  if (*s == '.' || (*s >= '0' && *s <= '9'))
  {
    token->mType = IoOldOoglToken::NUMBER;
    token->mFValue = atof(string);
  }

  else if (strstr(DELIMS, string) != NULL)
  {
    token->mType = IoOldOoglToken::SYMBOL;
  }
}

IoOldOoglToken::TokenType IoOldOoglLexer::GetCurrentType()
{
  return (mpCurrent == NULL)? IoOldOoglToken::UNKNOWN : mpCurrent->mType;
}

char *IoOldOoglLexer::GetCurrentString()
{
  return (mpCurrent == NULL)? NULL : mpCurrent->mpCValue;
}

float IoOldOoglLexer::GetCurrentNumber()
{
  return (mpCurrent == NULL || mpCurrent->mType != IoOldOoglToken::NUMBER)? 0
    : (float)mpCurrent->mFValue;
}

int IoOldOoglLexer::LookAhead(const IoOldOoglToken::TokenType expect)
{
  if (mpNext == NULL) LookAhead();
  return (mpNext == NULL)? 0 : mpNext->mType == expect;
}

int IoOldOoglLexer::LookAhead(const char *expect)
{
  char *string = LookAhead();
  return (string == NULL)? 0 : strcmp(string, expect) == 0;
}

int IoOldOoglLexer::LookAhead(const float expect)
{
  if (mpNext == NULL) LookAhead();
  return (mpNext == NULL || mpNext->mType != IoOldOoglToken::NUMBER)? 0
    : mpNext->mFValue == expect;
}

int IoOldOoglLexer::Expect(const char *expect)
{
  char *string = GetNext();
  return (string == NULL)? 0 : strcmp(string, expect) == 0;
}

int IoOldOoglLexer::ExpectNum(int count, float *array, IoOldOoglToken::NumberType type)
{
        int n = 0, m = 0;  // To keep track of the number of numbers read.
        int *iarray;
        short *sarray;

// This is a bit of a hack to get the incrementing to work in VC++.  I'm 
// not sure why, but VC++ doesn't seem to interpret (int *)array as an 
// l-value and therefore cannot increment it.  There may be something else
// wierd here that is causing this error, but I don't see it at the moment.
// jcm - 10/16/97

        if (count <= 0) return n;

  // First check for lookahead.
        if (mpNext != NULL)
        {
                SwapForward();

                if (GetCurrentType() != IoOldOoglToken::NUMBER) return 0;

                if (type == IoOldOoglToken::INTEGER)
                {
                        int num = (int) GetCurrentNumber();
                        *((int *)array) = num;
                        iarray = (int *)array;
                        iarray++;
                        array = (float *)iarray;
                }
                else if (type == IoOldOoglToken::SHORT)
                {
                        short num = (short) GetCurrentNumber();
                        *((short *)array) = num;
                        sarray = (short *)array;
                        sarray++;
                        array = (float *)iarray;
                }
                else
                {
                        *array = GetCurrentNumber();
                        array++;
                }

                count--; n++;
                if (count <= 0) return n;
        }

        if (type == IoOldOoglToken::INTEGER)
                m = mpStream->fgetni(count, (int   *)array, mDataType);
        else if (type == IoOldOoglToken::SHORT)
                m = mpStream->fgetns(count, (short *)array, mDataType);
        else
                m = mpStream->fgetnf(count, (float *)array, mDataType);

        if (m == 1)
                SwapForward();
        if (m >= 1)
        {
                mpCurrent->mType = IoOldOoglToken::NUMBER;
                mpCurrent->mFValue = array[m-1];
                // mpCurrent->mpCValue = NULL;      <----- What about strings?
                if (m >= 2)
                {
                        mpPrev->mType = IoOldOoglToken::NUMBER;
                        mpPrev->mFValue = array[m-2];
                        // mpPrev->mpCValue = NULL;      <----- What about strings?
                }
        }
        return n+m;
}

int IoOldOoglLexer::SwapForward()
{
    if (mpPrev != NULL)
        mpNext = mpPrev;
    mpPrev = mpCurrent;
    mpCurrent = mpNext;
    mpNext = NULL;
    return 1;
}

int IoOldOoglLexer::SwapBackward()
{
    if (mpNext != NULL)
        return 0;
    mpNext = mpCurrent;
    mpCurrent = mpPrev;
    mpPrev = NULL;
    return 1;
}

