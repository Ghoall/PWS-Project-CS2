#pragma once
#include <windows.h>
#include <urlmon.h>
#include <iostream>
#include <string>
#pragma comment(lib, "urlmon.lib")

#include "../security/skCrypter.h"

bool DownloadFile(const char* url, const char* filePath) {
    HRESULT hr = URLDownloadToFileA(NULL, url, filePath, 0, NULL);
    return SUCCEEDED(hr);
}

bool LaunchDriverLoader(const std::string& loaderPath, const std::string& driverPath) {
    // Construct the command line: `loader.exe "path_to_driver.sys"`
    std::string command = "\"" + loaderPath + "\" \"" + driverPath + "\"";

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    // Create the process with the loader and driver path as arguments
    if (CreateProcessA(
        nullptr,                            // No application name (use command line)
        const_cast<char*>(command.c_str()), // Command line with loader and driver paths
        nullptr,                            // Default process security attributes
        nullptr,                            // Default thread security attributes
        FALSE,                              // Do not inherit handles
        0,                                  // No creation flags
        nullptr,                            // Use parent's environment
        nullptr,                            // Use parent's current directory
        &si,                                // Startup info
        &pi                                 // Process information
    )) {
        // Wait for the loader process to complete
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return true;
    }
    else {
        std::cout << skCrypt("Failed to launch driver loader. Error: ") << GetLastError() << std::endl;
        return false;
    }
}

bool _DeleteFile(const std::string& filePath) {
    // Attempt to delete the file
    if (std::remove(filePath.c_str()) == 0) {
        std::cout << skCrypt("File deleted successfully.\n");
        return true;
    }
    else {
        std::cerr << skCrypt("Error deleting file.\n");
        return false;
    }
}