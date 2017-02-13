#include "stdafx.h"

bool Utils::ChangeState(bool state)
{
	return state = !state;
}

char* Utils::GetStateAsWord(bool state)
{
	if (state)
		return "On";
	else
		return "Off";
}

char * Utils::GetAimField()
{
	sprintf_s(Aimbot::DisplayFieldOfAim, "%d", Aimbot::FieldOfAim);
	return Aimbot::DisplayFieldOfAim;
}

char * Utils::GetMinTraceValue()
{
	sprintf_s(Aimbot::DisplayMinTraceValue, "%f", Aimbot::MinTraceValue);
	return Aimbot::DisplayMinTraceValue;
}
