#include "rcs.h"

#include "../driver/driver.h"

#define KEY_DOWN -32768

// Normalize the yaw to be within -179 to 180
float NormalizeYaw2(float yaw) {
	if (yaw > 180.0f) {
		yaw -= 360.0f;  // Wrap around if greater than 180
	}
	else if (yaw < -179.0f) {
		yaw += 360.0f;  // Wrap around if less than -179
	}
	return yaw;
}

void RCS::run_rcs(Entity localPlayer, int32_t hits, Vector3 angles, float sens)
{
	uintptr_t weaponData = driver.read<uintptr_t>(localPlayer.m_pClippingWeapon + (cs2_dumper::schemas::client_dll::C_BaseEntity::m_nSubclassID + 0x8));

	bool automaticWeapon = driver.read<bool>(weaponData + cs2_dumper::schemas::client_dll::CCSWeaponBaseVData::m_bIsFullAuto);

	static Vector2 oldPunch;
	Vector2 v_angles = { angles.x, angles.y };
	Vector2 aimPunch = { localPlayer.aimPunchAngle.x, localPlayer.aimPunchAngle.y };

	if (automaticWeapon && hits > RCS::bullet)
	{
		Vector2 delta = v_angles - (v_angles + (oldPunch - (aimPunch * 2.f)));

		int X = (int)(delta.y / (sens * 0.011f) * RCS::scale.x);
		int Y = (int)(delta.x / (sens * 0.011f) * RCS::scale.y);

		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000))
			mouse_event(MOUSEEVENTF_MOVE, X, -Y, 0, 0);

		oldPunch = aimPunch * 2.0f;
	}
	else
	{
		oldPunch = { 0, 0 };
	}
}