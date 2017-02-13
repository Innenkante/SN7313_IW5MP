#pragma once
#include "stdafx.h"
static class Aimbot
{
public:
	static bool ClosestAimbotEnabled;
	static bool AimAssistEnabled;
	static bool BestTraceAimbotEnabled;
	static int FieldOfAim;
	static int AimboneID;
	static float MinTraceValue;
	static char* Bones_Collection[17];
	static void Wrapper();
	static char DisplayFieldOfAim[64];
	static char DisplayMinTraceValue[64];
private:
	static void ClosestAimbot(char * Bone);
	static void InScreenRangeAimbot(char* Bone, int FieldOfAim);
	static void BestTraceAimbot(float MinTraceVal);
};


