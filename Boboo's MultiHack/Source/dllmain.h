#pragma once
//StandartHeaders
#include <windows.h>
#include <windef.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <cstdlib>
#include <stdarg.h>
#include <Psapi.h>
#include <iostream>
#include <ctime>
#include<sstream>
#include <io.h>
#include <fcntl.h>
#include <string>
//


//MyHeaders
#include "Offsets.h"
#include "Structs.h"
#include "Typedefs.h"
#include "Drawing.h"
#define ScaleRadarX(x)(x * (640.0f / RefDef->Width ) )
#define ScaleRadarY(y)(y * (480.0f / RefDef->Height) )

//Methods
void MessageBoxMethod(const LPCSTR sometext);
void SendCommandToConsole(char* Cmd);
void FixBlindPerks();
void NoRecoil(bool state);
void RandomCreds();
void NoSpread(bool state);
void UnlockClasses();
void Laser(bool state);
bool GetState(bool state);
void _RegisterFont();
void DrawTextMW3(float x, float y, void* pFont, float* color, const char *Text, ...);




