#pragma once
class Menu_
{
public:
	void DrawMenuWrapper();
private:
	void DrawTabHeader(char* TabName, int LeftUPX, int LeftUPY, int RightDownX, int RightDownY, vec4_t ColorTab, int* Shader, int Size, void* Font, vec4_t ColorText, vec4_t ColorBackground);
	void DrawMenu(int BasePosMenuX);
};


