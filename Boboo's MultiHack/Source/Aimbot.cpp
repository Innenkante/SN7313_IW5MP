#include "stdafx.h"
#include "Aimbot.h"
#include "LinkingFix.h"

char* Bones_Collection[] =
{
	"j_head","j_neck","j_spine4","j_wrist_ri","j_wrist_le","j_elbow_ri","j_elbow_le","j_shoulder_ri","j_shoulder_le","j_ankle_ri","j_ankle_le","j_knee_ri","j_knee_le","j_hip_ri","j_hip_le","pelvis","j_mainroot",
};

void Aimbot_::ClosestAimbot(bool state, char * Bone)
{
	if (!state)
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



				float CurrentDistance = Math.GetDistance(RefDef->Origin, Utils.ParseVec(TagPos_bone));
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

			float CurrentDistance = Math.GetDistance(RefDef->Origin, Utils.ParseVec(TagPos_bone));
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
	Angles = Math.CalcAngles(RefDef->Origin, Utils.ParseVec(AimAt), RefDef->ViewAxis);

	float* ViewX = (float*)0x0106389C;
	float* ViewY = (float*)0x01063898;

	*ViewX += Angles.x;
	*ViewY += Angles.y;

}


void Aimbot_::InScreenRangeAimbot(bool state, char * Bone,int FieldOfAim)
{
	if (!state)
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
				float DistancePlayerBoneToScreenCenter = Math.GetDistance(Utils.ParseVec(PlayerScreenCenter), Utils.ParseVec(Screen_bone));

				if (!Engine.IsVisible(Entity[i]->ClientNumber))
					continue;

				if (DistancePlayerBoneToScreenCenter < FieldOfAim) //TODO
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
			float DistancePlayerBoneToScreenCenter = Math.GetDistance(Utils.ParseVec(PlayerScreenCenter), Utils.ParseVec(Screen_bone));

			if (!Engine.IsVisible(Entity[i]->ClientNumber)) //TODO
				continue;

			if (DistancePlayerBoneToScreenCenter < FieldOfAim) //TODO
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
	Angles = Math.CalcAngles(RefDef->Origin, Utils.ParseVec(AimAt), RefDef->ViewAxis);

	float* ViewX = (float*)0x0106389C;
	float* ViewY = (float*)0x01063898;

	*ViewX += Angles.x;
	*ViewY += Angles.y;


}

void Aimbot_::BestTraceAimbot(bool state)
{
	if (!state)
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
					if (tmptrace.fraction > BestTraceVal && !tmptrace.allsolid && tmptrace.fraction > 0.80)
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
				if (tmptrace.fraction > BestTraceVal && !tmptrace.allsolid && tmptrace.fraction > 0.80)
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
	Angles = Math.CalcAngles(RefDef->Origin, Utils.ParseVec(AimAt), RefDef->ViewAxis);

	float* ViewX = (float*)0x0106389C;
	float* ViewY = (float*)0x01063898;

	*ViewX += Angles.x;
	*ViewY += Angles.y;

	Engine.Shoot();

	
}

void Aimbot_::Wrapper()
{
	BestTraceAimbot(BestTraceAimbotEnabled);
	InScreenRangeAimbot(InScreenRangeAimbotEnabled,AimboneName,FieldOfAim);
	ClosestAimbot(ClosestAimbotEnabled,AimboneName);
}
