#include "weapon.h"

#include "../../gui/gui.h"

#include "../../gui/menu.h"

#include <locale>
#include <codecvt>
#include <iostream>

#define deagle u8"\uE001"
#define elite u8"\uE002"
#define fiveseven u8"\uE003"
#define glock u8"\uE004"
#define ak47 u8"\uE007"
#define aug u8"\uE008"
#define awp u8"\uE009"
#define famas u8"\uE00a"
#define g3sg1 u8"\uE00b"
#define galilar u8"\uE00d"
#define m249 u8"\uE03c"
#define m4a1 u8"\uE00e"
#define mac10 u8"\uE011"
#define p90 u8"\uE024"
#define mp5sd u8"mp5sd"
#define ump45 u8"\uE018"
#define xm1014 u8"\uE019"
#define bizon u8"\uE01a"
#define mag7 u8"\uE01b"
#define negev u8"\uE01c"
#define sawedoff u8"\uE01d"
#define tec9 u8"\uE01e"
#define taser u8"\uE01f"
#define hkp2000 u8"\uE013"
#define mp7 u8"\uE021"
#define mp9 u8"\uE022"
#define nova u8"\uE023"
#define p250 u8"\uE020"
#define shield u8"shield"
#define scar20 u8"\uE026"
#define sg556 u8"\uE027"
#define ssg08 u8"\uE028"
#define knife_gg u8"knife_gg"
#define knife u8"\uE02a"
#define flashbang u8"\uE02b"
#define hegrenade u8"\uE02c"
#define smokegrenade u8"\uE02d"
#define molotov u8"\uE02e"
#define decoy u8"\uE02f"
#define incgrenade u8"\uE030"
#define c4 u8"\uE031"
#define knife_t u8"\uE03b"
#define m4a1_silencer u8"\uE010"
#define usp_silencer u8"\uE03d"
#define cz75a u8"\uE03f"
#define revolver u8"\uE040"
#define knife_bayonet u8"\uE1f4"
#define knife_css u8"\uE02a"
#define knife_flip u8"\uE1f9"
#define knife_gut u8"\uE1fa"
#define knife_karambit u8"\uE1fb"
#define knife_m9_bayonet u8"\uE1fc"
#define knife_tactical u8"\uE1fd"
#define knife_falchion u8"\uE200"
#define knife_survival_bowie u8"\uE202"
#define knife_butterfly u8"\uE203"
#define knife_push u8"\uE204"
#define knife_cord u8"\uE02a"
#define knife_canis u8"\uE02a"
#define knife_ursus u8"\uE02a"
#define knife_gypsy_jackknife u8"\uE02a"
#define knife_outdoor u8"\uE02a"
#define knife_stiletto u8"\uE02a"
#define knife_widowmaker u8"\uE02a"
#define knife_skeleton u8"\uE02a"

