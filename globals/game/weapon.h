#pragma once
#include <map>
#include <string>
#include "../../../external/imgui/imgui.h"

#include "../math.h"

/*enum WeaponHashes {
    WEAPON_DEAGLE = HashString("deagle"),
    WEAPON_ELITE = HashString("elite"),
    WEAPON_FIVESEVEN = HashString("fiveseven"),
    WEAPON_GLOCK = HashString("glock"),
    WEAPON_AK47 = HashString("ak47"),
    WEAPON_AUG = HashString("aug"),
    WEAPON_AWP = HashString("awp"),
    WEAPON_FAMAS = HashString("famas"),
    WEAPON_G3SG1 = HashString("g3sg1"),
    WEAPON_GALILAR = HashString("galilar"),
    WEAPON_M249 = HashString("m249"),
    WEAPON_M4A1 = HashString("m4a1"),
    WEAPON_MAC10 = HashString("mac10"),
    WEAPON_P90 = HashString("p90"),
    WEAPON_MP5SD = HashString("mp5sd"),
    WEAPON_UMP45 = HashString("ump45"),
    WEAPON_XM1014 = HashString("xm1014"),
    WEAPON_BIZON = HashString("bizon"),
    WEAPON_MAG7 = HashString("mag7"),
    WEAPON_NEGEV = HashString("negev"),
    WEAPON_SAWEDOFF = HashString("sawedoff"),
    WEAPON_TEC9 = HashString("tec9"),
    WEAPON_TASER = HashString("taser"),
    WEAPON_HKP2000 = HashString("hkp2000"),
    WEAPON_MP7 = HashString("mp7"),
    WEAPON_MP9 = HashString("mp9"),
    WEAPON_NOVA = HashString("nova"),
    WEAPON_P250 = HashString("p250"),
    WEAPON_SHIELD = HashString("shield"),
    WEAPON_SCAR20 = HashString("scar20"),
    WEAPON_SG556 = HashString("sg556"),
    WEAPON_SSG08 = HashString("ssg08"),
    WEAPON_KNIFE_GG = HashString("knife_gg"),
    WEAPON_KNIFE = HashString("knife"),
    WEAPON_FLASHBANG = HashString("flashbang"),
    WEAPON_HEGRENADE = HashString("hegrenade"),
    WEAPON_SMOKEGRENADE = HashString("smokegrenade"),
    WEAPON_MOLOTOV = HashString("molotov"),
    WEAPON_DECOY = HashString("decoy"),
    WEAPON_INCGRENADE = HashString("incgrenade"),
    WEAPON_C4 = HashString("c4"),
    WEAPON_KNIFE_T = HashString("knife_t"),
    WEAPON_M4A1_SILENCER = HashString("m4a1_silencer"),
    WEAPON_USP_SILENCER = HashString("usp_silencer"),
    WEAPON_CZ75A = HashString("cz75a"),
    WEAPON_REVOLVER = HashString("revolver"),
    WEAPON_KNIFE_BAYONET = HashString("knife_bayonet"),
    WEAPON_KNIFE_CSS = HashString("knife_css"),
    WEAPON_KNIFE_FLIP = HashString("knife_flip"),
    WEAPON_KNIFE_GUT = HashString("knife_gut"),
    WEAPON_KNIFE_KARAMBIT = HashString("knife_karambit"),
    WEAPON_KNIFE_M9_BAYONET = HashString("knife_m9_bayonet"),
    WEAPON_KNIFE_TACTICAL = HashString("knife_tactical"),
    WEAPON_KNIFE_FALCHION = HashString("knife_falchion"),
    WEAPON_KNIFE_SURVIVAL_BOWIE = HashString("knife_survival_bowie"),
    WEAPON_KNIFE_BUTTERFLY = HashString("knife_butterfly"),
    WEAPON_KNIFE_PUSH = HashString("knife_push"),
    WEAPON_KNIFE_CORD = HashString("knife_cord"),
    WEAPON_KNIFE_CANIS = HashString("knife_canis"),
    WEAPON_KNIFE_URSUS = HashString("knife_ursus"),
    WEAPON_KNIFE_GYPSY_JACKKNIFE = HashString("knife_gypsy_jackknife"),
    WEAPON_KNIFE_OUTDOOR = HashString("knife_outdoor"),
    WEAPON_KNIFE_STILETTO = HashString("knife_stiletto"),
    WEAPON_KNIFE_WIDOWMAKER = HashString("knife_widowmaker"),
    WEAPON_KNIFE_SKELETON = HashString("knife_skeleton")
};*/

