#include "reader.h"
#include "../gui/gui.h"
#include "../globals/globals.h"
#include "../globals/math.h"
#include "../globals/offsets.h"
#include "../globals/entity.h"
#include "../gui/settings.h"
#include "../globals/game/bones.h"
#include "../features/aimbot.h"
#include "../globals/game/weapon.h"
#include "../gui/menu.h"
#include "../features/triggerbot.h"
#include "../driver/driver.h"
#include "../features/misc.h"
#include <cstdint>
#include <iostream>
#include <array>
#include <string>
#include <thread>
#include "../../external/imgui/imgui.h"
#include <mmsystem.h>
#include "../security/skCrypter.h"
#include "../features/hitsound.h"
#include "../features/radar.h"
#include "../features/rcs.h"
#pragma comment(lib, "Winmm.lib")
#define KEY_DOWN -32768
#define KEY_UP 0

// Function to update and refresh the cache
void updateCache() {
	// Clear current cache entries
	cache::playerControllerCache.clear();
	cache::playerPawnCache.clear();
	cache::entityList = 0;
	cache::localPlayer = 0;

	cache::entityList = driver.read<std::uintptr_t>(globals::client + offsets::client_dll::dwEntityList);
	if (cache::entityList)
		return;

	cache::localPlayer = driver.read<std::uintptr_t>(globals::client + offsets::client_dll::dwLocalPlayerPawn);
	if (cache::localPlayer)
		return;

	for (int i = 0; i <= 10; i++) {
		uintptr_t list_entry1 = driver.read<uintptr_t>(cache::entityList + (8 * (i & 0x7FFF) >> 9) + 16);
		if (!list_entry1) continue;

		uintptr_t playerController = driver.read<uintptr_t>(list_entry1 + 120 * (i & 0x1FF));
		if (!playerController) continue;

		// Cache playerController for this index
		cache::playerControllerCache[i] = playerController;

		uintptr_t controllerPawn = driver.read<uint32_t>(playerController + cs2_dumper::schemas::client_dll::CBasePlayerController::m_hPawn);
		if (!controllerPawn) continue;

		uintptr_t list_entry2 = driver.read<uintptr_t>(cache::entityList + 0x8 * ((controllerPawn & 0x7FFF) >> 9) + 16);
		if (!list_entry2) continue;

		uintptr_t playerPawn = driver.read<uintptr_t>(list_entry2 + 120 * (controllerPawn & 0x1FF));
		if (!playerPawn) continue;

		// Cache playerPawn for this index
		cache::playerPawnCache[i] = playerPawn;
	}

	// Reset the update flag
	cache::cacheUpdateNeeded = false;
}

