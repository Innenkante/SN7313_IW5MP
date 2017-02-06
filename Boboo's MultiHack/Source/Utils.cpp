#include "stdafx.h"

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
