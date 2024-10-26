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
	frameIdle = 0;
	frameRun = 0;
	frameDeath = 0;
	frameSurprise = 0;
	frameRollingBomb = 0;
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
	int slowRatio = 3;
	Color color(RGB(248, 0, 248));
	cameraView = GetCamera()->GetCameraViewport();

	if (bFlipX == false)
	{
		int bx = GetImages()->rebelSoldierBitmap.bitRun.bmWidth;
		int by = GetImages()->rebelSoldierBitmap.bitRun.bmHeight;
		int w = bx / FrameCount_Run;
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
		int bx = GetImages()->rebelSoldierBitmap.bitRunFlip.bmWidth;
		int by = GetImages()->rebelSoldierBitmap.bitRunFlip.bmHeight;
		int w = bx / FrameCount_Run;
		int h = by;

		if (cameraView.left > destPos.x + bx * imgRatio || cameraView.right < destPos.x) return false;
		if (cameraView.top > destPos.y + by * imgRatio || cameraView.bottom < destPos.y) return false;

		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hRunFlipImg);

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
	int destOffsetX = -44;
	int destOffsetY = -12;
	int xStart[FrameCount_Death] = { 0,1,2,3,4,5,6,7,8,9,10 };
	int slowRatio = 3;
	Color color(RGB(248, 0, 248));
	cameraView = GetCamera()->GetCameraViewport();

	if (bFlipX == false)
	{
		int bx = GetImages()->rebelSoldierBitmap.bitDeath.bmWidth;
		int by = GetImages()->rebelSoldierBitmap.bitDeath.bmHeight;
		int w = bx / FrameCount_Death;
		int h = by;


		if (cameraView.left > destPos.x + bx * imgRatio || cameraView.right < destPos.x) return false;
		if (cameraView.top > destPos.y + by * imgRatio || cameraView.bottom < destPos.y) return false;

		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hDeathImg);

		int frame = (frameRun / slowRatio) % FrameCount_Death;
		frameRun++;
		if ((frameRun / slowRatio) >= FrameCount_Death) frameRun = 0;

		TransparentBlt(hdc, destPos.x - cameraView.left + destOffsetX, destPos.y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}
	else
	{
		int bx = GetImages()->rebelSoldierBitmap.bitDeathFlip.bmWidth;
		int by = GetImages()->rebelSoldierBitmap.bitDeathFlip.bmHeight;
		int w = bx / FrameCount_Death;
		int h = by;

		if (cameraView.left > destPos.x + bx * imgRatio || cameraView.right < destPos.x) return false;
		if (cameraView.top > destPos.y + by * imgRatio || cameraView.bottom < destPos.y) return false;

		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hDeathFlipImg);

		int frame = (frameRun / slowRatio) % FrameCount_Death;
		frameRun++;
		if ((frameRun / slowRatio) >= FrameCount_Death) frameRun = 0;

		TransparentBlt(hdc, destPos.x - cameraView.left + destOffsetX, destPos.y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);

	return true;
}

bool metalSlug::AnimRebelSoldier::PlaySurprise(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos)
{
	int destOffsetX = -44;
	int destOffsetY = -20;
	int xStart[FrameCount_Surprise] = { 0,1,2,3,4,5,6,7,8,9 };
	int slowRatio = 3;
	Color color(RGB(248, 0, 248));
	cameraView = GetCamera()->GetCameraViewport();

	if (bFlipX == false)
	{
		int bx = GetImages()->rebelSoldierBitmap.bitSurprise.bmWidth;
		int by = GetImages()->rebelSoldierBitmap.bitSurprise.bmHeight;
		int w = bx / FrameCount_Surprise;
		int h = by;


		if (cameraView.left > destPos.x + bx * imgRatio || cameraView.right < destPos.x) return false;
		if (cameraView.top > destPos.y + by * imgRatio || cameraView.bottom < destPos.y) return false;

		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hSurpriseImg);

		int frame = (frameRun / slowRatio) % FrameCount_Surprise;
		frameRun++;
		if ((frameRun / slowRatio) >= FrameCount_Surprise) frameRun = 0;

		TransparentBlt(hdc, destPos.x - cameraView.left + destOffsetX, destPos.y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}
	else
	{
		int bx = GetImages()->rebelSoldierBitmap.bitSurpriseFlip.bmWidth;
		int by = GetImages()->rebelSoldierBitmap.bitSurpriseFlip.bmHeight;
		int w = bx / FrameCount_Surprise;
		int h = by;

		if (cameraView.left > destPos.x + bx * imgRatio || cameraView.right < destPos.x) return false;
		if (cameraView.top > destPos.y + by * imgRatio || cameraView.bottom < destPos.y) return false;

		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hSurpriseFlipImg);

		int frame = (frameRun / slowRatio) % FrameCount_Surprise;
		frameRun++;
		if ((frameRun / slowRatio) >= FrameCount_Surprise) frameRun = 0;

		TransparentBlt(hdc, destPos.x - cameraView.left + destOffsetX, destPos.y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);

	return true;
}

bool metalSlug::AnimRebelSoldier::PlayRollingBomb(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos)
{
	int destOffsetX = -44;
	int destOffsetY = -12;
	int xStart[FrameCount_RollingBomb] = { 0,1,2,3,4,5,6,7,8,9 };
	int slowRatio = 3;
	Color color(RGB(248, 0, 248));
	cameraView = GetCamera()->GetCameraViewport();

	if (bFlipX == false)
	{
		int bx = GetImages()->rebelSoldierBitmap.bitRollingBomb.bmWidth;
		int by = GetImages()->rebelSoldierBitmap.bitRollingBomb.bmHeight;
		int w = bx / FrameCount_RollingBomb;
		int h = by;


		if (cameraView.left > destPos.x + bx * imgRatio || cameraView.right < destPos.x) return false;
		if (cameraView.top > destPos.y + by * imgRatio || cameraView.bottom < destPos.y) return false;

		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hRollingBombImg);

		int frame = (frameRun / slowRatio) % FrameCount_RollingBomb;
		frameRun++;
		if ((frameRun / slowRatio) >= FrameCount_RollingBomb) frameRun = 0;

		TransparentBlt(hdc, destPos.x - cameraView.left + destOffsetX, destPos.y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}
	else
	{
		int bx = GetImages()->rebelSoldierBitmap.bitRollingBombFlip.bmWidth;
		int by = GetImages()->rebelSoldierBitmap.bitRollingBombFlip.bmHeight;
		int w = bx / FrameCount_RollingBomb;
		int h = by;

		if (cameraView.left > destPos.x + bx * imgRatio || cameraView.right < destPos.x) return false;
		if (cameraView.top > destPos.y + by * imgRatio || cameraView.bottom < destPos.y) return false;

		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hRollingBombFlipImg);

		int frame = (frameRun / slowRatio) % FrameCount_RollingBomb;
		frameRun++;
		if ((frameRun / slowRatio) >= FrameCount_RollingBomb) frameRun = 0;

		TransparentBlt(hdc, destPos.x - cameraView.left + destOffsetX, destPos.y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);

	return true;
}