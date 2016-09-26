#include "stdafx.h"

float Math::GetDistance(Vector3D source, Vector3D destination)
{
	return sqrt(pow(destination.x - source.x, 2) + pow(destination.y - source.y, 2) + pow(destination.z - source.z, 2));
}

float Math::GetDistance(Vector2D source, Vector2D destination)
{
	return sqrt(pow(destination.x - source.x, 2) + pow(destination.y - source.y, 2));
}

float Math::GetMagnitude(Vector3D vec)
{
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

Vector3D Math::SubtractVec(Vector3D src, Vector3D dest)
{
	Vector3D vec(0, 0, 0);
	vec.x = dest.x - src.x;
	vec.y = dest.y - src.y;
	vec.z = dest.z - src.z;

	return vec;
}


Vector2D Math::SubtractVec(Vector2D src, Vector2D dest)
{
	return Vector2D(dest.x - src.x, dest.y - src.y);
}



Vector3D Math::NormalizeVec(Vector3D vec)
{
	float Length = GetMagnitude(vec);

	vec.x /= Length;
	vec.y /= Length;
	vec.z /= Length;

	return vec;
}

Vector3D Math::MultiplyVec(Vector3D src, Vector3D dest)
{
	src.x *= dest.x;
	src.y *= dest.y;
	src.z *= dest.z;

	return src;
}

Vector2D Math::CalcAngles(Vector3D src, Vector3D dest, Vector3D ViewAxis[3])
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

void Math::AngleVectors(Vector3D angles, Vector3D * forward, Vector3D * right, Vector3D * up)
{
	float angle;
	float sr, sp, sy, cr, cp, cy;

	angle = angles.x * (PI * 2 / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles.y * (PI * 2 / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles.z * (PI * 2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	if (forward)
	{
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up)
	{
		up->x = (cr*sp*cy + -sr*-sy);
		up->y = (cr*sp*sy + -sr*cy);
		up->z = cr*cp;
	}

}

Vector3D Math::VectorToAngles(Vector3D vec)
{
	float	forward;
	float	yaw, pitch;

	if (vec.y == 0 && vec.z == 0)
	{
		yaw = 0;
		if (vec.z > 0)
			pitch = 90;
		else
			pitch = 270;
	}
	else
	{
		if (vec.x)
			yaw = (atan2(vec.y, vec.x) * (180.0f / PI));
		else if (vec.y > 0)
			yaw = 90.0f;
		else
			yaw = 270.0f;

		if (yaw < 0.0f)
			yaw += 360.0f;

		forward = sqrt((vec.x * vec.x) + (vec.y  * vec.y));
		pitch = (atan2(vec.z, forward) * (180.0f / PI));

		if (pitch < 0.0f)
			pitch += 360;
	}

	return Vector3D(-pitch, yaw,0);
}
