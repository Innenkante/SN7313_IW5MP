#pragma once


static class Engine_
{
public:
	DrawEngineText_t DrawEngineText_ = (DrawEngineText_t)DRAWENGINETEXTOFF;
	DrawRotatedPic_t DrawRotatedPic_ = (DrawRotatedPic_t)0x0042F420;
	RegisterFont_t RegisterFont_ = (RegisterFont_t)REGISTERFONTOFF;
	RegisterShader_t RegisterShader_ = (RegisterShader_t)REGISTERSHADEROFF;
	GetScreenMatrix_t GetScreenMatrix_ = (GetScreenMatrix_t)SCREENMATRIXOFF;
	World2Screen_t WorldToScreen_ = (World2Screen_t)0x004e5fc0;
	RegisterTag_t RegisterTag_ = (RegisterTag_t)0x4922E0;
	ProcessCMD ProcessCMD_ = (ProcessCMD)0x429920;
	bool GetTagPos(Entity_T* ent, char* tagname, float* out);
	Weapon_t* GetWeapon(int WeaponID);
	Trace_t TraceToTarget(float* TargetVector);
	void Shoot();
	bool IsVisible(int ClientNumber);
	MessageGiver_t MessageGiver_ = (MessageGiver_t)0x004A6660;
	int GetXUID(int ClientNumber);
private:
	CG_Trace_t Trace_ = (CG_Trace_t)0x55A820;
	CL_IsEntityVisible_t IsEntityVisible_= (CL_IsEntityVisible_t)0x54E6D0;
};


