#include "stdafx.h"

Vector2D Utils_::ParsVec(float ScreenInFloat[2])
{
	Vector2D vec(0, 0);
	vec.x = ScreenInFloat[0];
	vec.y = ScreenInFloat[1];
	return vec;
}

Vector3D Utils_::ParseVec(float PointInFloat[3])
{
	Vector3D vec(0, 0, 0);
	vec.x = PointInFloat[0];
	vec.y = PointInFloat[1];
	vec.z = PointInFloat[2];
	return vec;
}

bool Utils_::ChangeState(bool state)
{
	if (state)
		state = false;
	else
		state = true;
	return state;
}
