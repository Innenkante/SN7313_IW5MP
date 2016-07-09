//TODO CLEAN SOURCE FROM UNESCESSARY STUFF AND USE DIFFRENT FILES MAYBE?
#include "stdafx.h"

bool AimbotEnabled = false;
bool NoSpreadEnabled = false;
bool NoRecoilEnabled = false;
bool FullBrightEnabled = false;
bool LaserEnabled = false;
bool RadarEnabled = false;
bool MenuEnabled = true;
bool GrabGuidEnabled = false;
bool ESPEnabled = false;
bool ESPMenu_Enabled = false;
//ESPConfigMenu Values
bool ESP_DrawBox = true;
bool ESP_DrawBones = true;
bool ESP_DrawName = true;
bool ESP_DrawClientNum = true;
bool ESP_DrawRank = true;
bool ESP_DrawDistance = true;
bool ESP_DrawScore = true;
bool ESP_DrawGUID = true;
bool ESP_Draw3DBox = false;
bool ESP_DrawWeapon = false;

vec4_t ColorWhite = { 1.0f,1.0f,1.0f,1.0f };
vec4_t ColorGreen = { 0.0f,  1.0f,  0.0f,  1.0f };
vec4_t ColorRed = { 1.0f,  0.0f,  0.0f,  1.0f };
vec4_t ColorBlue = { 0.0f,  0.0f,  1.0f,  1.0f };
vec4_t ColorBlack = { 0.0f,0.0f,0.0f,1.0f };
vec4_t ColorOrange = { 255.f, 165.f, 0.0f,1.0f };

void* Font_Menu_GUID;

//

DrawEngineText_t DrawEngineText_ = (DrawEngineText_t)DRAWENGINETEXTOFF;
DrawRotatedPic_t DrawRotatedPic_ = (DrawRotatedPic_t)0x0042F420;
RegisterFont_t RegisterFont_ = (RegisterFont_t)REGISTERFONTOFF;
DrawEngineRadar_t DrawEngineRadar_ = (DrawEngineRadar_t)DRAWENGINERADAROFF;
OverlayPackage_t OverlayPackage_ = (OverlayPackage_t)0x0054BD70;
OverlayEnemy_t OverlayEnemey_ = (OverlayEnemy_t)0x004CD2B0;
OverlayFriendly_t OverlayFriendly_ = (OverlayFriendly_t)0x004370C0;
//OverlayHeli_t OverlayHeli_ = (OverlayHeli_t)0x004C3FB0;
//OverlayLocal_t OverlayLocal_ = (OverlayLocal_t)0x004FD740;
//OverlayPlane_t OverlayPlane_ = (OverlayPlane_t)0x0052A6C0;
//OverlayTurret_t OverlayTurret_ = (OverlayTurret_t)0x00561BF0;

RegisterShader_t RegisterShader_ = (RegisterShader_t)REGISTERSHADEROFF;
GetScreenMatrix_t GetScreenMatrix_ = (GetScreenMatrix_t)SCREENMATRIXOFF;
World2Screen_t WorldToScreen_ = (World2Screen_t)0x004e5fc0;
RegisterTag_t RegisterTag_ = (RegisterTag_t)0x4922E0;

CG_Draw2D Draw2D = NULL;

bool GetState(bool state)
{
	if (state)
		state = false;
	else
		state = true;
	return state;
}


void MessageBoxMethod(const LPCSTR sometext)
{
	MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
}

void SendCommandToConsole(char* CMD)
{
	DWORD dwCall = SENDCOMMANDTOCONSOLEOFF;
	__asm
	{
		push CMD;
		push 0;
		push 0;
		call dwCall;
		add esp, 0xC;
	}

}

void* RegisterFont(char* font)
{
	return RegisterFont_(font);
}

int* RegisterShader(char* shader)
{
	return RegisterShader_(shader);
}

void DrawTextMW3(float x, float y, void* pFont, float* color, const char *Text, ...) 
{
	char buf[1024] = "";
	va_list va_alist;
	va_start(va_alist, Text);
	vsnprintf_s(buf, sizeof(buf), Text, va_alist);
	va_end(va_alist);

	DrawEngineText_((char*)Text, 0x7FFFFFFF, pFont, x, y, 1.0f, 1.0f, 0.0f, color, 0);
}

void NoRecoil(bool state)
{
	BYTE* nr = (BYTE*)NORECOILOFF;
	if (state)
		*nr = 235;
	else
		*nr = 116;
}


void NoSpread(bool state)
{
	float* nospr = (float*)NOSPREADOFF;
	if (state)
		*nospr = 0;
	else
		*nospr = 0.6499999762f;
}

void ChangeName()
{
	srand(static_cast<int>(time(NULL)));
	BYTE* checkname = (BYTE*)PLAYERNAMECHECKBYTEOFF;
	*checkname = 0xC3;
	int random = rand() % 100;
	char* name = (char*)PLAYERNAMEOFF;
	char newname[16];
	sprintf(newname, "Bot %d", random);
	for (int i = 0; i < 16; i++)
		name[i] = newname[i];
}


void RandomCreds()
{
	srand(static_cast<int>(time(NULL)));
	*(ULONG*)0x05CCB272 = (ULONG)(0x11000010000000 + rand() + (rand() * 10) + (rand() * 100));//steam
	*(ULONG*)0x00464A58 = (ULONG)(0x11000010000000 + rand() + (rand() * 10) + (rand() * 100));//xna
	*(ULONG*)0x05A7B1D8 = (ULONG)(0x11000010000000 + rand() + (rand() * 10) + (rand() * 100));//xuid

	ChangeName();
}

void FixBlindPerks()
{
	ClientInfo_T* Clients[18];
	for (int i = 0; i < 18; i++)
	{
		Clients[i] = (ClientInfo_T*)(CLIENTOFF + ((int)CLIENTSIZE * i));
		if (Clients[i] != Clients[*(int*)0x8FF250])
		{
			if (Clients[i]->Perk & 0x20 || Clients[i]->Perk & 0x40)
				Clients[i]->Perk = 0x0;
		}
	}
}

void FullBright(bool state)
{
	int* fullbright = (int*)FULLBRIGHTOFF;
	if (state)
		*fullbright = 4;
	else
		*fullbright = 9;

}


void UnlockClasses()
{
	int *force1 = (int*)FORCECLASS1;
	int *force2 = (int*)FORCECLASS2;
	int *force3 = (int*)FORCECLASS3;
	int *force4 = (int*)FORCECLASS4;
	int *force5 = (int*)FORCECLASS5;
	int *force6 = (int*)FORCECLASS6;
	int *force7 = (int*)FORCECLASS7;
	int *force8 = (int*)FORCECLASS8;
	int *force9 = (int*)FORCECLASS9;

	*force1 = 7;
	*force2 = 0;
	*force3 = 0;
	*force4 = 0;
	*force5 = 0;
	*force6 = 0;
	*force7 = 0;
	*force8 = 0;
	*force9 = 0;
}

