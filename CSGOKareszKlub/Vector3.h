#pragma once
#include <string>

class Vector3 {

public:
	float x, y, z;

	Vector3(float x = 0.f, float y = 0.f, float z = 0.f);
	Vector3(float arr[]);
	Vector3(const Vector3& other);

	float* data();
	float& operator[](size_t i);

	bool equals(const Vector3& other) const;
	bool operator==(const Vector3& other);
	bool operator!=(const Vector3& other);

	Vector3& operator=(const Vector3& other);
	Vector3& operator+=(const Vector3& other);
	Vector3& operator+=(const float& scalar);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator-=(const float& scalar);
	Vector3& operator*=(const Vector3& other);
	Vector3& operator*=(const float& scalar);
	Vector3& operator/=(const Vector3& other);
	Vector3& operator/=(const float& scalar);

	Vector3 operator+(const Vector3& other);
	Vector3 operator+(const float& other);
	Vector3 operator-(const Vector3& other);
	Vector3 operator-(const float& other);
	Vector3 operator*(const Vector3& other);
	Vector3 operator*(const float& other);
	Vector3 operator/(const Vector3& other);
	Vector3 operator/(const float& other);

	float length();
	float length_2d_sqr();
	float length_2d();
	float distance_to(const Vector3& other);
	float dot_product(const Vector3& other) const;
	Vector3 cross_product(const Vector3& other) const;
	Vector3& normalize_self();
	Vector3 normalized();
	Vector3& abs_self();
	Vector3 abs();
	std::string to_string();
};
