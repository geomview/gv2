#include "IoDataStream.h"
#include <sys/types.h>
//#include <errno.h>

#if defined(unix) || defined(__unix)
# include <sys/time.h>
# ifndef NeXT
#  include <unistd.h>
# endif
# ifdef AIX
#  include <sys/select.h>
# endif
#endif

#if WIN32
#include <io.h>
#endif

#include <stdlib.h>
#include <string.h>
#ifdef UNIX
#include <bstring.h>
#endif
#include <ctype.h>

   /* Speedy binary I/O if the machine is known to be big-endian */
#if m68k || mc68000 || mips || sparc || __hpux || AIX
# define BIG_ENDIAN 1
#endif

#ifndef BIG_ENDIAN
# if defined(unix) || defined(__unix)
#  include <netinet/in.h>	/* for ntohl(), etc. */
# else

int ntohl(unsigned int v) {
   return ((v>>24)&0xFF | (v>>8)&0xFF00 | (v<<8)&0xFF0000 | (v&0xFF)<<24);
}
int ntohs(unsigned int s) {
   return ((s>>8)&0xFF | (s&0xFF)<<8);
}
#define htonl(v)  ntohl(v)
#define htons(v)  ntohs(v)
# endif
#endif

#ifdef __hpux	/* Hack names of stdio buffer fields */
#define _base __base
#define _ptr __ptr
#define _cnt __cnt
#endif 

#ifdef __FreeBSD__
#define _base _bf._base
#define _ptr _p
#define _cnt _r
#endif

#if defined(__linux__) && !defined(_STDIO_USES_IOSTREAM)
	/* Handle older (pre-1.0) Linux stdio fields,
	 * making them look like later ones.
	 */
#define	 _IO_read_base	_base
#define  _IO_read_ptr	_gptr
#define	 _IO_read_end	_egptr
#endif

	/* Peer into a stdio buffer, check whether it has data available
	 * for reading.  Almost portable given the common stdio ancestry.
	 */
#ifdef __linux__
#define F_HASDATA(f)  ((f)->_IO_read_ptr < (f)->_IO_read_end)
#else
#define F_HASDATA(f)  ((f)->_cnt > 0)
#endif

IoDataStream::IoDataStream(FILE *fp)
{
	mpFile = fp;
	mToken = NULL;
	mTRoom = 0;
	mLineNo = 0;
	mFileName[0] = '\0';
}

IoDataStream::IoDataStream(char *filename, char *mode)
{
	mpFile = NULL;
	mToken = NULL;
	mTRoom = 0;
	mLineNo = 0;
	strcpy(mFileName, filename);
	FOpen(filename, mode);
}

IoDataStream::~IoDataStream()
{
// jcm-purify 12/4/97
    if (mToken) delete mToken;
    if (mpFile) ::fclose(mpFile);
}

char *IoDataStream::GetFileName()
{
  return mFileName;
}

void IoDataStream::SetFileName(char *filename)
{
  strcpy(mFileName, filename);
}

int IoDataStream::AttachFILE(FILE *fp)
{
    if (mpFile) ::fclose(mpFile);
    mpFile = fp;
    mLineNo = 0;
    return (fp != NULL);
}

void IoDataStream::DetachFILE()
{
    mpFile = NULL;
}

int IoDataStream::FOpen(const char *filename, char *mode)
{
    if (mpFile) 
        ::fclose(mpFile);

    mpFile = ::fopen(filename, mode);
    
    if (mpFile == NULL) 
    {
      //        char *er = strerror(errno);
      char *er = "errno not defined yet because I don't know how to resolve _errno in MSVC yet [mbp Tue Feb  6 14:39:21 2001]";
        fprintf(stderr, er);
    }

    mLineNo = 0;
    strcpy(mFileName, filename);
    return (mpFile != NULL);
}

int IoDataStream::FClose()
{
    int r = ::fclose(mpFile);
    mpFile = NULL;
    return r;
}

int IoDataStream::error()
{
    return ferror(mpFile);
}

int IoDataStream::GetC()
{
    int c = getc(mpFile);
    if (c == '\n') mLineNo++;
    return c;
}

