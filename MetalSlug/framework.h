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

// Sound 용도 - 헤더 순서 중요
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

// 코드
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

// etc

#include <vector>
#include <algorithm>
#include <windowsx.h>
#include <random>
#include <map>

// Custom
#include "Images.h"
#include "Game.h"
#include "Camera.h"
#include "CSound.h"
#include "CSoundMgr.h"
using namespace metalSlug;
using namespace std;

extern HWND g_hWnd;