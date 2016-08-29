#include "stdafx.h"
#include "ESP.h"
#include "LinkingFix.h"

void ESP_::CirlceESP(bool state)
{
	if (!state)
		return;
	Entity_T* Entity[18];
	ClientInfo_T* Clients[18];
	RefDef_T* refdef = (RefDef_T*)(REFDEFOFF);
	CG_T* cg = (CG_T*)(CGOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	float* ViewX = (float*)0x0106389C;
	float* ViewY = (float*)0x01063898;
	CGS_T * CGS = (CGS_T*)(CGSOFF);
	bool DeathMatch = false;

	if (CGS->GameType[0] == 'd' && CGS->GameType[1] == 'm')
	{
		DeathMatch = true;
	}

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * (int)ENTITYSIZE));
		Clients[i] = (ClientInfo_T*)(CLIENTOFF + (i * (int)CLIENTSIZE));
		if (Entity[i]->ClientNumber != cg->ClientNumber && Entity[i]->IsAlive & 0x01 && Entity[i]->Type == Entity_Type::Player && Entity[i]->Valid && Clients[i]->Valid)
		{
			float TagPos_head[3];
			float Screen_head[2];

			float TagPos_MainRoot[3];
			float Screen_MainRoot[2];

			Engine.GetTagPos(Entity[i], "j_head", TagPos_head);
			Engine.GetTagPos(Entity[i], "j_mainroot", TagPos_MainRoot);


			ScreenMatrix* Matrix = Engine.GetScreenMatrix_();

			Engine.WorldToScreen_(0x0, Matrix, TagPos_head, Screen_head);
			Engine.WorldToScreen_(0x0, Matrix, TagPos_MainRoot, Screen_MainRoot);

			if (DeathMatch)
			{
				Draw.DrawCirlceOnScreen(Utils.ParsVec(Screen_MainRoot), Math.GetDistance(Utils.ParsVec(Screen_MainRoot), Utils.ParsVec(Screen_head)), ColorRed);
				continue;
			}
			if (Clients[i]->Team == LocalClient->Team)
				Draw.DrawCirlceOnScreen(Utils.ParsVec(Screen_MainRoot), Math.GetDistance(Utils.ParsVec(Screen_MainRoot), Utils.ParsVec(Screen_head)), ColorGreen);
			else
				Draw.DrawCirlceOnScreen(Utils.ParsVec(Screen_MainRoot), Math.GetDistance(Utils.ParsVec(Screen_MainRoot), Utils.ParsVec(Screen_head)), ColorRed);

		}
	}
}

void ESP_::NameESP(bool state)
{
	if (!state)
		return;
	Entity_T* Entity[18];
	ClientInfo_T* Clients[18];
	RefDef_T* refdef = (RefDef_T*)(REFDEFOFF);
	CG_T* cg = (CG_T*)(CGOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	float* ViewX = (float*)0x0106389C;
	float* ViewY = (float*)0x01063898;
	CGS_T * CGS = (CGS_T*)(CGSOFF);
	bool DeathMatch = false;

	if (CGS->GameType[0] == 'd' && CGS->GameType[1] == 'm')
	{
		DeathMatch = true;
	}

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * (int)ENTITYSIZE));
		Clients[i] = (ClientInfo_T*)(CLIENTOFF + (i * (int)CLIENTSIZE));
		if (Entity[i]->ClientNumber != cg->ClientNumber && Entity[i]->IsAlive & 0x01 && Entity[i]->Type == Entity_Type::Player && Entity[i]->Valid && Clients[i]->Valid)
		{
			float TagPos_head[3];
			float Screen_head[2];
			Engine.GetTagPos(Entity[i], "j_head", TagPos_head);
			ScreenMatrix* Matrix = Engine.GetScreenMatrix_();
			Engine.WorldToScreen_(0x0, Matrix, TagPos_head, Screen_head);
			char buf_Name[1024];
			sprintf_s(buf_Name, "^3 %s ", Clients[i]->Name);
			Draw.DrawTextMW3(Screen_head[0] + 32, Screen_head[1] + -5, Engine.RegisterFont_(FONT_SMALL_DEV), ColorWhite, buf_Name); //Name 
		}
	}
}

