#pragma once
#include "../globals/entity.h"

namespace RCS
{
	inline int bullet = 0; // 0.5, 0.6
	inline Vector2 scale = { 0.2f, 0.5f };

	void run_rcs(Entity localPlayer, int32_t hits, Vector3 angles, float sens);
}