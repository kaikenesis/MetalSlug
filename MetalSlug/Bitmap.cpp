#include "framework.h"
#include "Bitmap.h"
#include "Game.h"

using namespace std;
using namespace metalSlug;

ULONG_PTR g_GdiplusToken;

HBITMAP hDoubleBufferImg;
RECT rectView;

HBITMAP hBackgroundImg;
BITMAP bitBackground;

#define BACKSKYIMG_HEIGHT_START 0
#define BACKSKYIMG_WIDTH_START 0
#define BACKSKYIMG_HEIGHT 272
#define BACKSKYIMG_WIDTH 2374

int curFrame = 0;
int FrameMax = 0;
int FrameMin = 0;

void UpdateRectView(RECT rect)
{
	rectView = rect;
}

void CreateBitmap()
{
	// Background
	hBackgroundImg = (HBITMAP)LoadImage(NULL, _T("images/Metal-Slug-3-Mission-1_backGround.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hBackgroundImg == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("배경 이미지 로드 에러"), _T("Error"), MB_OK);
	}
	else
		GetObject(hBackgroundImg, sizeof(BITMAP), &bitBackground);
}

void DrawBitmap(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;

	DrawBackGround(hdc, hMemDC, hOldBitmap);
	
	Gdi_Draw(hdc);
}

void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
	HDC hDoubleBufferDC;
	HBITMAP hOldDoubleBufferBitmap;

	hDoubleBufferDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImg == NULL)
	{
		hDoubleBufferImg = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
	}
	hOldDoubleBufferBitmap = (HBITMAP)SelectObject(hDoubleBufferDC, hDoubleBufferImg);

	DrawBitmap(hWnd, hDoubleBufferDC);

	BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hDoubleBufferDC, 0, 0, SRCCOPY);
	SelectObject(hDoubleBufferDC, hOldDoubleBufferBitmap);
	DeleteDC(hDoubleBufferDC);
}

void DeleteBitmap()
{
	DeleteObject(hBackgroundImg);
}

void Gdi_Init()
{
	GdiplusStartupInput gpsi;
	GdiplusStartup(&g_GdiplusToken, &gpsi, NULL);
	
	CreateObject();
	//=====================================================================================================================
	// EnemyCharacter
	//=====================================================================================================================

}

void Gdi_Draw(HDC hdc)
{
	Graphics graphics(hdc);

	DrawObject(&graphics);
}

void Gdi_End()
{
	DeleteObject();

	GdiplusShutdown(g_GdiplusToken);
}

void UpdateFrame(HWND hWnd)
{
	curFrame++;
	if (curFrame > FrameMax)
		curFrame = FrameMin;
}

//======================================================================================================================
// Background

void DrawBackGround(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBackgroundImg);
	int bx = bitBackground.bmWidth;
	int by = bitBackground.bmHeight;
	
	TransparentBlt(hdc, -200, -200, bx*4, by*4, hMemDC, 0, 0, bx, by, RGB(248, 0, 248));

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}