void ESP_::SlotESP(bool state)
{
	if (!state)
		return;
	Entity_T* Entity[18];
	ClientInfo_T* Clients[18];
	RefDef_T* refdef = (RefDef_T*)(REFDEFOFF);
	CG_T* cg = (CG_T*)(CGOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	float* ViewX = (float*)0x0106389C;
	float* ViewY = (float*)0x01063898;
	CGS_T * CGS = (CGS_T*)(CGSOFF);
	bool DeathMatch = false;

	if (CGS->GameType[0] == 'd' && CGS->GameType[1] == 'm')
	{
		DeathMatch = true;
	}

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * (int)ENTITYSIZE));
		Clients[i] = (ClientInfo_T*)(CLIENTOFF + (i * (int)CLIENTSIZE));
		if (Entity[i]->ClientNumber != cg->ClientNumber && Entity[i]->IsAlive & 0x01 && Entity[i]->Type == Entity_Type::Player && Entity[i]->Valid && Clients[i]->Valid)
		{
			float TagPos_head[3];
			float Screen_head[2];
			Engine.GetTagPos(Entity[i], "j_head", TagPos_head);
			ScreenMatrix* Matrix = Engine.GetScreenMatrix_();
			Engine.WorldToScreen_(0x0, Matrix, TagPos_head, Screen_head);
			char buf_Slot[1024];
			sprintf_s(buf_Slot, "^3 %s ", Clients[i]->ClientNumber);
			Draw.DrawTextMW3(Screen_head[0] + 32, Screen_head[1] + 8, Engine.RegisterFont_(FONT_SMALL_DEV), ColorWhite, buf_Slot); 
		}
	}
}


void ESP_::RankESP(bool state)
{
	if (!state)
		return;
	Entity_T* Entity[18];
	ClientInfo_T* Clients[18];
	RefDef_T* refdef = (RefDef_T*)(REFDEFOFF);
	CG_T* cg = (CG_T*)(CGOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	float* ViewX = (float*)0x0106389C;
	float* ViewY = (float*)0x01063898;
	CGS_T * CGS = (CGS_T*)(CGSOFF);
	bool DeathMatch = false;

	if (CGS->GameType[0] == 'd' && CGS->GameType[1] == 'm')
	{
		DeathMatch = true;
	}

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * (int)ENTITYSIZE));
		Clients[i] = (ClientInfo_T*)(CLIENTOFF + (i * (int)CLIENTSIZE));
		if (Entity[i]->ClientNumber != cg->ClientNumber && Entity[i]->IsAlive & 0x01 && Entity[i]->Type == Entity_Type::Player && Entity[i]->Valid && Clients[i]->Valid)
		{
			float TagPos_head[3];
			float Screen_head[2];
			Engine.GetTagPos(Entity[i], "j_head", TagPos_head);
			ScreenMatrix* Matrix = Engine.GetScreenMatrix_();
			Engine.WorldToScreen_(0x0, Matrix, TagPos_head, Screen_head);
			char buf_Rank[1024];
			sprintf_s(buf_Rank, "^3 %s ", Clients[i]->Rank);
			Draw.DrawTextMW3(Screen_head[0] + 32, Screen_head[1] + 18, Engine.RegisterFont_(FONT_SMALL_DEV), ColorWhite, buf_Rank);
		}
	}
}

void ESP_::DistanceESP(bool state)
{
	if (!state)
		return;
	Entity_T* Entity[18];
	ClientInfo_T* Clients[18];
	RefDef_T* refdef = (RefDef_T*)(REFDEFOFF);
	CG_T* cg = (CG_T*)(CGOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	float* ViewX = (float*)0x0106389C;
	float* ViewY = (float*)0x01063898;
	CGS_T * CGS = (CGS_T*)(CGSOFF);
	bool DeathMatch = false;

	if (CGS->GameType[0] == 'd' && CGS->GameType[1] == 'm')
	{
		DeathMatch = true;
	}

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * (int)ENTITYSIZE));
		Clients[i] = (ClientInfo_T*)(CLIENTOFF + (i * (int)CLIENTSIZE));
		if (Entity[i]->ClientNumber != cg->ClientNumber && Entity[i]->IsAlive & 0x01 && Entity[i]->Type == Entity_Type::Player && Entity[i]->Valid && Clients[i]->Valid)
		{
			float TagPos_head[3];
			float Screen_head[2];
			Engine.GetTagPos(Entity[i], "j_head", TagPos_head);
			ScreenMatrix* Matrix = Engine.GetScreenMatrix_();
			Engine.WorldToScreen_(0x0, Matrix, TagPos_head, Screen_head);
			char buf_Distance[1024];
			float distance = Math.GetDistance(refdef->Origin, Utils.ParseVec(TagPos_head));
			sprintf_s(buf_Distance, "^3 %f ", distance);
			Draw.DrawTextMW3(Screen_head[0] + 32, Screen_head[1] + 28, Engine.RegisterFont_(FONT_SMALL_DEV), ColorWhite, buf_Distance);
		}
	}
}