int IoDataStream::UnGetC(int c)
{
    if (c == '\n') mLineNo--;
    return ungetc(c, mpFile);
}

int IoDataStream::PutC(int c)
{
    if (c == '\n') mLineNo++;
    return putc(c, mpFile);
}

int IoDataStream::PutS(const char *s)
{
    //if (c == '\n') mLineNo++;
    return fputs(s, mpFile);
}

int IoDataStream::Read(char *buf, int count)
{
  int nbytes = read(fileno(mpFile), buf, count);
  int i;
  for (i=0; i<nbytes; ++i) {
    if (buf[i]=='\n') { mLineNo++; }
  }
  return nbytes;
}


int IoDataStream::PrintF(const char *format, ...)
{
    va_list alist;
    va_start(alist, format);
    int val = vfprintf(mpFile, format, alist);
    va_end(alist);
    return val;
}

int IoDataStream::fnextc(WhiteSpaceFlag whiteSpaceFlag)
{
    register int c;

    c = GetC();
    for(;;) 
    {
        switch(c) 
        {
        case EOF:
            return(EOF);

        case ' ':  case '\t': // Always skip blanks and tabs
            break;	

        case '#':
            if(whiteSpaceFlag & _COMMENT)	// stop on comments, else skip
                goto fim;
            
            while((c = GetC()) != '\n' && c != EOF);
            continue;		// Rescan this c

        case '\n':
            if(!(whiteSpaceFlag & _NEWLINE))	// stop on \n's, else skip them
                break;

        default:
            fim:
            UnGetC(c);
            return(c);
        }
        c = GetC();
    }
}

static float f_pow10[11] = {
    1e0f, 1e1f, 1e2f, 1e3f, 1e4f, 1e5f, 1e6f, 1e7f, 1e8f, 1e9f, 1e10f
};

#define fPow10(n)  ((unsigned)(n) > 10 ? fpow10(n) : f_pow10[n])

static float fpow10(int n)
{
    register int k;
    register float v;

    if((k = n) < 0)
        k = -k;
 
    v = f_pow10[k & 7];
    if(k >= 8) 
    {
        float unit = 1e8f;

        k >>= 3;
        for(;;) 
        {
            if(k & 1)
                v *= unit;
            if((k >>= 1) == 0)
                break;
            unit *= unit;
        }
    }
    return((float)(n < 0 ? 1.0/v : v));
}

/*
 * Read an array of white-space-separated floats from file 'f' in ASCII, fast.
 * Returns the number successfully read.
 */
int IoDataStream::fgetnf(int maxf, float *fv, DataType dataType)
{
    int ngot;
    float v;
    register int c = EOF;
    register long n;
    long w;
    int s, es, nd, any;

    if(dataType == BINARY) 
    {
#if BIG_ENDIAN
        /* Easy -- our native floating point == big-endian IEEE */
        return fread((char *)fv, sizeof(float), maxf, mpFile);
#else /* not native big-endian IEEE */
        for(n=0; n<maxf && fread((char *)&w,sizeof(long),1,mpFile) > 0; n++)
            *(long *)&fv[n] = ntohl(w);
        return n;
#endif /* not native big-endian IEEE */
    }

  /* Read ASCII format floats */
    for(ngot = 0; ngot < maxf; ngot++) 
    {
        if(fnextc(SIG_NONE) == EOF)
          return(ngot);

        n = 0;
        s = 0;
        nd = 0;
        any = 0;

        if((c = GetC()) == '-') 
        {
            s = 1;
            c = GetC();
        }

        while(c >= '0' && c <= '9') 
        {
            n = n*10 + c - '0';
            nd++;
            if(n >= 214748364) 	/* 2^31 / 10 */
            {
                v = any ? v*fPow10(nd) + (float)n : (float)n;
                nd = n = 0;
                any = 1;
            }
            c = GetC();
        }

        v = any ? v*fPow10(nd) + (float)n : (float)n;

        any += nd;

        if(c == '.') 
        {
            nd = n = 0;

            while((c = GetC()) >= '0' && c <= '9') 
            {
                n = n*10 + c - '0';
                nd++;
                if(n >= 214748364) 
                {
                    v += (float)n / fPow10(nd);
                    n = 0;
                }
            }
            v += (float)n / fPow10(nd);
        }

        if(any == 0 && nd == 0)
            break;
        if(c == 'e' || c == 'E') 
        {
            es = nd = 0;
            switch(c = GetC()) 
            {
            case '-':
                es = 1;	/* And fall through */
            case '+':
                c = GetC();
            }

            n = 0;
            while(c >= '0' && c <= '9') 
            {
                n = n*10 + c - '0';
                nd++;
                c = GetC();
            }
            if(nd == 0)
                break;
            if(es) 
                v /= fPow10(n);
            else 
                v *= fPow10(n);
        }
           
        fv[ngot] = s ? -v : v;
    }
    if(c!=EOF) UnGetC(c);
    return(ngot);
}

