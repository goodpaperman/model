// rewriting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef int length; 

class Point3d
{
    typedef void* length; 
public:
    void mumble(length val) { _val = val; } 
    length mumble() { return _val; } 

private:
    //typedef void* length; 
    length _val; 
}; 

int main(int argc, char* argv[])
{
    Point3d d; 
	return 0;
}
