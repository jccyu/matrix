#pragma once

class Vec 
{
	double dim[3];
public:
	Vec(double x, double y, double z);
	Vec(const Vec &other);
	Vec &operator=(const Vec &other);
	~Vec() {};

	const double operator[](size_t i) const;

	Vec operator+(const Vec &val) const;
	Vec operator-(const Vec &val) const;
};

class Polygon {
	Vec points[3];
public:
	Polygon(Vec x, Vec y, Vec z);
	Polygon(const Polygon &other);
	Polygon &operator=(const Polygon &other);
	~Polygon() {};

	const Vec operator[](size_t i) const;

	Polygon operator+(const Vec &val) const;
	Polygon operator-(const Vec &val) const;
};