#include "vec.h"

Vec::Vec(double x, double y, double z) : dim{ x, y, z } {}

Vec::Vec(const Vec &other) : dim{ other[0], other[1], other[2] } {}

Vec &Vec::operator=(const Vec &other) { 
	dim[0] = other.dim[0]; 
	dim[1] = other.dim[1];
	dim[2] = other.dim[2];
	return *this; }

Vec::~Vec() {}

const double Vec::operator[](size_t i) const { return dim[i]; }

Vec Vec::operator+(const Vec &val) const
{ return { dim[0] + val[0], dim[1] + val[1], dim[2] + val[2] }; }

Vec Vec::operator-(const Vec &val) const
{ return { dim[0] - val[0], dim[1] - val[1], dim[2] - val[2] }; }