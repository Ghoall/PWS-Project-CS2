#pragma once
#include <Windows.h>
#include "../../external/imgui/imgui.h"

class Input
{
private:

	HHOOK keyboard_hook;
	HHOOK mouse_hook;

public:

	static LRESULT CALLBACK KeyboardCallback(int nCode, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK MouseCallback(int nCode, WPARAM wParam, LPARAM lParam);

	void SetHook();
	void ReleaseHook();
} inline input;

class InputManager
{
public:

	bool toggle_menu = false;
	bool left_click, right_click;
	ImVec2 mouse_position;

} inline input_manager;