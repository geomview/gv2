//-*-C++-*-
#ifndef OOGLLEXER_H
#define OOGLLEXER_H


// class IoOldOoglLexer
// 
// All OOGL file reading should go through this class.  

#include "UtMath.h"
#include "IoDataStream.h"
#include "IoOldOoglToken.h"

class IoOldOoglLexer 
{

public:
    IoOldOoglLexer(IoDataStream* = NULL);
    ~IoOldOoglLexer();

    // Opening and closing files for reading.
    int Open(const char *fname);
    int Close();

    // Read the next token.  Return the string associated with it.
    // If NULL, then EOF.
    char *GetNext();

    // Put the current token back to be read again.
    // You can only go back one step.
    void UngetCurrent();
    // NOTE:  Try to avoid using this function and use LookAhead instead.
    // Then I will get rid of this function.

    // Look at the next token without advancing the input.
    // Return the string associated with it.
    char *LookAhead();

    // Peek ahead to check if the next token is of a certain type expected.
    // Returns true if the TokenType, string or float matches exactly.
    // Checking the float will return false if the TokenType is not a NUMBER.
    int LookAhead(const IoOldOoglToken::TokenType expect);
    int LookAhead(const char *expect);
    int LookAhead(const float expect);

    // Peek at the current token and return various parts.
    IoOldOoglToken::TokenType GetCurrentType();
    char *GetCurrentString();
    float GetCurrentNumber();  // Returns 0 if not NUMBER.

    // Set the input data type to either ASCII or binary.
    inline void DataTypeASCII()  { mDataType = IoDataStream::ASCII; };
    inline void DataTypeBinary() { mDataType = IoDataStream::BINARY; };
    inline IoDataStream::DataType DataType()  { return mDataType; };

    // Functions for reading several numbers at a time.
    virtual int ExpectNum(int count, float *array, IoOldOoglToken::NumberType type);
    inline int ExpectInt(int c,   int *a)  
        { return ExpectNum(c, (float*)a, IoOldOoglToken::INTEGER); };
    inline int ExpectShort(int c, short *a)
        { return ExpectNum(c, (float*)a, IoOldOoglToken::SHORT); };
    inline int ExpectFloat(int c, float *a)
        { return ExpectNum(c, (float*)a, IoOldOoglToken::FLOAT); };

    int Expect(const char *expect);

    // Reporting errors.
    void Error() {};

    // Return the current line number.
    virtual inline int LineNumber() { return mpStream? mpStream->lineNumber() : 0; }

    virtual inline const char *FileName() { return mpFName; }

  //private:
public:
    // Read a token from the stream into the given token holder.
    void ReadToken(IoOldOoglToken *token);

    // Shift the tokens around.
    int SwapForward();
    int SwapBackward();

private:
    IoDataStream            *mpStream;
    IoDataStream::DataType  mDataType;

    IoOldOoglToken *mpNext, *mpCurrent, *mpPrev;

    UtBool mStreamDynCreated;

    char *mpFName;
};


#endif // OOGLLEXER_H