void ESP_::XUIDESP(bool state)
{
	if (!state)
		return;
	Entity_T* Entity[18];
	ClientInfo_T* Clients[18];
	RefDef_T* refdef = (RefDef_T*)(REFDEFOFF);
	CG_T* cg = (CG_T*)(CGOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	float* ViewX = (float*)0x0106389C;
	float* ViewY = (float*)0x01063898;
	CGS_T * CGS = (CGS_T*)(CGSOFF);
	bool DeathMatch = false;

	if (CGS->GameType[0] == 'd' && CGS->GameType[1] == 'm')
	{
		DeathMatch = true;
	}

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * (int)ENTITYSIZE));
		Clients[i] = (ClientInfo_T*)(CLIENTOFF + (i * (int)CLIENTSIZE));
		if (Entity[i]->ClientNumber != cg->ClientNumber && Entity[i]->IsAlive & 0x01 && Entity[i]->Type == Entity_Type::Player && Entity[i]->Valid && Clients[i]->Valid)
		{
			float TagPos_head[3];
			float Screen_head[2];
			Engine.GetTagPos(Entity[i], "j_head", TagPos_head);
			ScreenMatrix* Matrix = Engine.GetScreenMatrix_();
			Engine.WorldToScreen_(0x0, Matrix, TagPos_head, Screen_head);
			char buf_XUID[1024];
			long GUID = Engine.GetXUID(Clients[i]->ClientNumber);
			sprintf_s(buf_XUID, "^3 %d ", GUID);
			Draw.DrawTextMW3(Screen_head[0] + 32, Screen_head[1] + 38, Engine.RegisterFont_(FONT_SMALL_DEV), ColorWhite, buf_XUID);
		}
	}
}
void ESP_::BoneESP(bool state)
{
	if (!state)
		return;
	Entity_T* Entity[18];
	ClientInfo_T* Client[18];
	CG_T* cg = (CG_T*)(CGOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	CGS_T * CGS = (CGS_T*)CGSOFF;
	bool DeathMatch = false;

	if (CGS->GameType[0] == 'd' && CGS->GameType[1] == 'm')
	{
		DeathMatch = true;
	}

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * ENTITYSIZE));
		Client[i] = (ClientInfo_T*)(CLIENTOFF + (i * CLIENTSIZE));

		if (Entity[i]->ClientNumber != cg->ClientNumber && Entity[i]->IsAlive & 0x01 && Entity[i]->Type == Entity_Type::Player && Entity[i]->Valid && Client[i]->Valid)
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


			Engine.GetTagPos(Entity[i], "j_hip_ri", TagPos_hip_r);
			Engine.GetTagPos(Entity[i], "j_hip_le", TagPos_hip_l);

			Engine.GetTagPos(Entity[i], "j_knee_ri", TagPos_knee_r);
			Engine.GetTagPos(Entity[i], "j_knee_le", TagPos_knee_l);

			Engine.GetTagPos(Entity[i], "j_ankle_ri", TagPos_ankle_r);
			Engine.GetTagPos(Entity[i], "j_ankle_le", TagPos_ankle_l);

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

			Engine.GetTagPos(Entity[i], "j_shoulder_ri", TagPos_shoulder_r);
			Engine.GetTagPos(Entity[i], "j_shoulder_le", TagPos_shoulder_l);

			Engine.GetTagPos(Entity[i], "j_elbow_ri", TagPos_elbow_r);
			Engine.GetTagPos(Entity[i], "j_elbow_le", TagPos_elbow_l);

			Engine.GetTagPos(Entity[i], "j_wrist_ri", TagPos_wrist_r);
			Engine.GetTagPos(Entity[i], "j_wrist_le", TagPos_wrist_l);

			//Backbone "j_mainroot"   , "j_spineupper"   , "j_spinelower" , "j_spine4"

			float TagPos_spineupper[3];
			float TagPos_mainroot[3];
			float TagPos_spinelower[3];

			float Screen_spineupper[2];
			float Screen_mainroot[2];
			float Screen_spinelower[2];

			Engine.GetTagPos(Entity[i], "j_spineupper", TagPos_spineupper);
			Engine.GetTagPos(Entity[i], "j_mainroot", TagPos_mainroot);
			Engine.GetTagPos(Entity[i], "j_spinelower", TagPos_spinelower);

			//Head "j_helmet"     , "j_head"            , "j_neck"
			float TagPos_helmet[3];
			float TagPos_head[3];
			float TagPos_neck[3];

			float Screen_helmet[2];
			float Screen_head[2];
			float Screen_neck[2];

			Engine.GetTagPos(Entity[i], "j_helmet", TagPos_helmet);
			Engine.GetTagPos(Entity[i], "j_head", TagPos_head);
			Engine.GetTagPos(Entity[i], "j_neck", TagPos_neck);

			//Pelvis
			float TagPos_Pelvis[3];
			float Screen_Pelvis[2];

			Engine.GetTagPos(Entity[i], "pelvis", TagPos_Pelvis);


			ScreenMatrix* Matrix = Engine.GetScreenMatrix_();


			//Legs
			Engine.WorldToScreen_(0x0, Matrix, TagPos_hip_r, Screen_hip_r);
			Engine.WorldToScreen_(0x0, Matrix, TagPos_hip_l, Screen_hip_l);

			Engine.WorldToScreen_(0x0, Matrix, TagPos_knee_r, Screen_knee_r);
			Engine.WorldToScreen_(0x0, Matrix, TagPos_knee_l, Screen_knee_l);

			Engine.WorldToScreen_(0x0, Matrix, TagPos_ankle_r, Screen_ankle_r);
			Engine.WorldToScreen_(0x0, Matrix, TagPos_ankle_l, Screen_ankle_l);

			//Arms
			Engine.WorldToScreen_(0x0, Matrix, TagPos_shoulder_r, Screen_shoulder_r);
			Engine.WorldToScreen_(0x0, Matrix, TagPos_shoulder_l, Screen_shoulder_l);

			Engine.WorldToScreen_(0x0, Matrix, TagPos_elbow_r, Screen_elbow_r);
			Engine.WorldToScreen_(0x0, Matrix, TagPos_elbow_l, Screen_elbow_l);

			Engine.WorldToScreen_(0x0, Matrix, TagPos_wrist_r, Screen_wrist_r);
			Engine.WorldToScreen_(0x0, Matrix, TagPos_wrist_l, Screen_wrist_l);

			//Backbone
			Engine.WorldToScreen_(0x0, Matrix, TagPos_spineupper, Screen_spineupper);
			Engine.WorldToScreen_(0x0, Matrix, TagPos_mainroot, Screen_mainroot);
			Engine.WorldToScreen_(0x0, Matrix, TagPos_spinelower, Screen_spinelower);

			//Head
			Engine.WorldToScreen_(0x0, Matrix, TagPos_helmet, Screen_helmet);
			Engine.WorldToScreen_(0x0, Matrix, TagPos_head, Screen_head);
			Engine.WorldToScreen_(0x0, Matrix, TagPos_neck, Screen_neck);

			//Pelvis
			Engine.WorldToScreen_(0x0, Matrix, TagPos_Pelvis, Screen_Pelvis);

			Draw.DrawLine(Screen_Pelvis[0], Screen_Pelvis[1], Screen_Pelvis[0] + 1, Screen_Pelvis[1] + 1, ColorOrange, Engine.RegisterShader_("white"), 5); //The Peniiiis

			if (DeathMatch)
			{
				Draw.DrawLine(Screen_hip_r[0], Screen_hip_r[1], Screen_knee_r[0], Screen_knee_r[1], ColorRed, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_knee_r[0], Screen_knee_r[1], Screen_ankle_r[0], Screen_ankle_r[1], ColorRed, Engine.RegisterShader_("white"), 2);

				//Left Leg
				Draw.DrawLine(Screen_hip_l[0], Screen_hip_l[1], Screen_knee_l[0], Screen_knee_l[1], ColorRed, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_knee_l[0], Screen_knee_l[1], Screen_ankle_l[0], Screen_ankle_l[1], ColorRed, Engine.RegisterShader_("white"), 2);

				//Right Arm
				Draw.DrawLine(Screen_shoulder_r[0], Screen_shoulder_r[1], Screen_elbow_r[0], Screen_elbow_r[1], ColorRed, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_elbow_r[0], Screen_elbow_r[1], Screen_wrist_r[0], Screen_wrist_r[1], ColorRed, Engine.RegisterShader_("white"), 2);

				//Left Arm
				Draw.DrawLine(Screen_shoulder_l[0], Screen_shoulder_l[1], Screen_elbow_l[0], Screen_elbow_l[1], ColorRed, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_elbow_l[0], Screen_elbow_l[1], Screen_wrist_l[0], Screen_wrist_l[1], ColorRed, Engine.RegisterShader_("white"), 2);

				//Back bone
				Draw.DrawLine(Screen_spineupper[0], Screen_spineupper[1], Screen_mainroot[0], Screen_mainroot[1], ColorRed, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_mainroot[0], Screen_mainroot[1], Screen_spinelower[0], Screen_spinelower[1], ColorRed, Engine.RegisterShader_("white"), 2);

				//Head
				Draw.DrawLine(Screen_helmet[0], Screen_helmet[1], Screen_head[0], Screen_head[1], ColorRed, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_head[0], Screen_head[1], Screen_neck[0], Screen_neck[1], ColorRed, Engine.RegisterShader_("white"), 2);

				//Neck -> Backbone connection
				Draw.DrawLine(Screen_neck[0], Screen_neck[1], Screen_spineupper[0], Screen_spineupper[1], ColorRed, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_Pelvis[0], Screen_Pelvis[1], Screen_Pelvis[0] + 1, Screen_Pelvis[1] + 1, ColorOrange, Engine.RegisterShader_("white"), 5);

				continue;
			}
			if (Client[i]->Team == LocalClient->Team)
			{
				//Right leg
				Draw.DrawLine(Screen_hip_r[0], Screen_hip_r[1], Screen_knee_r[0], Screen_knee_r[1], ColorGreen, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_knee_r[0], Screen_knee_r[1], Screen_ankle_r[0], Screen_ankle_r[1], ColorGreen, Engine.RegisterShader_("white"), 2);

				//Left Leg
				Draw.DrawLine(Screen_hip_l[0], Screen_hip_l[1], Screen_knee_l[0], Screen_knee_l[1], ColorGreen, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_knee_l[0], Screen_knee_l[1], Screen_ankle_l[0], Screen_ankle_l[1], ColorGreen, Engine.RegisterShader_("white"), 2);

				//Right Arm
				Draw.DrawLine(Screen_shoulder_r[0], Screen_shoulder_r[1], Screen_elbow_r[0], Screen_elbow_r[1], ColorGreen, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_elbow_r[0], Screen_elbow_r[1], Screen_wrist_r[0], Screen_wrist_r[1], ColorGreen, Engine.RegisterShader_("white"), 2);

				//Left Arm
				Draw.DrawLine(Screen_shoulder_l[0], Screen_shoulder_l[1], Screen_elbow_l[0], Screen_elbow_l[1], ColorGreen, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_elbow_l[0], Screen_elbow_l[1], Screen_wrist_l[0], Screen_wrist_l[1], ColorGreen, Engine.RegisterShader_("white"), 2);

				//Back bone
				Draw.DrawLine(Screen_spineupper[0], Screen_spineupper[1], Screen_mainroot[0], Screen_mainroot[1], ColorGreen, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_mainroot[0], Screen_mainroot[1], Screen_spinelower[0], Screen_spinelower[1], ColorGreen, Engine.RegisterShader_("white"), 2);

				//Head
				Draw.DrawLine(Screen_helmet[0], Screen_helmet[1], Screen_head[0], Screen_head[1], ColorGreen, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_head[0], Screen_head[1], Screen_neck[0], Screen_neck[1], ColorGreen, Engine.RegisterShader_("white"), 2);

				//Neck -> Backbone connection
				Draw.DrawLine(Screen_neck[0], Screen_neck[1], Screen_spineupper[0], Screen_spineupper[1], ColorGreen, Engine.RegisterShader_("white"), 2);
			}
			else
			{
				//Right leg
				Draw.DrawLine(Screen_hip_r[0], Screen_hip_r[1], Screen_knee_r[0], Screen_knee_r[1], ColorRed, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_knee_r[0], Screen_knee_r[1], Screen_ankle_r[0], Screen_ankle_r[1], ColorRed, Engine.RegisterShader_("white"), 2);

				//Left Leg
				Draw.DrawLine(Screen_hip_l[0], Screen_hip_l[1], Screen_knee_l[0], Screen_knee_l[1], ColorRed, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_knee_l[0], Screen_knee_l[1], Screen_ankle_l[0], Screen_ankle_l[1], ColorRed, Engine.RegisterShader_("white"), 2);

				//Right Arm
				Draw.DrawLine(Screen_shoulder_r[0], Screen_shoulder_r[1], Screen_elbow_r[0], Screen_elbow_r[1], ColorRed, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_elbow_r[0], Screen_elbow_r[1], Screen_wrist_r[0], Screen_wrist_r[1], ColorRed, Engine.RegisterShader_("white"), 2);

				//Left Arm
				Draw.DrawLine(Screen_shoulder_l[0], Screen_shoulder_l[1], Screen_elbow_l[0], Screen_elbow_l[1], ColorRed, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_elbow_l[0], Screen_elbow_l[1], Screen_wrist_l[0], Screen_wrist_l[1], ColorRed, Engine.RegisterShader_("white"), 2);
				
				//Back bone
				Draw.DrawLine(Screen_spineupper[0], Screen_spineupper[1], Screen_mainroot[0], Screen_mainroot[1], ColorRed, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_mainroot[0], Screen_mainroot[1], Screen_spinelower[0], Screen_spinelower[1], ColorRed, Engine.RegisterShader_("white"), 2);

				//Head
				Draw.DrawLine(Screen_helmet[0], Screen_helmet[1], Screen_head[0], Screen_head[1], ColorRed, Engine.RegisterShader_("white"), 2);
				Draw.DrawLine(Screen_head[0], Screen_head[1], Screen_neck[0], Screen_neck[1], ColorRed, Engine.RegisterShader_("white"), 2);

				//Neck -> Backbone connection
				Draw.DrawLine(Screen_neck[0], Screen_neck[1], Screen_spineupper[0], Screen_spineupper[1], ColorRed, Engine.RegisterShader_("white"), 2);
			}
		}
	}
}

