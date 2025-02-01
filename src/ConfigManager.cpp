//
// Created by sarthak on 2/1/25.
//

#include "ConfigManager.hpp"

// Platform specific includes
#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#elif __APPLE__
#include <cstdlib>
#elif __linux__
#include <cstdlib>
#endif