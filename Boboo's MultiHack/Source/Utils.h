#pragma once
static class Utils
{
public:
	static Vector2D ParsVec(float ScreenInFloat[2]);
	static Vector3D ParseVec(float PointInFloat[3]);
	static bool ChangeState(bool state);
	static char * GetStateAsWord(bool state);
	static char* IntToChar(int num);
	static char* FloatToChar(float num);
private:

};

