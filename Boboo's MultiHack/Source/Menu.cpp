#include "stdafx.h"
#include "Menu.h"

#include "LinkingFix.h"

bool Menu:: Enabled;
int Menu:: BasePosX;
int Menu:: BasePosY;
int Menu:: OptionNumber;
int Menu:: CurrentActiveMenu;

std::map<char*, void*> font_map_menu;

void Menu::register_fonts()
{
	font_map_menu[FONT_CONSOLE] = Engine.RegisterFont_(FONT_CONSOLE);
	font_map_menu[FONT_SMALL] = Engine.RegisterFont_(FONT_SMALL);
}

std::map<char*, int*> shader_map_menu;
void Menu::register_shaders()
{
	shader_map_menu["white"] = Engine.RegisterShader_("white");
}


void Menu::DrawMenu(int BasePosMenuX,int BasePosMenuY)
{
	DrawTabHeader("ESP", BasePosMenuX, BasePosMenuY, BasePosMenuX + 40, BasePosMenuY + 30, ColorWhite, shader_map_menu["white"], 3, font_map_menu[FONT_SMALL], ColorBlack, ColorBlue); //Size X = 40
	DrawTabHeader("Aimbot", BasePosMenuX + 40, BasePosMenuY, BasePosMenuX + 40 + 65, BasePosMenuY + 30, ColorWhite, shader_map_menu["white"], 3, font_map_menu[FONT_SMALL], ColorBlack, ColorGreen); //Size X = 65
	DrawTabHeader("Misc", BasePosMenuX + 40 + 65, BasePosMenuY, BasePosMenuX + 40 + 65 + 45, BasePosMenuY + 30, ColorWhite, shader_map_menu["white"], 3, font_map_menu[FONT_SMALL], ColorBlack, ColorOrange); //Size X = 45
	DrawTabHeader("Utils", BasePosMenuX + 40 + 65 + 45, BasePosMenuY, BasePosMenuX + 40 + 65 + 45 + 50, BasePosMenuY + 30, ColorWhite, shader_map_menu["white"], 3, font_map_menu[FONT_SMALL], ColorBlack, ColorRed); //Size X = 50
}

