#pragma once
#include "../../external/imgui/imgui.h"
#include "overlay.h"

namespace gui
{
	void MainLoop(Overlay& overlay);

	inline bool open = true;
	inline bool bMenu = true;
	inline bool bWatermark = true;

	inline ImDrawList* drawList; // Get the draw list once
	inline ImDrawList* drawListForeground;
}