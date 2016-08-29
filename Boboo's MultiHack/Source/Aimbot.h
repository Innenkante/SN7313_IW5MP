#pragma once
#include "stdafx.h"
class Aimbot_
{
public:
	bool ClosestAimbotEnabled;
	bool InScreenRangeAimbotEnabled;
	bool BestTraceAimbotEnabled;
	int FieldOfAim;
	char* AimboneName;
	void ClosestAimbot(bool state, char* Bone);
	void InScreenRangeAimbot(bool state, char* Bone,int FieldOfAim);
	void BestTraceAimbot(bool state);
	void Wrapper();
private:

};


