#include "entities.h"
#include "global.h"
#include "interfaces.h"
#include <iostream>

Vector3 Entity::get_eye_position() {
	return origin + view_offset;
}

bool Entity::is_alive() {
	return health > 0 && health <= 100;
}

Vector3 LocalPlayer::get_eye_position()
{
	return origin + view_offset;
}

bool LocalPlayer::is_alive() {
	return health > 0 && health <= 100;
}

QAngle LocalPlayer::get_view_angles() {
	QAngle temp;
	interfaces::client_state->get_view_angles(temp);
	return temp;
}

void LocalPlayer::set_view_angles(QAngle& angle) {
	interfaces::client_state->set_view_angles(angle);
}

void LocalPlayer::aim_at(const Vector3& point) {
	auto angle = QAngle::calc_angle(get_eye_position(), point);
	set_view_angles(angle);
}