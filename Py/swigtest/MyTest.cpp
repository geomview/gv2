#include "MyTest.h"
#include <stdio.h>

MyTest::MyTest()
{
  printf("MyTest contstructor called\n");
}

MyTest::~MyTest()
{
  printf("MyTest destructor called\n");
}

int  MyTest::MapToStandardSquare(int x, int y,
				      double *sx, double *sy)
{
  *sx = x + .12;
  *sy = y + .34;
  return 0;
}
