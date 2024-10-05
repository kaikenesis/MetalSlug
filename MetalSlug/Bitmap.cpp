#include "Bitmap.h"
#include "Game.h"
#include "AnimEri.h"

using namespace std;

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

	Eri::Init();

	//=====================================================================================================================
	// EnemyCharacter
	//=====================================================================================================================

	

	// 공통 프레임을 맞추려했는데 그렇게하니 처음부터 재생해야될 애니메이션에서는 문제가 생김
	vector<int> frames;
	frames.push_back(Eri::GetEriIdleFrame());
	frames.push_back(Eri::GetEriJumpIdleStartFrame());
	frames.push_back(Eri::GetEriStopFrame());
	frames.push_back(Eri::GetEriRunStartFrame());
	frames.push_back(Eri::GetEriRunFrame());
	FrameMax = Lcm(frames);
}

void Gdi_Draw(HDC hdc)
{
	Graphics graphics(hdc);

	Eri::PlayEriAnimation(&graphics);
}

void Gdi_End()
{
	Eri::Delete();

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
