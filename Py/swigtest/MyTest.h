//-*-C++-*-
#ifndef MYTEST_H
#define MYTEST_H

#include <stdio.h>

class MyTest {

public:
    MyTest();
    virtual ~MyTest();

    int MapToStandardSquare(int x, int y,
			    double *sx, double *sy);

};

#endif // MYTEST_H