void Laser(bool state)
{
	BYTE* laser = (BYTE*)LASEROFF;

	if (state)
		*laser = 0;
	else
		*laser = 37;
}


char* GetBoolInChar(bool b)
{
	char buf[40] = "";
	if (b)
		sprintf_s(buf, "^2On");
	if (!b)
		sprintf_s(buf, "^1Off");
	return buf;
}

char* GetPlayerName()
{
	const char* Name = (const char*)PLAYERNAMEOFF;
	char buf[32] = "";
	sprintf(buf, Name);
	return buf;
}

char* GetPlayerID()
{
	int* ID = (int*)XUIDOFF;
	char buf[16];
	sprintf(buf, "%ld", *ID);
	return buf;
}

char* GetServerName()
{
	const char* ServerName = (const char*)SERVERNAMEOFF;
	char buf[64] = "";
	sprintf(buf, ServerName);
	return buf;
}

char* GetServerIP()
{
	const char* ServerIP = (const char*)SERVERIPOFF;
	char buf[32] = "";
	sprintf(buf, ServerIP);
	return buf;
}


//void ChopperBoxes()
//{
//	DWORD dwCall = 0x5AA470;
//	if (WhEnabled)
//	{
//		FixBlindPerks();
//		__asm
//		{
//			push 0x0;
//			call[dwCall];
//			add esp, 0x4;
//		}
//	}
//	else
//		return;
//}

void DrawRadar()
{
	if (RadarEnabled)
	{
		RefDef_T* RefDef = (RefDef_T*)REFDEFOFF;
		RadarHud radarhud;
		int RadarW = 225;
		int RadarH = RadarW;

		int RadarX = RefDef->Width - RadarW;
		int RadarY = 13;

		radarhud.x = ScaleRadarX(RadarX);
		radarhud.y = ScaleRadarY(RadarY);
		radarhud.w = ScaleRadarX(RadarW);
		radarhud.h = ScaleRadarY(RadarH);

		DrawEngineRadar_(0, 0, 0, &radarhud, RegisterShader("black"), ColorWhite);
		OverlayPackage_(0, 0, 0, &radarhud, *RegisterShader("black"), ColorWhite);

		//OverlayLocal_(0, 0, 0, &radarhud, ColorBlue);
		OverlayEnemey_(0, 0, 0, &radarhud, ColorRed);
		OverlayFriendly_(0, 0, 0, &radarhud, ColorGreen);

	}
	else
		return;
}


void ForceJugg()
{
	CG_T* cg = (CG_T*)CGOFF;
	int* MagicNum = (int*)MATCHIDOFF;
	char buffer[1024];
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (CLIENTSIZE * cg->ClientNumber));
	if (LocalClient->Team == 1)
		sprintf(buffer, "cmd mr %d 9 allies", *MagicNum);
	if(LocalClient->Team == 2)
		sprintf(buffer, "cmd mr %d 9 axis", *MagicNum);
	SendCommandToConsole(buffer);

}

void ChangeTeam()
{
	CG_T* cg = (CG_T*)CGOFF;
	int* MagicNum = (int*)MATCHIDOFF;
	char buffer[1024];
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + CLIENTSIZE * cg->ClientNumber);
	if(LocalClient->Team == 1)
		sprintf(buffer, "cmd mr %d 2 allies", *MagicNum);
	if(LocalClient->Team == 2)
		sprintf(buffer, "cmd mr %d 2 axis", *MagicNum); //This shit aint working right till now :S and thx to Kenny for the menuresponses they are bae
	SendCommandToConsole(buffer);
}

void CallCrashVote()
{
	char buffer[1024];
	sprintf(buffer,"callvote map_rotate"); //Sometime is crashes the server when g_allowvote 1
	SendCommandToConsole(buffer);
}

int GetGUID(int index)
{
	return *(int*)(*(DWORD *)0x132C3A0 + 0x60 + (0x40 * index));
}

void GrabGUID()
{
	if (!GrabGuidEnabled)
		return;
	int Count_Entrys = 0;
	for (int i = 0; i < 18; i++)
	{
		int GUID = GetGUID(i);
		ClientInfo_T* Client = (ClientInfo_T*)(CLIENTOFF + (i* (int)CLIENTSIZE));
		if (!Client->Valid)
			continue;
		Count_Entrys++;
		char tmp_buf[2048];
		sprintf_s(tmp_buf, "^3 %s ^3[^1 %d ^3] ^4| ^2 %d", Client->Name,i, GUID);
		//ESPMenu_Enabled = false;
		DrawTextMW3(10, 190 + Count_Entrys * 24, RegisterFont(FONT_BIG_DEV), ColorWhite, tmp_buf);
	}
}

void DrawCrossHair()
{
	RefDef_T* refdef = (RefDef_T*)REFDEFOFF;

	if (!refdef->Width || !refdef->Height)
		return;
	DrawTextMW3(refdef->Width / 2 - 7 , refdef->Height / 2 + 10, RegisterFont(FONT_BIG_DEV), ColorGreen, "+"); //Maybe -6 and + 11? but atm it looks good doe

}

void DrawLine(float x1, float y1, float x2,float y2, vec4_t Color, int *Shader,int size) //Thx to Kenny I lub you <3
{
	ScreenMatrix *Screen = GetScreenMatrix_();
	float x, y, angle, l1, l2, h1;
	h1 = y2 - y1;
	l1 = x2 - x1;
	l2 = sqrt(l1 * l1 + h1 * h1);
	x = x1 + ((l1 - l2) / 2);
	y = y1 + (h1 / 2);
	angle = (float)atan(h1 / l1) * (180 / 3.14159265358979323846);
	DrawRotatedPic_(Screen, x, y, l2, size, angle, Color, Shader);
}

void DrawLineFor3D(Vector3D Position, float x1, float y1, float z1, float x2, float y2, float z2, vec4_t color,int *Shader)
{
	float pointPos1[3] = { Position.x + x1, Position.y + y1, Position.z + z1 };
	float pointPos2[3] = { Position.x + x2, Position.y + y2, Position.z + z2 };
	float xy1[2], xy2[2];
	ScreenMatrix* Calc = GetScreenMatrix_();
	if (WorldToScreen_(0, Calc, pointPos1, xy1) && WorldToScreen_(0, Calc, pointPos2, xy2))
		DrawLine(xy1[0], xy1[1], xy2[0], xy2[1], color, Shader,2);
}