void Menu::DrawESPOptions(int BasePosX, int BasePosY,int WidthX,int LengthY)
{
	Draw::DrawRectangleFilled(BasePosX, BasePosY, WidthX, LengthY, ColorBlue);
	Draw::DrawRectangle(BasePosX, BasePosY, BasePosX + WidthX, BasePosY, BasePosX + WidthX, BasePosY + LengthY, BasePosX, BasePosY + LengthY, ColorWhite, shader_map_menu["white"], 3);

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 25 , font_map_menu[FONT_CONSOLE], ColorBlack, "Cirlces:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 25, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(ESP::CircleESPEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 45, font_map_menu[FONT_CONSOLE], ColorBlack, "Bones:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 45, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(ESP::BoneESPEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 65, font_map_menu[FONT_CONSOLE], ColorBlack, "Names:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 65, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(ESP::NameESPEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 85, font_map_menu[FONT_CONSOLE], ColorBlack, "Slot:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 85, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(ESP::SlotESPEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 105, font_map_menu[FONT_CONSOLE], ColorBlack, "Rank:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 105, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(ESP::RankESPEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 125, font_map_menu[FONT_CONSOLE], ColorBlack, "Distance:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 125, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(ESP::DistanceESPEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 145, font_map_menu[FONT_CONSOLE], ColorBlack, "XUID:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 145, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(ESP::XUIDESPEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 165, font_map_menu[FONT_CONSOLE], ColorBlack, "3DBox:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 165, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(ESP::ThreeDBoxESPEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 185, font_map_menu[FONT_CONSOLE], ColorBlack, "Weapons:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 185, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(ESP::WeaponESPEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 205, font_map_menu[FONT_CONSOLE], ColorBlack, "Snaplines:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 205, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(ESP::SnaplineESPEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 225, font_map_menu[FONT_CONSOLE], ColorBlack, "Shaders:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 225, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(ESP::ShaderESPEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 245, font_map_menu[FONT_CONSOLE], ColorBlack, "Visible:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 245, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(ESP::VisibleESPEnabled));
	

}

void Menu::DrawAimbotOptions(int BasePosX, int BasePosY, int WidthX, int LengthY)
{
	Draw::DrawRectangleFilled(BasePosX, BasePosY, WidthX, LengthY, ColorGreen);
	Draw::DrawRectangle(BasePosX, BasePosY, BasePosX + WidthX, BasePosY, BasePosX + WidthX, BasePosY + LengthY, BasePosX, BasePosY + LengthY, ColorWhite, shader_map_menu["white"], 3);

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 25, font_map_menu[FONT_CONSOLE], ColorBlack, "Aimbone:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 25, font_map_menu[FONT_CONSOLE], ColorBlack, Aimbot::Bones_Collection[Aimbot::AimboneID]);

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 45, font_map_menu[FONT_CONSOLE], ColorBlack, "AimField:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 45, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetAimField());

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 65, font_map_menu[FONT_CONSOLE], ColorBlack, "Min. TraceValue:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 65, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetMinTraceValue());

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 85, font_map_menu[FONT_CONSOLE], ColorBlack, "Closest Aimbot:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 85, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(Aimbot::ClosestAimbotEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 105, font_map_menu[FONT_CONSOLE], ColorBlack, "Aim Assist:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 105, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(Aimbot::AimAssistEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 125, font_map_menu[FONT_CONSOLE], ColorBlack, "Trace Aimbot:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 125, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(Aimbot::BestTraceAimbotEnabled));
}

void Menu::DrawMiscOptions(int BasePosX, int BasePosY, int WidthX, int LengthY)
{
	Draw::DrawRectangleFilled(BasePosX, BasePosY, WidthX, LengthY, ColorOrange);
	Draw::DrawRectangle(BasePosX, BasePosY, BasePosX + WidthX, BasePosY, BasePosX + WidthX, BasePosY + LengthY, BasePosX, BasePosY + LengthY, ColorWhite, shader_map_menu["white"], 3);

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 25, font_map_menu[FONT_CONSOLE], ColorBlack, "NoRecoil:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 25, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(Misc::NoRecoilEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 45, font_map_menu[FONT_CONSOLE], ColorBlack, "FullBright:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 45, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(Misc::FullBrightEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 65, font_map_menu[FONT_CONSOLE], ColorBlack, "Laser:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 65, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(Misc::LaserEnabled));
	
	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 85, font_map_menu[FONT_CONSOLE], ColorBlack, "Crosshair:");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 85, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(Misc::CrosshairEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 105, font_map_menu[FONT_CONSOLE], ColorBlack, "NoSpread(DVAR):");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 105, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(Misc::NoSpreadEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 125, font_map_menu[FONT_CONSOLE], ColorBlack, "Ingame Console");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 125, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(Misc::IngameConsoleEnabled));

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 145, font_map_menu[FONT_CONSOLE], ColorBlack, "No Gun");
	Draw::DrawTextMW3(BasePosX + 150, BasePosY + 145, font_map_menu[FONT_CONSOLE], ColorBlack, Utils::GetStateAsWord(Misc::NoGunEnabled));
}

void Menu::DrawUtilsOptions(int BasePosX, int BasePosY, int WidthX, int LengthY)
{
	Draw::DrawRectangleFilled(BasePosX, BasePosY, WidthX, LengthY, ColorRed);
	Draw::DrawRectangle(BasePosX, BasePosY, BasePosX + WidthX, BasePosY, BasePosX + WidthX, BasePosY + LengthY, BasePosX, BasePosY + LengthY, ColorWhite, shader_map_menu["white"], 3);

	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 25, font_map_menu[FONT_CONSOLE], ColorBlack, "Change Name");
	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 45, font_map_menu[FONT_CONSOLE], ColorBlack, "Unlock Classes");
	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 65, font_map_menu[FONT_CONSOLE], ColorBlack, "Force Juggernaut");
	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 85, font_map_menu[FONT_CONSOLE], ColorBlack, "Change Team");
	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 105, font_map_menu[FONT_CONSOLE], ColorBlack, "Votekick Exploit");
	//125 -> Leaving one line space
	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 145, font_map_menu[FONT_CONSOLE], ColorBlack, "User:");
	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 165, font_map_menu[FONT_CONSOLE], ColorBlack, Misc::GetPlayerName());
	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 185, font_map_menu[FONT_CONSOLE], ColorBlack, Misc::GetPlayerXUID());
	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 205, font_map_menu[FONT_CONSOLE], ColorBlack, "Server:");
	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 225, font_map_menu[FONT_CONSOLE], ColorBlack, Misc::GetServerName());
	Draw::DrawTextMW3(BasePosX + 2, BasePosY + 245, font_map_menu[FONT_CONSOLE], ColorBlack, Misc::GetServerIP());


}

