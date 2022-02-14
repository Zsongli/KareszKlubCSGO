#pragma once
#include "Vector3.h"

class QAngle : public Vector3 {
public:
	static QAngle calc_angle(Vector3 p1, Vector3 p2);
	QAngle& clamp_self();
	QAngle clamped();
};