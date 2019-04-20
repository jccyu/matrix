#include <algorithm>
#include <iostream>
#include "camera.h"
#include "transform.h"
using namespace std;

void Camera::FillTriangle(double x1, double y1, double x2, double y2, double x3, double y3) 
{
	// sorting
	if (y1 > y2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	} if (y2 > y3) {
		std::swap(x2, x3);
		std::swap(y2, y3);
	} if (y1 > y2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	// check edge cases: no bot triangle
	if (y2 == y3) FillTopTriangle(x1, y1, x2, y2, x3);
	// check edge cases: no top triangle
	else if (y1 == y2) FillBotTriangle(x1, y1, x2, x3, y3);
	else {
		double x = x1 + (y2 - y1) / (y3 - y1) * (x3 - x1);
		FillTopTriangle(x1, y1, x2, y2, x);
		FillBotTriangle(x2, y2, x, x3, y3);
	}
}

void Camera::FillTopTriangle(double x1, double y1, double x2, double y2, double x3)
{
	double s1 = (x2 - x1) / (y2 - y1) * ratio;
	double s2 = (x3 - x1) / (y2 - y1) * ratio;
	double c1 = x1;
	double c2 = x1;
	for (double i = y1; i < y2; i += ratio)
	{
		FillLine(c1, i, c2);
		c1 += s1;
		c2 += s2;
	}
}

void Camera::FillBotTriangle(double x1, double y1, double x2, double x3, double y3)
{
	double s1 = (x3 - x1) / (y3 - y1) * ratio;
	double s2 = (x3 - x2) / (y3 - y1) * ratio;
	double c1 = x3;
	double c2 = x3;
	for (double i = y3; i > y1; i -= ratio)
	{
		FillLine(c1, i, c2);
		c1 -= s1;
		c2 -= s2;
	}
}

Camera::Camera(double ratio, size_t width, size_t height, double cdist, Vec view, double vangle) :
	ratio{ ratio }, width{ width }, height{ height }, cdist{ cdist }, view{ view }, vangle{ vangle } {}

void Camera::AddPoly(Polygon p)
{
	p = XZRotateTransform{ vangle }.Apply(p - view);
	polys.emplace_back(p);
}

void Camera::Move(Vec vector)
{
	for (auto &v : polys) {
		v = v - vector;
	}
}

void Camera::Zoom(double zoom)
{
	ZoomTransform zt{zoom};
	for (auto &v : polys) {
		v = zt.Apply(v);
	}
}

void Camera::Turn(double roll, double yaw)
{
	if (yaw != 0) {
		XZRotateTransform xzrt{ yaw };
		for (auto &v : polys)
			v = xzrt.Apply(v);
	}
	if (roll != 0) {
		YZRotateTransform yzrt{ roll };
		for (auto &v : polys)
			v = yzrt.Apply(v);
	}
	
}

void Camera::Render()
{
	// clear canvas
	Clear();

	for (auto &p : polys) {
		if (p[0][2] <= 0 || p[1][2] <= 0 || p[2][2] <= 0) continue;
		double x[3];
		double y[3];
		for (size_t i = 0; i < 3; i++)
		{
			x[i] = cdist * p[i][0] / p[i][2];
			y[i] = cdist * p[i][1] / p[i][2];
		}
		FillTriangle(x[0], y[0], x[1], y[1], x[2], y[2]);
		DrawLine(x[0], y[0], x[1], y[1]);
		DrawLine(x[1], y[1], x[2], y[2]);
		DrawLine(x[2], y[2], x[0], y[0]);
	}

	OnRendered();
}

TextCamera::TextCamera(double ratio, size_t width, size_t height, double cdist, Vec view, double vangle) :
	Camera{ ratio, width, height, cdist, view, vangle },
	pixels{ width, vector<char>(height, ' ') },
	halfwidth{ static_cast<double>(width) / 2 },
	halfheight{ ratio * static_cast<double>(height) / 2 } {}

void TextCamera::Clear()
{
	for (auto &v : pixels)
		for (auto &p : v)
			p = ' ';
}

void TextCamera::OnRendered()
{
	for (size_t i = 0; i < GetHeight(); i++)
	{
		for (size_t j = 0; j < GetWidth(); j++)
			cout << pixels[j][i];
		cout << endl;
	}
}

void TextCamera::DrawLine(double x1, double y1, double x2, double y2) { return; }

void TextCamera::FillLine(double x1, double y1, double x2) {
	if (y1 >= halfheight || y1 < -halfheight) return;
	y1 = (y1 + halfheight) / GetRatio();
	if (x1 > x2) { std::swap(x1, x2); }
	if (x1 >= halfwidth || x2 < -halfwidth) return;
	size_t len = x2 > halfwidth ? GetWidth() - 1 : x2 + halfwidth;
	for (size_t i = x1 < -halfwidth ? 0 : x1 + halfwidth; i < len; i++)
		pixels[i][y1] = '#';
}


