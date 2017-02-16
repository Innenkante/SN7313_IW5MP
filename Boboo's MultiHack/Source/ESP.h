#pragma once


class ESP
{
public:
	static bool CircleESPEnabled;
	static bool BoneESPEnabled;//1
	static bool NameESPEnabled;
	static bool SlotESPEnabled;
	static bool RankESPEnabled;
	static bool DistanceESPEnabled;
	static bool XUIDESPEnabled;
	static bool ThreeDBoxESPEnabled;
	static bool WeaponESPEnabled;
	static bool SnaplineESPEnabled;
	static bool ShaderESPEnabled;
	static bool VisibleESPEnabled;
	static bool MagicESPEnabled;
	static void Wrapper();
private:
	static void CirlceESP();
	static void NameESP();
	static void SlotESP();
	static void RankESP();
	static void DistanceESP();
	static void XUIDESP();
	static void BoneESP();
	static void ThreeDBoxESP();
	static void WeaponESP();
	static void SnaplineESP();
	static void ShaderESP();
	static void VisibleESP();
	static void MagicESP();
};
