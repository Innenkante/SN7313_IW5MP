#pragma once

class Draw_
{
public:
	void DrawTextMW3(float x, float y, void* pFont, float* color, const char *Text, ...);
	void DrawTextWithShader(char* Text, char* Shader, int x, int y, void* Font, vec4_t Color);
	void DrawCirlceOnScreen(Vector2D Position, float radius, vec4_t Color);
	void DrawCirlceSplashDamage(Vector3D PositionNade, float radius, vec4_t Color);
	void DrawShaderByName(float x, float y, float w, float h, vec4_t Color, char* Shader);
	void DrawShaderByInt(float x, float y, float w, float h, vec4_t Color, int* Shader);
	void DrawLine(float x1, float y1, float x2, float y2, vec4_t Color, int *Shader, int size);
	void DrawLineFor3D(Vector3D Position, float x1, float y1, float z1, float x2, float y2, float z2, vec4_t color, int *Shader);
	void DrawRectangle(int x, int y, int x2, int y2, int x3, int y3, int x4, int y4, vec4_t Color, int *Shader, int Size);
	void DrawRectangleFilled(float x, float y, float w, float h, float fThick, vec4_t ColorBackground);
	void Draw3DBox(Vector3D pos, float w, float h, vec4_t Color, int* Shader);
private:
	int AddIconToText(int startLen, int* shader, char* text, float iconW, float iconH, BOOL flipIconHorizontal);
	char* GetIconText(int* shader, float iconW, float iconH, BOOL flipIconHorizontal);
	char* AddTextAndShader(char* Text, char* Shader);
};