void reader::Read()
{
	if (cache::cacheUpdateNeeded) {
		updateCache();
	}

	//Have to read every time.
	globals::viewMatrix = driver.read<Matrix>(globals::client + offsets::client_dll::dwViewMatrix);
	Vector3 viewAngles = driver.read<Vector3>(globals::client + offsets::client_dll::dwViewAngles);

	if (!cache::entityList) cache::entityList = driver.read<std::uintptr_t>(globals::client + offsets::client_dll::dwEntityList);
	
	if (!cache::localPlayer) cache::localPlayer = driver.read<std::uintptr_t>(globals::client + offsets::client_dll::dwLocalPlayerPawn);

	local_entity = driver.read<Entity>(cache::localPlayer);


	uintptr_t sens = driver.read<uintptr_t>(globals::client + offsets::client_dll::dwSensitivity);
	float sensitivity = driver.read<float>(sens + offsets::client_dll::dwSensitivity_sensitivity);

	Vector3 bestAim = { 0, 0, 0 };
	float _distance = 0;
	float max = FLT_MAX;


	int32_t hits = driver.read<int32_t>(local_entity.m_pBulletServices + cs2_dumper::schemas::client_dll::CCSPlayer_BulletServices::m_totalHitsOnServer);
	int32_t shotsFired = driver.read<int32_t>(cache::localPlayer + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_iShotsFired);
	
	if (cache::cacheUpdateNeeded) {
		updateCache();
	}

	if (settings::misc::bRadar) {
		radar.run_radar_circle();
	}

	if (settings::rcs::bRcs) {
		RCS::run_rcs(local_entity, shotsFired, viewAngles, sensitivity);
	}

	for (int i = 0; i <= 10; i++)
	{
		Entity temp{ 0 };

		// Check if playerController is already cached
		uintptr_t playerController;
		if (cache::playerControllerCache.find(i) != cache::playerControllerCache.end()) {
			playerController = cache::playerControllerCache[i];
		}
		else {
			uintptr_t list_entry1 = driver.read<uintptr_t>(cache::entityList + (8 * (i & 0x7FFF) >> 9) + 16);
			if (!list_entry1)
				continue;

			playerController = driver.read<uintptr_t>(list_entry1 + 120 * (i & 0x1FF));
			if (!playerController)
				continue;

			// Cache playerController for this index
			cache::playerControllerCache[i] = playerController;
		}

		// Check if playerPawn is already cached
		uintptr_t playerPawn;
		if (cache::playerPawnCache.find(i) != cache::playerPawnCache.end()) {
			playerPawn = cache::playerPawnCache[i];
		}
		else {
			uintptr_t controllerPawn = driver.read<uint32_t>(playerController + cs2_dumper::schemas::client_dll::CBasePlayerController::m_hPawn);
			if (!controllerPawn)
				continue;

			uintptr_t list_entry2 = driver.read<uintptr_t>(cache::entityList + 0x8 * ((controllerPawn & 0x7FFF) >> 9) + 16);
			if (!list_entry2)
				continue;

			playerPawn = driver.read<uintptr_t>(list_entry2 + 120 * (controllerPawn & 0x1FF));
			if (!playerPawn)
				continue;

			// Cache playerPawn for this index
			cache::playerPawnCache[i] = playerPawn;
		}


		if (playerPawn == cache::localPlayer)
			continue;

		temp = driver.read<Entity>(playerPawn);

		if (temp.Health > 100 || temp.Health <= 0)
			continue;

		if (temp.Team == local_entity.Team)
			continue;

		entity = temp;

		Vector3 origin_s = entity.Origin.w2s(globals::viewMatrix);
		if (origin_s.x == 0 && origin_s.y == 0)
			continue;

		Bone bones; read_bones(entity.m_pGameSceneNode, bones);

		Vector3 head_s = bones.Bone7;

		Vector3 head_aim = { head_s.x, head_s.y, head_s.z - 4.f };
		Vector3 head_aim_s = head_aim.w2s(globals::viewMatrix);

		if (settings::aimbot::bAimbot)
		{
			aimbot::FindClosestPlayer(head_aim_s, bestAim, max);
		}

		//FOV OPTIMIZED
		if (settings::aimbot::bFov)
		{
			gui::drawList->AddCircle({ 1920.f / 2, 1080.f / 2 }, settings::aimbot::fovSize, ImColor(settings::aimbot::fov_color[0], settings::aimbot::fov_color[1], settings::aimbot::fov_color[2], settings::aimbot::fov_color[3]), 0, 1.f);
		}

		// Skip rendering if the entity is off-screen
		if (origin_s.x < 0 || origin_s.y < 0 || origin_s.x > 1920 || origin_s.y > 1080)
			continue;

		if (gui::bMenu)
			continue;

		//ESP Switch
		if (settings::esp::bEspSwitch)
		{
			Vector3 head_box = { head_s.x, head_s.y, head_s.z + 9.f };
			Vector3 head_box_s = head_box.w2s(globals::viewMatrix);

			const float h = origin_s.y - head_box_s.y;
			const float w = h * 0.35f;

			ImVec2 box_top_left = { head_box_s.x - w, head_box_s.y };
			ImVec2 box_bottom_right = { head_box_s.x + w, origin_s.y };

			//Box OPTIMIZED
			if (settings::esp::bBox)
			{
				gui::drawList->AddRect(box_top_left, box_bottom_right, ImColor(settings::esp::box_color[0], settings::esp::box_color[1], settings::esp::box_color[2], settings::esp::box_color[3]), 1.f, 0, 2.0f);
			}

			//corner box
			if (settings::esp::bCornerBox) //FIX
			{
				//const ImColor color = IM_COL32(0, 173, 237, 255);
				const int thickness = 2.5;

				float BoxHeight = (float)(head_box_s.y - origin_s.y);
				float CornerHeight = abs(head_box_s.y - origin_s.y);
				float CornerWidth = BoxHeight * 0.80;

				int X = head_box_s.x - (CornerWidth / 2);
				int Y = head_box_s.y;

				float lineW = (CornerWidth / 3);
				float lineH = (CornerHeight / 3);

				gui::drawList->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImColor(settings::esp::cornerbox_color[0], settings::esp::cornerbox_color[1], settings::esp::cornerbox_color[2], settings::esp::cornerbox_color[3]), thickness);
				gui::drawList->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImColor(settings::esp::cornerbox_color[0], settings::esp::cornerbox_color[1], settings::esp::cornerbox_color[2], settings::esp::cornerbox_color[3]), thickness);
				gui::drawList->AddLine(ImVec2(X + CornerWidth - lineW, Y), ImVec2(X + CornerWidth, Y), ImColor(settings::esp::cornerbox_color[0], settings::esp::cornerbox_color[1], settings::esp::cornerbox_color[2], settings::esp::cornerbox_color[3]), thickness);
				gui::drawList->AddLine(ImVec2(X + CornerWidth, Y), ImVec2(X + CornerWidth, Y + lineH), ImColor(settings::esp::cornerbox_color[0], settings::esp::cornerbox_color[1], settings::esp::cornerbox_color[2], settings::esp::cornerbox_color[3]), thickness);
				gui::drawList->AddLine(ImVec2(X, Y + CornerHeight - lineH), ImVec2(X, Y + CornerHeight), ImColor(settings::esp::cornerbox_color[0], settings::esp::cornerbox_color[1], settings::esp::cornerbox_color[2], settings::esp::cornerbox_color[3]), thickness);
				gui::drawList->AddLine(ImVec2(X, Y + CornerHeight), ImVec2(X + lineW, Y + CornerHeight), ImColor(settings::esp::cornerbox_color[0], settings::esp::cornerbox_color[1], settings::esp::cornerbox_color[2], settings::esp::cornerbox_color[3]), thickness);
				gui::drawList->AddLine(ImVec2(X + CornerWidth - lineW, Y + CornerHeight), ImVec2(X + CornerWidth, Y + CornerHeight), ImColor(settings::esp::cornerbox_color[0], settings::esp::cornerbox_color[1], settings::esp::cornerbox_color[2], settings::esp::cornerbox_color[3]), thickness);
				gui::drawList->AddLine(ImVec2(X + CornerWidth, Y + CornerHeight - lineH), ImVec2(X + CornerWidth, Y + CornerHeight), ImColor(settings::esp::cornerbox_color[0], settings::esp::cornerbox_color[1], settings::esp::cornerbox_color[2], settings::esp::cornerbox_color[3]), thickness);
			}

			if (settings::esp::bFillBox)
			{
				if (!settings::esp::bCornerBox)
				{
					gui::drawList->AddRectFilled(box_top_left, box_bottom_right, ImColor(settings::esp::fillbox_color[0], settings::esp::fillbox_color[1], settings::esp::fillbox_color[2], settings::esp::fillbox_color[3]), 1.f);
				}
				else
				{
					//TODO CORNER BOX
				}
			}

			//Snaplines OPTIMIZED
			if (settings::esp::bSnapLines)
			{
				gui::drawList->AddLine({ screen_center.x, 1080.f }, { origin_s.x, origin_s.y }, ImColor(settings::esp::snaplines_color[0], settings::esp::snaplines_color[1], settings::esp::snaplines_color[2], settings::esp::snaplines_color[3]), 1.5f);
			}

			//Skeleton OPTIMIZED
			if (settings::esp::bSkeleton)
			{
				Vector3 bone6 = bones.Bone7.w2s(globals::viewMatrix);
				Vector3 bone5 = bones.Bone6.w2s(globals::viewMatrix);
				Vector3 bone4 = bones.Bone5.w2s(globals::viewMatrix);
				Vector3 bone0 = bones.Bone1.w2s(globals::viewMatrix);
				Vector3 bone8 = bones.Bone9.w2s(globals::viewMatrix);
				Vector3 bone9 = bones.Bone10.w2s(globals::viewMatrix);
				Vector3 bone11 = bones.Bone12.w2s(globals::viewMatrix);
				Vector3 bone13 = bones.Bone14.w2s(globals::viewMatrix);
				Vector3 bone14 = bones.Bone15.w2s(globals::viewMatrix);
				Vector3 bone16 = bones.Bone17.w2s(globals::viewMatrix);
				Vector3 bone22 = bones.Bone23.w2s(globals::viewMatrix);
				Vector3 bone2 = bones.Bone3.w2s(globals::viewMatrix);
				Vector3 bone25 = bones.Bone26.w2s(globals::viewMatrix);
				Vector3 bone23 = bones.Bone24.w2s(globals::viewMatrix);
				Vector3 bone24 = bones.Bone25.w2s(globals::viewMatrix);
				Vector3 bone26 = bones.Bone27.w2s(globals::viewMatrix);
				Vector3 bone27 = bones.Bone28.w2s(globals::viewMatrix);

				//head to neck
				gui::drawList->AddLine({ bone6.x, bone6.y }, { bone5.x, bone5.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
				gui::drawList->AddLine({ bone5.x, bone5.y }, { bone4.x, bone4.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
				gui::drawList->AddLine({ bone4.x, bone4.y }, { bone0.x, bone0.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
				gui::drawList->AddLine({ bone4.x, bone4.y }, { bone8.x, bone8.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
				gui::drawList->AddLine({ bone8.x, bone8.y }, { bone9.x, bone9.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
				gui::drawList->AddLine({ bone9.x, bone9.y }, { bone11.x, bone11.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
				gui::drawList->AddLine({ bone4.x, bone4.y }, { bone13.x, bone13.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
				gui::drawList->AddLine({ bone13.x, bone13.y }, { bone14.x, bone14.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
				gui::drawList->AddLine({ bone14.x, bone14.y }, { bone16.x, bone16.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
				gui::drawList->AddLine({ bone4.x, bone4.y }, { bone2.x, bone2.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
				gui::drawList->AddLine({ bone0.x, bone0.y }, { bone22.x, bone22.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
				gui::drawList->AddLine({ bone0.x, bone0.y }, { bone25.x, bone25.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
				gui::drawList->AddLine({ bone22.x, bone22.y }, { bone23.x, bone23.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
				gui::drawList->AddLine({ bone23.x, bone23.y }, { bone24.x, bone24.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);					gui::drawList->AddLine({ bone25.x, bone25.y }, { bone26.x, bone26.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
				gui::drawList->AddLine({ bone26.x, bone26.y }, { bone27.x, bone27.y }, ImColor(settings::esp::skeleton_color[0], settings::esp::skeleton_color[1], settings::esp::skeleton_color[2], settings::esp::skeleton_color[3]), 1.5f);
			}

			//Names PRETTY OPTIMIZED
			if (settings::esp::bNames)
			{
				std::array<char, 128> buffer = driver.read<std::array<char, 128>>(playerController + cs2_dumper::schemas::client_dll::CBasePlayerController::m_iszPlayerName);
				std::string name(buffer.data());

				if (name.empty())
					name = skCrypt("no_name");

				const char* name_cstr = name.c_str();

				Vector3 text = { head_box.x, head_box.y, head_box.z + 6.f };
				Vector3 text_s = text.w2s(globals::viewMatrix);

				float baseOffset = 0.01f; // Desired offset above the head
				float y_offset;

				uintptr_t boneArray = driver.read<uintptr_t>(local_entity.m_pGameSceneNode + 0x1F0);
				Vector3 BoneLocal = driver.read<Vector3>(boneArray + (0x26 * 6)); //head

				float distance = BoneLocal.Distance(head_s);

				if (distance > 1560.f)
				{
					y_offset = (baseOffset * (distance * 0.6f));
				}
				else
				{
					y_offset = (baseOffset * distance); // Reduce the effect as the distance increases
				}

				ImVec2 icon_size = ImGui::CalcTextSize((const char*)name_cstr);
				ImVec2 actualPos = { text_s.x - (icon_size.x / 2), text_s.y - y_offset };

				ImGui::PushFont(font::inter_bold);

				gui::drawList->AddText(actualPos, ImColor(settings::esp::name_color[0], settings::esp::name_color[1], settings::esp::name_color[2], settings::esp::name_color[3]), name_cstr);

				ImGui::PopFont();
			}

			if (settings::esp::bWeapon)
			{
				std::uintptr_t weaponEntry2 = driver.read<std::uintptr_t>(entity.m_pClippingWeapon + 0x10);

				std::uintptr_t weaponClass = driver.read<std::uintptr_t>(weaponEntry2 + 0x20);
				if (weaponClass == 0)
					continue;

				std::array<char, 20> buffer = driver.read<std::array<char, 20>>(weaponClass);
				std::string wp_name(buffer.data());

				weapon::DrawWeaponName(wp_name, origin_s);
			}

			//if (settings::esp::bAmmo) // needs fixing
			//{
			//	const int ammo = driver.read<int>(m_pClippingWeapon + off::m_iClip1);
//
			//	Vector3 ammo_pos = entity.Origin;
			//	ammo_pos.x += 20.f;
//
			//	ammo_pos = ammo_pos.w2s(globals::viewMatrix);

				//ImVec2 textSize = ImGui::CalcTextSize(std::to_string(ammo).c_str());

				//ImVec2 ammoPos = { ammo_pos.x - (textSize.x / 2), ammo_pos.y - (textSize.y / 2) };

				//ImGui::PushFont(font::inter_bold);

				//gui::drawList->AddText({ ammo_pos.x, ammo_pos.y }, ImColor(1.f, 1.f, 1.f, 1.f), std::to_string(ammo).c_str());

				//ImGui::PopFont();
			//}
		}

		//TRIGGERBOT
		if (settings::triggerbot::bTrigger)
		{
			static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
			auto CurTimePoint = std::chrono::steady_clock::now();
			if (CurTimePoint - LastTimePoint >= std::chrono::milliseconds(triggerbot::TriggerDelay))
			{
				if (local_entity.Id > 0)
				{
					std::uintptr_t entEntry = driver.read<std::uintptr_t>(cache::entityList + 0x8 * (local_entity.Id >> 9) + 0x10);
					std::uintptr_t entity = driver.read<std::uintptr_t>(entEntry + 120 * (local_entity.Id & 0x1FF));

					int team = driver.read<int>(entity + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

					if ((GetAsyncKeyState(settings::triggerbot::trigger_key) && 1)
						&& team != local_entity.Team
						&& (team == 2 || team == 3)
						&& entity)
					{
						mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
						std::thread TriggerThread(triggerbot::ReleaseMouseButton);
						TriggerThread.detach();
					}

					LastTimePoint = CurTimePoint;
				}
			}
		}

		//Hitsound
		if ((settings::misc::hitsound > 0) && (settings::misc::hitsound < 3))
		{
			play_sound(hits);
		}

		if (settings::misc::bRadar)
			radar.run_radar(local_entity.Origin, entity.Origin, viewAngles);
	}

	//------- Outside FOR-LOOP -------//
	if (settings::aimbot::bAimbotSwitch) {
		if (settings::aimbot::bAimbot)
		{
			if ((GetAsyncKeyState(VK_SHIFT) && 1))
			{
				if (IsInsideFOVCircle(settings::aimbot::fovSize, bestAim.x, bestAim.y))
				{
					aimbot::DoAimbot(bestAim.x, bestAim.y);
				}
			}
		}
	}
}