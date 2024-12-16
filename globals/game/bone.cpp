#include "bones.h"
#include "../../driver/driver.h"

void read_bones(uintptr_t m_pGameSceneNode, Bone& bones)
{
	uintptr_t boneArray = driver.read<uintptr_t>(m_pGameSceneNode + 0x1F0); //aimstar source

	bones = driver.read<Bone>(boneArray);
}