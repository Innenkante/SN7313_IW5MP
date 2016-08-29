#pragma once

class ESP_
{
public:
	bool CircleESPEnabled; //0
	bool BoneESPEnabled;//1
	bool NameESPEnabled;
	bool SlotESPEnabled;
	bool RankESPEnabled;
	bool DistanceESPEnabled;
	bool ScoreESPEnabled;
	bool XUIDESPEnabled;
	bool ThreeDBoxESPEnabled;
	bool WeaponESPEnabled;
	bool SnaplineESPEnabled;
	bool ShaderESPEnabled;
	void CirlceESP(bool state);
	void BoneESP(bool state);
	void NameESP(bool state);
	void SlotESP(bool state);
	void RankESP(bool state);
	void DistanceESP(bool state);
	void XUIDESP(bool state);
	void ThreeDBoxESP(bool state);
	void WeaponESP(bool state);
	void SnaplineESP(bool state);
	void ShaderESP(bool state);
	void Wrapper();
private:

};

