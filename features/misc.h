#pragma once
#include <Windows.h>
#include <string>
#include <ShlObj.h>    // For SHGetFolderPath
#include <Urlmon.h>    // For URLDownloadToFile
#pragma comment(lib, "Urlmon.lib") // Link to the Urlmon library

#include "../globals/offsets.h"

void run_hitsound();
void download_hitsound();


#pragma pack(push, 1) // Ensure there is no extra padding between fields, push 1
/*struct C4_Info
{
	char padding_001[off::C_PlantedC4::m_nBombSite];
	int32_t m_nBombSite{ 0 };
	char padding_002[off::C_PlantedC4::m_flC4Blow - off::C_PlantedC4::m_nBombSite - sizeof(m_nBombSite)];
	float m_flC4Blow{ 0 };
	char padding_003[off::C_PlantedC4::m_bBeingDefused - off::C_PlantedC4::m_flC4Blow - sizeof(m_flC4Blow)];
	bool m_bBeingDefused{ };
	char padding_004[off::C_PlantedC4::m_bC4Activated - off::C_PlantedC4::m_bBeingDefused - sizeof(m_bBeingDefused)];
	bool m_bC4Activated{ };
};*/
#pragma pack(pop)

void c4_planted();