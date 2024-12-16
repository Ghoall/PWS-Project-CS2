#include "triggerbot.h"

void triggerbot::ReleaseMouseButton()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ShotDuration));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}