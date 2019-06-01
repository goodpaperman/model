// virtefficiency.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h> 
#include <windows.h> 

class Point3d; 
void cross_product(const Point3d &pA, const Point3d &pB); 

int main(int argc, char* argv[])
{
    int i=0; 
    long tick1 = GetTickCount(); 

    {
        class Point3d
        {
        public:
            Point3d(float xx = 0.0, float yy = 0.0, float zz = 0.0) 
                : x(xx), y(yy), z(zz) { } 

            float& fx() { return x; } 
            float& fy() { return y; } 
            float& fz() { return z; } 

        public:
            float x, y, z; 
        }; 

        Point3d pB(1.725, 0.875, 0.478); 
        Point3d pA(0.315, 0.317, 0.838); 

        for(i=0; i<10000000; i++)
        {
            pB.fx() = pA.fx() - pB.fz(); 
            pB.fy() = pA.fy() + pB.fx(); 
            pB.fz() = pA.fz() + pB.fy(); 
        }
    }

    long tick2 = GetTickCount(); 
    printf("inline class spend %d.\n", tick2-tick1); 

    {
        class Point3d
        {
        public:
            Point3d(float xx = 0.0, float yy = 0.0, float zz = 0.0) 
                : x(xx), y(yy), z(zz) { } 

        public:
            float x, y, z; 
        }; 

        Point3d pB(1.725, 0.875, 0.478); 
        Point3d pA(0.315, 0.317, 0.838); 

        for(i=0; i<10000000; i++)
        {
            cross_product(pA, pB); 
        }
    }

    tick2 = GetTickCount(); 
    printf("inline class spend %d.\n", tick2-tick1); 


	return 0;
}

void cross_product(const Point3d &pA, const Point3d &pB)
{
    Point3d pC; 
    pC.x = pA.y * pB.z - pA.z * pB.y; 
    pC.y = pA.z * pB.x - pA.x * pB.z; 
    pC.z = pA.x * pB.y - pA.y * pB.x; 
}