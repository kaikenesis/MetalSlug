#include "Bitmap.h"
#include "Game.h"
#include "AnimEri.h"

using namespace std;

ULONG_PTR g_GdiplusToken;

HBITMAP hDoubleBufferImg;
RECT rectView;

HBITMAP hBackgroundImg;
BITMAP bitBackground;

Bitmap* EriIdle;
Bitmap* EriJumpIdle;
Bitmap* EriJumpRun;
Bitmap* EriStop;
Bitmap* EriRun;
Bitmap* EriTurn;

#define BACKSKYIMG_HEIGHT_START 0
#define BACKSKYIMG_WIDTH_START 0
#define BACKSKYIMG_HEIGHT 272
#define BACKSKYIMG_WIDTH 2374

int curFrame = 0;
int FrameMax = 0;
int FrameMin = 0;

bool bCanFlip = false;
bool bEriFlipX = false;

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

	// Eri
	EriIdle = new Bitmap(_T("images/Eri Kasamoto_Idle.png"));
	EriJumpIdle = new Bitmap(_T("images/Eri Kasamoto_JumpIdle.png"));
	EriJumpRun = new Bitmap(_T("images/Eri Kasamoto_JumpRun.png"));
	EriStop = new Bitmap(_T("images/Eri Kasamoto_JumpEnd.png"));
	EriRun = new Bitmap(_T("images/Eri Kasamoto_Run.png"));
	EriTurn = new Bitmap(_T("images/Eri Kasamoto_Turn.png"));

	//=====================================================================================================================
	// EnemyCharacter
	//=====================================================================================================================

	// Rebel Soldier

	vector<int> frames;
	frames.push_back(GetEriIdleFrame());
	frames.push_back(GetEriJumpIdleStartFrame());
	frames.push_back(GetEriStopFrame());
	frames.push_back(GetEriRunStartFrame());
	frames.push_back(GetEriRunFrame());
	FrameMax = Lcm(frames);
}

void Gdi_Draw(HDC hdc)
{
	Graphics graphics(hdc);

	PlayEriAnimation(&graphics);
}

void Gdi_End()
{
	delete EriIdle;
	delete EriJumpIdle;
	delete EriJumpRun;
	delete EriStop;
	delete EriRun;
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

void SetFlip()
{
	bCanFlip = true;
}

//======================================================================================================================
// Animation

void PlayEriAnimation(Graphics* graphics)
{
	if (bCanFlip == true)
	{
		EriIdle->RotateFlip(RotateNoneFlipX);
		EriRun->RotateFlip(RotateNoneFlipX);
		EriJumpIdle->RotateFlip(RotateNoneFlipX);
		EriJumpRun->RotateFlip(RotateNoneFlipX);
		EriStop->RotateFlip(RotateNoneFlipX);

		bEriFlipX = !bEriFlipX;
		bCanFlip = false;
	}

	if (GetAxisX() == 0)
	{
		if (EriIdle)
		{
			AniEriIdle(graphics, GetPlayerPos(), EriIdle, curFrame, bEriFlipX);
		}
	}
	else
	{
		if (EriRun)
		{
			AniEriRun(graphics, GetPlayerPos(), EriRun, curFrame, bEriFlipX);
		}
	}
	
	// TestSample
	if (EriIdle)
	{
		AniEriIdle(graphics, PointF(100, 100),EriIdle, curFrame, bEriFlipX);
	}
	if (EriJumpIdle)
	{
		AniEriJumpIdle(graphics, PointF(150, 100),EriJumpIdle, curFrame, bEriFlipX);
	}
	if (EriJumpRun)
	{
		AniEriJumpRun(graphics, PointF(200, 100),EriJumpRun, curFrame, bEriFlipX);
	}
	if (EriStop)
	{
		AniEriStop(graphics, PointF(250, 100),EriStop, curFrame, bEriFlipX);
	}
	if (EriRun)
	{
		AniEriRun(graphics, PointF(300, 100),EriRun, curFrame, bEriFlipX);
	}
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