void DrawRectangle(int x, int y, int x2,int y2,int x3,int y3,int x4,int y4, vec4_t Color,int *Shader, int Size)//Tested and works like a charm
{
	DrawLine(x, y, x2, y2, Color, Shader, Size);
	DrawLine(x2, y2, x3, y3, Color, Shader, Size);
	DrawLine(x3, y3, x4, y4, Color, Shader, Size);
	DrawLine(x4, y4, x, y, Color, Shader, Size);
}

void Draw3DBox(Vector3D pos, float w, float h, vec4_t color, int* shader)
{
	//bottom
	DrawLineFor3D(pos, -w, -w, 0, w, -w, 0, color, shader);
	DrawLineFor3D(pos, -w, -w, 0, -w, w, 0, color, shader);
	DrawLineFor3D(pos, w, w, 0, w, -w, 0, color, shader);
	DrawLineFor3D(pos, w, w, 0, -w, w, 0, color, shader);

	//middle
	DrawLineFor3D(pos, -w, -w, 0, -w, -w, h, color, shader);
	DrawLineFor3D(pos, -w, w, 0, -w, w, h, color, shader);
	DrawLineFor3D(pos, w, -w, 0, w, -w, h, color, shader);
	DrawLineFor3D(pos, w, w, 0, w, w, h, color, shader);

	//top
	DrawLineFor3D(pos, -w, -w, h, w, -w, h, color, shader);
	DrawLineFor3D(pos, -w, -w, h, -w, w, h, color, shader);
	DrawLineFor3D(pos, w, w, h, w, -w, h, color, shader);
	DrawLineFor3D(pos, w, w, h, -w, w, h, color, shader);
}

float GetDistance(Vector3D source, Vector3D destination)
{
	return sqrt(pow(destination.x - source.x, 2) + pow(destination.y - source.y, 2) + pow(destination.z - source.z, 2));
}

float GetMagnitude(Vector3D vec)
{
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

bool GetTagPos(Entity_T* ent, char* tagname, float* out)
{
	WORD wTag = RegisterTag_(tagname);
	if (!wTag)
		return false;

	DWORD dwCall = 0x571790;

	__asm
	{
		MOV ESI, ent;
		MOVZX EDI, wTag;
		PUSH out;
		CALL dwCall;
		ADD ESP, 0x4
	}

	return true;
}

Vector3D ParseVec(float PointInFloat[3])
{
	Vector3D vec(0, 0, 0);
	vec.x = PointInFloat[0];
	vec.y = PointInFloat[1];
	vec.z = PointInFloat[2];
	return vec;
}

Vector3D SubtractVec(Vector3D src, Vector3D dest)
{
	Vector3D vec(0, 0, 0);
	vec.x = dest.x - src.x;
	vec.y = dest.y - src.y;
	vec.z = dest.z - src.z;

	return vec;
}

Vector3D NormalizeVec(Vector3D vec)
{
	float Length = GetMagnitude(vec);

	vec.x /= Length;
	vec.y /= Length;
	vec.z /= Length;

	return vec;
}

Vector3D MultiplyVec(Vector3D src, Vector3D dest)
{
	src.x *= dest.x;
	src.y *= dest.y;
	src.z *= dest.z;

	return src;
}

Vector2D CalcAngles(Vector3D src, Vector3D dest,Vector3D ViewAxis[3])
{
	Vector3D aimAt = SubtractVec(src, dest);
	Vector3D normalized = NormalizeVec(aimAt);

	aimAt = MultiplyVec(ViewAxis[1], normalized);
	float yaw = (float)(asin(aimAt.x + aimAt.y + aimAt.z) * (180 / PI));
	aimAt = MultiplyVec(ViewAxis[2], normalized);
	float pitch = (float)(-asin(aimAt.x + aimAt.y + aimAt.z) * (180 / PI));

	Vector2D angles(0, 0);
	angles.x = yaw;
	angles.y = pitch;
	
	return angles;
}
void DoAimbot()
{
	if (!AimbotEnabled)
		return;

	Entity_T* Entity[18];
	ClientInfo_T* Client[18];
	RefDef_T* RefDef = (RefDef_T*)REFDEFOFF;
	CG_T* cg = (CG_T*)(CGOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	int ClosestPlayerClientNumber = -1;
	float ClosestDistance = 999999999999.f;
	float TagPos_head[3];

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * ENTITYSIZE));
		Client[i] = (ClientInfo_T*)(CLIENTOFF + (i * CLIENTSIZE));

		if (i == cg->ClientNumber)
			continue;
	}

	for (int i = 0; i < 18; i++)
	{

		if (Client[i]->Valid && Entity[i]->Valid && Client[i]->Team != LocalClient->Team && Entity[i]->IsAlive)
		{
			if (!GetTagPos(Entity[i], "j_head", TagPos_head))
				continue;

			float CurrentDistance = GetDistance(RefDef->Origin, ParseVec(TagPos_head));
			if (CurrentDistance < ClosestDistance)
			{
				ClosestPlayerClientNumber = Entity[i]->ClientNumber;
				ClosestDistance = CurrentDistance;
			}
		}
	}

	if (ClosestPlayerClientNumber == -1)
		return;

	float fix[3];
	GetTagPos(Entity[ClosestPlayerClientNumber], "j_head", fix);
	Vector2D Angles = CalcAngles(RefDef->Origin, ParseVec(fix), RefDef->ViewAxis);

	float* ViewX = (float*)0x0106389C;
	float* ViewY = (float*)0x01063898;

	*ViewX += Angles.x;
	*ViewY += Angles.y;
}

//TODO Aimbone

DWORD GetWeaponPointer(int iWeaponID) {
	return *(DWORD*)(0x8ddb50 + ((iWeaponID & 0xFF) * 0x4));
}

char* GetWeaponName(int iWeaponID) {
	static char szWeapon[32];
	szWeapon[0] = 0;
	DWORD dwWeaponName = *(DWORD*)(GetWeaponPointer(iWeaponID) + 0x8);
	strcpy_s(szWeapon, (char*)dwWeaponName);
	if (strstr(szWeapon, "WEAPON_")) {
		char* szFixString = strrchr(szWeapon, '_') + 1;
		strcpy_s(szWeapon, szFixString);
	}
	return szWeapon;
}

void ESP_DrawWeapons()
{
	Entity_T* Entity[1024];
	std::ofstream WeaponESPDump;
	WeaponESPDump.open("WeaponESPdump.txt");
	for (int i = 0; i < 1024; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * ENTITYSIZE));
		if (Entity[i]->Type == Entity_Type::Item)
		{
			char* ItemName = GetWeaponName(Entity[i]->WeaponID);
			float ScreenPos[2];
			float WorldPos[] = { Entity[i]->Origin.x,Entity[i]->Origin.y,Entity[i]->Origin.z };
			WorldToScreen_(0x0, GetScreenMatrix_(), WorldPos, ScreenPos);
			if (ItemName != NULL)
				DrawTextMW3(ScreenPos[0], ScreenPos[1], RegisterFont(FONT_SMALL_DEV), ColorWhite, ItemName);
			WeaponESPDump << ItemName << ":" << ItemName << std::endl;
		}
	}
}

