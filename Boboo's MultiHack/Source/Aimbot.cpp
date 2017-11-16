#include "stdafx.h"
#include "Aimbot.h"
#include "LinkingFix.h"
#include "../NoSpread.h"


bool Aimbot::ClosestAimbotEnabled = false;
bool Aimbot::AimAssistEnabled = false;
bool Aimbot::BestTraceAimbotEnabled = false;
int Aimbot:: FieldOfAim = 50;
int Aimbot::AimboneID = 0;
float Aimbot::MinTraceValue = 0.82f;
char* Aimbot::Bones_Collection[] = { "j_head","j_neck","j_spine4","j_wrist_ri","j_wrist_le","j_elbow_ri","j_elbow_le","j_shoulder_ri","j_shoulder_le","j_ankle_ri","j_ankle_le","j_knee_ri","j_knee_le","j_hip_ri","j_hip_le","pelvis","j_mainroot"};
char Aimbot::DisplayFieldOfAim[] = {};
char Aimbot::DisplayMinTraceValue[] = {};


void Aimbot::ClosestAimbot(char * Bone)
{
	if (!ClosestAimbotEnabled)
		return;
	Entity_T* Entity[18];
	ClientInfo_T* Client[18];
	RefDef_T* RefDef = (RefDef_T*)REFDEFOFF;
	CG_T* cg = (CG_T*)(CGOFF);
	CGS_T* cgs = (CGS_T*)(CGSOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	Vector2D Angles(0, 0);
	int ClosestPlayerClientNumber = -1;
	float ClosestDistance = 999999999999.f;
	float TagPos_bone[3];
	bool DeathMatch = false;

	if (cgs->GameType[0] == 'd' && cgs->GameType[1] == 'm')
	{
		DeathMatch = true;
	}

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * ENTITYSIZE));
		Client[i] = (ClientInfo_T*)(CLIENTOFF + (i * CLIENTSIZE));
	}

	for (int i = 0; i < 18; i++)
	{

		if (DeathMatch)
		{
			if (Entity[i]->Valid && Entity[i]->IsAlive & 0x01 && Entity[i]->ClientNumber != cg->ClientNumber)
			{

				if (!Engine.GetTagPos(Entity[i], Bone, TagPos_bone))
					continue;

				Trace_t Tmp = Engine.TraceToTarget(TagPos_bone);
				if(Tmp.fraction < 0.87f)
					continue;



				float CurrentDistance = Math::GetDistance(RefDef->Origin, Vector3D(TagPos_bone));
				if (CurrentDistance < ClosestDistance)
				{
					ClosestPlayerClientNumber = Entity[i]->ClientNumber;
					ClosestDistance = CurrentDistance;

				}
			}
		}
		else if (Entity[i]->Valid && Entity[i]->IsAlive & 0x01 && Client[i]->Team != LocalClient->Team)
		{


			if (!Engine.GetTagPos(Entity[i], Bone, TagPos_bone))
				continue;

			Trace_t Tmp = Engine.TraceToTarget(TagPos_bone);
			if (Tmp.fraction < 0.87f)
				continue;

			float CurrentDistance = Math::GetDistance(RefDef->Origin, Vector3D(TagPos_bone));
			if (CurrentDistance < ClosestDistance)
			{
				ClosestPlayerClientNumber = Entity[i]->ClientNumber;
				ClosestDistance = CurrentDistance;
			}
		}
	}

	if (ClosestPlayerClientNumber == -1)
		return;

	float AimAt[3];
	Engine.GetTagPos(Entity[ClosestPlayerClientNumber], Bone, AimAt);
	Angles = Math::CalcAngles(RefDef->Origin, Vector3D(AimAt), RefDef->ViewAxis);

	float* ViewX = (float*)0x0106389C;
	float* ViewY = (float*)0x01063898;

	*ViewX += Angles.x;
	*ViewY += Angles.y;

}


