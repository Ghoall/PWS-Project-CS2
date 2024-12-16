#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>  // For std::ifstream
#include "../../external/json.hpp"
#include "settings.h"

namespace config
{
	std::string path = "C://cfg";

	std::vector<std::string> list;

	uint32_t selected_cfg = 0;

	template<typename Type>
	void try_val(nlohmann::ordered_json& j, std::string name, Type& _value) {
		if (name.empty())
			return;

		if (j.dump().find(name) == std::string::npos)
			return;

		j.at(name).get_to(_value);
	}

	bool refresh()
	{
		if (!std::filesystem::exists(path))
			std::filesystem::create_directory(path);

		list.clear();
		selected_cfg = 0;

		for (auto file : std::filesystem::directory_iterator(path))
		{
			std::string f_name = file.path().filename().string();

			if (size_t location = f_name.find(".json"); location != std::string::npos)
				f_name.replace(f_name.begin() + location, f_name.end(), "");

			if (!f_name.empty())
				list.push_back(f_name);

			printf("%s\n", f_name.c_str());
		}

		return true;
	}

	bool load(std::string name)
	{
		if (name.empty())
			return false;

		auto _path = std::string(path) + "\\" + name + ".json";

		if (!std::filesystem::exists(_path))
			return false;

		std::ifstream read_stream(_path);
		nlohmann::ordered_json j = nlohmann::ordered_json::parse(read_stream, 0, false);

		try_val(j, "cornerbox_color_r", settings::esp::cornerbox_color_r);
		try_val(j, "cornerbox_color_g", settings::esp::cornerbox_color_g);
		try_val(j, "cornerbox_color_b", settings::esp::cornerbox_color_b);
		try_val(j, "cornerbox_color_a", settings::esp::cornerbox_color_a);
		try_val(j, "snaplines_color_r", settings::esp::snaplines_color_r);
		try_val(j, "snaplines_color_g", settings::esp::snaplines_color_g);
		try_val(j, "snaplines_color_b", settings::esp::snaplines_color_b);
		try_val(j, "snaplines_color_a", settings::esp::snaplines_color_a);
		try_val(j, "skeleton_color_r", settings::esp::skeleton_color[0]);
		try_val(j, "skeleton_color_g", settings::esp::skeleton_color[1]);
		try_val(j, "skeleton_color_b", settings::esp::skeleton_color[2]);
		try_val(j, "skeleton_color_a", settings::esp::skeleton_color[3]);
		try_val(j, "fillbox_color_r", settings::esp::fillbox_color_r);
		try_val(j, "fillbox_color_g", settings::esp::fillbox_color_g);
		try_val(j, "fillbox_color_b", settings::esp::fillbox_color_b);
		try_val(j, "fillbox_color_a", settings::esp::fillbox_color_a);
		try_val(j, "fov_color_r", settings::aimbot::fov_color_r);
		try_val(j, "fov_color_g", settings::aimbot::fov_color_g);
		try_val(j, "fov_color_b", settings::aimbot::fov_color_b);
		try_val(j, "fov_color_a", settings::aimbot::fov_color_a);
		try_val(j, "bEspSwitch", settings::esp::bEspSwitch);
		try_val(j, "bBox", settings::esp::bBox);
		try_val(j, "bCornerBox", settings::esp::bCornerBox);
		try_val(j, "bSnapLines", settings::esp::bSnapLines);
		try_val(j, "bSkeleton", settings::esp::bSkeleton);
		try_val(j, "bFillBox", settings::esp::bFillBox);
		try_val(j, "bNames", settings::esp::bNames);
		try_val(j, "bAimbotSwitch", settings::aimbot::bAimbotSwitch);
		try_val(j, "bAimbot", settings::aimbot::bAimbot);
		try_val(j, "smoothing", settings::aimbot::smoothing);
		try_val(j, "bFov", settings::aimbot::bFov);
		try_val(j, "fovSize", settings::aimbot::fovSize);
		try_val(j, "bTrigger", settings::triggerbot::bTrigger);
		try_val(j, "triggerbot_trigger_delay", settings::triggerbot::trigger_delay);
		try_val(j, "misc_hitsound", settings::misc::hitsound);
		read_stream.close();

		config::refresh();

		//try_val(j, "bWeapon", settings::esp::bWeapon);
		//try_val(j, "weapon_color", settings::esp::weapon_color);
		//try_val(j, "bAmmo", settings::esp::bAmmo);

		return true;
	}

