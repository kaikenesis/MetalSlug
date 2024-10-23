#include "framework.h"
#include "Game.h"
#include "AnimRebelSoldier.h"

metalSlug::AnimRebelSoldier::AnimRebelSoldier()
{
	Init();
}

metalSlug::AnimRebelSoldier::~AnimRebelSoldier()
{
	Delete();
}

void metalSlug::AnimRebelSoldier::Init()
{
	CreateBitmap(hIdleImg, bitIdle, _T("images/Metal-Slug-3-Rebel-Soldier_Idle.bmp"));
	CreateBitmap(hRunImg, bitRun, _T("images/Metal-Slug-3-Rebel-Soldier_Run.bmp"));
	CreateBitmap(hDeathImg, bitDeath, _T("images/Metal-Slug-3-Rebel-Soldier_Death.bmp"));
	CreateBitmap(hSurpriseImg, bitSurprise, _T("images/Metal-Slug-3-Rebel-Soldier_Surprise.bmp"));
	CreateBitmap(hRollingBombImg, bitRollingBomb, _T("images/Metal-Slug-3-Rebel-Soldier_RollingBomb.bmp"));

	imgRatio = GetGlobalRatio();
}

void metalSlug::AnimRebelSoldier::Delete()
{
	DeleteObject(hIdleImg);
	DeleteObject(hRunImg);
	DeleteObject(hDeathImg);
	DeleteObject(hSurpriseImg);
	DeleteObject(hRollingBombImg);
}

void metalSlug::AnimRebelSoldier::CreateBitmap(HBITMAP& hBitmap, BITMAP& bitmap, LPCWSTR filePath)
{
	hBitmap = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hBitmap == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("이미지 로드 에러"), _T("Error"), MB_OK);
	}
	else
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
}

void metalSlug::AnimRebelSoldier::ResetFrame()
{
}

bool metalSlug::AnimRebelSoldier::PlayIdle(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos)
{
	int bx = bitIdle.bmWidth;
	int by = bitIdle.bmHeight;
	int w = bx / 4;
	int h = by;
	int srcOffsetY = 0;
	float imgSizeOffset = 1.0f;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destPos.x + bx * imgRatio || cameraView.right < destPos.x) return false;
	if (cameraView.top > destPos.y + by * imgRatio || cameraView.bottom < destPos.y) return false;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hIdleImg);

	if (bFlipX == false)
	{
		int xStart[FrameCount_Idle] = { 0,1,2,3,3,2,1,0 };
		int frame = frameIdle % FrameCount_Idle;
		frameIdle++;
		if (frameIdle >= FrameCount_Idle) frameIdle = 0;

		TransparentBlt(hdc, destPos.x - cameraView.left, destPos.y - cameraView.top, bx * imgRatio / imgSizeOffset, by * imgRatio / imgSizeOffset, hMemDC,
			w * xStart[frame], 0, bx, by - srcOffsetY, color.GetValue());
	}
	else
	{
	}
	
	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
	
	return true;
}

bool metalSlug::AnimRebelSoldier::PlayRun(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos)
{
	return false;
}

bool metalSlug::AnimRebelSoldier::PlayDeath(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos)
{
	return false;
}

bool metalSlug::AnimRebelSoldier::PlaySurprise(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos)
{
	return false;
}

bool metalSlug::AnimRebelSoldier::PlayRollingBomb(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos)
{
	return false;
}