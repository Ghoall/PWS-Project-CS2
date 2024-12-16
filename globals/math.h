#pragma once
#include <algorithm>
#include <Windows.h>
#include <functional>  // for std::hash

#include "../gui/settings.h"

struct Matrix
{
	float* operator[ ](int index)
	{
		return matrix[index];
	}

	float matrix[4][4];
};

class Vector2
{
public:
	float x, y;

	Vector2() {};
	Vector2(const float x, const float y) : x(x), y(y) {}
	Vector2 operator + (const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
	Vector2 operator - (const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
	Vector2 operator * (const float& rhs) const { return Vector2(x * rhs, y * rhs); }
	Vector2 operator / (const float& rhs) const { return Vector2(x / rhs, y / rhs); }
};

class Vector3
{
public:

	float x, y, z;

	Vector3() {};
	Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
	Vector3& operator += (const Vector3& rhs) { return *this = *this + rhs; }
	Vector3& operator -= (const Vector3& rhs) { return *this = *this - rhs; }
	Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }
	float Length() const { return sqrtf(x * x + y * y + z * z); }
	Vector3 Normalize() const { return *this * (1 / Length()); }

public:
	Vector3 w2s(Matrix vm) const
	{
		float _x = vm[0][0] * x + vm[0][1] * y + vm[0][2] * z + vm[0][3];
		float _y = vm[1][0] * x + vm[1][1] * y + vm[1][2] * z + vm[1][3];

		float w = vm[3][0] * x + vm[3][1] * y + vm[3][2] * z + vm[3][3];

		if (w < 0.01f)
			return { 0, 0, 0 };

		float inv_w = 1.f / w;
		_x *= inv_w;
		_y *= inv_w;

		float x = 1920 * 0.5f;
		float y = 1080 * 0.5f;

		x += 0.5f * _x * 1920 + 0.5f;
		y -= 0.5f * _y * 1080 + 0.5f;

		return { x, y, w };
	}

	float Distance(const Vector3& enemy) const
	{
		float dx = x - enemy.x;
		float dy = y - enemy.y;
		float dz = z - enemy.z;
		return std::sqrt(dx * dx + dy * dy + dz * dz);
	}

};

typedef struct {

	float x, y, z, w;
} Vector4;

inline const bool w2s(float* Matrix, const Vector3& origin, Vector2& out)
{
	Vector4 clip;
	clip.x = origin.x * Matrix[0] + origin.y * Matrix[1] + origin.z * Matrix[2] + Matrix[3];
	clip.y = origin.x * Matrix[4] + origin.y * Matrix[5] + origin.z * Matrix[6] + Matrix[7];
	clip.z = origin.x * Matrix[8] + origin.y * Matrix[9] + origin.z * Matrix[10] + Matrix[11];
	clip.w = origin.x * Matrix[12] + origin.y * Matrix[13] + origin.z * Matrix[14] + Matrix[15];

	if (clip.w < 0.1f) return false;

	Vector4 NDC;
	NDC.x = clip.x / clip.w;
	NDC.y = clip.y / clip.w;
	NDC.z = clip.z / clip.w;

	//maak de NDC coords naar Pixel Coords
	out.x = (1920 / 2 * NDC.x) + (1920 / 2);
	out.y = -(1080 / 2 * NDC.y) + (1080 / 2); //- omdat Pitch negatief is in Counter-Strike 2

	return true;
}

inline Vector2 screen_center{ 1920.f / 2, 1080.f / 2 };

inline float DistanceBetweenCross(float X, float Y)
{
	if (X < 0 && Y < 0 && X > 1920 && Y > 1080)
		return 0;

	float ydistance = (Y - (screen_center.y));
	float xdistance = (X - (screen_center.x));
	float Distance = sqrt(pow(xdistance, 2) + pow(ydistance, 2));
	return Distance;
}

//check if pixel coords are in FOV circle.
inline bool IsInsideFOVCircle(float fovRadius, float enemyHeadX, float enemyHeadY) {
	float distance = (DistanceBetweenCross(enemyHeadX, enemyHeadY));
	return distance <= fovRadius;
}

inline constexpr uint32_t HashString(const char* str) {
	uint32_t hash = 2166136261u;  // FNV-1a 32-bit offset basis
	while (*str) {
		hash ^= static_cast<uint32_t>(*str++);
		hash *= 16777619u;  // FNV-1a 32-bit prime
	}
	return hash;
}