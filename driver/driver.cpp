#include "../globals/globals.h"
#include "driver.h"
#include <thread>

#include <string>

void _Driver::prepare_driver()
{
	//Load user32.dll for hook in windows function (dependencies)
	LoadLibrary(skCrypt("user32.dll"));

    std::cout << skCrypt("[>] Starting Loader...\n");

	int32_t test = callback();

	if (test != 999)
	{
		BlockInput(TRUE);

		if (globals::map_d() != true)
		{
			BlockInput(FALSE);
			std::cout << skCrypt("[>] Could not load Driver!\n");
			std::this_thread::sleep_for(std::chrono::seconds(3));
			exit(-1);
		}

		if (callback() != 999)
		{
			BlockInput(FALSE);
			std::cout << skCrypt("[>] Could not load Driver!\n");
			std::this_thread::sleep_for(std::chrono::seconds(3));
			exit(-1);
		}

		std::this_thread::sleep_for(std::chrono::seconds(3));
		Beep(750, 300);
		BlockInput(FALSE);
	}

	MessageBoxA(NULL, skCrypt("Click OK once you are in the game's main menu..."), skCrypt("ATTENTION"), MB_OK | MB_ICONINFORMATION);

	Memory mem{ "cs2.exe" };

	n_driver::tProcessId = mem.procId;
	std::cout << skCrypt("[+] ProcessID = ") << n_driver::tProcessId << '\n';

	if (globals::client = get_mod_base(skCrypt("client.dll")), globals::client == 0)
	{
		std::cout << skCrypt("[-] Driver or cs2 not loaded, Closing...\n");
		std::this_thread::sleep_for(std::chrono::seconds(3));
		exit(-1);
	}
	std::cout << skCrypt("[+] Client = ") << globals::client << '\n';

	std::this_thread::sleep_for(std::chrono::seconds(3));

	std::cout << skCrypt("[>] Successfully Loaded!\n");
}