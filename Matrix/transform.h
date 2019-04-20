#pragma once
#include "vec.h"

class Transform 
{
	const double dim[3][3];
public:
	Transform(double a00, double a01, double a02, 
		double a10, double a11, double a12,
		double a20, double a21, double a22);
	~Transform();

	const double *operator[](size_t i) const;
	Vec Apply(const Vec &val);
	Polygon Apply(const Polygon &val);
};

class XZRotateTransform : public Transform
{
public:
	// in radian
	XZRotateTransform(double angle);
};

class YZRotateTransform : public Transform
{
public:
	// in radian
	YZRotateTransform(double angle);
};

class ScaleTransform : public Transform 
{
public:
	// x in x-axis ... etc.
	ScaleTransform(double x, double y, double z);
};

class ZoomTransform : public ScaleTransform
{
public:
	// zoom coeff.
	ZoomTransform(double zoom);
};
