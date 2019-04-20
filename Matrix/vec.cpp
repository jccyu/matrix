#include "vec.h"

Vec::Vec(double x, double y, double z) : dim{ x, y, z } {}

Vec::Vec(const Vec &other) : dim{ other[0], other[1], other[2] } {}

Vec &Vec::operator=(const Vec &other) 
{ 
	dim[0] = other.dim[0]; 
	dim[1] = other.dim[1];
	dim[2] = other.dim[2];
	return *this; 
}

const double Vec::operator[](size_t i) const { return dim[i]; }

Vec Vec::operator+(const Vec &val) const
{ return { dim[0] + val[0], dim[1] + val[1], dim[2] + val[2] }; }

Vec Vec::operator-(const Vec &val) const
{ return { dim[0] - val[0], dim[1] - val[1], dim[2] - val[2] }; }

Polygon::Polygon(Vec x, Vec y, Vec z) : points{ x, y, z } {}

Polygon::Polygon(const Polygon &other) : points{ other[0], other[1], other[2] } {}

Polygon &Polygon::operator=(const Polygon &other)
{
	points[0] = other[0];
	points[1] = other[1];
	points[2] = other[2];
	return *this;
}
const Vec Polygon::operator[](size_t i) const { return points[i]; }

Polygon Polygon::operator+(const Vec &val) const
{ return { points[0] + val, points[1] + val, points[2] + val }; }

Polygon Polygon::operator-(const Vec &val) const
{ return { points[0] - val, points[1] - val, points[2] - val }; }