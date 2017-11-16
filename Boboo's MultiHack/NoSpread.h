#pragma once
#include "LinkingFix.h"
namespace no_spread
{
	void(__cdecl* BG_GetSpreadForWeapon)(CG_T* cg, int weapon, float*BaseSpread, float*MaxSpread) = (void(__cdecl*)(CG_T*, int, float*, float*))0x004E1130;
	int(__cdecl* CG_GetLocalWeapon)(CG_T*) = (int(__cdecl*)(CG_T*))0x49DFF0;
	void GetRandomSpread(float* flSpreadRight, float* flSpreadUp)
	{
		DWORD dwCall = 0x5E0BC0;//0x5C8D00; 

		int iSeed = *(int*)0x96A25C - 1;//A4758C-1;

		int iSpreadSeed = 214013 * (214013 * (214013 * (214013 * iSeed + 2531011) + 2531011) + 2531011) + 2531011;

		__asm
		{
			lea eax, dword ptr ds : [flSpreadUp];
			push[eax];
			lea ecx, dword ptr ds : [flSpreadRight];
			push[ecx];
			lea esi, dword ptr ds : [iSpreadSeed];
			call dword ptr ds : [dwCall];
			add esp, 0x8
		}
	}

	void GetWeaponSpread(float*Spread)
	{
		float SpreadMultiplier = *(float*)0xA03950;//0xAE0CC8; 

		float MaxSpread = 0.0f;
		float BaseSpread = 0.0f;

		int iLocalWeapon = CG_GetLocalWeapon((CG_T*)CGOFF);

		BG_GetSpreadForWeapon((CG_T*)CGOFF, iLocalWeapon, &BaseSpread, &MaxSpread);

		*Spread = BaseSpread + ((MaxSpread - BaseSpread) * SpreadMultiplier / 255.0f);
	}

	void AngleVectors(const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up)
	{
		float			angle;
		static float	sr, sp, sy, cr, cp, cy;

		angle = angles[1] * (PI * 2 / 360);
		sy = sin(angle);
		cy = cos(angle);

		angle = angles[0] * (PI * 2 / 360);
		sp = sin(angle);
		cp = cos(angle);

		angle = angles[2] * (PI * 2 / 360);
		sr = sin(angle);
		cr = cos(angle);

		if (forward)
		{
			forward[0] = cp*cy;
			forward[1] = cp*sy;
			forward[2] = -sp;
		}
		if (right)
		{
			right[0] = (-1 * sr*sp*cy + -1 * cr*-sy);
			right[1] = (-1 * sr*sp*sy + -1 * cr*cy);
			right[2] = -1 * sr*cp;
		}
		if (up)
		{
			up[0] = (cr*sp*cy + -sr*-sy);
			up[1] = (cr*sp*sy + -sr*cy);
			up[2] = cr*cp;
		}
	}

	void VecToAngles(const vec3_t value1, vec3_t angles)
	{
		float	forward;
		float	yaw, pitch;

		if (value1[1] == 0 && value1[0] == 0)
		{
			yaw = 0;
			if (value1[2] > 0)
				pitch = 90;
			else
				pitch = 270;
		}
		else
		{
			if (value1[0])
				yaw = (atan2(value1[1], value1[0]) * (180.0f / PI));
			else if (value1[1] > 0)
				yaw = 90.0f;
			else
				yaw = 270.0f;

			if (yaw < 0.0f)
				yaw += 360.0f;

			forward = sqrt((value1[0] * value1[0]) + (value1[1] * value1[1]));
			pitch = (atan2(value1[2], forward) * (180.0f / PI));

			if (pitch < 0.0f)
				pitch += 360;
		}

		angles[0] = -pitch;
		angles[1] = yaw;
		angles[2] = 0;
	}

	float AngleNormalize360(float angle)
	{
		return ((float)(360.0 / 65536) * ((int)(angle * (65536 / 360.0)) & 65535));
	}

	float AngleNormalize180(float angle)
	{
		angle = AngleNormalize360(angle);
		if (angle > 180.0) {
			angle -= 360.0;
		}
		return angle;
	}

#define POW(x)((x)*(x))
#define VectorLength(a)         sqrt(POW((a)[0])+POW((a)[1])+POW((a)[2]))
#define VectorNormalize(a)      {vec_t l=VectorLength(a);(a)[0]/=l;(a)[1]/=l;(a)[2]/=l;}
#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])


	void ApplySpread()
	{
		RefDef_T* ref = (RefDef_T*)REFDEFOFF;

		float spread = 0.0f;
		float spread_x = 0.0f;
		float spread_y = 0.0f;
		float distance = 8192.0f;


		vec3_t spread_view, calc_spread_view, spread_angle, forward, right, up, dest;

		vec3_t weapon_angles;

		//weapon_angles[ 0 ] = *( float* )0xA44F98;
		//weapon_angles[ 1 ] = *( float* )0xA44F9C;
		weapon_angles[0] = ref->ViewAngles.x;
		weapon_angles[1] = ref->ViewAngles.y;
		weapon_angles[2] = ref->ViewAngles.z;

		AngleVectors(weapon_angles, forward, right, up);

		GetWeaponSpread(&spread);

		//spread *= 0.01745329238474369f;

		spread = tan(spread) * distance;

		GetRandomSpread(&spread_x, &spread_y);

		spread_x *= spread;
		spread_y *= spread;

		spread_view[0] = ref->Origin.x + forward[0] * distance + right[0] * spread_x + up[0] * spread_y;
		spread_view[1] = ref->Origin.y + forward[1] * distance + right[1] * spread_x + up[1] * spread_y;
		spread_view[2] = ref->Origin.z + forward[2] * distance + right[2] * spread_x + up[2] * spread_y;

		//VectorNormalize(spread_view);

		vec3_t v{ ref->Origin.x,ref->Origin.y,ref->Origin.z };
		VectorSubtract(spread_view, v, spread_angle);

		VecToAngles(spread_view, dest);

		vec3_t luul;

		luul[0] = weapon_angles[0] - spread_view[0];
		luul[1] = weapon_angles[1] - spread_view[1];
		luul[2] = weapon_angles[2] - spread_view[2];

		float* ViewX = (float*)0x0106389C;
		float* ViewY = (float*)0x01063898;

		Vector3D super_final(*ViewX, *ViewY, 0);

		super_final.x += luul[0];
		super_final.y = luul[1];


		/*cmd->viewangles[0] += ANGLE2SHORT(CU_Utils.AngleNormalize180(spread_angle[0]));
		cmd->viewangles[1] += ANGLE2SHORT(CU_Utils.AngleNormalize180(spread_angle[1]));
		cmd->viewangles[2] += ANGLE2SHORT(CU_Utils.AngleNormalize180(spread_angle[2]));

		if (Aimbot.Silent && Aimbot.BestTarget != -1)
		{
		float AimAt[2];
		CU_Utils.GetAngleToOrigin(Aimbot.vTemp, AimAt[0], AimAt[1]);

		cmd->viewangles[0] += ANGLE2SHORT(AimAt[1]);
		cmd->viewangles[1] += ANGLE2SHORT(AimAt[0]);
		}*/

		*ViewX += super_final.x;
		*ViewY += super_final.y;
	}
}