#pragma once
#include "../globals/math.h"

namespace aimbot
{
	void FindClosestPlayer(const Vector3& headpos, Vector3& bestaim, float& max);
	void DoAimbot(float x, float y);
}