int IoDataStream::fgetni(int maxi, int *iv, DataType dataType)
{
    int ngot;
    register int c = EOF;
    register long n;
    long w;
    int s, any;

    if(dataType == BINARY) 
    {
#if BIG_ENDIAN
        /* Easy -- our native floating point == big-endian IEEE */
        return fread((char *)iv, sizeof(int), maxi, mpFile);
#else /* not native big-endian int's */
        for(n = 0; n < maxi && fread(&w,4,1,mpFile) > 0; n++)
           iv[n] = ntohl(w);
        return n;
#endif /* not native big-endian int's */
    }

  /* Read ASCII format floats */
    for(ngot = 0; ngot < maxi; ngot++) 
    {
        if(fnextc(SIG_NONE) == EOF)
            return(ngot);

        n = 0;
        s = 0;
        any = 0;

        if((c = GetC()) == '-') 
        {
            s = 1;
            c = GetC();
        }

        while(c >= '0' && c <= '9') 
        { 
            n = n*10 + c - '0';
            any = 1;
            c = GetC();
        }
        if(!any)
            break;
        iv[ngot] = s ? -n : n;
    }
    if(c!=EOF) 
        UnGetC(c);

    return(ngot);
}

int IoDataStream::fgetns(int maxs, short *sv, DataType dataType)
{
    int ngot;
    register int c = EOF;
    register long n;
    short w;
    int s, any;

    if(dataType == BINARY) 
    {
#if BIG_ENDIAN
        /* Easy -- our native floating point == big-endian IEEE */
        return fread((char *)sv, sizeof(short), maxs, mpFile);
#else /* not native big-endian int's */
        for(n = 0; n < maxs && fread(&w,2,1,mpFile) > 0; n++)
            sv[n] = ntohs(w);
        return n;
#endif /* not native big-endian int's */
    }

  /* Read ASCII format floats */
    for(ngot = 0; ngot < maxs; ngot++) 
    {
        if(fnextc(SIG_NONE) == EOF)
            return(ngot);

        n = s = any = 0;

        if((c = GetC()) == '-') 
        {
            s = 1;
            c = GetC();
        }

        while(c >= '0' && c <= '9') 
        {
            n = n*10 + c - '0';
            any = 1;
            c = GetC();
        }

        if(!any)
            break;
        sv[ngot] = (short)(s ? -n : n);
    }
    if(c!=EOF) 
        UnGetC(c);
    return(ngot);
}

/*
 * Check for a string on a file.
 * If found, return 0.
 * If not, return the offset of the last matched char +1
 * and ungetc the failed char so the caller can see it.
 */
int IoDataStream::fexpectstr(char *str)
{
    register char *p = str;
    register int c;

    while(*p != '\0') 
    {
        if((c = GetC()) != *p++) 
        {
            if(c != EOF)
                UnGetC(c);
            return(p - str);
        }
    }
    return 0;
}

/*
 * Check for a string on a file, skipping leading blanks.
 */
int IoDataStream::fexpecttoken(char *str)
{
    (void) fnextc(SIG_NONE);
    return fexpectstr(str);
}