void ESP_::ThreeDBoxESP(bool state)
{
	if (!state)
		return;
	Entity_T* Entity[18];
	ClientInfo_T* Client[18];
	CG_T* cg = (CG_T*)(CGOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	CGS_T * CGS = (CGS_T*)(CGSOFF);
	bool DeathMatch = false;

	if (CGS->GameType[0] == 'd' && CGS->GameType[1] == 'm')
	{
		DeathMatch = true;
	}

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * ENTITYSIZE));
		Client[i] = (ClientInfo_T*)(CLIENTOFF + (i * CLIENTSIZE));

		if (Entity[i]->ClientNumber != cg->ClientNumber && Entity[i]->IsAlive & 0x01 && Entity[i]->Type == Entity_Type::Player && Entity[i]->Valid && Client[i]->Valid)
		{
			if (DeathMatch)
			{
				Draw.Draw3DBox(Entity[i]->Origin, 40, 80, ColorRed, Engine.RegisterShader_("white"));
				continue;
			}
			if (Client[i]->Team == LocalClient->Team)
				Draw.Draw3DBox(Entity[i]->Origin, 40, 80, ColorGreen, Engine.RegisterShader_("white"));
			else
				Draw.Draw3DBox(Entity[i]->Origin, 40, 80, ColorRed, Engine.RegisterShader_("white"));
		}
	}
}