void Menu::DrawCurrentOption(int BasePosX, int BasePosY, int Width)
{
	Draw::DrawShaderByName(BasePosX + Width - 20, (BasePosY + 40) + (20 * OptionNumber), 14, 14, ColorWhite, "killiconheadshot");
}

void Menu::DrawMenuWrapper()
{
	if (Enabled)
	{
		
		DrawMenu(BasePosX, BasePosY);
		if (CurrentActiveMenu ==  ESPMenuTab)
			DrawESPOptions(BasePosX, BasePosY + 30, 200, 300);
		if (CurrentActiveMenu == AimbotMenuTab)
			DrawAimbotOptions(BasePosX, BasePosY + 30, 200, 200);
		if (CurrentActiveMenu == MiscMenuTab)
			DrawMiscOptions(BasePosX, BasePosY + 30, 200, 200);
		if (CurrentActiveMenu == UtilsMenuTab)
			DrawUtilsOptions(BasePosX, BasePosY + 30, 200, 300);
		DrawCurrentOption(BasePosX, BasePosY, 200);
	}
	return;
}

void Menu::DrawTabHeader(char * TabName, int LeftUPX, int LeftUPY, int RightDownX, int RightDownY, vec4_t ColorTab, int * Shader, int Size, void * Font, vec4_t ColorText, vec4_t ColorBackground)
{
	Draw::DrawRectangleFilled(LeftUPX, LeftUPY, RightDownX - LeftUPX, RightDownY - LeftUPY, ColorBackground);
	Draw::DrawRectangle(LeftUPX, LeftUPY, RightDownX, LeftUPY, RightDownX, RightDownY, LeftUPX, RightDownY, ColorTab, Shader, Size);
	Draw::DrawTextMW3(LeftUPX + 2, RightDownY, Font, ColorText, TabName);
}

