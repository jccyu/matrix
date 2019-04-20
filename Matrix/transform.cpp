#include <cmath>
#include "transform.h"

Transform::Transform(double a00, double a01, double a02, 
	double a10, double a11, double a12,
	double a20, double a21, double a22) :
	dim{ {a00, a01, a02}, {a10, a11, a12}, {a20, a21, a22} } {}

Transform::~Transform() {}

const double *Transform::operator[](size_t i) const { return dim[i]; }

Vec Transform::Apply(const Vec &val)
{
	return { dim[0][0] * val[0] + dim[0][1] * val[1] + dim[0][2] * val[2],
			 dim[1][0] * val[0] + dim[1][1] * val[1] + dim[1][2] * val[2],
			 dim[2][0] * val[0] + dim[2][1] * val[1] + dim[2][2] * val[2] };
}

Polygon Transform::Apply(const Polygon &val)  { return { Apply(val[0]), Apply(val[1]), Apply(val[2]) }; }

XZRotateTransform::XZRotateTransform(double angle) :
	Transform{ cos(angle), 0, sin(angle), 0, 1, 0, -sin(angle), 0, cos(angle) } {}

YZRotateTransform::YZRotateTransform(double angle) : 
	Transform{ 1, 0, 0, 0, cos(angle), -sin(angle), 0, sin(angle), cos(angle) } {}

ScaleTransform::ScaleTransform(double x, double y, double z) :
	Transform{ x, 0, 0, 0, y, 0, 0, 0, z } {}

ZoomTransform::ZoomTransform(double zoom) :
	ScaleTransform{ zoom, zoom, zoom } {}