#pragma once
#include <cstdint>
#include <Windows.h>
#include <iostream>

#include "../memory/memory.h"
#include "../security/skCrypter.h"

template<typename ... Arg>
uint64_t call_hook(const Arg ... args)
{
	void* function = GetProcAddress(LoadLibrary(skCrypt("win32u.dll")), skCrypt("NtOpenCompositionSurfaceSectionInfo"));

	if (!function)
	{
		std::cout << skCrypt("[-] Failed to find Windows Function...\n");
		return 0;
	}

	auto func = static_cast<uint64_t(_stdcall*)(Arg...)>(function);

	return func(args ...);
}

namespace n_driver
{
	inline ULONG tProcessId = 0;
}

class _Driver
{
private:
	typedef struct _G_MEMORY
	{
		void* buffer_addr;
		ULONG_PTR address;
		size_t size;
		ULONG pid;
		BOOLEAN write;
		BOOLEAN read;
		BOOLEAN req_base;
		void* output;
		const char* mod_name;
		ULONG64 module_base;
		ULONG callback;
	}G_MEMORY;

public:
	void prepare_driver();

	static ULONG64 get_mod_base(const char* name)
	{
		G_MEMORY communication = { 0 };
		communication.pid = n_driver::tProcessId;
		communication.req_base = TRUE;
		communication.read = FALSE;
		communication.write = FALSE;
		communication.mod_name = name;

		call_hook(&communication);

		ULONG64 base = 0;
		base = communication.module_base;

		if (!base)
			return 0;

		return base;
	}

	template <class T>
	T read(UINT_PTR address)
	{
		T response{};
		G_MEMORY communication;
		communication.pid = n_driver::tProcessId;
		communication.size = sizeof(T);
		communication.address = address;
		communication.read = TRUE;
		communication.write = FALSE;
		communication.req_base = FALSE;
		communication.output = &response;
		call_hook(&communication);

		return response;
	}

	bool _Write(UINT_PTR write_address, UINT_PTR source_addr, SIZE_T write_size)
	{
		G_MEMORY communication;
		communication.pid = n_driver::tProcessId;
		communication.address = write_address;
		communication.read = FALSE;
		communication.write = TRUE;
		communication.req_base = FALSE;
		communication.buffer_addr = reinterpret_cast<void*>(source_addr);
		communication.size = write_size;
		call_hook(&communication);

		return true;
	}

	template <typename W>
	bool write(UINT_PTR write_address, const W& value)
	{
		return _Write(write_address, (UINT_PTR)&value, sizeof(W));
	}

	ULONG callback()
	{
		G_MEMORY communication{ 0 };
		communication.callback = 100;
		communication.read = FALSE;
		communication.write = FALSE;
		communication.req_base = FALSE;
		call_hook(&communication);

		ULONG number = communication.callback;

		return number;
	}
}; inline _Driver driver;