void ESP_::WeaponESP(bool state)
{
	if (!state)
		return;
	Entity_T* Entity[2048];
	float oldangle = 0;
	for (int i = 0; i < 2048; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * ENTITYSIZE));


		if (Entity[i]->Type == Entity_Type::Item && Entity[i]->Valid && Entity[i]->IsAlive & 0x01)
		{
			weapon_t* Weapon = Engine.GetWeapon(Entity[i]->WeaponID);
			float ScreenPos[2];
			float WorldPos[] = { Entity[i]->Origin.x,Entity[i]->Origin.y,Entity[i]->Origin.z + 50 };
			Engine.WorldToScreen_(0x0, Engine.GetScreenMatrix_(), WorldPos, ScreenPos);
			if (Weapon->weaponName != NULL)
			{
				//DrawTextMW3(ScreenPos[0], ScreenPos[1], RegisterFont(FONT_SMALL_DEV), ColorGreen, Weapon->weaponname);
				RefDef_T* RefDef = (RefDef_T*)REFDEFOFF;
				float Distance = Math.GetDistance(RefDef->Origin, Utils.ParseVec(WorldPos)) / 500;
				if (Weapon->weaponName[17] == 'B' && Weapon->weaponName[18] == 'A' && Weapon->weaponName[19] == 'G')
					Draw.DrawShaderByName(ScreenPos[0], ScreenPos[1], 80 / Distance, 60 / Distance, ColorWhite, "specialty_scavenger");
				else
					Draw.DrawShaderByInt(ScreenPos[0], ScreenPos[1], 80 / Distance, 60 / Distance, ColorWhite, Weapon->weaponShader);
			}
		}
		if (Entity[i]->Type == Entity_Type::Player_Corpse)
		{
			float ScreenPos[2];
			float WorldPos[] = { Entity[i]->Origin.x,Entity[i]->Origin.y,Entity[i]->Origin.z };
			Engine.WorldToScreen_(0x0, Engine.GetScreenMatrix_(), WorldPos, ScreenPos);
			RefDef_T* RefDef = (RefDef_T*)REFDEFOFF;
			float Distance = Math.GetDistance(RefDef->Origin, Utils.ParseVec(WorldPos)) / 500;
			Draw.DrawShaderByName(ScreenPos[0], ScreenPos[1], 60 / Distance, 40 / Distance, ColorWhite, "headicon_dead");
		}
		if (Entity[i]->Type == Entity_Type::Turret)
		{
			weapon_t* Weapon = Engine.GetWeapon(Entity[i]->WeaponID);
			float ScreenPos[2];
			float WorldPos[] = { Entity[i]->Origin.x,Entity[i]->Origin.y,Entity[i]->Origin.z };
			Engine.WorldToScreen_(0x0, Engine.GetScreenMatrix_(), WorldPos, ScreenPos);
			RefDef_T* RefDef = (RefDef_T*)REFDEFOFF;
			float Distance = Math.GetDistance(RefDef->Origin, Utils.ParseVec(WorldPos)) / 500;
			Draw.DrawShaderByInt(ScreenPos[0], ScreenPos[1], 60 / Distance, 40 / Distance, ColorWhite, Weapon->weaponShader);

		}
		if (Entity[i]->Type == Entity_Type::Explosive)
		{
			weapon_t* Weapon = Engine.GetWeapon(Entity[i]->WeaponID);
			float ScreenPos[2];
			float WorldPos[] = { Entity[i]->Origin.x,Entity[i]->Origin.y,Entity[i]->Origin.z + 50 };
			Engine.WorldToScreen_(0x0, Engine.GetScreenMatrix_(), WorldPos, ScreenPos);
			if (Weapon->weaponName != NULL)
			{
				//Look here : http://denkirson.proboards.com/thread/4482 and here http://gaming.stackexchange.com/questions/118448/grenade-blast-radius
				RefDef_T* RefDef = (RefDef_T*)REFDEFOFF;
				float Distance = Math.GetDistance(RefDef->Origin, Utils.ParseVec(WorldPos)) / 500;
				if (strstr(Weapon->modelName, "frag_grenade_mp") || strstr(Weapon->modelName, "semtex"))
				{
					Draw.DrawShaderByInt(ScreenPos[0], ScreenPos[1], 80 / Distance, 60 / Distance, ColorRed, Weapon->weaponShader);
					Draw.DrawCirlceSplashDamage(Entity[i]->Origin, 248.031, ColorRed); //6,3 meters in inch; 
				}
				if (strstr(Weapon->modelName, "flash_grenade_mp"))
				{
					Draw.DrawShaderByName(ScreenPos[0], ScreenPos[1], 80 / Distance, 60 / Distance, ColorOrange, "hud_flashbangicon");
					Draw.DrawCirlceSplashDamage(Entity[i]->Origin, 708.661, ColorOrange);
				}
				if (strstr(Weapon->modelName, "throwingknife_mp"))
					Draw.DrawShaderByName(ScreenPos[0], ScreenPos[1], 80 / Distance, 60 / Distance, ColorOrange, "equipment_throwing_knife");
				if (strstr(Weapon->modelName, "smoke_grenade_mp"))
					Draw.DrawShaderByName(ScreenPos[0], ScreenPos[1], 80 / Distance, 60 / Distance, ColorOrange, "weapon_smokegrenade");
				if (strstr(Weapon->modelName, "concussion_grenade_mp"))
				{
					Draw.DrawShaderByName(ScreenPos[0], ScreenPos[1], 80 / Distance, 60 / Distance, ColorOrange, "weapon_concgrenade");
					Draw.DrawCirlceSplashDamage(Entity[i]->Origin, 472.441, ColorOrange);
				}
			}
		}
		if (Entity[i]->Type == Entity_Type::Helicopter)
		{
			weapon_t* Weapon = Engine.GetWeapon(Entity[i]->WeaponID);
			float ScreenPos[2];
			float WorldPos[] = { Entity[i]->Origin.x,Entity[i]->Origin.y,Entity[i]->Origin.z + 50 };
			Engine.WorldToScreen_(0x0, Engine.GetScreenMatrix_(), WorldPos, ScreenPos);
			if (Weapon->weaponName != NULL)
			{
				Draw.DrawShaderByInt(ScreenPos[0], ScreenPos[1], 80, 60, ColorWhite, Weapon->weaponShader);
			}
		}
		if (Entity[i]->Type == Entity_Type::Plane)
		{
			weapon_t* Weapon = Engine.GetWeapon(Entity[i]->WeaponID);
			float ScreenPos[2];
			float WorldPos[] = { Entity[i]->Origin.x,Entity[i]->Origin.y,Entity[i]->Origin.z + 50 };
			Engine.WorldToScreen_(0x0, Engine.GetScreenMatrix_(), WorldPos, ScreenPos);
			if (Weapon->weaponName != NULL)
			{
				Draw.DrawShaderByInt(ScreenPos[0], ScreenPos[1], 80, 60, ColorWhite, Weapon->weaponShader);
			}
		}
	}
}

