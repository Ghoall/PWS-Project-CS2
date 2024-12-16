#include "radar.h"

// Normalize the yaw to be within -179 to 180
float NormalizeYaw(float yaw) {
	if (yaw > 180.0f) {
		yaw -= 360.0f;  // Wrap around if greater than 180
	}
	else if (yaw < -179.0f) {
		yaw += 360.0f;  // Wrap around if less than -179
	}
	return yaw;
}

float get_enemy_yaw_rad(Vector3 localPos, Vector3 enemyPos, Vector3 viewAngles) {
	float angle = atan2(enemyPos.y - localPos.y, enemyPos.x - localPos.x) * 180 / M_PI;
	angle = (viewAngles.y - angle) * M_PI / 180;

	return angle;
}

ImVec2 _Radar::get_point_distance(Vector3 localPos, Vector3 enemyPos, Vector3 viewAngles) {

	float distance = localPos.Distance(enemyPos);

	if (distance > this->radarMaxRange)
		return { 0, 0 };

	float RadarDistance = (distance / this->radarMaxRange) * this->radarRadius;

	float angle = get_enemy_yaw_rad(localPos, enemyPos, viewAngles);

	float radarX = this->radarCenter.x + RadarDistance * sin(angle);
	float radarY = this->radarCenter.y - RadarDistance * cos(angle); // Invert y for radar representation

	return { radarX, radarY };
}

void _Radar::run_radar(Vector3 LocalPos, Vector3 EnemyPos, Vector3 viewAngles) {

	ImVec2 point_pos = get_point_distance(LocalPos, EnemyPos, viewAngles);
	if (point_pos.x == 0 && point_pos.y == 0)
		return;

	gui::drawListForeground->AddCircleFilled(point_pos, this->pointSize, this->pointColor);
}

void _Radar::run_radar_circle()
{
	gui::drawListForeground->AddCircleFilled(this->radarCenter, this->radarRadius, IM_COL32(20, 20, 20, 100)); //inside
	gui::drawListForeground->AddCircle(this->radarCenter, this->radarRadius + 1.f, IM_COL32(0, 0, 0, 200), 0, 3.f); //outline
}