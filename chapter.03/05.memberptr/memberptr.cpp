// memberptr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h> 
#include <windows.h> 

class Point3d 
{
public:
    virtual ~Point3d() {} 
    
//protected:
    static Point3d origin; 
    float x, y, z; 
}; 

struct Base1 { int val1; }; 
struct Base2 { int val2; }; 
struct Derived : Base1, Base2 { int vald; }; 

void func1(int Derived::*dump, Derived* pd)
{
    pd->*dump = 2; 
}

void func2(Derived* pd)
{
    int Base2::*bmp = &Base2::val2; 
    func1(bmp, pd); 
}

int main(int argc, char* argv[])
{
    printf("&Point3d::x = %p\n", &Point3d::x); 
    printf("&Point3d::y = %p\n", &Point3d::y); 
    printf("&Point3d::z = %p\n", &Point3d::z); 

    printf("&Base1::val1 = %p \n", &Base1::val1); 
    printf("&Base2::val2 = %p \n", &Base2::val2); 
    printf("&Derived::val1 = %p \n", &Derived::val1); 
    printf("&Derived::val2 = %p \n", &Derived::val2); 
    printf("&Derived::vald = %p \n", &Derived::vald); 

    Derived d; 
    func2(&d); 
    //func2(NULL); 

    int i = 0; 
    long tick1 = 0, tick2 = 0; 
    tick1 = GetTickCount(); 

    {
        class Point3d
        {
        public:
            Point3d(float xx = 0.0, float yy = 0.0, float zz = 0.0) 
                : _x(xx), _y(yy), _z(zz) { } 

        public:
            float _x, _y, _z; 
        }; 

        Point3d pB(1.725, 0.875, 0.478); 
        Point3d pA(0.315, 0.317, 0.838); 

        for(i=0; i<10000000; i++)
        {
            pB._x = pA._x - pB._z; 
            pB._y = pA._y + pB._x; 
            pB._z = pA._z + pB._y; 
        }
    }

    tick2 = GetTickCount(); 
    printf("directly member data spend %d.\n", tick2-tick1); 
    
    {
        class Point3d
        {
        public:
            Point3d(float xx = 0.0, float yy = 0.0, float zz = 0.0) 
                : _x(xx), _y(yy), _z(zz) { } 

        public:
            float _x, _y, _z; 
        }; 

        Point3d pB(1.725, 0.875, 0.478); 
        Point3d pA(0.315, 0.317, 0.838); 
        float* ax = &pA._x, *ay = &pA._y, *az = &pA._z; 
        float* bx = &pB._x, *by = &pB._y, *bz = &pB._z; 

        for(i=0; i<10000000; i++)
        {
            *bx = *ax - *bz; 
            *by = *ay + *bx; 
            *bz = *az + *by; 
        }
    }

    tick1 = GetTickCount(); 
    printf("pointer to member data class spend %d.\n", tick1-tick2); 

    {
        class Point3d
        {
        public:
            Point3d(float xx = 0.0, float yy = 0.0, float zz = 0.0) 
                : _x(xx), _y(yy), _z(zz) { } 
            
        public:
            float _x, _y, _z; 
        }; 

        Point3d pB(1.725, 0.875, 0.478); 
        Point3d pA(0.315, 0.317, 0.838); 

        float Point3d::* ax = &Point3d::_x, Point3d::*ay = &Point3d::_y, Point3d::*az = &Point3d::_z; 
        float Point3d::* bx = &Point3d::_x, Point3d::*by = &Point3d::_y, Point3d::*bz = &Point3d::_z; 

        for(i=0; i<10000000; i++)
        {
            pB.*bx = pA.*ax - pB.*bz; 
            pB.*by = pA.*ay + pB.*bx; 
            pB.*bz = pA.*az + pB.*by; 
        }
    }

    tick2 = GetTickCount(); 
    printf("pointer to member data class spend %d.\n", tick2-tick1); 

    {
        class Point1d
        {
        public:
            Point1d(float xx = 0.0) 
                : _x(xx) { } 
            
        public:
            float _x; 
        }; 

        class Point2d : public Point1d
        {
        public:
            Point2d(float xx = 0.0, float yy = 0.0) 
                : Point1d(xx), _y(yy) { } 
            
        public:
            float _y; 
        }; 

        class Point3d : public Point2d
        {
        public:
            Point3d(float xx = 0.0, float yy = 0.0, float zz = 0.0) 
                : Point2d(xx, yy), _z(zz) { } 
            
        public:
            float _z; 
        }; 

        Point3d pB(1.725, 0.875, 0.478); 
        Point3d pA(0.315, 0.317, 0.838); 

        float Point3d::* ax = &Point3d::_x, Point3d::*ay = &Point3d::_y, Point3d::*az = &Point3d::_z; 
        float Point3d::* bx = &Point3d::_x, Point3d::*by = &Point3d::_y, Point3d::*bz = &Point3d::_z; 

        for(i=0; i<10000000; i++)
        {
            pB.*bx = pA.*ax - pB.*bz; 
            pB.*by = pA.*ay + pB.*bx; 
            pB.*bz = pA.*az + pB.*by; 
        }
    }

    tick1 = GetTickCount(); 
    printf("thri-derived class with pointer to member data spend %d.\n", tick1-tick2); 

    {
        class Point1d
        {
        public:
            Point1d(float xx = 0.0) 
                : _x(xx) { } 
            
        public:
            float _x; 
        }; 

        class Point2d : virtual public Point1d
        {
        public:
            Point2d(float xx = 0.0, float yy = 0.0) 
                : Point1d(xx), _y(yy) { } 
            
        public:
            float _y; 
        }; 

        class Point3d : public Point2d
        {
        public:
            Point3d(float xx = 0.0, float yy = 0.0, float zz = 0.0) 
                : Point2d(xx, yy), _z(zz) { } 
            
        public:
            float _z; 
        }; 

        Point3d pB(1.725, 0.875, 0.478); 
        Point3d pA(0.315, 0.317, 0.838); 

        float Point3d::* ax = &Point3d::_x, Point3d::*ay = &Point3d::_y, Point3d::*az = &Point3d::_z; 
        float Point3d::* bx = &Point3d::_x, Point3d::*by = &Point3d::_y, Point3d::*bz = &Point3d::_z; 

        for(i=0; i<10000000; i++)
        {
            pB.*bx = pA.*ax - pB.*bz; 
            pB.*by = pA.*ay + pB.*bx; 
            pB.*bz = pA.*az + pB.*by; 
        }
    }

    tick2 = GetTickCount(); 
    printf("thri-derived 1-virtual class with pointer to member data spend %d.\n", tick2-tick1); 

    {
        class Point1d
        {
        public:
            Point1d(float xx = 0.0) 
                : _x(xx) { } 
            
        public:
            float _x; 
        }; 

        class Point2d : virtual public Point1d
        {
        public:
            Point2d(float xx = 0.0, float yy = 0.0) 
                : Point1d(xx), _y(yy) { } 
            
        public:
            float _y; 
        }; 

        class Point3d : virtual public Point2d
        {
        public:
            Point3d(float xx = 0.0, float yy = 0.0, float zz = 0.0) 
                : Point2d(xx, yy), _z(zz) { } 
            
        public:
            float _z; 
        }; 

        Point3d pB(1.725, 0.875, 0.478); 
        Point3d pA(0.315, 0.317, 0.838); 

        float Point3d::* ax = &Point3d::_x, Point3d::*ay = &Point3d::_y, Point3d::*az = &Point3d::_z; 
        float Point3d::* bx = &Point3d::_x, Point3d::*by = &Point3d::_y, Point3d::*bz = &Point3d::_z; 

        for(i=0; i<10000000; i++)
        {
            pB.*bx = pA.*ax - pB.*bz; 
            pB.*by = pA.*ay + pB.*bx; 
            pB.*bz = pA.*az + pB.*by; 
        }
    }

    tick1 = GetTickCount(); 
    printf("thri-derived 2-virtual class with pointer to member data spend %d.\n", tick1-tick2); 

	return 0;
}
