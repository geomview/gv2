//-*-C++-*-
#ifndef OOGLTOKEN_H
#define OOGLTOKEN_H

// class IoOldOoglToken
// 
// Holds an OOGL file token.

#include "IoOldOoglToken.h"

class IoOldOoglToken {

public:
    IoOldOoglToken();
    ~IoOldOoglToken();

public:
    typedef enum {
        UNKNOWN,
        NUMBER,
        STRING,
        SYMBOL
    } TokenType;

    typedef enum {
        FLOAT,
        INTEGER,
        SHORT
    } NumberType;

    TokenType mType;
    double mFValue;
    char *mpCValue;
};


#endif // OOGLTOKEN_H

