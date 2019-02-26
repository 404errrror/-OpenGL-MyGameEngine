#pragma once
class Vector3
{
public:
	float x, y, z;
public:
	Vector3(float x = 0, float y = 0, float z = 0);
	~Vector3();

	Vector3 operator+ (Vector3&);
	Vector3 operator- (Vector3&);
	Vector3 operator* (float&);
};