void ESP_Draw3DBoxes()
{
	Entity_T* Entity[18];
	ClientInfo_T* Client[18];
	CG_T* cg = (CG_T*)(CGOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	CGS_T * CGS = (CGS_T*)CGSOFF;

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * ENTITYSIZE));
		Client[i] = (ClientInfo_T*)(CLIENTOFF + (i * CLIENTSIZE));

		if (Entity[i]->ClientNumber != cg->ClientNumber && Entity[i]->IsAlive && Entity[i]->Type == Entity_Type::Player && Entity[i]->Valid && Client[i]->Valid)
		{
			if (CGS->GameType == "dm")
			{
				Draw3DBox(Entity[i]->Origin, 40, 80, ColorRed, RegisterShader("white"));
				return;
			}
			if (Client[i]->Team == LocalClient->Team)
				Draw3DBox(Entity[i]->Origin, 40, 80, ColorGreen, RegisterShader("white"));
			else
				Draw3DBox(Entity[i]->Origin, 40, 80, ColorRed, RegisterShader("white"));
		}
	}
}

void ESP_ColorBones()
{
	Entity_T* Entity[18];
	ClientInfo_T* Client[18];
	CG_T* cg = (CG_T*)(CGOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	CGS_T * CGS = (CGS_T*)CGSOFF;

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * ENTITYSIZE));
		Client[i] = (ClientInfo_T*)(CLIENTOFF + (i * CLIENTSIZE));

		if (Entity[i]->ClientNumber != cg->ClientNumber && Entity[i]->IsAlive && Entity[i]->Type == Entity_Type::Player && Entity[i]->Valid && Client[i]->Valid)
		{
			//Legs
			float TagPos_hip_r[3];
			float TagPos_hip_l[3];
			float TagPos_knee_r[3];
			float TagPos_knee_l[3];
			float TagPos_ankle_r[3];
			float TagPos_ankle_l[3];

			float Screen_hip_r[2];
			float Screen_hip_l[2];
			float Screen_knee_r[2];
			float Screen_knee_l[2];
			float Screen_ankle_r[2];
			float Screen_ankle_l[2];


			GetTagPos(Entity[i], "j_hip_ri", TagPos_hip_r);
			GetTagPos(Entity[i], "j_hip_le", TagPos_hip_l);

			GetTagPos(Entity[i], "j_knee_ri", TagPos_knee_r);
			GetTagPos(Entity[i], "j_knee_le", TagPos_knee_l);

			GetTagPos(Entity[i], "j_ankle_ri", TagPos_ankle_r);
			GetTagPos(Entity[i], "j_ankle_le", TagPos_ankle_l);

			//Arms
			float TagPos_shoulder_r[3];
			float TagPos_shoulder_l[3];
			float TagPos_elbow_r[3];
			float TagPos_elbow_l[3];
			float TagPos_wrist_r[3];
			float TagPos_wrist_l[3];

			float Screen_shoulder_r[2];
			float Screen_shoulder_l[2];
			float Screen_elbow_r[2];
			float Screen_elbow_l[2];
			float Screen_wrist_r[2];
			float Screen_wrist_l[2];

			GetTagPos(Entity[i], "j_shoulder_ri", TagPos_shoulder_r); 
			GetTagPos(Entity[i], "j_shoulder_le", TagPos_shoulder_l);

			GetTagPos(Entity[i], "j_elbow_ri", TagPos_elbow_r);
			GetTagPos(Entity[i], "j_elbow_le", TagPos_elbow_l);

			GetTagPos(Entity[i], "j_wrist_ri", TagPos_wrist_r);
			GetTagPos(Entity[i], "j_wrist_le", TagPos_wrist_l);

			//Backbone "j_mainroot"   , "j_spineupper"   , "j_spinelower" , "j_spine4"

			float TagPos_spineupper[3];
			float TagPos_mainroot[3];
			float TagPos_spinelower[3];

			float Screen_spineupper[2];
			float Screen_mainroot[2];
			float Screen_spinelower[2];

			GetTagPos(Entity[i], "j_spineupper", TagPos_spineupper);
			GetTagPos(Entity[i], "j_mainroot", TagPos_mainroot);
			GetTagPos(Entity[i], "j_spinelower", TagPos_spinelower); 

			//Head "j_helmet"     , "j_head"            , "j_neck"
			float TagPos_helmet[3];
			float TagPos_head[3];
			float TagPos_neck[3];

			float Screen_helmet[2];
			float Screen_head[2];
			float Screen_neck[2];

			GetTagPos(Entity[i], "j_helmet", TagPos_helmet);
			GetTagPos(Entity[i], "j_head", TagPos_head);
			GetTagPos(Entity[i], "j_neck", TagPos_neck);

			//Pelvis
			float TagPos_Pelvis[3];
			float Screen_Pelvis[2];

			GetTagPos(Entity[i], "pelvis", TagPos_Pelvis);


			ScreenMatrix* Matrix = GetScreenMatrix_();


			//Legs
			WorldToScreen_(0x0, Matrix, TagPos_hip_r, Screen_hip_r);
			WorldToScreen_(0x0, Matrix, TagPos_hip_l, Screen_hip_l);

			WorldToScreen_(0x0, Matrix, TagPos_knee_r, Screen_knee_r);
			WorldToScreen_(0x0, Matrix, TagPos_knee_l, Screen_knee_l);

			WorldToScreen_(0x0, Matrix, TagPos_ankle_r, Screen_ankle_r);
			WorldToScreen_(0x0, Matrix, TagPos_ankle_l, Screen_ankle_l);

			//Arms
			WorldToScreen_(0x0, Matrix, TagPos_shoulder_r, Screen_shoulder_r);
			WorldToScreen_(0x0, Matrix, TagPos_shoulder_l, Screen_shoulder_l);

			WorldToScreen_(0x0, Matrix, TagPos_elbow_r, Screen_elbow_r);
			WorldToScreen_(0x0, Matrix, TagPos_elbow_l, Screen_elbow_l);

			WorldToScreen_(0x0, Matrix, TagPos_wrist_r, Screen_wrist_r);
			WorldToScreen_(0x0, Matrix, TagPos_wrist_l, Screen_wrist_l);

			//Backbone
			WorldToScreen_(0x0, Matrix, TagPos_spineupper, Screen_spineupper);
			WorldToScreen_(0x0, Matrix, TagPos_mainroot, Screen_mainroot);
			WorldToScreen_(0x0, Matrix, TagPos_spinelower, Screen_spinelower);

			//Head
			WorldToScreen_(0x0, Matrix, TagPos_helmet, Screen_helmet);
			WorldToScreen_(0x0, Matrix, TagPos_head, Screen_head);
			WorldToScreen_(0x0, Matrix, TagPos_neck, Screen_neck);

			//Pelvis
			WorldToScreen_(0x0, Matrix, TagPos_Pelvis, Screen_Pelvis);

			if (CGS->GameType == "dm ")
			{
				DrawLine(Screen_hip_r[0], Screen_hip_r[1], Screen_knee_r[0], Screen_knee_r[1], ColorRed, RegisterShader("white"), 2);
				DrawLine(Screen_knee_r[0], Screen_knee_r[1], Screen_ankle_r[0], Screen_ankle_r[1], ColorRed, RegisterShader("white"), 2);

				//Left Leg
				DrawLine(Screen_hip_l[0], Screen_hip_l[1], Screen_knee_l[0], Screen_knee_l[1], ColorRed, RegisterShader("white"), 2);
				DrawLine(Screen_knee_l[0], Screen_knee_l[1], Screen_ankle_l[0], Screen_ankle_l[1], ColorRed, RegisterShader("white"), 2);

				//Right Arm
				DrawLine(Screen_shoulder_r[0], Screen_shoulder_r[1], Screen_elbow_r[0], Screen_elbow_r[1], ColorRed, RegisterShader("white"), 2);
				DrawLine(Screen_elbow_r[0], Screen_elbow_r[1], Screen_wrist_r[0], Screen_wrist_r[1], ColorRed, RegisterShader("white"), 2);

				//Left Arm
				DrawLine(Screen_shoulder_l[0], Screen_shoulder_l[1], Screen_elbow_l[0], Screen_elbow_l[1], ColorRed, RegisterShader("white"), 2);
				DrawLine(Screen_elbow_l[0], Screen_elbow_l[1], Screen_wrist_l[0], Screen_wrist_l[1], ColorRed, RegisterShader("white"), 2);

				//Back bone
				DrawLine(Screen_spineupper[0], Screen_spineupper[1], Screen_mainroot[0], Screen_mainroot[1], ColorRed, RegisterShader("white"), 2);
				DrawLine(Screen_mainroot[0], Screen_mainroot[1], Screen_spinelower[0], Screen_spinelower[1], ColorRed, RegisterShader("white"), 2);

				//Head
				DrawLine(Screen_helmet[0], Screen_helmet[1], Screen_head[0], Screen_head[1], ColorRed, RegisterShader("white"), 2);
				DrawLine(Screen_head[0], Screen_head[1], Screen_neck[0], Screen_neck[1], ColorRed, RegisterShader("white"), 2);

				//Neck -> Backbone connection
				DrawLine(Screen_neck[0], Screen_neck[1], Screen_spineupper[0], Screen_spineupper[1], ColorRed, RegisterShader("white"), 2);
				DrawLine(Screen_Pelvis[0], Screen_Pelvis[1], Screen_Pelvis[0] + 1, Screen_Pelvis[1] + 1, ColorOrange, RegisterShader("white"), 5);
				return;
			}
			if (Client[i]->Team == LocalClient->Team)
			{
				//Right leg
				DrawLine(Screen_hip_r[0], Screen_hip_r[1], Screen_knee_r[0], Screen_knee_r[1], ColorGreen, RegisterShader("white"), 2);
				DrawLine(Screen_knee_r[0], Screen_knee_r[1], Screen_ankle_r[0], Screen_ankle_r[1], ColorGreen, RegisterShader("white"), 2);

				//Left Leg
				DrawLine(Screen_hip_l[0], Screen_hip_l[1], Screen_knee_l[0], Screen_knee_l[1], ColorGreen, RegisterShader("white"), 2);
				DrawLine(Screen_knee_l[0], Screen_knee_l[1], Screen_ankle_l[0], Screen_ankle_l[1], ColorGreen, RegisterShader("white"), 2);

				//Right Arm
				DrawLine(Screen_shoulder_r[0], Screen_shoulder_r[1], Screen_elbow_r[0], Screen_elbow_r[1], ColorGreen, RegisterShader("white"), 2);
				DrawLine(Screen_elbow_r[0], Screen_elbow_r[1], Screen_wrist_r[0], Screen_wrist_r[1], ColorGreen, RegisterShader("white"), 2);

				//Left Arm
				DrawLine(Screen_shoulder_l[0], Screen_shoulder_l[1], Screen_elbow_l[0], Screen_elbow_l[1], ColorGreen, RegisterShader("white"), 2);
				DrawLine(Screen_elbow_l[0], Screen_elbow_l[1], Screen_wrist_l[0], Screen_wrist_l[1], ColorGreen, RegisterShader("white"), 2);

				//Back bone
				DrawLine(Screen_spineupper[0], Screen_spineupper[1], Screen_mainroot[0], Screen_mainroot[1], ColorGreen, RegisterShader("white"), 2);
				DrawLine(Screen_mainroot[0], Screen_mainroot[1], Screen_spinelower[0], Screen_spinelower[1], ColorGreen, RegisterShader("white"), 2);

				//Head
				DrawLine(Screen_helmet[0], Screen_helmet[1], Screen_head[0], Screen_head[1], ColorGreen, RegisterShader("white"), 2);
				DrawLine(Screen_head[0], Screen_head[1], Screen_neck[0], Screen_neck[1], ColorGreen, RegisterShader("white"), 2);

				//Neck -> Backbone connection
				DrawLine(Screen_neck[0], Screen_neck[1], Screen_spineupper[0], Screen_spineupper[1], ColorGreen, RegisterShader("white"), 2);
			}
			else
			{
				//Right leg
				DrawLine(Screen_hip_r[0], Screen_hip_r[1], Screen_knee_r[0], Screen_knee_r[1], ColorRed, RegisterShader("white"), 2);
				DrawLine(Screen_knee_r[0], Screen_knee_r[1], Screen_ankle_r[0], Screen_ankle_r[1], ColorRed, RegisterShader("white"), 2);

				//Left Leg
				DrawLine(Screen_hip_l[0], Screen_hip_l[1], Screen_knee_l[0], Screen_knee_l[1], ColorRed, RegisterShader("white"), 2);
				DrawLine(Screen_knee_l[0], Screen_knee_l[1], Screen_ankle_l[0], Screen_ankle_l[1], ColorRed, RegisterShader("white"), 2);

				//Right Arm
				DrawLine(Screen_shoulder_r[0], Screen_shoulder_r[1], Screen_elbow_r[0], Screen_elbow_r[1], ColorRed, RegisterShader("white"), 2);
				DrawLine(Screen_elbow_r[0], Screen_elbow_r[1], Screen_wrist_r[0], Screen_wrist_r[1], ColorRed, RegisterShader("white"), 2);

				//Left Arm
				DrawLine(Screen_shoulder_l[0], Screen_shoulder_l[1], Screen_elbow_l[0], Screen_elbow_l[1], ColorRed, RegisterShader("white"), 2);
				DrawLine(Screen_elbow_l[0], Screen_elbow_l[1], Screen_wrist_l[0], Screen_wrist_l[1], ColorRed, RegisterShader("white"), 2);

				//Back bone
				DrawLine(Screen_spineupper[0], Screen_spineupper[1], Screen_mainroot[0], Screen_mainroot[1], ColorRed, RegisterShader("white"), 2);
				DrawLine(Screen_mainroot[0], Screen_mainroot[1], Screen_spinelower[0], Screen_spinelower[1], ColorRed, RegisterShader("white"), 2);

				//Head
				DrawLine(Screen_helmet[0], Screen_helmet[1], Screen_head[0], Screen_head[1], ColorRed, RegisterShader("white"), 2);
				DrawLine(Screen_head[0], Screen_head[1], Screen_neck[0], Screen_neck[1], ColorRed, RegisterShader("white"), 2);

				//Neck -> Backbone connection
				DrawLine(Screen_neck[0], Screen_neck[1], Screen_spineupper[0], Screen_spineupper[1], ColorRed, RegisterShader("white"), 2);
			}

			DrawLine(Screen_Pelvis[0], Screen_Pelvis[1], Screen_Pelvis[0] + 1 , Screen_Pelvis[1] + 1, ColorOrange, RegisterShader("white"), 5);
		}
	}

}

