#pragma once

#include <Windows.h>
#include <dwmapi.h>
#include <iostream>
#include "../../external/imgui/imgui.h"
#include "../../external/imgui/imgui_impl_dx11.h"
#include "../../external/imgui/imgui_impl_win32.h"
#include <d3d11.h>

namespace overlay
{
	inline HWND hwnd;
	inline ID3D11Device* d3d11Device;
	inline ID3D11DeviceContext* d3d11DevCon;
	inline IDXGISwapChain* swap_chain;
	inline ID3D11RenderTargetView* render_target_view;
	inline ImDrawList* draw_list;

	inline int game_screen_width, game_screen_height;
}

inline WNDCLASSEXW wc{ };

class Overlay
{

public:
	static inline DWORD procId;

	bool InitDevice();
	void DestroyDevice();

	void InitImGui();
	void DestroyImGui();
	void InitRenderTarget();
	void DestroyRenderTarget();

	void OpenWindow();

	const void Render();

	void InputHandler();
	bool MessageLoop();
	void ToggleTransparency(bool enable);
	Overlay(HINSTANCE hInstance, int nCmdShow);
	~Overlay();
};