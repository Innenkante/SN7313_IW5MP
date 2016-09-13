#include "stdafx.h"

#include "LinkingFix.h"

void Draw::DrawTextMW3(int x, int y, void * pFont, float * color, const char * Text, ...)
{
	char buf[1024] = "";
	va_list va_alist;
	va_start(va_alist, Text);
	vsnprintf_s(buf, sizeof(buf), Text, va_alist);
	va_end(va_alist);

	Engine.DrawEngineText_((char*)Text, 0x7FFFFFFF, pFont, x, y, 1.0f, 1.0f, 0.0f, color, 0);
}

void Draw::DrawTextWithShader(char * Text, char * Shader, int x, int y, void * Font, vec4_t Color)
{
	char Buf[1024];
	sprintf_s(Buf, "%s", AddTextAndShader(Text, Shader));
	DrawTextMW3(x, y, Font, Color, Buf);
}

void Draw::DrawCirlceOnScreen(Vector2D Position, float radius, vec4_t Color)
{
	for (int i = 1; i <= 360; i += 10)
	{
		int x = i + 10;
		Vector2D PositionOld(Position.x + (radius * cos(i * PI / 180)), Position.y + (radius * sin(i * PI / 180)));
		Vector2D PositionNew(Position.x + (radius * cos(x * PI / 180)), Position.y + (radius * sin(x * PI / 180)));

		DrawLine(PositionOld.x, PositionOld.y, PositionNew.x, PositionNew.y, Color, Engine.RegisterShader_("white"), 1);
	}
}

void Draw::DrawCirlceSplashDamage(Vector3D PositionNade, float radius, vec4_t Color)
{
	for (int i = 1; i <= 360; i += 10)
	{
		int x = i + 10;
		float ScreenPositionOfRadiusOld[2];
		float ScreenPositionOfRadiusNew[2];

		float PositionNadeRadiusOld[] = { (float)PositionNade.x + (radius * cos(i * PI / 180)),(float)PositionNade.y + (radius * sin(i * PI / 180)), PositionNade.z };
		float PositionNadeRadiusNew[] = { (float)PositionNade.x + (radius * cos(x * PI / 180)),(float)PositionNade.y + (radius * sin(x * PI / 180)), PositionNade.z };
		Engine.WorldToScreen_(0x0, Engine.GetScreenMatrix_(), PositionNadeRadiusOld, ScreenPositionOfRadiusOld);
		Engine.WorldToScreen_(0x0, Engine.GetScreenMatrix_(), PositionNadeRadiusNew, ScreenPositionOfRadiusNew);

		DrawLine(ScreenPositionOfRadiusOld[0], ScreenPositionOfRadiusOld[1], ScreenPositionOfRadiusNew[0], ScreenPositionOfRadiusNew[1], Color, Engine.RegisterShader_("white"), 5);
	}
}

void Draw::DrawShaderByName(float x, float y, float w, float h, vec4_t Color, char * Shader)
{
	Engine.DrawRotatedPic_(Engine.GetScreenMatrix_(), x, y, w, h, 0, ColorWhite, Engine.RegisterShader_(Shader));
}

void Draw::DrawShaderByInt(float x, float y, float w, float h, vec4_t Color, int * Shader)
{
	Engine.DrawRotatedPic_(Engine.GetScreenMatrix_(), x, y, w, h, 0, ColorWhite, Shader);
}

void Draw::DrawLine(float x1, float y1, float x2, float y2, vec4_t Color, int * Shader, int size)
{
	float x, y, angle, l1, l2, h1;
	h1 = y2 - y1;
	l1 = x2 - x1;
	l2 = sqrt(l1 * l1 + h1 * h1);
	x = x1 + ((l1 - l2) / 2);
	y = y1 + (h1 / 2);
	angle = (float)atan(h1 / l1) * (180 / 3.14159265358979323846);
	Engine.DrawRotatedPic_(Engine.GetScreenMatrix_(), x, y, l2, size, angle, Color, Shader);
}

void Draw::DrawLineFor3D(Vector3D Position, float x1, float y1, float z1, float x2, float y2, float z2, vec4_t color, int * Shader)
{
	float pointPos1[3] = { Position.x + x1, Position.y + y1, Position.z + z1 };
	float pointPos2[3] = { Position.x + x2, Position.y + y2, Position.z + z2 };
	float xy1[2], xy2[2];
	ScreenMatrix* Calc = Engine.GetScreenMatrix_();
	if (Engine.WorldToScreen_(0, Calc, pointPos1, xy1) && Engine.WorldToScreen_(0, Calc, pointPos2, xy2))
		DrawLine(xy1[0], xy1[1], xy2[0], xy2[1], color, Shader, 2);
}

void Draw::DrawRectangle(int x, int y, int x2, int y2, int x3, int y3, int x4, int y4, vec4_t Color, int * Shader, int Size)
{
	DrawLine(x, y, x2, y2, Color, Shader, Size);
	DrawLine(x2, y2, x3, y3, Color, Shader, Size);
	DrawLine(x3, y3, x4, y4, Color, Shader, Size);
	DrawLine(x4, y4, x, y, Color, Shader, Size);
}

void Draw::DrawRectangleFilled(int x, int y, float w, float h, float fThick, vec4_t ColorBackground)
{
	Engine.DrawRotatedPic_(Engine.GetScreenMatrix_(), x, y, w, h, 0, ColorBackground, Engine.RegisterShader_("white"));
}

void Draw::Draw3DBox(Vector3D pos, float w, float h, vec4_t Color, int * Shader)
{
	//bottom
	DrawLineFor3D(pos, -w, -w, 0, w, -w, 0, Color, Shader);
	DrawLineFor3D(pos, -w, -w, 0, -w, w, 0, Color, Shader);
	DrawLineFor3D(pos, w, w, 0, w, -w, 0, Color, Shader);
	DrawLineFor3D(pos, w, w, 0, -w, w, 0, Color, Shader);

	//middle
	DrawLineFor3D(pos, -w, -w, 0, -w, -w, h, Color, Shader);
	DrawLineFor3D(pos, -w, w, 0, -w, w, h, Color, Shader);
	DrawLineFor3D(pos, w, -w, 0, w, -w, h, Color, Shader);
	DrawLineFor3D(pos, w, w, 0, w, w, h, Color, Shader);

	//top
	DrawLineFor3D(pos, -w, -w, h, w, -w, h, Color, Shader);
	DrawLineFor3D(pos, -w, -w, h, -w, w, h, Color, Shader);
	DrawLineFor3D(pos, w, w, h, w, -w, h, Color, Shader);
	DrawLineFor3D(pos, w, w, h, -w, w, h, Color, Shader);
}

int Draw::AddIconToText(int startLen, int * shader, char * text, float iconW, float iconH, BOOL flipIconHorizontal)
{
	DWORD dwFunc = 0x5AE5D0;
	__asm
	{
		push flipIconHorizontal
		push iconH
		push iconW
		mov edi, text
		mov ebx, shader
		mov eax, startLen
		call dwFunc
	}
}

char * Draw::GetIconText(int * shader, float iconW, float iconH, BOOL flipIconHorizontal)
{
	static char Buf[512];
	memset(Buf, 0, 512);
	int end = AddIconToText(0, shader, Buf, iconW, iconH, flipIconHorizontal);
	Buf[end] = 0;
	return Buf;
}

char * Draw::AddTextAndShader(char * Text, char * Shader)
{
	int* icon = Engine.RegisterShader_(Shader);
	char Buf[1024];
	sprintf_s(Buf, "%s %s", Text, GetIconText(icon, 3.f, 1.8f, TRUE));
	return Buf;
}