int IoDataStream::fescape()
{
    int n, k, c = GetC();

    switch(c) 
    {
    case 'n': return '\n';
    case 'b': return '\b';
    case 't': return '\t';
    case 'r': return '\r';
    }

    if(c < '0' || c > '7')
        return c;

    n = c-'0';  k = 2;
    while((c = GetC()) >= '0' && c <= '7') 
    {
        n = n*8 | c-'0';
        if(--k <= 0)
            return n;
    }
    if(c != EOF) 
        UnGetC(c);
    return n;
}

/*
 * Get a token, return a string or NULL.
 * Tokens may be "quoted" or 'quoted'; backslashes accepted.
 * The string is statically allocated and should be copied if
 * needed before the next call to ftoken().
 */
char * IoDataStream::ftoken(WhiteSpaceFlag whiteSpaceFlags)
{
    register int c;
    register char *p;
    register int term;

    if((term = fnextc(whiteSpaceFlags)) == EOF)
        return NULL;
    
    if(mToken == NULL) 
    {
        mTRoom = 50;
        //    mToken = malloc(mTRoom * sizeof(char));
        mToken = new char[mTRoom];
        if(mToken == NULL)
            return NULL;
    }

    p = mToken;

    switch(term) 
    {
    case '"':
    case '\'':
        (void)GetC();  
        for(;;) 
        {
            if( (c = GetC()) == EOF || c == term )
                break;
            else if(c == '\\')
                c = fescape();

            *p++ = c;
            
            if(p == &mToken[mTRoom]) 
            {
                // mToken = realloc(mToken, mTRoom * 2);

                char *oldtoken = mToken;
                mToken = new char[mTRoom * 2];
                memcpy(mToken, oldtoken, mTRoom);
                delete oldtoken;

                if(mToken == NULL)
                    return NULL;
                p = &mToken[mTRoom];
                mTRoom *= 2;
            }
        }
        break;

    default:
        if(isspace(term))
            return NULL;
        while((c = GetC()) != EOF && !isspace(c)) 
        {
            if(c == '\\')
            c = fescape();
            *p++ = c;
            if(p == &mToken[mTRoom]) 
            {
                // mToken = realloc(mToken, mTRoom * 2);

                char *oldtoken = mToken;
                mToken = new char[mTRoom * 2];
                memcpy(mToken, oldtoken, mTRoom);
                delete oldtoken;

                if(mToken == NULL)
                    return NULL;
                p = &mToken[mTRoom];
                mTRoom *= 2;
            }
        }
        break;
    }
    *p = '\0';
    return mToken;
}


/*
 * Get a token, return a string or NULL.
 * Tokens may be "quoted" or 'quoted'; backslashes accepted.
 * The string is statically allocated and should be copied if
 * needed before the next call to ftoken().
 */
char * IoDataStream::fdelimtok(char *delims, WhiteSpaceFlag whiteSpaceFlag)
{
    register int c;
    register char *p;
    register char *q;
    register int term;

    if((term = fnextc(whiteSpaceFlag)) == EOF)
        return NULL;

    if(mToken == NULL) 
    {
        mTRoom = 50;
        // mToken = malloc(mTRoom * sizeof(char));
        mToken = new char[mTRoom];
        if(mToken == NULL)
            return NULL;
    }

    p = mToken;
    switch(term) 
    {
    case '"':
    case '\'':
        (void) GetC();

        for(;;) 
        { 
            if((c = GetC()) == EOF || c == term)
                break;
            else if(c == '\\')
                c = fescape();
        
            *p++ = c;

            if(p == &mToken[mTRoom]) 
            {
                // mToken = realloc(mToken, mTRoom * 2);

                char *oldtoken = mToken;
                mToken = new char[mTRoom * 2];
                memcpy(mToken, oldtoken, mTRoom);
                delete oldtoken;

                if(mToken == NULL)
                    return NULL;
                p = &mToken[mTRoom];
                mTRoom *= 2;
            }
        }
        break;

    default:
        if(isspace(term))
            return NULL;
        
        while((c = GetC()) != EOF && !isspace(c)) 
        {
            if(c == '\\')
            	c = fescape();
            *p = c;
            if(++p == &mToken[mTRoom]) 
            {
            	// mToken = realloc(mToken, mTRoom * 2);

                char *oldtoken = mToken;
                mToken = new char[mTRoom * 2];
                memcpy(mToken, oldtoken, mTRoom);
                delete oldtoken;

                if(mToken == NULL)
	                return NULL;

                p = &mToken[mTRoom];
                mTRoom *= 2;
            }

            for(q = delims; *q && c != *q; q++);

            if(*q) 
            {
                if(p > mToken+1) 
                {
                    p--;
                    UnGetC(c);
	            }
	            break;
            }
        }
        break;
    }
    *p = '\0';
    return mToken;
}


