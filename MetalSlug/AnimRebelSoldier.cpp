#include "framework.h"
#include "AnimRebelSoldier.h"

metalSlug::AnimRebelSoldier::AnimRebelSoldier()
{
	Init();
}

metalSlug::AnimRebelSoldier::~AnimRebelSoldier()
{
}

void metalSlug::AnimRebelSoldier::Init()
{
	imgRatio = GetGlobalRatio();
}

void metalSlug::AnimRebelSoldier::ResetFrame()
{
	
}

bool metalSlug::AnimRebelSoldier::PlayIdle(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos)
{
	int destOffsetX = -44;
	int destOffsetY = -12;
	int xStart[FrameCount_Idle] = { 0,1,2,3,3,2,1,0 };
	int slowRatio = 2;
	Color color(RGB(248, 0, 248));
	cameraView = GetCamera()->GetCameraViewport();

	if (bFlipX == false)
	{
		int bx = GetImages()->rebelSoldierBitmap.bitIdle.bmWidth;
		int by = GetImages()->rebelSoldierBitmap.bitIdle.bmHeight;
		int w = bx / 4;
		int h = by;
		

		if (cameraView.left > destPos.x + bx * imgRatio || cameraView.right < destPos.x) return false;
		if (cameraView.top > destPos.y + by * imgRatio || cameraView.bottom < destPos.y) return false;

		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hIdleImg);

		int frame = (frameIdle / slowRatio) % FrameCount_Idle;
		frameIdle++;
		if ((frameIdle / slowRatio) >= FrameCount_Idle) frameIdle = 0;

		TransparentBlt(hdc, destPos.x - cameraView.left + destOffsetX, destPos.y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}
	else
	{
		int bx = GetImages()->rebelSoldierBitmap.bitIdleFlip.bmWidth;
		int by = GetImages()->rebelSoldierBitmap.bitIdleFlip.bmHeight;
		int w = bx / 4;
		int h = by;

		if (cameraView.left > destPos.x + bx * imgRatio || cameraView.right < destPos.x) return false;
		if (cameraView.top > destPos.y + by * imgRatio || cameraView.bottom < destPos.y) return false;

		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hIdleFlipImg);

		
		int frame = (frameIdle / slowRatio) % FrameCount_Idle;
		frameIdle++;
		if ((frameIdle / slowRatio) >= FrameCount_Idle) frameIdle = 0;

		TransparentBlt(hdc, destPos.x - cameraView.left + destOffsetX, destPos.y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
	
	return true;
}

bool metalSlug::AnimRebelSoldier::PlayRun(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos)
{
	int destOffsetX = -44;
	int destOffsetY = -12;
	int xStart[FrameCount_Run] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	int slowRatio = 4;
	Color color(RGB(248, 0, 248));
	cameraView = GetCamera()->GetCameraViewport();

	if (bFlipX == false)
	{
		int bx = GetImages()->rebelSoldierBitmap.bitRun.bmWidth;
		int by = GetImages()->rebelSoldierBitmap.bitRun.bmHeight;
		int w = bx / 4;
		int h = by;


		if (cameraView.left > destPos.x + bx * imgRatio || cameraView.right < destPos.x) return false;
		if (cameraView.top > destPos.y + by * imgRatio || cameraView.bottom < destPos.y) return false;

		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hRunImg);

		int frame = (frameRun / slowRatio) % FrameCount_Run;
		frameRun++;
		if ((frameRun / slowRatio) >= FrameCount_Run) frameRun = 0;

		TransparentBlt(hdc, destPos.x - cameraView.left + destOffsetX, destPos.y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}
	else
	{
		int bx = GetImages()->rebelSoldierBitmap.bitIdleFlip.bmWidth;
		int by = GetImages()->rebelSoldierBitmap.bitIdleFlip.bmHeight;
		int w = bx / 4;
		int h = by;

		if (cameraView.left > destPos.x + bx * imgRatio || cameraView.right < destPos.x) return false;
		if (cameraView.top > destPos.y + by * imgRatio || cameraView.bottom < destPos.y) return false;

		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hIdleFlipImg);

		int frame = (frameRun / slowRatio) % FrameCount_Run;
		frameRun++;
		if ((frameRun / slowRatio) >= FrameCount_Run) frameRun = 0;

		TransparentBlt(hdc, destPos.x - cameraView.left + destOffsetX, destPos.y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);

	return true;
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