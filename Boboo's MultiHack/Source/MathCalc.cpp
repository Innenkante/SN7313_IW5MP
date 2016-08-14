#include "stdafx.h"

float Math_::GetDistance(Vector3D source, Vector3D destination)
{
	return sqrt(pow(destination.x - source.x, 2) + pow(destination.y - source.y, 2) + pow(destination.z - source.z, 2));
}

float Math_::GetDistance(Vector2D source, Vector2D destination)
{
	return sqrt(pow(destination.x - source.x, 2) + pow(destination.y - source.y, 2));
}

float Math_::GetMagnitude(Vector3D vec)
{
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

Vector3D Math_::SubtractVec(Vector3D src, Vector3D dest)
{
	Vector3D vec(0, 0, 0);
	vec.x = dest.x - src.x;
	vec.y = dest.y - src.y;
	vec.z = dest.z - src.z;

	return vec;
}

Vector3D Math_::NormalizeVec(Vector3D vec)
{
	float Length = GetMagnitude(vec);

	vec.x /= Length;
	vec.y /= Length;
	vec.z /= Length;

	return vec;
}

Vector3D Math_::MultiplyVec(Vector3D src, Vector3D dest)
{
	src.x *= dest.x;
	src.y *= dest.y;
	src.z *= dest.z;

	return src;
}

Vector2D Math_::CalcAngles(Vector3D src, Vector3D dest, Vector3D ViewAxis[3])
{
	Vector3D aimAt = SubtractVec(src, dest);
	Vector3D normalized = NormalizeVec(aimAt);

	aimAt = MultiplyVec(ViewAxis[1], normalized);
	float yaw = (float)(asin(aimAt.x + aimAt.y + aimAt.z) * (180 / PI));
	aimAt = MultiplyVec(ViewAxis[2], normalized);
	float pitch = (float)(-asin(aimAt.x + aimAt.y + aimAt.z) * (180 / PI));

	Vector2D angles(0, 0);
	angles.x = yaw;
	angles.y = pitch;

	return angles;
}
