#pragma once
typedef float vec_t;
typedef vec_t vec4_t[4];
typedef int(*tDrawEngineText)(char* Text, int NumOfChars, void* Font, float X, float Y, float scaleX, float scaleY, float unk1, float* Color, int unk2);
typedef void* (*tRegisterFont)(char* szName);
typedef void(__cdecl* tDrawEngineRadar)(int unk1, int disableRotation, int unk2, CRadarHud* radar, int* shader, vec4_t color);
typedef int* (*R_RegisterShaderPtr) (char* ShaderName);
typedef CScreenMatrix* (__cdecl* tGetScreenMatrix)();