void ESP_Draw2DBoxes()
{
	Entity_T* Entity[18];
	ClientInfo_T* Clients[18];
	RefDef_T* refdef = (RefDef_T*)(REFDEFOFF);
	CG_T* cg = (CG_T*)(CGOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	float* ViewX = (float*)0x0106389C;
	float* ViewY = (float*)0x01063898;
	CGS_T * CGS = (CGS_T*)CGSOFF;

	for (int i = 0;i < 18;i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * (int)ENTITYSIZE));
		Clients[i] = (ClientInfo_T*)(CLIENTOFF + (i * (int)CLIENTSIZE));
		if (Entity[i]->ClientNumber != cg->ClientNumber && Entity[i]->IsAlive &&  Entity[i]->Type == Entity_Type::Player && Entity[i]->Valid && Clients[i]->Valid)
		{
			float TagPos_head[3];
			float Screen_head[2];

			float TagPos_shoulder_r[3];
			float TagPos_shoulder_l[3];

			float Screen_shoulder_r[2];
			float Screen_shoulder_l[2];


			float TagPos_ankle_r[3];
			float TagPos_ankle_l[3];

			float Screen_ankle_r[2];
			float Screen_ankle_l[2];

			GetTagPos(Entity[i], "j_head", TagPos_head);

			GetTagPos(Entity[i], "j_shoulder_ri", TagPos_shoulder_r);
			GetTagPos(Entity[i], "j_shoulder_le", TagPos_shoulder_l);

			GetTagPos(Entity[i], "j_ankle_ri", TagPos_ankle_r);
			GetTagPos(Entity[i], "j_ankle_le", TagPos_ankle_l);

			ScreenMatrix* Matrix = GetScreenMatrix_();

			WorldToScreen_(0x0, Matrix, TagPos_shoulder_r, Screen_shoulder_r);
			WorldToScreen_(0x0, Matrix, TagPos_shoulder_l, Screen_shoulder_l);
			WorldToScreen_(0x0, Matrix, TagPos_ankle_r, Screen_ankle_r);
			WorldToScreen_(0x0, Matrix, TagPos_ankle_l, Screen_ankle_l);

			WorldToScreen_(0x0, Matrix, TagPos_head, Screen_head);

			float distance = GetDistance(refdef->Origin, ParseVec(TagPos_head));

			char buf_Name[1024];
			char buf_ClientNum[1024];
			char buf_Distance[1024];
			char buf_Rank[1024];
			char buf_Score[1024];
			char buf_GUID[1024];

			sprintf(buf_Name, "^3 %s ", Clients[i]->Name);
			sprintf(buf_ClientNum, "^3Slot: ^1 %d", Entity[i]->ClientNumber);
			sprintf(buf_Distance, "Dist: %d", (int)distance);
			sprintf(buf_Rank, "Rank: %d", Clients[i]->Rank + 1); //Rank starts at -1 so rank 80 = 79 internal
			sprintf(buf_Score, "Score: %d", Clients[i]->Score);
			sprintf(buf_GUID, "^3GUID: ^1 %d", GetGUID(i));


			if (ESP_DrawName)
				DrawTextMW3(Screen_head[0] - 40, Screen_head[1] - 5, RegisterFont(FONT_SMALL_DEV), ColorWhite, buf_Name); //Name 
			if (ESP_DrawClientNum)
				DrawTextMW3(Screen_head[0] + 32, Screen_head[1] + 8, RegisterFont(FONT_SMALL_DEV), ColorWhite, buf_ClientNum); //ClientNumber
			if (ESP_DrawDistance)
				DrawTextMW3(Screen_head[0] + 32, Screen_head[1] + 18, RegisterFont(FONT_SMALL_DEV), ColorBlue, buf_Distance); //Distance
			if (ESP_DrawRank)
				DrawTextMW3(Screen_head[0] + 32, Screen_head[1] + 28, RegisterFont(FONT_SMALL_DEV), ColorBlue, buf_Rank); //Rank
			if (ESP_DrawScore)
				DrawTextMW3(Screen_head[0] + 32, Screen_head[1] + 38, RegisterFont(FONT_SMALL_DEV), ColorBlue, buf_Score); //Score
			if (ESP_DrawGUID)
				DrawTextMW3(Screen_head[0] + 32, Screen_head[1] + 48, RegisterFont(FONT_SMALL_DEV), ColorWhite, buf_GUID); //GUID

			if (ESP_DrawBox)
			{
				if (sizeof(CGS->GameType) == 2)
				{
					DrawRectangle(Screen_shoulder_r[0], Screen_shoulder_r[1], Screen_shoulder_l[0], Screen_shoulder_l[1], Screen_ankle_r[0], Screen_ankle_r[1], Screen_ankle_l[0], Screen_ankle_l[1],ColorRed,RegisterShader("white"),2);
					return;
				}
				if (Clients[i]->Team == LocalClient->Team)
					DrawRectangle(Screen_shoulder_r[0], Screen_shoulder_r[1], Screen_shoulder_l[0], Screen_shoulder_l[1], Screen_ankle_r[0], Screen_ankle_r[1], Screen_ankle_l[0], Screen_ankle_l[1], ColorGreen, RegisterShader("white"), 2);
				else
					DrawRectangle(Screen_shoulder_r[0], Screen_shoulder_r[1], Screen_shoulder_l[0], Screen_shoulder_l[1], Screen_ankle_r[0], Screen_ankle_r[1], Screen_ankle_l[0], Screen_ankle_l[1], ColorRed, RegisterShader("white"), 2); 
			}
		}
	}
}

