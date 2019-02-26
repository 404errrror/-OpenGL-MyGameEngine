#include "Vector3.h"



Vector3::Vector3(float x, float y, float z)
{
}


Vector3::~Vector3()
{
}


Vector3 Vector3::operator+ (Vector3& value)
{
	return Vector3(x + value.x, y + value.y, z + value.z);
}


Vector3 Vector3::operator- (Vector3& value)
{
	return Vector3(x - value.x, y - value.y, z - value.z);
}


Vector3 Vector3::operator* (float& value)
{
	return Vector3(x * value, y * value, z * value);
}