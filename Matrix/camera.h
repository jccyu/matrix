#pragma once
#include <vector>
#include "renderer.h"

struct Pixel 
{
	bool On;
};

class Camera : Renderer
{

	// height to width ratio for each pixel
	// seems to be 1.5 for default windows font
	const double ratio;
	// pixel width
	const size_t width;
	// pixel height
	const size_t height;
	// distance to camera canvas
	const double cdist;

	const double halfwidth;
	const double halfheight;

	// camera staring position
	const Vec view;
	// camera starting XZ angle (in radian)
	const double vangle;

	std::vector<Vec> points;

protected:
	std::vector<std::vector<Pixel>> pixels;

public:
	// YZ angle is assumed to be zero (i.e. looking at horizon)
	Camera(double ratio, size_t width, size_t height, double cdist, Vec view, double vangle);
	virtual ~Camera() {};

	size_t GetWidth() const;
	size_t GetHeight() const;

	void AddPoint(Vec v) override;

	void Move(Vec vector) override;
	void Zoom(double zoom) override;
	void Turn(double roll, double yaw) override;

	void UpdatePixels();
};

class TextCamera : public Camera
{
public:
	TextCamera(double ratio, size_t width, size_t height, double cdist, Vec view, double vangle);
	virtual ~TextCamera() {};

	void Render() override;
};

