#include "overlay.h"
#include "input.h"
#include <tlhelp32.h> 

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);

// Function to suspend all threads of a process
bool SuspendProcess(DWORD processID) {
	// Take a snapshot of all threads in the system
	HANDLE hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnapshot == INVALID_HANDLE_VALUE) {
		std::cerr << "Failed to create thread snapshot.\n";
		return false;
	}

	THREADENTRY32 threadEntry;
	threadEntry.dwSize = sizeof(THREADENTRY32);

	// Iterate through all threads
	if (Thread32First(hThreadSnapshot, &threadEntry)) {
		do {
			// Check if the thread belongs to the target process
			if (threadEntry.th32OwnerProcessID == processID) {
				// Open the thread and suspend it
				HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadEntry.th32ThreadID);
				if (hThread != nullptr) {
					SuspendThread(hThread); // Suspend the thread
					CloseHandle(hThread);   // Close the handle after suspending
				}
				else {
					std::cerr << "Failed to open thread ID: " << threadEntry.th32ThreadID << "\n";
				}
			}
		} while (Thread32Next(hThreadSnapshot, &threadEntry));
	}
	else {
		std::cerr << "No threads found in the snapshot.\n";
		CloseHandle(hThreadSnapshot);
		return false;
	}

	CloseHandle(hThreadSnapshot);
	return true;
}

// Function to resume all threads of a process
bool ResumeProcess(DWORD processID) {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		return false;
	}

	THREADENTRY32 te;
	te.dwSize = sizeof(THREADENTRY32);

	// Iterate through all threads
	if (Thread32First(hSnapshot, &te)) {
		do {
			if (te.th32OwnerProcessID == processID) {
				// Open the thread
				HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
				if (hThread) {
					// Resume the thread
					ResumeThread(hThread);
					CloseHandle(hThread);
				}
			}
		} while (Thread32Next(hSnapshot, &te));
	}

	CloseHandle(hSnapshot);
	return true;
}

bool Overlay::InitDevice()
{
	DXGI_SWAP_CHAIN_DESC swap_chain_description;
	ZeroMemory(&swap_chain_description, sizeof(swap_chain_description));
	swap_chain_description.BufferCount = 2;
	swap_chain_description.BufferDesc.Width = 0;
	swap_chain_description.BufferDesc.Height = 0;
	swap_chain_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_description.BufferDesc.RefreshRate.Numerator = 144;
	swap_chain_description.BufferDesc.RefreshRate.Denominator = 1;
	swap_chain_description.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_description.OutputWindow = overlay::hwnd;
	swap_chain_description.SampleDesc.Count = 1;
	swap_chain_description.SampleDesc.Quality = 0;
	swap_chain_description.Windowed = TRUE;
	swap_chain_description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	D3D_FEATURE_LEVEL feature_level;
	D3D_FEATURE_LEVEL feature_level_array[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, feature_level_array, 2, D3D11_SDK_VERSION, &swap_chain_description, &overlay::swap_chain, &overlay::d3d11Device, &feature_level, &overlay::d3d11DevCon) != S_OK)
		return false;

	InitRenderTarget();

	ShowWindow(overlay::hwnd, SW_SHOW);
	UpdateWindow(overlay::hwnd);

	return true;
}

void Overlay::DestroyDevice()
{
	DestroyRenderTarget();
	overlay::swap_chain->Release();
	overlay::d3d11DevCon->Release();
	overlay::d3d11Device->Release();
}

Overlay::~Overlay()
{
	DestroyDevice();
	if (overlay::hwnd)
	{
		DestroyWindow(overlay::hwnd);

		UnregisterClassW(wc.lpszClassName, wc.hInstance);
	}
}

void Overlay::InitRenderTarget()
{
	ID3D11Texture2D* back_buffer = nullptr;
	overlay::swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
	if (back_buffer)
	{
		overlay::d3d11Device->CreateRenderTargetView(back_buffer, NULL, &overlay::render_target_view);
		back_buffer->Release();
	}
}

void Overlay::DestroyRenderTarget()
{
	if (!overlay::render_target_view)
		return;

	overlay::render_target_view->Release();
	overlay::render_target_view = NULL;
}


Overlay::Overlay(HINSTANCE hInstance, int nCmdShow)
{
	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEXW));

	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"...";

	RegisterClassExW(&wc);

	overlay::hwnd = CreateWindowExW(
		//WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
		WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW,
		wc.lpszClassName,
		L"...",   // title of the window
		WS_POPUP,    // window style
		0,    // x-position of the window
		0,    // y-position of the window
		1920,    // width of the window
		1080,    // height of the window
		nullptr,    // we have no parent window, NULL
		nullptr,    // we aren't using menus, NULL
		wc.hInstance,    // application handle
		nullptr);    // used with multiple windows, NULL

	SetLayeredWindowAttributes(overlay::hwnd, RGB(0, 0, 0), BYTE(255), LWA_ALPHA);

	{
		RECT client_area{};
		GetClientRect(overlay::hwnd, &client_area);

		RECT window_area{};
		GetWindowRect(overlay::hwnd, &window_area);

		POINT diff{};
		ClientToScreen(overlay::hwnd, &diff);

		const MARGINS margins
		{
			window_area.left + (diff.x - window_area.left),
			window_area.top + (diff.y - window_area.top),
			client_area.right,
			client_area.bottom
		};

		DwmExtendFrameIntoClientArea(overlay::hwnd, &margins);
	}

	ShowWindow(overlay::hwnd, 1);
	
	if (!InitDevice())
		return;
}

void Overlay::ToggleTransparency(bool enable) {
	LONG_PTR style = GetWindowLongPtr(overlay::hwnd, GWL_EXSTYLE);
	if (enable) {
		style |= WS_EX_TRANSPARENT;
	}
	else {
		style &= ~WS_EX_TRANSPARENT;
	}
	SetWindowLongPtr(overlay::hwnd, GWL_EXSTYLE, style);

	// To make the changes take effect immediately
	SetWindowPos(overlay::hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return 0L;

	// this is the main message handler for the program
	// sort through and find what code to run for the message given
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}
