// efficiency.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h> 
#include <windows.h> 

int main(int argc, char* argv[])
{
    int i=0; 
    long tick1 = GetTickCount(); 


    {
        float pA_x = 1.725, pA_y = 0.875, pA_z = 0.478; 
        float pB_x = 0.315, pB_y = 0.317, pB_z = 0.838; 
        
        for(i=0; i<10000000; i++)
        {
            pB_x = pA_x - pB_z; 
            pB_y = pA_y + pB_x; 
            pB_x = pA_x + pB_y; 
        }
    }

    long tick2 = GetTickCount(); 
    printf("local variable spend %d.\n", tick2-tick1); 

    {
        enum fusy{ x, y, z}; 
        float pB[3] = { 1.725, 0.875, 0.478 }; 
        float pA[3] = { 0.315, 0.317, 0.838 }; 
        
        for(i=0; i<10000000; i++)
        {
            pB[x] = pA[x] - pB[z]; 
            pB[y] = pA[y] + pB[x]; 
            pB[z] = pA[z] + pB[y]; 
        }
    }

    tick1 = GetTickCount(); 
    printf("local array spend %d.\n", tick1-tick2); 

    {
        struct { float x, y, z; } pB = { 1.725, 0.875, 0.478 }, 
            pA = { 0.315, 0.317, 0.838 }; 
        
        for(i=0; i<10000000; i++)
        {
            pB.x = pA.x - pB.z; 
            pB.y = pA.y + pB.x; 
            pB.z = pA.z + pB.y; 
        }
    }

    tick2 = GetTickCount(); 
    printf("struct spend %d.\n", tick2-tick1); 

    {
        class Point3d
        {
        public:
            Point3d(float xx = 0.0, float yy = 0.0, float zz = 0.0) 
                : _x(xx), _y(yy), _z(zz) { } 

            float& x() { return _x; } 
            float& y() { return _y; } 
            float& z() { return _z; } 

        private: 
            float _x, _y, _z; 
        }; 

        Point3d pB(1.725, 0.875, 0.478); 
        Point3d pA(0.315, 0.317, 0.838); 

        for(i=0; i<10000000; i++)
        {
            pB.x() = pA.x() - pB.z(); 
            pB.y() = pA.y() + pB.x(); 
            pB.z() = pA.z() + pB.y(); 
        }
    }

    tick1 = GetTickCount(); 
    printf("inline class spend %d.\n", tick1-tick2); 

    {
        class Point3d
        {
        public:
            Point3d(float xx = 0.0, float yy = 0.0, float zz = 0.0) 
                : _x(xx), _y(yy), _z(zz) { } 

            float x() { return _x; } 
            void x(float newX) { _x = newX; } 
            float y() { return _y; } 
            void y(float newY) { _y = newY; } 
            float z() { return _z; } 
            void z(float newZ) { _z = newZ; } 

        private: 
            float _x, _y, _z; 
        }; 

        Point3d pB(1.725, 0.875, 0.478); 
        Point3d pA(0.315, 0.317, 0.838); 

        for(i=0; i<10000000; i++)
        {
            pB.x(pA.x() - pB.z()); 
            pB.y(pA.y() + pB.x()); 
            pB.z(pA.z() + pB.y()); 
        }
    }

    tick2 = GetTickCount(); 
    printf("get/set class spend %d.\n", tick2-tick1); 

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

        for(i=0; i<10000000; i++)
        {
            pB._x = pA._x - pB._z; 
            pB._y = pA._y + pB._x; 
            pB._z = pA._z + pB._y; 
        }
    }

    tick1 = GetTickCount(); 
    printf("thri-derived direct class spend %d.\n", tick1-tick2); 

    {
        class Point1d
        {
        public:
            Point1d(float xx = 0.0) 
                : _x(xx) { } 

            float x() { return _x; }
            void x(float newX) { _x = newX; } 

        private: 
            float _x; 
        }; 

        class Point2d : public Point1d
        {
        public:
            Point2d(float xx = 0.0, float yy = 0.0)
                : Point1d(xx), _y(yy) { } 

            float y() { return _y; }
            void y(float newY) { _y = newY; } 

        private: 
            float _y; 
        }; 

        class Point3d : public Point2d
        {
        public:
            Point3d(float xx = 0.0, float yy = 0.0, float zz = 0.0) 
                : Point2d(xx, yy), _z(zz) { } 

            float z() { return _z; } 
            void z(float newZ) { _z = newZ; } 

        private: 
            float _z; 
        }; 

        Point3d pB(1.725, 0.875, 0.478); 
        Point3d pA(0.315, 0.317, 0.838); 

        for(i=0; i<10000000; i++)
        {
            pB.x(pA.x() - pB.z()); 
            pB.y(pA.y() + pB.x()); 
            pB.z(pA.z() + pB.y()); 
        }
    }

    tick2 = GetTickCount(); 
    printf("thri-derived inline spend %d.\n", tick2-tick1); 

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

        for(i=0; i<10000000; i++)
        {
            pB._x = pA._x - pB._z; 
            pB._y = pA._y + pB._x; 
            pB._z = pA._z + pB._y; 
        }
    }

    tick1 = GetTickCount(); 
    printf("thri-derived 1-virtual direct class spend %d.\n", tick1-tick2); 

    {
        class Point1d
        {
        public:
            Point1d(float xx = 0.0) 
                : _x(xx) { } 

            float x() { return _x; }
            void x(float newX) { _x = newX; } 

        private: 
            float _x; 
        }; 

        class Point2d : virtual public Point1d
        {
        public:
            Point2d(float xx = 0.0, float yy = 0.0)
                : Point1d(xx), _y(yy) { } 

            float y() { return _y; }
            void y(float newY) { _y = newY; } 

        private: 
            float _y; 
        }; 

        class Point3d : public Point2d
        {
        public:
            Point3d(float xx = 0.0, float yy = 0.0, float zz = 0.0) 
                : Point2d(xx, yy), _z(zz) { } 

            float z() { return _z; } 
            void z(float newZ) { _z = newZ; } 

        private: 
            float _z; 
        }; 

        Point3d pB(1.725, 0.875, 0.478); 
        Point3d pA(0.315, 0.317, 0.838); 

        for(i=0; i<10000000; i++)
        {
            pB.x(pA.x() - pB.z()); 
            pB.y(pA.y() + pB.x()); 
            pB.z(pA.z() + pB.y()); 
        }
    }

    tick2 = GetTickCount(); 
    printf("thri-derived 1-virtual inline spend %d.\n", tick2-tick1); 

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

        for(i=0; i<10000000; i++)
        {
            pB._x = pA._x - pB._z; 
            pB._y = pA._y + pB._x; 
            pB._z = pA._z + pB._y; 
        }
    }

    tick1 = GetTickCount(); 
    printf("thri-derived 2-virtual direct class spend %d.\n", tick1-tick2); 

    {
        class Point1d
        {
        public:
            Point1d(float xx = 0.0) 
                : _x(xx) { } 

            float x() { return _x; }
            void x(float newX) { _x = newX; } 

        private: 
            float _x; 
        }; 

        class Point2d : virtual public Point1d
        {
        public:
            Point2d(float xx = 0.0, float yy = 0.0)
                : Point1d(xx), _y(yy) { } 

            float y() { return _y; }
            void y(float newY) { _y = newY; } 

        private: 
            float _y; 
        }; 

        class Point3d : virtual public Point2d
        {
        public:
            Point3d(float xx = 0.0, float yy = 0.0, float zz = 0.0) 
                : Point2d(xx, yy), _z(zz) { } 

            float z() { return _z; } 
            void z(float newZ) { _z = newZ; } 

        private: 
            float _z; 
        }; 

        Point3d pB(1.725, 0.875, 0.478); 
        Point3d pA(0.315, 0.317, 0.838); 

        for(i=0; i<10000000; i++)
        {
            pB.x(pA.x() - pB.z()); 
            pB.y(pA.y() + pB.x()); 
            pB.z(pA.z() + pB.y()); 
        }
    }

    tick2 = GetTickCount(); 
    printf("thri-derived 2-virtual inline spend %d.\n", tick2-tick1); 


	return 0;
}
