#include "stdafx.h"

Utils_ Utils;
bool Engine_::GetTagPos(Entity_T * ent, char * tagname, float * out)
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

void Engine_::SendCommandToConsole(char * CMD)
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

weapon_t * Engine_::GetWeapon(int WeaponID)
{
	return*(weapon_t**)(0x008DDB50 + 0x04 * WeaponID);
}

Trace_t Engine_::TraceToTarget(float * TargetVector)
{
	CG_T* CG = (CG_T*)CGOFF;
	RefDef_T* RefDef = (RefDef_T*)REFDEFOFF;
	Trace_t tr;
	vec3_t NullVec = { 0,0,0 };
	vec3_t start = { RefDef->Origin.x,RefDef->Origin.y,RefDef->Origin.z };
	Trace_(&tr, start, TargetVector, CG->ClientNumber, 0x803003);
	return tr;
}

bool Shooting = false;
void Engine_::Shoot()
{
	
	byte* Scoped = (byte*)0x10603B0;
	Input_t* Input = (Input_t*)0x00B39EE0;
	*Scoped = 1;
	if (Shooting)
		Input->Weapon.Pressed = 1;
	Shooting = Utils.ChangeState(Shooting);
}

bool Engine_::IsVisible(int ClientNumber)
{
	return IsEntityVisible_(0, (int*)(0x00A08630 + (0x1F8 * (ClientNumber & 2047))));
}

int Engine_::GetXUID(int ClientNumber)
{
	return *(int*)(*(DWORD *)0x132C3A0 + 0x60 + (0x40 * ClientNumber));
}
