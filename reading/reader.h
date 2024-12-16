#pragma once
#include "../memory/memory.h"
#include "../security/skCrypter.h"
#include <unordered_map>

inline Memory mem{ "cs2.exe" };

namespace cache
{
	inline bool cacheUpdateNeeded = false;  // Set this to true when cache needs refreshing
	inline std::unordered_map<int, uintptr_t> playerControllerCache;
	inline std::unordered_map<int, uintptr_t> playerPawnCache;

	inline std::uintptr_t entityList;
	inline std::uintptr_t localPlayer;
}

class reader
{
public:
	void Read();
};

inline reader read;