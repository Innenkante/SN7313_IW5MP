#pragma once

static class Draw
{
public:
	static void DrawTextMW3(int x, int y, void * pFont, float * color, const char * Text, ...);
	static void DrawTextWithShader(char* Text, char* Shader, int x, int y, void* Font, vec4_t Color);
	static void DrawCirlceOnScreen(Vector2D Position, float radius, vec4_t Color);
	static void DrawCirlceSplashDamage(Vector3D PositionNade, float radius, vec4_t Color);
	static void DrawShaderByName(float x, float y, float w, float h, vec4_t Color, char* Shader);
	static void DrawShaderByInt(float x, float y, float w, float h, vec4_t Color, int* Shader);
	static void DrawLine(float x1, float y1, float x2, float y2, vec4_t Color, int *Shader, int size);
	static void DrawLineFor3D(Vector3D Position, float x1, float y1, float z1, float x2, float y2, float z2, vec4_t color, int *Shader);
	static void DrawRectangle(int x, int y, int x2, int y2, int x3, int y3, int x4, int y4, vec4_t Color, int *Shader, int Size);
	static void DrawRectangleFilled(int x, int y, float w, float h, vec4_t ColorBackground);
	static void Draw3DBox(Vector3D pos, float w, float h, vec4_t Color, int* Shader);
private:
	static int AddIconToText(int startLen, int* shader, char* text, float iconW, float iconH, BOOL flipIconHorizontal);
	static char* GetIconText(int* shader, float iconW, float iconH, BOOL flipIconHorizontal);
	static char* AddTextAndShader(char* Text, char* Shader);
};





