//-*-C++-*-
#ifndef __IODATASTREAM_H__
#define __IODATASTREAM_H__

// class IoDataStream
// 
// All MG I/O should go through this class.  To do I/O with this class,
// create an instance of it, associate that instance with a file, and
// then call the I/O member functions.
// 
// In the future we may implement ways to have this class associated with
// something other than a FILE; in particular a character string.

#include <stdio.h>
#include <stdarg.h>

class IoDataStream 
{

private:
    enum {                      // these values are used internally
        _NONE    = 0x0,         // to set the values of the
        _NEWLINE = 0x1,         // WhiteSpaceFlag enum type below.
        _COMMENT = 0x2
    };

public:
    IoDataStream(FILE *fp = NULL);
    IoDataStream(char *filename, char *mode);
    ~IoDataStream();

    // Open a file and associate it with this IoDataStream instance.
    // Parameters are the same as for the standard C library FOpen()
    // function.
    int FOpen(const char *filename, char *mode);

    // Close the file associated with this IoDataStream.
    int FClose();

    // Associate an already opened file with this IoDataStream.  First
    // closes any file currently associated with this IoDataStream.
    int AttachFILE(FILE *fp);

    // Unassociate it.  Does not close the file.
    void DetachFILE();

    // Get the name of the file associated with this data stream,
    // if any.
    char *GetFileName();

    // Set the name of the file associated with this data stream;
    // this is so that callers can give meaningful names to streams
    // that aren't really associated with a file.
    void SetFileName(char *fileanme);

    // Get a character from this IoDataStream.  Like the standard C library
    // getc() function.
    int GetC();

    // Analogous to standard C library "ungetc".  Actually uses "ungetc"
    // for files, so supports the same size "unget" buffer (not sure
    // what that size is).
    int UnGetC(int c);

    // Put a character
    int PutC(int c);

    // Put a string
    int PutS(const char *s);

    // Read a string of count chars into buffer buf; return the
    // actual number of chars read.  Like the system read(2) call.
    int Read(char *buf, int count);

    // formatted printing, like standard C "PrintF":
    int PrintF(const char *format, ...);

    int error();

    typedef enum {
        // Skip blanks, tabs, newlines, and comments (#...\n):
        SIG_NONE                = _NONE,
        // Skip blanks, tabs, and comments, but newlines are interesting
        //   (including the \n that terminates a comment):
        SIG_NEWLINE             = _NEWLINE,
        // Skip blanks, tabs, and newlines, but stop at #:
        SIG_COMMENT             = _COMMENT,
        // Skip blanks and tabs but stop at # or \n:
        SIG_COMMENT_AND_NEWLINE = _NEWLINE|_COMMENT
    } WhiteSpaceFlag;

    // Advances f to the next "interesting" character and returns it.
    // The returned char is ungetc'ed so the next getc() will yield the
    // same value. "Interesting" depends on the value of whiteSpaceFlag.
    int fnextc(WhiteSpaceFlag whiteSpaceFlag);

    typedef enum {
        ASCII,
        BINARY
    } DataType;

    // Read an array of floats from a file in ASCII or BINARY format.
    // Returns number of floats successfully read, should = nfloats.
    // BINARY means "IEEE 32-bit floating-point" format.
    int fgetnf(int maxf, float *fv, DataType dataType);

    // Read an array of ints from a file in ASCII or BINARY format.
    // Returns number of ints successfully read, should = nints.
    // BINARY means "32-bit big-endian" integer format.
    int fgetni(int maxi, int *iv, DataType dataType);

    // Read an array of shorts from a file in ASCII or BINARY format.
    // Returns number of shorts successfully read, should = nints.
    // BINARY means "16-bit big-endian" integer format.
    int fgetns(int maxs, short *sv, DataType dataType);

    // Expect the given string to appear immediately on file.  Return 0
    // if the complete string is found, else the offset+1 of the last
    // matched char within string.  The first unmatched char is
    // ungetc'd.
    int fexpectstr(char *str);

    // Expect the given string to appear on the file, possibly after
    // skipping some white space and comments.  Return 0 if found, else
    // the offset+1 of last matched char in string.  The first unmatched
    // char is ungetc'd.
    int fexpecttoken(char *str);

    // Skips uninteresting characters with fnextc(whiteSpaceFlag), then
    // returns a "token" - string of consecutive interesting characters.
    // Returns NULL if EOF is reached with no token, or if flags
    // specifies stopping at end-of-line and this is encountered with no
    // token found.  The token is effectively statically allocated and
    // will be overwritten by the next ftoken() call.
    char * ftoken(WhiteSpaceFlag whiteSpaceFlag);

    // Like ftoken(), but specially handles the characters in delims[].
    // If one appears at the beginning of the token, it's returned as a
    // single-character token.  If a member of delims[] appears after
    // other characters have been accumulated, it's considered to
    // terminate the token.  So successive calls to fdelimtok("()", f,
    // 0) on a file containing (fred smith) would return "(", "fred",
    // "smith", and ")".  Behavior is undefined if one of the predefined
    // delimiters (white space or #) appears in delims[].  Explicit
    // quoting (with ", ' or \) overrides detection of delimiters.
    char * fdelimtok(char *delims, WhiteSpaceFlag whiteSpaceFlag);

    // Reads 4x4 matrices from FILE.  Returns the number of matrices
    // found, up to ntransforms.  Returns 0 if no numbers are found.  On
    // finding incomplete matrices (not a multiple of 16 floats) returns
    // -1, regardless of whether any whole matrices were found.
    // Matrices are expected in the form used to transform a row vector
    // multiplied on the left, i.e.  p * T -> p'; thus Euclidean
    // translations appear in the last row.
    int fgettransform(int ntrans,
                    float *trans /* float trans[ntrans][4][4] */,
                    DataType dataType);


    // Writes 'nfloats' floats to the given file.  ASCII is in %g format,
    // separated by blanks.
    int fputnf(int count, float *v, DataType dataType);

    // Writes 4x4 matrices to FILE.  Returns the number written, i.e.
    // ntrans unless an error occurs.
    int fputtransform(int ntrans, float *trans, DataType dataType);

    // async_fnextc() and async_getc() return NODATA if none is
    // immediately available
    enum {
        NODATA = -2
    };

    // WARNING!!! Current implementation of these async_* functions
    // doesn't look like it will work on non-Unix systems.  In
    // particular, before using these on Windows, we need to fix them!!
    // mbp Thu May 08 15:29:30 1997

    int async_getc();
    int async_fnextc(WhiteSpaceFlag whiteSpaceFlag);

    int lineNumber() { return mLineNo; }

private:
    FILE *mpFile;
    char *mToken;
    int   mTRoom;

    int mLineNo;

    int fescape();              // not quite sure what this does
                                    // mbp Thu May 08 15:11:36 1997

    char mFileName[1024];
};

#endif //__IODATASTREAM_H__