void Menu::SwitchOnOrOff(int Key)
{
	if (CurrentActiveMenu == ESPMenuTab)
	{
		switch (OptionNumber)
		{
		case 0:
			if (Key)
				ESP::CircleESPEnabled = true;
			else
				ESP::CircleESPEnabled = false;
			break;
		case 1:
			if (Key)
				ESP::BoneESPEnabled = true;
			else
				ESP::BoneESPEnabled = false;
			break;
		case 2:
			if (Key)
				ESP::NameESPEnabled = true;
			else
				ESP::NameESPEnabled = false;
			break;
		case 3:
			if (Key)
				ESP::SlotESPEnabled = true;
			else
				ESP::SlotESPEnabled = false;
			break;
		case 4:
			if (Key)
				ESP::RankESPEnabled = true;
			else
				ESP::RankESPEnabled = false;
			break;
		case 5:
			if (Key)
				ESP::DistanceESPEnabled = true;
			else
				ESP::DistanceESPEnabled = false;
			break;
		case 6:
			if (Key)
				ESP::XUIDESPEnabled = true;
			else
				ESP::XUIDESPEnabled = false;
			break;
		case 7:
			if (Key)
				ESP::ThreeDBoxESPEnabled = true;
			else
				ESP::ThreeDBoxESPEnabled = false;
			break;
		case 8:
			if (Key)
				ESP::WeaponESPEnabled = true;
			else
				ESP::WeaponESPEnabled = false;
			break;
		case 9:
			if (Key)
				ESP::SnaplineESPEnabled = true;
			else
				ESP::SnaplineESPEnabled = false;
			break;
		case 10:
			if (Key)
				ESP::ShaderESPEnabled = true;
			else
				ESP::ShaderESPEnabled = false;
			break;
		case 11:
			if (Key)
				ESP::VisibleESPEnabled = true;
			else
				ESP::VisibleESPEnabled = false;
			break;
		default:
			Engine.MessageGiver_(0, "Error in ESPMenu OnOrOff Switch");
			break;
		}
	}
	if (CurrentActiveMenu == AimbotMenuTab)
	{
		switch (OptionNumber)
		{
		case 0:
			if (Key)
			{
				if (Aimbot::AimboneID != 16)
					Aimbot::AimboneID++;
				else
					Aimbot::AimboneID = 0;
				Sleep(500);
			}
			else
			{
				if (Aimbot::AimboneID != 0)
					Aimbot::AimboneID--;
				else
					Aimbot::AimboneID = 16;
				Sleep(500);
			}
			break;
		case 1:
			if (Key)
			{
				Aimbot::FieldOfAim++;
				Sleep(100);
			}
			else
			{
				Aimbot::FieldOfAim--;
				Sleep(100);
			}
			break;
		case 2:
			if (Key)
			{
				Aimbot::MinTraceValue = Aimbot::MinTraceValue + 0.01f;
				Sleep(100);
			}
			else
			{
				Aimbot::MinTraceValue = Aimbot::MinTraceValue - 0.01f;
				Sleep(100);
			}
			break;
		case 3:
			if (Key)
			{
				Aimbot::AimAssistEnabled = false;
				Aimbot::BestTraceAimbotEnabled = false;
				Aimbot::ClosestAimbotEnabled = true;
			}
			else
			{
				Aimbot::ClosestAimbotEnabled = false;
			}
			break;
		case 4:
			if (Key)
			{
				Aimbot::ClosestAimbotEnabled = false;
				Aimbot::BestTraceAimbotEnabled = false;
				Aimbot::AimAssistEnabled = true;
			}
			else
			{
				Aimbot::AimAssistEnabled = false;
			}
			break;
		case 5:
			if (Key)
			{
				Aimbot::AimAssistEnabled = false;
				Aimbot::ClosestAimbotEnabled = false;
				Aimbot::BestTraceAimbotEnabled = true;
			}
			else
			{
				Aimbot::BestTraceAimbotEnabled = false;
			}
			break;
		default:
			Engine.MessageGiver_(0, "Error in AimbotMenu OnOrOff Switch");
			break;
		}
	}
	if (CurrentActiveMenu == MiscMenuTab)
	{
		switch (OptionNumber)
		{
		case 0:
			if (Key)
			{
				Misc::NoRecoilEnabled = true;
				Misc::NoRecoil();
			}
			else
			{
				Misc::NoRecoilEnabled = false;
				Misc::NoRecoil();
			}
			break;
		case 1:
			if (Key)
			{
				Misc::FullBrightEnabled = true;
				Misc::FullBright();
			}
			else
			{
				Misc::FullBrightEnabled = false;
				Misc::FullBright();
			}
			break;
		case 2:
			if (Key)
			{
				Misc::LaserEnabled = true;
				Misc::Laser();
			}
			else
			{
				Misc::LaserEnabled = false;
				Misc::Laser();
			}
			break;
		case 3:
			if (Key)
			{
				Misc::CrosshairEnabled = true;
			}
			else
			{
				Misc::CrosshairEnabled = false;
			}
			break;
		case 4:
			if (Key)
			{
				Misc::NoSpreadEnabled = true;
				Misc::NoSpread();
			}
			else
			{
				Misc::NoSpreadEnabled = false;
				Misc::NoSpread();
			}
			break;
		case 5:
			if (Key)
			{
				Misc::IngameConsoleEnabled = true;
				Sleep(100);
			}
			else
			{
				Misc::IngameConsoleEnabled = false;
			}
			break;
		case 6:
			if (Key)
			{
				Misc::NoGunEnabled = true;
				Misc::NoGun();
			}
			else
			{
				Misc::NoGunEnabled = false;
				Misc::NoGun();
			}
			break;
		default:
			Engine.MessageGiver_(0, "Error in MiscMenu OnOrOff Switch");
			break;
		}
	}
	if (CurrentActiveMenu == UtilsMenuTab)
	{
		switch (OptionNumber)
		{
		case 0:
			if (Key)
				Misc::ChangeName();
			break;
		case 1:
			if (Key)
				Misc::UnlockClasses();
			break;
		case 2:
			if (Key)
				Misc::ForceJugg();
			Sleep(500);
			break;
		case 3:
			if (Key)
				Misc::ChangeTeam();
			Sleep(500);
			break;
		case 4:
			if (Key)
				Misc::VoteKickPlayerExploit();
			Sleep(500);
			break;
		default:
			Engine.MessageGiver_(0, "Error in UtilsMenu OnOrOff Switch");
			break;
		}
	}
}