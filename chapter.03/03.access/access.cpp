// access.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h> 

class Point3d
{
public:
    float x; 
public:
    float y; 
public:
    float z; 
}; 

template< class class_type, 
          class data_type1, 
          class data_type2 >
char* access_order(
          data_type1 class_type::*mem1, 
          data_type2 class_type::*mem2 )
{
    //assert(mem1 != mem2); 
    return mem1 < mem2 
        ? "member 1 occurs first" 
        : "member 2 occurs first"; 
}

int main(int argc, char* argv[])
{
    printf(access_order(&Point3d::z, &Point3d::y)); 
	return 0;
}