	bool save(std::string name)
	{
		if (name.empty())
			return false;

		auto _path = std::string(path) + "\\" + name + ".json";
		// Create the JSON object and serialize all the values, including the color arrays
		nlohmann::ordered_json j = nlohmann::ordered_json
		{
{"bEspSwitch", settings::esp::bEspSwitch},
{"bBox", settings::esp::bBox},
{"bCornerBox", settings::esp::bCornerBox},
{"cornerbox_color_r", settings::esp::cornerbox_color_r},
{"cornerbox_color_g", settings::esp::cornerbox_color_g},
{"cornerbox_color_b", settings::esp::cornerbox_color_b},
{"cornerbox_color_a", settings::esp::cornerbox_color_a},
{"bSnapLines", settings::esp::bSnapLines},
{"snaplines_color_r", settings::esp::snaplines_color_r},
{"snaplines_color_g", settings::esp::snaplines_color_g},
{"snaplines_color_b", settings::esp::snaplines_color_b},
{"snaplines_color_a", settings::esp::snaplines_color_a},
{"bSkeleton", settings::esp::bSkeleton},
{"skeleton_color_r", settings::esp::skeleton_color[0]},
{"skeleton_color_g", settings::esp::skeleton_color[1]},
{"skeleton_color_b", settings::esp::skeleton_color[2]},
{"skeleton_color_a", settings::esp::skeleton_color[3]},
{"bFillBox", settings::esp::bFillBox},
{"fillbox_color_r", settings::esp::fillbox_color_r},
{"fillbox_color_g", settings::esp::fillbox_color_g},
{"fillbox_color_b", settings::esp::fillbox_color_b},
{"fillbox_color_a", settings::esp::fillbox_color_a},
{"bNames", settings::esp::bNames},
{"bAimbotSwitch", settings::aimbot::bAimbotSwitch},
{"bAimbot", settings::aimbot::bAimbot},
{"smoothing", settings::aimbot::smoothing},
{"bFov", settings::aimbot::bFov},
{"fov_color_r", settings::aimbot::fov_color_r},
{"fov_color_g", settings::aimbot::fov_color_g},
{"fov_color_b", settings::aimbot::fov_color_b},
{"fov_color_a", settings::aimbot::fov_color_a},
{"fovSize", settings::aimbot::fovSize},
{"bTrigger", settings::triggerbot::bTrigger},
{"triggerbot_trigger_delay", settings::triggerbot::trigger_delay},
{"misc_hitsound", settings::misc::hitsound}
		};

		std::ofstream output(_path);
		output << j.dump(4);
		output.close();

		if (!std::filesystem::exists(_path))
			return false;

		config::refresh();

		return true;
	}

	bool remove(std::string name)
	{
		if (name.empty())
			return false;

		auto _path = std::string(path) + "\\" + name + ".json";
		if (!std::filesystem::exists(_path))
			return false;

		std::filesystem::remove(_path);
		config::refresh();

		return true;
	}
}

#include <unordered_map>

// Function to initialize the ASCII to VK map
inline std::unordered_map<int, int> createAsciiToVKMap() {
	 std::unordered_map<int, int> asciiToVK;

	// Mouse Buttons
	asciiToVK[1] = 0x01;   // Left mouse button
	asciiToVK[2] = 0x02;   // Right mouse button
	asciiToVK[3] = 0x03;   // Middle mouse button (scroll wheel)
	asciiToVK[4] = 0x04;   // Mouse button 4
	asciiToVK[5] = 0x05;   // Mouse button 5
	asciiToVK[6] = 0x06;   // Mouse button 6
	asciiToVK[7] = 0x07;   // Mouse button 7
	asciiToVK[8] = 0x08;   // Mouse button 8

	// Function Keys
	asciiToVK['F1'] = 0x70;
	asciiToVK['F2'] = 0x71;
	asciiToVK['F3'] = 0x72;
	asciiToVK['F4'] = 0x73;
	asciiToVK['F5'] = 0x74;
	asciiToVK['F6'] = 0x75;
	asciiToVK['F7'] = 0x76;
	asciiToVK['F8'] = 0x77;
	asciiToVK['F9'] = 0x78;
	asciiToVK['F10'] = 0x79;
	asciiToVK['F11'] = 0x7A;
	asciiToVK['F12'] = 0x7B;

	// Number Keys
	for (int i = 0; i <= 9; ++i) {
		asciiToVK['0' + i] = 0x30 + i; // '0' to '9'
	}

	// Alphabet Keys
	for (char c = 'A'; c <= 'Z'; ++c) {
		asciiToVK[c] = 0x41 + (c - 'A'); // 'A' to 'Z'
	}

	// Modifier Keys
	asciiToVK[0x11] = 0x11; // CTRL
	asciiToVK[0x10] = 0x10; // SHIFT
	asciiToVK[0x12] = 0x12; // ALT
	asciiToVK[0x1B] = 0x1B; // ESC
	asciiToVK[0x09] = 0x09; // TAB
	asciiToVK[0x20] = 0x20; // SPACE
	asciiToVK[0x08] = 0x08; // BACKSPACE
	asciiToVK[0x0D] = 0x0D; // ENTER

	// Arrow Keys
	asciiToVK[0x26] = 0x26; // UP
	asciiToVK[0x28] = 0x28; // DOWN
	asciiToVK[0x25] = 0x25; // LEFT
	asciiToVK[0x27] = 0x27; // RIGHT

	// Miscellaneous Keys
	asciiToVK[0x2D] = 0x2D; // INSERT
	asciiToVK[0x2E] = 0x2E; // DELETE
	asciiToVK[0x24] = 0x24; // HOME
	asciiToVK[0x23] = 0x23; // END
	asciiToVK[0x21] = 0x21; // PAGE UP
	asciiToVK[0x22] = 0x22; // PAGE DOWN

	return asciiToVK;
}

inline static auto asciiToVK = createAsciiToVKMap(); // Create the map once