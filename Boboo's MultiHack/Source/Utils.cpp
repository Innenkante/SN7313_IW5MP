#include "stdafx.h"

Vector2D Utils::ParsVec(float ScreenInFloat[2])
{
	Vector2D vec(0, 0);
	vec.x = ScreenInFloat[0];
	vec.y = ScreenInFloat[1];
	return vec;
}

Vector3D Utils::ParseVec(float PointInFloat[3])
{
	Vector3D vec(0, 0, 0);
	vec.x = PointInFloat[0];
	vec.y = PointInFloat[1];
	vec.z = PointInFloat[2];
	return vec;
}

bool Utils::ChangeState(bool state)
{
	if (state)
		state = false;
	else
		state = true;
	return state;
}

char* Utils::GetStateAsWord(bool state)
{
	if (state)
		return "On";
	else
		return "Off";
}

char * Utils::IntToChar(int num)
{
	char buf[1024];
	sprintf_s(buf, "%d", num);
	return buf;
}

char * Utils::FloatToChar(float num)
{
	char buf[1024];
	sprintf_s(buf, "%f", num);
	return buf;
}
