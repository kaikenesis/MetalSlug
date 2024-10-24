// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Gdi

#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;

#pragma comment(lib,"msimg32.lib")

#include <vector>
#include <algorithm>
#include <windowsx.h>

// Custom
#include "Images.h"
#include "Game.h"
using namespace metalSlug;