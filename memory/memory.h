#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <string_view>
#include <vector>

class Memory
{
private:
	void* processHandle = nullptr;

public:
	std::uint32_t procId = 0;

	// Memory Constructor - used for finding the processId and opening the handle
	Memory(const std::string_view processName) noexcept
	{
		::PROCESSENTRY32 entry = { };
		entry.dwSize = sizeof(::PROCESSENTRY32);

		const auto procSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		while (::Process32Next(procSnap, &entry))
		{
			if (!processName.compare(entry.szExeFile))
			{
				procId = entry.th32ProcessID;
				processHandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, static_cast<DWORD>(procId));
				break;
			}
		}

		// Close the handle
		if (procSnap)
			::CloseHandle(procSnap);
	}

	// Memory Deconstructor - cleanup by closing the process handle to the game's memory.
	~Memory()
	{
		if (processHandle)
			::CloseHandle(processHandle);
	}
};