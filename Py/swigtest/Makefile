PYTHONINC = /usr/local/include/python2.0
CXX = c++
INCLUDES = -I${PYTHONINC}

all: mytestcmodule.so

MyTest.o: MyTest.cpp MyTest.h
	${CXX} -c MyTest.cpp

mytest_wrap.o: mytest_wrap.cpp
	${CXX} ${CFLAGS} -c ${INCLUDES} -o mytest_wrap.o mytest_wrap.cpp

mytestcmodule.so: mytest_wrap.o MyTest.o
	${CXX} ${CFLAGS} -shared -o mytestcmodule.so mytest_wrap.o MyTest.o

mytest.py mytest_wrap.cpp: mytest.i MyTest.i
	swig -o mytest_wrap.cpp -python -c++ -shadow mytest.i
