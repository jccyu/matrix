#pragma once
#include "tracker.h"

class Renderer : public Tracker
{
public:
	virtual ~Renderer() {};
	virtual void Render() = 0;
};