enum WeaponHashes {
    WEAPON_DEAGLE = HashString("weapon_deagle"),
    WEAPON_ELITE = HashString("weapon_elite"),
    WEAPON_FIVESEVEN = HashString("weapon_fiveseven"),
    WEAPON_GLOCK = HashString("weapon_glock"),
    WEAPON_AK47 = HashString("weapon_ak47"),
    WEAPON_AUG = HashString("weapon_aug"),
    WEAPON_AWP = HashString("weapon_awp"),
    WEAPON_FAMAS = HashString("weapon_famas"),
    WEAPON_G3SG1 = HashString("weapon_g3sg1"),
    WEAPON_GALILAR = HashString("weapon_galilar"),
    WEAPON_M249 = HashString("weapon_m249"),
    WEAPON_M4A1 = HashString("weapon_m4a1"),
    WEAPON_MAC10 = HashString("weapon_mac10"),
    WEAPON_P90 = HashString("weapon_p90"),
    WEAPON_MP5SD = HashString("weapon_mp5sd"),
    WEAPON_UMP45 = HashString("weapon_ump45"),
    WEAPON_XM1014 = HashString("weapon_xm1014"),
    WEAPON_BIZON = HashString("weapon_bizon"),
    WEAPON_MAG7 = HashString("weapon_mag7"),
    WEAPON_NEGEV = HashString("weapon_negev"),
    WEAPON_SAWEDOFF = HashString("weapon_sawedoff"),
    WEAPON_TEC9 = HashString("weapon_tec9"),
    WEAPON_TASER = HashString("weapon_taser"),
    WEAPON_HKP2000 = HashString("weapon_hkp2000"),
    WEAPON_MP7 = HashString("weapon_mp7"),
    WEAPON_MP9 = HashString("weapon_mp9"),
    WEAPON_NOVA = HashString("weapon_nova"),
    WEAPON_P250 = HashString("weapon_p250"),
    WEAPON_SHIELD = HashString("weapon_shield"),
    WEAPON_SCAR20 = HashString("weapon_scar20"),
    WEAPON_SG556 = HashString("weapon_sg556"),
    WEAPON_SSG08 = HashString("weapon_ssg08"),
    WEAPON_KNIFE_GG = HashString("weapon_knife_gg"),
    WEAPON_KNIFE = HashString("weapon_knife"),
    WEAPON_FLASHBANG = HashString("weapon_flashbang"),
    WEAPON_HEGRENADE = HashString("weapon_hegrenade"),
    WEAPON_SMOKEGRENADE = HashString("weapon_smokegrenade"),
    WEAPON_MOLOTOV = HashString("weapon_molotov"),
    WEAPON_DECOY = HashString("weapon_decoy"),
    WEAPON_INCGRENADE = HashString("weapon_incgrenade"),
    WEAPON_C4 = HashString("weapon_c4"),
    WEAPON_KNIFE_T = HashString("weapon_knife_t"),
    WEAPON_M4A1_SILENCER = HashString("weapon_m4a1_silencer"),
    WEAPON_USP_SILENCER = HashString("weapon_usp_silencer"),
    WEAPON_CZ75A = HashString("weapon_cz75a"),
    WEAPON_REVOLVER = HashString("weapon_revolver"),
    WEAPON_KNIFE_BAYONET = HashString("weapon_knife_bayonet"),
    WEAPON_KNIFE_CSS = HashString("weapon_knife_css"),
    WEAPON_KNIFE_FLIP = HashString("weapon_knife_flip"),
    WEAPON_KNIFE_GUT = HashString("weapon_knife_gut"),
    WEAPON_KNIFE_KARAMBIT = HashString("weapon_knife_karambit"),
    WEAPON_KNIFE_M9_BAYONET = HashString("weapon_knife_m9_bayonet"),
    WEAPON_KNIFE_TACTICAL = HashString("weapon_knife_tactical"),
    WEAPON_KNIFE_FALCHION = HashString("weapon_knife_falchion"),
    WEAPON_KNIFE_SURVIVAL_BOWIE = HashString("weapon_knife_survival_bowie"),
    WEAPON_KNIFE_BUTTERFLY = HashString("weapon_knife_butterfly"),
    WEAPON_KNIFE_PUSH = HashString("weapon_knife_push"),
    WEAPON_KNIFE_CORD = HashString("weapon_knife_cord"),
    WEAPON_KNIFE_CANIS = HashString("weapon_knife_canis"),
    WEAPON_KNIFE_URSUS = HashString("weapon_knife_ursus"),
    WEAPON_KNIFE_GYPSY_JACKKNIFE = HashString("weapon_knife_gypsy_jackknife"),
    WEAPON_KNIFE_OUTDOOR = HashString("weapon_knife_outdoor"),
    WEAPON_KNIFE_STILETTO = HashString("weapon_knife_stiletto"),
    WEAPON_KNIFE_WIDOWMAKER = HashString("weapon_knife_widowmaker"),
    WEAPON_KNIFE_SKELETON = HashString("weapon_knife_skeleton")
};

// Convert UTF-8 std::string to UTF-16 std::wstring
inline std::wstring StringToWString(const std::string& str) {
    // Convert UTF-8 to UTF-16 (std::wstring)
    std::wstring wstr;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        char16_t ch = *it;
        if (ch >= 0x80) {
            if (ch >= 0x800) {
                wstr.push_back(((ch >> 12) & 0x0F) | 0xE0);
                wstr.push_back(((ch >> 6) & 0x3F) | 0x80);
                wstr.push_back((ch & 0x3F) | 0x80);
            }
            else {
                wstr.push_back(((ch >> 6) & 0x1F) | 0xC0);
                wstr.push_back((ch & 0x3F) | 0x80);
            }
        }
        else {
            wstr.push_back(ch);
        }
    }
    return wstr;
}

// Convert UTF-16 std::wstring to UTF-8 std::string
inline std::string WStringToString(const std::wstring& wstr) {
    // Convert UTF-16 std::wstring to UTF-8 std::string
    std::string str;
    for (std::wstring::const_iterator it = wstr.begin(); it != wstr.end(); ++it) {
        char16_t ch = *it;
        if (ch >= 0x800) {
            str.push_back(((ch >> 12) & 0x0F) | 0xE0);
            str.push_back(((ch >> 6) & 0x3F) | 0x80);
            str.push_back((ch & 0x3F) | 0x80);
        }
        else if (ch >= 0x80) {
            str.push_back(((ch >> 6) & 0x1F) | 0xC0);
            str.push_back((ch & 0x3F) | 0x80);
        }
        else {
            str.push_back(ch);
        }
    }
    return str;
}

namespace weapon
{
    void DrawWeaponName(const std::string& weaponName, const Vector3& screenPos);
}

