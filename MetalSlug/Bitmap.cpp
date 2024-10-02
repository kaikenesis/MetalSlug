#include "Bitmap.h"

using namespace std;

ULONG_PTR g_GdiplusToken;

HBITMAP hDoubleBufferImg;
RECT rectView;

HBITMAP hBackgroundImg;
BITMAP bitBackground;

Bitmap* EriIdle;
Bitmap* EriJumpStart;
Bitmap* EriJumpEnd;

#define BACKSKYIMG_HEIGHT_START 0
#define BACKSKYIMG_WIDTH_START 0
#define BACKSKYIMG_HEIGHT 272
#define BACKSKYIMG_WIDTH 2374

#define FrameCount_Idle 8
#define FrameCount_JumpIdleStart 16
#define FrameCount_JumpEnd 12

int curFrame = 0;
int FrameMax = 0;
int FrameMin = 0;

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
}

void Gdi_Init()
{
	GdiplusStartupInput gpsi;
	GdiplusStartup(&g_GdiplusToken, &gpsi, NULL);

	//=====================================================================================================================
	// PlayerCharacter
	//=====================================================================================================================

	// Eri
	EriIdle = new Bitmap(_T("images/Eri Kasamoto_Idle.png"));
	EriJumpStart = new Bitmap(_T("images/Eri Kasamoto_JumpIdle.png"));
	EriJumpEnd = new Bitmap(_T("images/Eri Kasamoto_JumpEnd.png"));

	//=====================================================================================================================
	// EnemyCharacter
	//=====================================================================================================================

	// Rebel Soldier

	vector<int> frames;
	frames.push_back(FrameCount_Idle);
	frames.push_back(FrameCount_JumpIdleStart);
	frames.push_back(FrameCount_JumpEnd);
	FrameMax = Lcm(frames);
}

void Gdi_Draw(HDC hdc)
{
	Graphics graphics(hdc);

	if (EriIdle)
	{
		AniEriIdle(&graphics);
	}
	if (EriJumpStart)
	{
		AniEriJumpStart(&graphics);
	}
	if (EriJumpEnd)
	{
		AniEriJumpEnd(&graphics);
	}
}

void Gdi_End()
{
	delete EriIdle;
	delete EriJumpStart;
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
	
	TransparentBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, bx, by, RGB(248, 0, 248));

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

//======================================================================================================================
// Animation

void AniEriIdle(Graphics* graphics)
{
	int xStart[FrameCount_Idle] = { 0,35,71,105,105,71,35,0};
	int upperBody_yStart = 0;
	int upperBody_Height = 32;
	int lowerBody_yStart = upperBody_yStart + upperBody_Height;
	int lowerBody_Height = 32;
	int lowerBody_DrawStart = 27;
	int frame = curFrame % FrameCount_Idle;

	graphics->DrawImage(EriIdle, 100, 100 + lowerBody_DrawStart, 147, 0, 33, lowerBody_Height, UnitPixel);
	graphics->DrawImage(EriIdle, 100+4, 100+10, xStart[frame], upperBody_yStart, 33, upperBody_Height, UnitPixel);
}

void AniEriJumpStart(Graphics* graphics)
{
	int xStart[FrameCount_JumpIdleStart] = { 0,34,70,105,142,177,177,142,142,105,105,105,105,105,105,105 };
	int upperBody_yStart = 0;
	int upperBody_Height = 32;
	int lowerBody_yStart = upperBody_yStart + upperBody_Height;
	int lowerBody_Height = 30;
	int lowerBody_DrawStart = 27;
	int frame = curFrame % FrameCount_JumpIdleStart;

	graphics->DrawImage(EriJumpStart, 200, 100 + lowerBody_DrawStart, xStart[frame], lowerBody_yStart, 33, lowerBody_Height, UnitPixel);
	graphics->DrawImage(EriJumpStart, 200, 100, xStart[frame], upperBody_yStart, 33, upperBody_Height, UnitPixel);
}

void AniEriJumpEnd(Graphics* graphics)
{
	int xStart[FrameCount_JumpEnd] = { 1,36,72,110,110,72,72,36,36,1,1 };
	int Body_yStart = 0;
	int Body_Height = 36;
	int frame = curFrame % FrameCount_JumpEnd;

	graphics->DrawImage(EriJumpEnd, 300, 120, xStart[frame], Body_yStart, 35, Body_Height, UnitPixel);
}

int Gcd(int a, int b)
{
	int A = max(a, b);
	int B = min(a, b);

	while (A % B != 0)
	{
		int R = A % B;
		A = B;
		B = R;
	}
	return B;
}

int Lcm(vector<int> arr)
{
	int res = arr[0];
	for (int i = 1; i < arr.size(); i++)
	{
		int GCD = Gcd(res, arr[i]);
		int LCM = res * arr[i] / GCD;
		res = LCM;
	}
	return res;
}
