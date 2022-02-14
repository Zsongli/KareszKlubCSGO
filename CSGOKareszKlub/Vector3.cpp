#include "Vector3.h"
#include <cmath>

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(float arr[])
{
	this->x = arr[0];
	this->y = arr[1];
	this->z = arr[2];
}

Vector3::Vector3(const Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float* Vector3::data()
{
	return reinterpret_cast<float*>(this);
}

float& Vector3::operator[](size_t i)
{
	return this->data()[i];
}

bool Vector3::equals(const Vector3& other) const
{
	return other.x == this->x && other.y == this->y && other.z == this->z;
}

bool Vector3::operator==(const Vector3& other)
{
	return this->equals(other);
}

bool Vector3::operator!=(const Vector3& other)
{
	return !this->equals(other);
}

Vector3& Vector3::operator=(const Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Vector3& Vector3::operator+=(const float& scalar)
{
	this->x += scalar;
	this->y += scalar;
	this->z += scalar;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

Vector3& Vector3::operator-=(const float& scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	this->z -= scalar;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	return *this;
}

Vector3& Vector3::operator*=(const float& scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	return *this;
}

Vector3& Vector3::operator/=(const float& scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
	return *this;
}

Vector3 Vector3::operator+(const Vector3& other)
{
	return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3 Vector3::operator+(const float& other)
{
	return Vector3(this->x + other, this->y + other, this->z + other);
}

Vector3 Vector3::operator-(const Vector3& other)
{
	return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3 Vector3::operator-(const float& other)
{
	return Vector3(this->x - other, this->y - other, this->z - other);
}

Vector3 Vector3::operator*(const Vector3& other)
{
	return Vector3(this->x * other.x, this->y * other.y, this->z * other.z);
}

Vector3 Vector3::operator*(const float& other)
{
	return Vector3(this->x * other, this->y * other, this->z * other);
}

Vector3 Vector3::operator/(const Vector3& other)
{
	return Vector3(this->x / other.x, this->y / other.y, this->z / other.z);
}

Vector3 Vector3::operator/(const float& other)
{
	return Vector3(this->x / other, this->y / other, this->z / other);
}

float Vector3::length()
{
	return std::sqrtf(x * x + y * y + z * z);
}

float Vector3::length_2d_sqr()
{
	return x * x + y * y;
}

float Vector3::length_2d()
{
	return std::sqrtf(length_2d_sqr());
}

float Vector3::dot_product(const Vector3& other) const
{
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector3 Vector3::cross_product(const Vector3& other) const
{
	return Vector3(this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x);
}

Vector3& Vector3::normalize_self()
{
	auto x_rev = this->x / 360.f;
	if (this->x > 180.f || this->x < -180.f) {
		x_rev = std::abs(x_rev);
		x_rev = std::round(x_rev);

		if (this->x < 0.f)
			this->x = (this->x + 360.f * x_rev);

		else
			this->x = (this->x - 360.f * x_rev);
	}

	auto y_rev = this->y / 360.f;
	if (this->y > 180.f || this->y < -180.f) {
		y_rev = std::abs(y_rev);
		y_rev = std::round(y_rev);

		if (this->y < 0.f)
			this->y = (this->y + 360.f * y_rev);

		else
			this->y = (this->y - 360.f * y_rev);
	}

	auto z_rev = this->z / 360.f;
	if (this->z > 180.f || this->z < -180.f) {
		z_rev = std::abs(z_rev);
		z_rev = std::round(z_rev);

		if (this->z < 0.f)
			this->z = (this->z + 360.f * z_rev);

		else
			this->z = (this->z - 360.f * z_rev);
	}

	return *this;
}

Vector3 Vector3::normalized()
{
	auto tmp = *this;
	tmp.normalize_self();
	return tmp;
}

Vector3& Vector3::abs_self()
{
	this->x = std::abs(x);
	this->y = std::abs(y);
	this->z = std::abs(z);
	return *this;
}

Vector3 Vector3::abs()
{
	auto tmp = *this;
	tmp.abs_self();
	return tmp;
}

float Vector3::distance_to(const Vector3& other)
{
	return (*this - other).length();
}

std::string Vector3::to_string() {
	return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
}