//void DUMPCGS()
//{
//	std::ofstream CGSDump;
//	CGSDump.open("CGS_DUMP.txt");
//	CGS_T* CGS = (CGS_T*)CGSOFF;
//
//	CGSDump << CGS->HostName << ":" << CGS->MapName << ":" << CGS->GameType << std::endl;
//}

void ESP_Main()
{
	if (ESPEnabled)
	{
		if(ESP_Draw2DBoxes)
			ESP_Draw2DBoxes();
		if (ESP_DrawBones)
			ESP_ColorBones();
		if (ESP_Draw3DBox)
			ESP_Draw3DBoxes();
		if(ESP_DrawWeapon)
			ESP_DrawWeapons();
	}

}

void ESP_Menu()
{
	char buf_esp[4096];
	sprintf(buf_esp, "^2ESP ^3Menu \n");
	strncat(buf_esp, "^5Boxes[1]: ", sizeof(buf_esp));
	strncat(buf_esp, GetBoolInChar(ESP_DrawBox), sizeof(buf_esp));
	strncat(buf_esp, "\n^5", sizeof(buf_esp));
	strncat(buf_esp, "^5Bones[2]: ", sizeof(buf_esp));
	strncat(buf_esp, GetBoolInChar(ESP_DrawBones), sizeof(buf_esp));
	strncat(buf_esp, "\n^5", sizeof(buf_esp));
	strncat(buf_esp, "^5Name[3]: ", sizeof(buf_esp));
	strncat(buf_esp, GetBoolInChar(ESP_DrawName), sizeof(buf_esp));
	strncat(buf_esp, "\n^5", sizeof(buf_esp));
	strncat(buf_esp, "^5ClientNum[4]: ", sizeof(buf_esp));
	strncat(buf_esp, GetBoolInChar(ESP_DrawClientNum), sizeof(buf_esp));
	strncat(buf_esp, "\n^5", sizeof(buf_esp));
	strncat(buf_esp, "^5Distance[5]: ", sizeof(buf_esp));
	strncat(buf_esp, GetBoolInChar(ESP_DrawDistance), sizeof(buf_esp));
	strncat(buf_esp, "\n^5", sizeof(buf_esp));
	strncat(buf_esp, "^5Rank[6]: ", sizeof(buf_esp));
	strncat(buf_esp, GetBoolInChar(ESP_DrawRank), sizeof(buf_esp));
	strncat(buf_esp, "\n^5", sizeof(buf_esp));
	strncat(buf_esp, "^5Score[7]: ", sizeof(buf_esp));
	strncat(buf_esp, GetBoolInChar(ESP_DrawScore), sizeof(buf_esp));
	strncat(buf_esp, "\n^5", sizeof(buf_esp));
	strncat(buf_esp, "^5GUID[8]: ", sizeof(buf_esp));
	strncat(buf_esp, GetBoolInChar(ESP_DrawGUID), sizeof(buf_esp));
	strncat(buf_esp, "\n^5", sizeof(buf_esp));
	strncat(buf_esp, "^53DBoxes[9]: ", sizeof(buf_esp));
	strncat(buf_esp, GetBoolInChar(ESP_Draw3DBox), sizeof(buf_esp));
	strncat(buf_esp, "\n^5", sizeof(buf_esp));
	strncat(buf_esp, "^5Weapons[Multiply]: ", sizeof(buf_esp));
	strncat(buf_esp, GetBoolInChar(ESP_DrawWeapon), sizeof(buf_esp));
	strncat(buf_esp, "\n^5", sizeof(buf_esp));
		if(ESPMenu_Enabled)
			DrawTextMW3(10, 190, RegisterFont(FONT_BIG_DEV),ColorWhite,buf_esp);

}