/*
 * Load one or more Transforms from a file.
 * Return 1 on success, 0 on failure.
 */
int IoDataStream::fgettransform(int ntrans,
			    float *trans /* float trans[ntrans][4][4] */,
			    DataType dataType)
{
    register float *T;
    int nt;

    for(nt = 0; nt < ntrans; nt++) 
    {
        T = trans + 16*nt;
        switch(fgetnf(16, T, dataType)) 
        {
        case 16:
            break;

        case 0:
            return nt;

        default:
            return -1;
        }
    }
    return ntrans;
}

int IoDataStream::fputnf(int count, float *v, DataType dataType)
{
    register int i;
    long w;
    if(dataType == BINARY) 
    {
#if BIG_ENDIAN
        return fwrite(v, sizeof(float), count, mpFile);
#else
        for(i = 0; i < count; i++) 
        {
            w = htonl(*(long *)&v[i]);
            fwrite(&w, sizeof(float), 1, mpFile);
        }
        return count;
#endif
    }

    fprintf(mpFile, "%g", v[0]);

    for(i = 1; i < count; i++)
        fprintf(mpFile, " %g", v[i]);

    return count;
}

int IoDataStream::fputtransform(int ntrans, float *trans, DataType dataType)
{
    register int i, n;
    register float *p;

    if(dataType == BINARY) 
    {
#if BIG_ENDIAN
        return fwrite(trans, 4*4*sizeof(float), ntrans, mpFile);
#else
        // OOGLError(1, "fputtransform: need code to handle binary writes for this architecture.");
        // !!! ??? XXXX need to deal with this
        // mbp Thu May 08 11:50:07 1997
        return 0;
#endif
    }

    /* ASCII. */

    for(n = 0; n < ntrans; n++) 
    {
        p = trans + n*16;
        for(i = 0; i < 4; i++, p += 4) 
        {
            fprintf(mpFile, "  %12.8g  %12.8g  %12.8g  %12.8g\n",
                p[0], p[1], p[2], p[3]);
        }
        if(ferror(mpFile))
            return n;
        fprintf(mpFile, "\n");
    }
    return ntrans;
}

/***************************************************************************/

int IoDataStream::async_getc()
{

#if defined(unix) || defined(__unix)

    fd_set fds;
    static struct timeval notime = { 0, 0 };

    if(F_HASDATA(mpFile))
        return GetC();

    FD_ZERO(&fds);
    FD_SET(fileno(mpFile), &fds);

    if(select(fileno(mpFile)+1, &fds, NULL, NULL, &notime) == 1)
        return fgetc(mpFile);

    return NODATA;
#else

    // YO!! Doesn't seem like this will work on non-unix systems!!!
    // Some variant of the above may work on Windows, but need to
    // look into it. mbp Thu May 08 15:29:58 1997

    return GetC();
#endif
}

int IoDataStream::async_fnextc(WhiteSpaceFlag whiteSpaceFlag)
{
    register int c;

    c = async_getc();

    for(;;) 
    {
        switch(c) {
        case EOF:
        case NODATA:
            return(c);

        case ' ':
        case '\t':
            break;			// Always skip blanks and tabs

        case '#':
            if(whiteSpaceFlag & _COMMENT)	// stop on comments, else skip
                goto fim;

            while((c = GetC()) != '\n' && c != EOF)
            {
            }
            
            continue;			/* Rescan this c */

        case '\n':
            if(!(whiteSpaceFlag & _NEWLINE))	// stop on \n's, else skip them
                break;

        default:
fim:
            UnGetC(c);
            return(c);
        }

        c = async_getc();
    }
}

