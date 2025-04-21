#pragma once

#include <windows.h>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <functional>
#include <queue>
using namespace std;

#include <assert.h>

#include "Types.h"
#include "Defines.h"
#include "Enums.h"
#include "Values.h"

#include <format>
#include <filesystem>
namespace fs = std::filesystem;

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#pragma comment(lib, "msimg32.lib")
