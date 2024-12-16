#pragma once
#include <cstdint>

#include "offsets.h"
#include "math.h"

#pragma pack(push, 1) // Ensure there is no extra padding between fields, push 1

struct Entity
{
	char pad_000[cs2_dumper::schemas::client_dll::C_BaseEntity::m_pGameSceneNode];
	uintptr_t m_pGameSceneNode{ 0 };
	char pad_0000[cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth - cs2_dumper::schemas::client_dll::C_BaseEntity::m_pGameSceneNode - sizeof(m_pGameSceneNode)];
	int32_t Health{ 0 }; 
	char pad_0001[cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum - cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth - sizeof(Health)];
	int32_t Team{ 0 }; 
	char pad_0002[cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin - cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum - sizeof(Team)];
	Vector3 Origin{ 0, 0, 0 }; 
	char pad_0004[cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_pClippingWeapon - cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin - sizeof(Origin)];
	uintptr_t m_pClippingWeapon{ 0 };
	char pad_0003[cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_iIDEntIndex - cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_pClippingWeapon - sizeof(m_pClippingWeapon)];
	int32_t Id{ 0 }; //Who is this player looking at?
	char pad_0005[cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_pBulletServices - cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_iIDEntIndex - sizeof(Id)];
	uintptr_t m_pBulletServices{ 0 };
	char pad_0006[cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_aimPunchAngle - cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_pBulletServices - sizeof(m_pBulletServices)];
	Vector3 aimPunchAngle{ 0, 0, 0 };

	// add shots fired
};
#pragma pack(pop)

inline Entity entity;
inline Entity local_entity;