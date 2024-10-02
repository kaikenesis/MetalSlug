#include "Bitmap.h"


using namespace std;

ULONG_PTR g_GdiplusToken;

HBITMAP hDoubleBufferImg;
RECT rectView;

HBITMAP hBackgroundImg;
BITMAP bitBackground;

HBITMAP hRebelSoldierImg;
BITMAP bitRebelSoldier;

Bitmap* EriIdle;
Bitmap* EriJump;

#define BACKSKYIMG_HEIGHT_START 0
#define BACKSKYIMG_WIDTH_START 0
#define BACKSKYIMG_HEIGHT 272
#define BACKSKYIMG_WIDTH 2374

int Jump_Frame_Max = 0;
int Jump_Frame_Min = 0;
int curFrame = Jump_Frame_Min;

void InitRectView(RECT rect)
{
	rectView = rect;
}

void CreateBitmap()
{
	// Background
	hBackgroundImg = (HBITMAP)LoadImage(NULL, _T("images/Neo-Geo-NGCD-Metal-Slug-3-Mission-1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
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
	//DrawEri(hdc, hMemDC, hOldBitmap);
	
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
	DeleteObject(hRebelSoldierImg);
}

void Gdi_Init()
{
	GdiplusStartupInput gpsi;
	GdiplusStartup(&g_GdiplusToken, &gpsi, NULL);

	//=====================================================================================================================
	// PlayerCharacter
	//=====================================================================================================================

	// Eri -> width : 36, height :
	EriIdle = new Bitmap(_T("images/Eri Kasamoto_Idle.png"));
	EriJump = new Bitmap(_T("images/Eri Kasamoto_Jump.png"));

	//=====================================================================================================================
	// EnemyCharacter
	//=====================================================================================================================

	// Rebel Soldier

	Jump_Frame_Max = 6 - 1;
	Jump_Frame_Min = 0;
	curFrame = Jump_Frame_Min;
}

void Gdi_Draw(HDC hdc)
{
	Graphics graphics(hdc);

	if (EriIdle)
	{
		//AniEriIdle(&graphics);
	}
	if (EriJump)
	{
		AniEriJump(&graphics);
	}
}

void Gdi_End()
{
	delete EriIdle;
	delete EriJump;
	GdiplusShutdown(g_GdiplusToken);
}

CachedBitmap* ImageToCachedBitmap(Image* pImg, int ImgWidth, int ImgHeight)
{
	HDC hTempDC;
	return nullptr;
}

void UpdateFrame(HWND hWnd)
{
	curFrame++;
	if (curFrame > Jump_Frame_Max)
		curFrame = Jump_Frame_Min;
}

//======================================================================================================================
// Background

void DrawBackGround(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBackgroundImg);
	int bx = bitBackground.bmWidth;
	int by = bitBackground.bmHeight;
	
	TransparentBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, bx, by, RGB(248, 0, 248));

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

//======================================================================================================================
// Animation

void AniEriIdle(Graphics* graphics)
{
	int xStart[4] = { 0,34,70,105};
	int upperBody_yStart = 650;
	int upperBody_Height = 32;
	int lowerBody_yStart = upperBody_yStart + upperBody_Height;
	int lowerBody_Height = 30;
	int lowerBody_DrawStart = 27;

	graphics->DrawImage(EriIdle, 100, 100 + lowerBody_DrawStart, 147, lowerBody_yStart, 33, lowerBody_Height, UnitPixel);
	graphics->DrawImage(EriIdle, 100, 100, xStart[curFrame], upperBody_yStart, 33, upperBody_Height, UnitPixel);
}

void AniEriJump(Graphics* graphics)
{
	int xStart[6] = { 0,34,70,105,142,177 };
	int upperBody_yStart = 0;
	int upperBody_Height = 32;
	int lowerBody_yStart = upperBody_yStart + upperBody_Height;
	int lowerBody_Height = 30;
	int lowerBody_DrawStart = 27;

	ImageAttributes imgAttr;
	//imgAttr.SetColorKey(Color());

	graphics->DrawImage(EriJump, 100, 100 + lowerBody_DrawStart, xStart[curFrame], lowerBody_yStart, 33, lowerBody_Height, UnitPixel);
	graphics->DrawImage(EriJump, 100, 100, xStart[curFrame], upperBody_yStart, 33, upperBody_Height, UnitPixel);

	graphics->DrawImage(EriJump, 200, 100 + lowerBody_DrawStart, xStart[curFrame], lowerBody_yStart, 33, lowerBody_Height, UnitPixel);
	graphics->DrawImage(EriJump, 200, 100, xStart[curFrame], upperBody_yStart, 33, upperBody_Height, UnitPixel);
}