void Aimbot::InScreenRangeAimbot(char * Bone,int FieldOfAim)
{
	if (!AimAssistEnabled)
		return;
	Entity_T* Entity[18];
	ClientInfo_T* Client[18];
	RefDef_T* RefDef = (RefDef_T*)REFDEFOFF;
	CG_T* cg = (CG_T*)(CGOFF);
	CGS_T* cgs = (CGS_T*)(CGSOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	Vector2D Angles(0, 0);
	int ClosestPlayerClientNumber = -1;
	float ClosestDistance = 999999999999.f;
	float TagPos_bone[3];
	float Screen_bone[2];
	bool DeathMatch = false;

	if (cgs->GameType[0] == 'd' && cgs->GameType[1] == 'm')
	{
		DeathMatch = true;
	}

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * ENTITYSIZE));
		Client[i] = (ClientInfo_T*)(CLIENTOFF + (i * CLIENTSIZE));
	}

	for (int i = 0; i < 18; i++)
	{
		if (DeathMatch)
		{
			if (Entity[i]->Valid && Entity[i]->IsAlive & 0x01 && Entity[i]->ClientNumber != cg->ClientNumber)
			{
				if (!Engine.GetTagPos(Entity[i], Bone, TagPos_bone))
					return;
				Engine.WorldToScreen_(0x0, Engine.GetScreenMatrix_(), TagPos_bone, Screen_bone);
				float PlayerScreenCenter[] = { RefDef->Width / 2, RefDef->Height / 2 };
				float DistancePlayerBoneToScreenCenter = Math::GetDistance(Vector3D(PlayerScreenCenter), Vector3D(Screen_bone));

				if (!Engine.IsVisible(Entity[i]->ClientNumber))
					continue;

				if (DistancePlayerBoneToScreenCenter < FieldOfAim)
				{
					if (DistancePlayerBoneToScreenCenter < ClosestDistance)
					{

						ClosestDistance = DistancePlayerBoneToScreenCenter;
						ClosestPlayerClientNumber = Entity[i]->ClientNumber;

					}
				}
			}
		}
		else if (Entity[i]->Valid && Entity[i]->IsAlive & 0x01 && Client[i]->Team != LocalClient->Team)
		{
			if (!Engine.GetTagPos(Entity[i], Bone, TagPos_bone))
				return;
			Engine.WorldToScreen_(0x0, Engine.GetScreenMatrix_(), TagPos_bone, Screen_bone);
			float PlayerScreenCenter[] = { RefDef->Width / 2, RefDef->Height / 2 };
			float DistancePlayerBoneToScreenCenter = Math::GetDistance(Vector3D(PlayerScreenCenter), Vector3D(Screen_bone));

			if (!Engine.IsVisible(Entity[i]->ClientNumber)) 
				continue;

			if (DistancePlayerBoneToScreenCenter < FieldOfAim) 
			{
				if (DistancePlayerBoneToScreenCenter < ClosestDistance)
				{
					ClosestDistance = DistancePlayerBoneToScreenCenter;
					ClosestPlayerClientNumber = Entity[i]->ClientNumber;
				}
			}
		}
	}
	if (ClosestPlayerClientNumber == -1)
		return;

	float AimAt[3];
	Engine.GetTagPos(Entity[ClosestPlayerClientNumber], Bone, AimAt);
	Angles = Math::CalcAngles(RefDef->Origin, Vector3D(AimAt), RefDef->ViewAxis);

	float* ViewX = (float*)0x0106389C;
	float* ViewY = (float*)0x01063898;

	*ViewX += Angles.x;
	*ViewY += Angles.y;


}

void Aimbot::BestTraceAimbot(float MinTraceVal)
{
	if (!BestTraceAimbotEnabled)
		return;
	Entity_T* Entity[18];
	ClientInfo_T* Client[18];
	RefDef_T* RefDef = (RefDef_T*)REFDEFOFF;
	CG_T* cg = (CG_T*)(CGOFF);
	CGS_T* cgs = (CGS_T*)(CGSOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	Vector2D Angles(0, 0);
	float BestTraceVal = 0.f;
	int ClosestPlayerClientNumber = -1;
	float ClosestDistance = 999999999999.f;
	float TagPos_bone[3];
	float Screen_bone[2];
	bool DeathMatch = false;
	int BestBoneID = -1;

	if (cgs->GameType[0] == 'd' && cgs->GameType[1] == 'm')
	{
		DeathMatch = true;
	}

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * ENTITYSIZE));
		Client[i] = (ClientInfo_T*)(CLIENTOFF + (i * CLIENTSIZE));
	}

	for (int i = 0; i < 18; i++)
	{
		if (DeathMatch)
		{
			if (Entity[i]->Valid && Entity[i]->IsAlive & 0x01 && Entity[i]->ClientNumber != cg->ClientNumber)
			{
				for (int x = 0; x < 17; x++)
				{
					if (!Engine.GetTagPos(Entity[i], Bones_Collection[x], TagPos_bone))
						continue;
					Trace_t tmptrace = Engine.TraceToTarget(TagPos_bone);
					if (tmptrace.fraction > BestTraceVal && !tmptrace.allsolid && tmptrace.fraction > MinTraceVal)
					{
						BestBoneID = x;
						BestTraceVal = tmptrace.fraction;
						ClosestPlayerClientNumber = Entity[i]->ClientNumber;
					}
				}
			}
		}
		else if (Entity[i]->Valid && Entity[i]->IsAlive & 0x01 && Client[i]->Team != LocalClient->Team)
		{
			for (int x = 0; x < 17; x++)
			{
				if (!Engine.GetTagPos(Entity[i], Bones_Collection[x], TagPos_bone))
					continue;
				Trace_t tmptrace = Engine.TraceToTarget(TagPos_bone);
				if (tmptrace.fraction > BestTraceVal && !tmptrace.allsolid && tmptrace.fraction > MinTraceVal)
				{
					BestBoneID = x;
					BestTraceVal = tmptrace.fraction;
					ClosestPlayerClientNumber = Entity[i]->ClientNumber;
				}
			}
		}

	}
	if (ClosestPlayerClientNumber == -1)
		return;

	if (BestBoneID == -1)
		return;

	float AimAt[3];
	Engine.GetTagPos(Entity[ClosestPlayerClientNumber],Bones_Collection[BestBoneID], AimAt);
	Angles = Math::CalcAngles(RefDef->Origin, Vector3D(AimAt), RefDef->ViewAxis);

	float* ViewX = (float*)0x0106389C;
	float* ViewY = (float*)0x01063898;

	*ViewX += Angles.x;
	*ViewY += Angles.y;
	//no_spread::ApplySpread();

	Weapon_t* CurrentWeapon = Engine.GetWeapon(Entity[cg->ClientNumber]->WeaponID);
	if (strstr(CurrentWeapon->ModelName, "msr") || strstr(CurrentWeapon->ModelName, "l96a1"))
		return;
	Engine.Shoot();
}



void Aimbot::Wrapper()
{
	BestTraceAimbot(MinTraceValue);
	InScreenRangeAimbot(Bones_Collection[AimboneID],FieldOfAim);
	ClosestAimbot(Bones_Collection[AimboneID]);
}
