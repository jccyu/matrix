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

	// camera staring position
	const Vec view;
	// camera starting XZ angle (in radian)
	const double vangle;

	virtual void Clear() = 0;
	virtual void OnRendered() {};

	virtual void DrawLine(double x1, double y1, double x2, double y2) = 0;
	virtual void FillLine(double x1, double y1, double x2) = 0;
	void FillTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
	void FillTopTriangle(double x1, double y1, double x2, double y2, double x3);
	void FillBotTriangle(double x1, double y1, double x2, double x3, double y3);

protected:
	// polygons
	std::vector<Polygon> polys;

public:
	// YZ angle is assumed to be zero (i.e. looking at horizon)
	Camera(double ratio, size_t width, size_t height, double cdist, Vec view, double vangle);
	virtual ~Camera() {};

	double GetRatio() const { return ratio; };
	size_t GetWidth() const { return width; };
	size_t GetHeight() const { return height; };

	void AddPoly(Polygon p) override;

	void Move(Vec vector) override;
	void Zoom(double zoom) override;
	void Turn(double roll, double yaw) override;

	void Render() override;
};

class TextCamera : public Camera
{
	// half of width in double
	const double halfwidth;
	// half of height in double
	const double halfheight;
	// pixels
	std::vector<std::vector<char>> pixels;

	void Clear() override;
	void OnRendered() override;

	void DrawLine(double x1, double y1, double x2, double y2) override;
	void FillLine(double x1, double y1, double x2) override;

public:
	TextCamera(double ratio, size_t width, size_t height, double cdist, Vec view, double vangle);
	virtual ~TextCamera() {};

};