void ESP_::SnaplineESP(bool state)
{
	if (!state)
		return;
	Entity_T* Entity[18];
	ClientInfo_T* Client[18];
	CG_T* cg = (CG_T*)(CGOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	CGS_T * CGS = (CGS_T*)(CGSOFF);
	RefDef_T* RefDef = (RefDef_T*)REFDEFOFF;
	bool DeathMatch = false;

	if (CGS->GameType[0] == 'd' && CGS->GameType[1] == 'm')
	{
		DeathMatch = true;
	}

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * ENTITYSIZE));
		Client[i] = (ClientInfo_T*)(CLIENTOFF + (i * CLIENTSIZE));
		if (Entity[i]->ClientNumber != cg->ClientNumber && Entity[i]->IsAlive & 0x01 && Entity[i]->Type == Entity_Type::Player && Entity[i]->Valid && Client[i]->Valid)
		{
			float TagPos[3];
			float ScreenPos[2];

			Engine.GetTagPos(Entity[i], "j_head", TagPos);
			Engine.WorldToScreen_(0x0, Engine.GetScreenMatrix_(), TagPos, ScreenPos);

			if (DeathMatch)
			{
				Draw.DrawLine(RefDef->Width / 2, RefDef->Height, ScreenPos[0], ScreenPos[1], ColorRed, Engine.RegisterShader_("white"), 2);
				continue;
			}
			if (Client[i]->Team == LocalClient->Team)
				Draw.DrawLine(RefDef->Width / 2, RefDef->Height, ScreenPos[0], ScreenPos[1], ColorGreen, Engine.RegisterShader_("white"), 2);
			else
				Draw.DrawLine(RefDef->Width / 2, RefDef->Height, ScreenPos[0], ScreenPos[1], ColorRed, Engine.RegisterShader_("white"), 2);
		}

	}
}

