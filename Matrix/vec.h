#pragma once

class Vec 
{
	double dim[3];
public:
	Vec(double x, double y, double z);
	Vec(const Vec &other);
	Vec &operator=(const Vec &other);
	~Vec();

	const double operator[](size_t i) const;

	Vec operator+(const Vec &val) const;
	Vec operator-(const Vec &val) const;
};