void weapon::DrawWeaponName(const std::string& weaponName, const Vector3& screenPos)
{
	if (weaponName.empty())
		return;

	if (screenPos.x <= 0 || screenPos.y <= 0)
		return;

    ImVec2 icon_size;
	ImVec2 actualPos;

    ImGui::PushFont(font::weapons);

    switch (HashString(weaponName.c_str())) {
    case WEAPON_DEAGLE:
        icon_size = ImGui::CalcTextSize((const char*)deagle);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)deagle);
        break;

    case WEAPON_ELITE:
        icon_size = ImGui::CalcTextSize((const char*)elite);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)elite);
        break;

    case WEAPON_FIVESEVEN:
        icon_size = ImGui::CalcTextSize((const char*)fiveseven);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)fiveseven);
        break;

    case WEAPON_GLOCK:
        icon_size = ImGui::CalcTextSize((const char*)glock);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)glock);
        break;

    case WEAPON_AK47:
        icon_size = ImGui::CalcTextSize((const char*)ak47);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)ak47);
        break;

    case WEAPON_AUG:
        icon_size = ImGui::CalcTextSize((const char*)aug);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)aug);
        break;

    case WEAPON_AWP:
        icon_size = ImGui::CalcTextSize((const char*)awp);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)awp);
        break;

    case WEAPON_FAMAS:
        icon_size = ImGui::CalcTextSize((const char*)famas);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)famas);
        break;

    case WEAPON_G3SG1:
        icon_size = ImGui::CalcTextSize((const char*)g3sg1);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)g3sg1);
        break;

    case WEAPON_GALILAR:
        icon_size = ImGui::CalcTextSize((const char*)galilar);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)galilar);
        break;

    case WEAPON_M249:
        icon_size = ImGui::CalcTextSize((const char*)m249);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)m249);
        break;

    case WEAPON_M4A1:
        icon_size = ImGui::CalcTextSize((const char*)m4a1);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)m4a1);
        break;

    case WEAPON_MAC10:
        icon_size = ImGui::CalcTextSize((const char*)mac10);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)mac10);
        break;

    case WEAPON_P90:
        icon_size = ImGui::CalcTextSize((const char*)p90);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)p90);
        break;

    case WEAPON_MP5SD:
        icon_size = ImGui::CalcTextSize((const char*)mp5sd);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)mp5sd);
        break;

    case WEAPON_UMP45:
        icon_size = ImGui::CalcTextSize((const char*)ump45);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)ump45);
        break;

    case WEAPON_XM1014:
        icon_size = ImGui::CalcTextSize((const char*)xm1014);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)xm1014);
        break;

    case WEAPON_BIZON:
        icon_size = ImGui::CalcTextSize((const char*)bizon);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)bizon);
        break;

    case WEAPON_MAG7:
        icon_size = ImGui::CalcTextSize((const char*)mag7);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)mag7);
        break;

    case WEAPON_NEGEV:
        icon_size = ImGui::CalcTextSize((const char*)negev);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)negev);
        break;

    case WEAPON_SAWEDOFF:
        icon_size = ImGui::CalcTextSize((const char*)sawedoff);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)sawedoff);
        break;

    case WEAPON_TEC9:
        icon_size = ImGui::CalcTextSize((const char*)tec9);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)tec9);
        break;

    case WEAPON_TASER:
        icon_size = ImGui::CalcTextSize((const char*)taser);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)taser);
        break;

    case WEAPON_HKP2000:
        icon_size = ImGui::CalcTextSize((const char*)hkp2000);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)hkp2000);
        break;

    case WEAPON_MP7:
        icon_size = ImGui::CalcTextSize((const char*)mp7);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)mp7);
        break;

    case WEAPON_MP9:
        icon_size = ImGui::CalcTextSize((const char*)mp9);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)mp9);
        break;

    case WEAPON_NOVA:
        icon_size = ImGui::CalcTextSize((const char*)nova);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)nova);
        break;

    case WEAPON_P250:
        icon_size = ImGui::CalcTextSize((const char*)p250);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)p250);
        break;

    case WEAPON_SHIELD:
        icon_size = ImGui::CalcTextSize((const char*)shield);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)shield);
        break;

    case WEAPON_SCAR20:
        icon_size = ImGui::CalcTextSize((const char*)scar20);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)scar20);
        break;

    case WEAPON_SG556:
        icon_size = ImGui::CalcTextSize((const char*)sg556);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)sg556);
        break;

    case WEAPON_SSG08:
        icon_size = ImGui::CalcTextSize((const char*)ssg08);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)ssg08);
        break;

    case WEAPON_KNIFE_GG:
        icon_size = ImGui::CalcTextSize((const char*)knife_gg);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_gg);
        break;

    case WEAPON_KNIFE:
        icon_size = ImGui::CalcTextSize((const char*)knife);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife);
        break;

    case WEAPON_FLASHBANG:
        icon_size = ImGui::CalcTextSize((const char*)flashbang);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)flashbang);
        break;

    case WEAPON_HEGRENADE:
        icon_size = ImGui::CalcTextSize((const char*)hegrenade);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)hegrenade);
        break;

    case WEAPON_SMOKEGRENADE:
        icon_size = ImGui::CalcTextSize((const char*)smokegrenade);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)smokegrenade);
        break;

    case WEAPON_MOLOTOV:
        icon_size = ImGui::CalcTextSize((const char*)molotov);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)molotov);
        break;

    case WEAPON_INCGRENADE:
        icon_size = ImGui::CalcTextSize((const char*)incgrenade);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)incgrenade);
        break;

    case WEAPON_DECOY:
        icon_size = ImGui::CalcTextSize((const char*)decoy);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)decoy);
        break;

    case WEAPON_C4:
        icon_size = ImGui::CalcTextSize((const char*)c4);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)c4);
        break;

    case WEAPON_KNIFE_T:
        icon_size = ImGui::CalcTextSize((const char*)knife_t);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_t);
        break;

    case WEAPON_KNIFE_BAYONET:
        icon_size = ImGui::CalcTextSize((const char*)knife_bayonet);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_bayonet);
        break;

    case WEAPON_KNIFE_CSS:
        icon_size = ImGui::CalcTextSize((const char*)knife_css);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_css);
        break;

    case WEAPON_KNIFE_FLIP:
        icon_size = ImGui::CalcTextSize((const char*)knife_flip);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_flip);
        break;

    case WEAPON_KNIFE_GUT:
        icon_size = ImGui::CalcTextSize((const char*)knife_gut);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_gut);
        break;

    case WEAPON_KNIFE_KARAMBIT:
        icon_size = ImGui::CalcTextSize((const char*)knife_karambit);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_karambit);
        break;

    case WEAPON_KNIFE_M9_BAYONET:
        icon_size = ImGui::CalcTextSize((const char*)knife_m9_bayonet);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_m9_bayonet);
        break;

    case WEAPON_KNIFE_TACTICAL:
        icon_size = ImGui::CalcTextSize((const char*)knife_tactical);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_tactical);
        break;

    case WEAPON_KNIFE_FALCHION:
        icon_size = ImGui::CalcTextSize((const char*)knife_falchion);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_falchion);
        break;

    case WEAPON_KNIFE_SURVIVAL_BOWIE:
        icon_size = ImGui::CalcTextSize((const char*)knife_survival_bowie);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_survival_bowie);
        break;

    case WEAPON_KNIFE_BUTTERFLY:
        icon_size = ImGui::CalcTextSize((const char*)knife_butterfly);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_butterfly);
        break;

    case WEAPON_KNIFE_PUSH:
        icon_size = ImGui::CalcTextSize((const char*)knife_push);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_push);
        break;

    case WEAPON_KNIFE_CORD:
        icon_size = ImGui::CalcTextSize((const char*)knife_cord);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_cord);
        break;

    case WEAPON_KNIFE_CANIS:
        icon_size = ImGui::CalcTextSize((const char*)knife_canis);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_canis);
        break;

    case WEAPON_KNIFE_URSUS:
        icon_size = ImGui::CalcTextSize((const char*)knife_ursus);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_ursus);
        break;

    case WEAPON_KNIFE_GYPSY_JACKKNIFE:
        icon_size = ImGui::CalcTextSize((const char*)knife_gypsy_jackknife);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_gypsy_jackknife);
        break;

    case WEAPON_KNIFE_OUTDOOR:
        icon_size = ImGui::CalcTextSize((const char*)knife_outdoor);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_outdoor);
        break;

    case WEAPON_KNIFE_STILETTO:
        icon_size = ImGui::CalcTextSize((const char*)knife_stiletto);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_stiletto);
        break;

    case WEAPON_KNIFE_WIDOWMAKER:
        icon_size = ImGui::CalcTextSize((const char*)knife_widowmaker);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_widowmaker);
        break;

    case WEAPON_KNIFE_SKELETON:
        icon_size = ImGui::CalcTextSize((const char*)knife_skeleton);
        actualPos = { screenPos.x - (icon_size.x / 2), screenPos.y + 5 };
        gui::drawList->AddText(actualPos, ImColor(settings::esp::weapon_color[0], settings::esp::weapon_color[1], settings::esp::weapon_color[2], settings::esp::weapon_color[3]), (const char*)knife_skeleton);
        break;

    default:
        break;
    }

	ImGui::PopFont();
}