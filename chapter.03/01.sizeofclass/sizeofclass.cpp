// sizeofclass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h> 

class X { }; 
class Y : public virtual X { }; 
class Z : public virtual X { }; 
class A : public Y, public Z { }; 

class B 
{
    int b; 
}; 

class C : public virtual B 
{
    int c; 
}; 

class D : public virtual B 
{
    int d; 
}; 

class E : public C, public D
{
    int e; 
}; 

int main(int argc, char* argv[])
{
    printf("sizeof X == %d \n", sizeof X); 
    printf("sizeof Y == %d \n", sizeof Y); 
    printf("sizeof Z == %d \n", sizeof Z); 
    printf("sizeof A == %d \n", sizeof A); 
    
    printf("sizeof B == %d \n", sizeof B); 
    printf("sizeof C == %d \n", sizeof C); 
    printf("sizeof D == %d \n", sizeof D); 
    printf("sizeof E == %d \n", sizeof E); 
	return 0;
}
