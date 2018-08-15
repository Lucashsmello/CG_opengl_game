/*
 * Point.h
 *
 *  Created on: Mar 30, 2013
 *      Author: lucasmello
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <cmath>
#include "GL/glut.h"

#ifndef PI
#define PI 3.14159
#endif


template <class T>
struct Point {
	T x,y,z;
public:
	Point(T x=0,T y=0,T z=0){
		this->x=x;
		this->y=y;
		this->z=z;
	}

	template <class X>
	Point(const Point<X>& p){
		x=p.x;
		y=p.y;
		z=p.z;
	}

	template <class X>
	bool operator==(const Point<X>& p){
		return x==p.x and y==p.y and z==p.z;
	}

	template <class X>
	void operator+=(const Point<X>& p){
		x+=p.x;
		y+=p.y;
		z+=p.z;
	}

	template <class X>
	void operator-=(const Point<X>& p){
		x-=p.x;
		y-=p.y;
		z-=p.z;
	}

	template <class X>
	Point<T> operator-(const Point<X>& p) const{
		return Point(x-p.x,y-p.y,z-p.z);
	}

	template <class X>
	Point<T> operator+(const Point<X>& p) const{
		return Point(x+p.x,y+p.y,z+p.z);
	}

	Point<T> operator*(double v) const{
		return Point(x*v,y*v,z*v);
	}

	void operator*=(double v){
		x*=v;
		y*=v;
		z*=v;
	}

	Point<T> operator/(double v) const{
		return Point(x/v,y/v,z/v);
	}

	Point<T> operator-() const{
		return Point(-x,-y,-z);
	}

	template <class X>
	static double InnerProduct(Point<X> p1, Point<X> p2){
		return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
	}

	double getMagnitude() const{
		return sqrt(InnerProduct(*this,*this));
	}

	double distance(Point<T> p) const{
		Point<T> diff=*this-p;
		return sqrt(InnerProduct(diff,diff));
	}

	void rotateXZ(double ang){
		ang*=PI/180.0;
		T oldx=x;
		x=x*cos(ang)+z*sin(ang);
		z=z*cos(ang)-oldx*sin(ang);
	}

	void print() const{
		std::cout << "(" << x << "," << y << ',' << z << ")";
	}
};

typedef Point<GLdouble> RealPoint;


#endif /* POINT_H_ */
