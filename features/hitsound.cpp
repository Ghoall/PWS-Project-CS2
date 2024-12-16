#include "hitsound.h"
#include "../globals/sounds.h"
#include "../driver/driver.h"
#include "../globals/offsets.h"
#include "../gui/settings.h"

#include <Windows.h>
#include <string>
#include <ShlObj.h>    // For SHGetFolderPath
#include <Urlmon.h>    // For URLDownloadToFile
#pragma comment(lib, "Urlmon.lib") // Link to the Urlmon library

int previous_hits = 0;

void play_sound(int32_t hits)
{
	if (hits != previous_hits) {
		if (hits == 0 && previous_hits == 0) {
			//nothing
		}
		else 
		{
			switch (settings::misc::hitsound)
			{
			case 1:
				PlaySoundA(reinterpret_cast<char*>(neverlose_sound), NULL, SND_ASYNC | SND_MEMORY);
				break;
			case 2:
				PlaySoundA(reinterpret_cast<char*>(skeet_sound), NULL, SND_ASYNC | SND_MEMORY);
				break;
			default:
				break;
			}
		}
	}
	previous_hits = hits;
}