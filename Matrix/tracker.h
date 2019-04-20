#pragma once
#include "vec.h"

class Tracker
{
public:
	virtual ~Tracker() {};

	virtual void AddPoly(Polygon p) = 0;

	virtual void Move(Vec vector) = 0;
	virtual void Zoom(double zoom) = 0;
	virtual void Turn(double roll, double yaw) = 0;
};