void Menu()
{

	char buf[4096];
	sprintf(buf, "^2Boboo's ^3MultiHack ^4beta!\n");
	strncat(buf, "^5ESP[F3]: ", sizeof(buf));
	strncat(buf, GetBoolInChar(ESPEnabled), sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "No Recoil[F4]: ", sizeof(buf));
	strncat(buf, GetBoolInChar(NoRecoilEnabled), sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "No Spread[F5]: ", sizeof(buf));
	strncat(buf, GetBoolInChar(NoSpreadEnabled), sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "Fullbright[F6]: ", sizeof(buf));
	strncat(buf, GetBoolInChar(FullBrightEnabled), sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "Second radar[F7]: ", sizeof(buf));
	strncat(buf, GetBoolInChar(RadarEnabled), sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "Laser[F8]: ", sizeof(buf));
	strncat(buf, GetBoolInChar(LaserEnabled), sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "Unlock Classes[F9]", sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "Change Credentials[F10]", sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "ChangeTeam[F11]", sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "Force Juggernaut[F12]", sizeof(buf));
	strncat(buf, "\n^5",sizeof(buf));
	strncat(buf, "Crash Vote[END]", sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "Show player IDs[INSERT]", sizeof(buf));
	strncat(buf, "\n^3", sizeof(buf));
	//Other stuff:
	strncat(buf, "Name: ^:", sizeof(buf));
	strncat(buf, GetPlayerName(), sizeof(buf));
	strncat(buf, "\n^3", sizeof(buf));
	strncat(buf, "ID: ^:", sizeof(buf));
	strncat(buf, GetPlayerID(), sizeof(buf));
	strncat(buf, "\n^3", sizeof(buf));
	strncat(buf, "Servername: ^;", sizeof(buf));
	strncat(buf, GetServerName(), sizeof(buf));
	strncat(buf, "\n^3", sizeof(buf));
	strncat(buf, "Server IP: ^;", sizeof(buf));
	strncat(buf, GetServerIP(), sizeof(buf));
	strncat(buf, "\n", sizeof(buf));

	//Fucking ugly but hey it works
	
	if (MenuEnabled)
	{
		DrawTextMW3(550, 30, RegisterFont(FONT_BIG_DEV), ColorWhite, buf);
	}
}

//HOOK!////////////////////////////////////////////////////////////////////////////////////
//void MakeJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen)
//{
//	DWORD dwOldProtect, dwBkup, dwRelAddr;
//
//	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
//	dwRelAddr = (DWORD)(dwJumpTo - (DWORD)pAddress) - 5;
//	*pAddress = 0xE9;
//
//	*((DWORD *)(pAddress + 0x1)) = dwRelAddr;
//	for (DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
//	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
//
//	return;
//}

