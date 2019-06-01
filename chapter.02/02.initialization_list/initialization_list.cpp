// initialization_list.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h> 

class X 
{
public:
    int i; 
    int j; 

public:
    X(int val)
        : j(val), i(j)
    {
    }
}; 

class Y 
{
public:
    int i; 
    int j; 
public:
    Y(int val)
        : j(val)
    {
        i = j; 
    }
}; 

class Z 
{
public:
    int i; 
    int j; 
    int zfoo(int val) { /*return val;*/ return j + val;  } 
public:
    Z(int val)
        : i( zfoo(val) ), j(val)
    {
    }
}; 

class W : public Y 
{
    int _fval; 
public:
    int fval() { return _fval; }
    W(int val) 
        : _fval(val), 
        Y( fval() ) 
    {
    }
}; 

int main(int argc, char* argv[])
{
    X x(3); 
    Y y(5); 
    printf("x.i = %d x.j = %d \n", x.i, x.j); 
    printf("y.i = %d y.j = %d \n", y.i, y.j); 

    Z z(4); 
    printf("z.i = %d z.j = %d \n", z.i, z.j); 

    W w(2); 
    printf("w._fval = %d w.i = %d w.j = %d \n", w.fval(), w.i, w.j); 
	return 0;
}