void ESP_::ShaderESP(bool state)
{
	if (!state)
		return;
	Entity_T* Entity[18];
	ClientInfo_T* Client[18];
	CG_T* cg = (CG_T*)(CGOFF);
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (cg->ClientNumber * CLIENTSIZE));
	CGS_T * CGS = (CGS_T*)(CGSOFF);
	RefDef_T* RefDef = (RefDef_T*)(REFDEFOFF);
	bool DeathMatch = false;

	if (CGS->GameType[0] == 'd' && CGS->GameType[1] == 'm')
	{
		DeathMatch = true;
	}

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(ENTITYOFF + (i * ENTITYSIZE));
		Client[i] = (ClientInfo_T*)(CLIENTOFF + (i * CLIENTSIZE));
		if (Entity[i]->ClientNumber != cg->ClientNumber && Entity[i]->IsAlive & 0x01 && Entity[i]->Type == Entity_Type::Player && Entity[i]->Valid && Client[i]->Valid)
		{
			float TagPos_Head[3];
			float Screen_Pos[2];

			if (!Engine.GetTagPos(Entity[i], "j_shoulder_ri", TagPos_Head))
				return;


			float Distance = Math.GetDistance(RefDef->Origin, Utils.ParseVec(TagPos_Head)) / 500;
			Engine.WorldToScreen_(0x0, Engine.GetScreenMatrix_(), TagPos_Head, Screen_Pos);

			if (Client[i]->Team != LocalClient->Team)
				Draw.DrawShaderByName(Screen_Pos[0], Screen_Pos[1], 80 / Distance, 60 / Distance, ColorWhite, "waypoint_kill");
			else
				Draw.DrawShaderByName(Screen_Pos[0], Screen_Pos[1], 80, 60, ColorWhite, "waypoint_defend");
		}

	}
}

void ESP_::Wrapper()
{
	CirlceESP(CircleESPEnabled);
	BoneESP(BoneESPEnabled);
	ThreeDBoxESP(ThreeDBoxESPEnabled);
	WeaponESP(WeaponESPEnabled);
	SnaplineESP(SnaplineESPEnabled);
	ShaderESP(ShaderESPEnabled);
	NameESP(NameESPEnabled);
	XUIDESP(XUIDESPEnabled);
	RankESP(RankESPEnabled);
	SlotESP(SlotESPEnabled);
	Misc.Crosshair(Misc.CrosshairEnabled);
}
