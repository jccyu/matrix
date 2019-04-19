#include <iostream>
#include "camera.h"
#include "transform.h"
using namespace std;

Camera::Camera(double ratio, size_t width, size_t height, double cdist, Vec view, double vangle) :
	ratio{ ratio }, width{ width }, height{ height }, cdist{ cdist }, view{ view }, vangle{ vangle },
	halfwidth{ static_cast<double>(width) / 2 }, 
	halfheight{ static_cast<double>(height) / 2 },
	pixels{ width, vector<Pixel>{ height, { false } } } {}

size_t Camera::GetWidth() const { return width; }

size_t Camera::GetHeight() const { return height; }

void Camera::AddPoint(Vec v)
{
	v = XZRotateTransform{vangle}.Apply(v - view);
	points.emplace_back(v);
}

void Camera::Move(Vec vector)
{
	for (auto &v : points) {
		v = v - vector;
	}
}

void Camera::Zoom(double zoom)
{
	ZoomTransform zt{zoom};
	for (auto &v : points) {
		v = zt.Apply(v);
	}
}

void Camera::Turn(double roll, double yaw)
{
	if (yaw != 0) {
		XZRotateTransform xzrt{ yaw };
		for (auto &v : points)
			v = xzrt.Apply(v);
	}
	if (roll != 0) {
		YZRotateTransform yzrt{ roll };
		for (auto &v : points)
			v = yzrt.Apply(v);
	}
	
}

void Camera::UpdatePixels()
{
	for (auto &v : pixels)
		for (auto &p : v)
			p.On = false;
	for (auto &v : points) {
		if (v[2] <= 0) continue;
		double xproj = cdist * v[0] / v[2];
		if (xproj > halfwidth || xproj < -halfwidth) continue;
		double yproj = cdist * v[1] / v[2];
		if (yproj > halfheight || yproj < -halfheight) continue;
		pixels[xproj + halfwidth][yproj + halfheight].On = true;
	 }
}

TextCamera::TextCamera(double ratio, size_t width, size_t height, double cdist, Vec view, double vangle) :
	Camera{ ratio, width, height, cdist, view, vangle } {}

void TextCamera::Render()
{
	UpdatePixels();
	for (size_t i = 0; i < GetHeight(); i++)
	{
		for (size_t j = 0; j < GetWidth(); j++)
			cout << (pixels[j][i].On ? '.' : ' ');
		cout << endl;
	}
}