void *DetourFunction(BYTE *src, const BYTE *dst, const int len)
{
	BYTE *jmp = (BYTE*)malloc(len + 5);
	DWORD dwBack;

	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwBack);
	memcpy(jmp, src, len);
	jmp += len;
	jmp[0] = 0xE9;
	*(DWORD*)(jmp + 1) = (DWORD)(src + len - jmp) - 5;
	src[0] = 0xE9;
	*(DWORD*)(src + 1) = (DWORD)(dst - src) - 5;
	for (int i = 5; i<len; i++)
		src[i] = 0x90;
	VirtualProtect(src, len, dwBack, &dwBack);
	return (jmp - len);
}

DWORD dwCall = HOOKCALL;
DWORD dwReturn = HOOKRETURN; 

__declspec(naked) void ShowMenu()
{
	__asm
	{
		CALL[dwCall]
		PUSHAD;
		PUSHFD;
	}
	Menu(); //The ingame menu
	GrabGUID(); //The little DrawText menu u see oin the right
	DrawCrossHair(); //Crosshair dot
	ESP_Menu(); //The ESP Menu
	DrawRadar(); //The second radar lmao
	ESP_Main();
	__asm
	{
		POPFD;
		POPAD;
		JMP[dwReturn]

	}
}/////////////////////////////////////////////////////////////////////////////////////////////////////////

void Func()
{
	DrawTextMW3(200, 200, RegisterFont(FONT_BIG), ColorBlue, "CG_Draw2D hook");
}

void PlaceJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen) {
	DWORD dwOldProtect, dwBkup, dwRelAddr;

	// Basic VirtualProtect... y'all should know this
	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	// Calculate the "distance" we're gonna have to jump - the size of the JMP instruction
	dwRelAddr = (DWORD)(dwJumpTo - (DWORD)pAddress) - 5;

	// Write the JMP opcode @ our jump position...
	*pAddress = 0xE9;

	// Write the offset to where we're gonna jump
	*((DWORD *)(pAddress + 0x1)) = dwRelAddr;

	// Overwrite the rest of the bytes with NOPs
	for (DWORD x = 0x5; x < dwLen; x++)
		*(pAddress + x) = 0x90;

	// Restore the default permissions
	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);

}
DWORD dwJMPback = 0x430436;
__declspec(naked) void hkDraw2D()
{
	__asm PUSHAD
	__asm PUSHFD

	DoAimbot();

	__asm POPFD
	__asm POPAD


	__asm PUSH ESI
	__asm MOV ESI, [ESP + 8]
	__asm PUSH ESI

	__asm JMP[dwJMPback]
}

DWORD WINAPI _MainMethod(LPVOID lpParam)
{
	//My keyboardhook
	while (true)
	{
		if (GetAsyncKeyState(VK_F2)) //ChatSpam
		{
			MenuEnabled = GetState(MenuEnabled);
			Sleep((100));
		}
		if (GetAsyncKeyState(VK_F3)) //ChopperBox
		{
			ESPEnabled = GetState(ESPEnabled);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F4)) //NoRecoil
		{
			NoRecoilEnabled = GetState(NoRecoilEnabled);
			NoRecoil(NoRecoilEnabled);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F5)) //NoSpread
		{
			NoSpreadEnabled = GetState(NoSpreadEnabled);
			NoSpread(NoSpreadEnabled);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F6)) ////FullBright
		{
			FullBrightEnabled = GetState(FullBrightEnabled);
			FullBright(FullBrightEnabled); 
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F7)) //Second Radar
		{
			RadarEnabled = GetState(RadarEnabled);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F8)) //Laser
		{
			LaserEnabled = GetState(LaserEnabled);
			Laser(LaserEnabled);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F9)) //Unlock locked classes
		{
			UnlockClasses();
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F10)) //Randomize credentials
		{
			RandomCreds();
			Sleep(100);
		} 
		if (GetAsyncKeyState(VK_F11)) //Change Team
		{
			ChangeTeam();
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F12)) //Forces a juggernaut
		{
			ForceJugg();
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_END)) //Calls a vote which may crash the server
		{
			CallCrashVote();
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_INSERT)) //Opens the stealing menu
		{
			GrabGuidEnabled = GetState(GrabGuidEnabled);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_NUMPAD0)) //Opens up the ESP Menu
		{
			ESPMenu_Enabled = GetState(ESPMenu_Enabled);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			AimbotEnabled = GetState(AimbotEnabled); 
			Sleep(100);
		}
		if (ESPMenu_Enabled)
		{
			if (GetAsyncKeyState(VK_NUMPAD1)) //Boxes
			{
				ESP_DrawBox = GetState(ESP_DrawBox);
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_NUMPAD2)) //Bones
			{
				ESP_DrawBones = GetState(ESP_DrawBones);
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_NUMPAD3)) //Name
			{
				ESP_DrawName = GetState(ESP_DrawName);
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_NUMPAD4)) //Clientnum
			{
				ESP_DrawClientNum = GetState(ESP_DrawClientNum);
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_NUMPAD5)) //Distance
			{
				ESP_DrawDistance = GetState(ESP_DrawDistance);
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_NUMPAD6)) //Rank
			{
				ESP_DrawRank = GetState(ESP_DrawRank);
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_NUMPAD7)) //Score
			{
				ESP_DrawScore = GetState(ESP_DrawScore);
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_NUMPAD8)) //GUID
			{
				ESP_DrawGUID = GetState(ESP_DrawGUID);
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_NUMPAD9)) //3D Boxes
			{
				ESP_Draw3DBox = GetState(ESP_Draw3DBox);
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_MULTIPLY))
			{
				ESP_DrawWeapon = GetState(ESP_DrawWeapon);
				Sleep(100);
			}
		}
		//DoAimbot(); 
		Sleep(10);
		char* ServerName = GetServerName();
		if (sizeof(ServerName) == 0)
		{
			NoSpreadEnabled = false;
			NoRecoilEnabled = false;
			ESPEnabled = false;
			FullBrightEnabled = false;
			LaserEnabled = false;
			RadarEnabled = false;
			MenuEnabled = true;
			GrabGuidEnabled = false;
			ESPMenu_Enabled = false;
			ESPEnabled = false;
		}
	}

	return 1;
}


BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD Reason, LPVOID Reserved)
{
	if (Reason == DLL_PROCESS_ATTACH) {
		MessageBoxMethod("Attached to Process");
		DetourFunction((PBYTE)0x0064427B, (PBYTE)ShowMenu, 5); //Thanks to google/pastebin/hkDavy for showing me the hook
		PlaceJMP((PBYTE)0x430430, (DWORD)hkDraw2D, 6); //MPGH ftw
		CreateThread(NULL, 0, &_MainMethod, NULL, 0, NULL); //Creating the Thread
	}

	return TRUE;
}
