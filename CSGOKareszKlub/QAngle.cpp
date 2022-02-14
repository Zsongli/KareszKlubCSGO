#include "QAngle.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <cmath>

QAngle QAngle::calc_angle(Vector3 p1, Vector3 p2)
{
	QAngle angles;
	Vector3 delta = p2 - p1;

	if (delta.y == 0 && delta.x == 0) {
		angles.x = delta.z > 0.f ? 270.f : 90.f;
		angles.y = 0;
	}
	else {
		angles.x = (atan2(-delta.z, delta.length_2d()) * (180 / M_PI));
		if (angles.x < 0)
			angles.x += 360;

		angles.y = (atan2(delta.y, delta.x) * (180 / M_PI));
		if (angles.y < 0)
			angles.y += 360;
	}

	angles.z = 0;

	angles.normalize_self();

	return angles;

}

QAngle& QAngle::clamp_self()
{
	while (this->x < -180.0f)
		this->x += 360.0f;

	while (this->x > 180.0f)
		this->x -= 360.0f;

	if (this->x > 89.0f)
		this->x = 89.0f;

	if (this->x < -89.0f)
		this->x = -89.0f;

	while (this->y < -180.0f)
		this->y += 360.0f;

	while (this->y > 180.0f)
		this->y -= 360.0f;

	this->z = 0.0f;

	return *this;
}

QAngle QAngle::clamped()
{
	QAngle tmp = *this;
	tmp.clamp_self();
	return tmp;
}
