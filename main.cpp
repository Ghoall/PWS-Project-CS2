#include <iostream>
#include <Windows.h>

#include "globals/globals.h"
#include "gui/overlay.h"
#include "gui/gui.h"
#include "driver/driver.h"

#define CONSOLE

INT WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    //DEBUG
#ifdef CONSOLE
    AllocConsole();
    FILE* f;
    freopen_s(&f, skCrypt("CONOUT$"), "w", stdout);
    freopen_s(&f, skCrypt("CONIN$"), "r", stdin);
#endif

    driver.prepare_driver();

    Overlay overlay(hInstance, nCmdShow);

    gui::MainLoop(overlay);

    overlay.~Overlay();

#ifdef CONSOLE
    std::cout << skCrypt("Closing Console.....") << '\n';
    Sleep(2000);

    if (f)  fclose(f);
    FreeConsole();
#endif

    return 0;
}

