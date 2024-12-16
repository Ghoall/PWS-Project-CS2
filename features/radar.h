#pragma once
#include "../../external/imgui/imgui.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../globals/math.h"
#include "../gui/gui.h"

class _Radar
{
private:
	ImVec2 radarCenter = { (150 * 2) / 2, (150 * 2) / 2 };
	float radarRadius = 125.f;
	float radarMaxRange = 1450.0f;  // Maximum range the radar can represent (game units)

	float pointSize = 5.f;
	ImColor pointColor = ImColor(1.f, 0.f, 0.f, 1.f);

public:
	void run_radar(Vector3 LocalPos, Vector3 EnemyPos, Vector3 viewAngles);
	void run_radar_circle();
	ImVec2 get_point_distance(Vector3 localPos, Vector3 enemyPos, Vector3 viewAngles);
}; inline _Radar radar;