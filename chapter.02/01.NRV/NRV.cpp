// NRV.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <stdio.h> 

class test
{
    friend test foo(double); 
public:
    test() 
    {
        memset(array, 0, 100 * sizeof(double)); 
    } 

private:
    double array[100]; 
}; 

test foo(double val)
{
    test local; 
    local.array[0] = val; 
    local.array[99] = val; 
    return local; 
}

class demo
{
    friend demo foo2(double); 
public:
    demo() 
    {
        memset(array, 0, 100 * sizeof(double)); 
    } 

    inline demo(const demo& d)
    {
        memcpy(this, &d, sizeof(demo)); 
    }

private:
    double array[100]; 
}; 

demo foo2(double val)
{
    demo local; 
    local.array[0] = val; 
    local.array[99] = val; 
    return local; 
}

int main(int argc, char* argv[])
{
    long tick1 = GetTickCount(); 
    for(int cnt = 0; cnt < 10000000; cnt++)
        test t = foo(double(cnt)); 
    
    long tick2 = GetTickCount(); 
    for(cnt = 0; cnt < 10000000; cnt++)
        demo d = foo2(double(cnt)); 


    long tick3 = GetTickCount(); 
    printf("test elapsed %d\n demo elapsed %d\n", tick2-tick1, tick3-tick2); 
	return 0;
}
