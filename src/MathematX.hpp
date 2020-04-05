#pragma once

#include <cmath>

double deg2rad (double degrees)
{
	return degrees * 4.0 * atan (1.0) / 180.0;
}

double rad2deg(double radians)
{
	return radians * 180.0 / M_PI;
}

float xfov_to_yfov(float xfov, float aspect)
{
	return 2.0f * atan(tan(xfov * 0.5f) / aspect);
}


