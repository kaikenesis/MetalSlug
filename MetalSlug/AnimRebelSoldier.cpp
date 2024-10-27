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

bool metalSlug::AnimRebelSoldier::PlayIdle(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, PointF destPos)
{
	int bx = GetImages()->rebelSoldierBitmap.bitIdle.bmWidth;
	int by = GetImages()->rebelSoldierBitmap.bitIdle.bmHeight;
	int w = bx / 4;
	int h = by;
	cameraView = GetCamera()->GetCameraViewport();

	if (cameraView.left > destPos.X + bx * imgRatio || cameraView.right < destPos.X) return false;
	if (cameraView.top > destPos.Y + by * imgRatio || cameraView.bottom < destPos.Y) return false;

	int destOffsetX = -44;
	int destOffsetY = -12;
	int xStart[FrameCount_Idle] = { 0,1,2,3,3,2,1,0 };
	int slowRatio = 2;
	Color color(RGB(248, 0, 248));

	int frame = (frameIdle / slowRatio) % FrameCount_Idle;
	frameIdle++;
	if ((frameIdle / slowRatio) >= FrameCount_Idle) frameIdle = 0;

	if (bFlipX == false)
	{
		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hIdleImg);

		TransparentBlt(hdc, destPos.X - cameraView.left + destOffsetX, destPos.Y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}
	else
	{
		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hIdleFlipImg);

		TransparentBlt(hdc, destPos.X - cameraView.left + destOffsetX, destPos.Y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
	
	return true;
}

bool metalSlug::AnimRebelSoldier::PlayRun(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, PointF destPos)
{
	int bx = GetImages()->rebelSoldierBitmap.bitRun.bmWidth;
	int by = GetImages()->rebelSoldierBitmap.bitRun.bmHeight;
	int w = bx / FrameCount_Run;
	int h = by;
	cameraView = GetCamera()->GetCameraViewport();

	if (cameraView.left > destPos.X + bx * imgRatio || cameraView.right < destPos.X) return false;
	if (cameraView.top > destPos.Y + by * imgRatio || cameraView.bottom < destPos.Y) return false;

	int destOffsetX = -44;
	int destOffsetY = -12;
	int xStart[FrameCount_Run] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	int slowRatio = 3;
	Color color(RGB(248, 0, 248));

	int frame = (frameRun / slowRatio) % FrameCount_Run;
	frameRun++;
	if ((frameRun / slowRatio) >= FrameCount_Run) frameRun = 0;

	if (bFlipX == false)
	{
		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hRunImg);

		TransparentBlt(hdc, destPos.X - cameraView.left + destOffsetX, destPos.Y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}
	else
	{
		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hRunFlipImg);

		TransparentBlt(hdc, destPos.X - cameraView.left + destOffsetX, destPos.Y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);

	return true;
}

bool metalSlug::AnimRebelSoldier::PlayDeath(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, PointF destPos)
{
	if (bBlink == true)
	{
		blinkCount++;
		bBlink = false;
		return false;
	}

	int bx = GetImages()->rebelSoldierBitmap.bitDeath.bmWidth;
	int by = GetImages()->rebelSoldierBitmap.bitDeath.bmHeight;
	int w = bx / FrameCount_Death;
	int h = by;
	cameraView = GetCamera()->GetCameraViewport();

	if (cameraView.left > destPos.X + bx * imgRatio || cameraView.right < destPos.X) return false;
	if (cameraView.top > destPos.Y + by * imgRatio || cameraView.bottom < destPos.Y) return false;

	int destOffsetX = -44;
	int destOffsetY = -12;
	int xStart[FrameCount_Death] = { 0,1,2,3,4,5,6,7,8,9,10 };
	int slowRatio = 3;
	Color color(RGB(248, 0, 248));

	int frame = (frameDeath / slowRatio) % FrameCount_Death;
	frameDeath++;
	if ((frameDeath / slowRatio) >= FrameCount_Death)
	{
		bBlink = true;
		frameDeath = FrameCount_Death * slowRatio - 1;
	}

	if (bFlipX == false)
	{
		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hDeathImg);

		TransparentBlt(hdc, destPos.X - cameraView.left + destOffsetX, destPos.Y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}
	else
	{
		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hDeathFlipImg);

		TransparentBlt(hdc, destPos.X - cameraView.left + destOffsetX, destPos.Y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);

	return true;
}

bool metalSlug::AnimRebelSoldier::PlaySurprise(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, PointF destPos)
{
	int bx = GetImages()->rebelSoldierBitmap.bitSurprise.bmWidth;
	int by = GetImages()->rebelSoldierBitmap.bitSurprise.bmHeight;
	int w = bx / FrameCount_Surprise;
	int h = by;
	cameraView = GetCamera()->GetCameraViewport();

	if (cameraView.left > destPos.X + bx * imgRatio || cameraView.right < destPos.X) return false;
	if (cameraView.top > destPos.Y + by * imgRatio || cameraView.bottom < destPos.Y) return false;

	int destOffsetX = -44;
	int destOffsetY = -20;
	int xStart[FrameCount_Surprise] = { 0,1,2,3,4,5,6,7,8,9 };
	int slowRatio = 3;
	Color color(RGB(248, 0, 248));

	int frame = (frameSurprise / slowRatio) % FrameCount_Surprise;
	frameSurprise++;
	if ((frameSurprise / slowRatio) >= FrameCount_Surprise)
	{
		bPlaySurprise = false;
		frameSurprise = 0;
	}

	if (bFlipX == false)
	{
		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hSurpriseImg);

		TransparentBlt(hdc, destPos.X - cameraView.left + destOffsetX, destPos.Y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}
	else
	{
		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hSurpriseFlipImg);

		TransparentBlt(hdc, destPos.X - cameraView.left + destOffsetX, destPos.Y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);

	return true;
}

bool metalSlug::AnimRebelSoldier::PlayRollingBomb(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, PointF destPos)
{
	int bx = GetImages()->rebelSoldierBitmap.bitRollingBomb.bmWidth;
	int by = GetImages()->rebelSoldierBitmap.bitRollingBomb.bmHeight;
	int w = bx / FrameCount_RollingBomb;
	int h = by;
	cameraView = GetCamera()->GetCameraViewport();

	if (cameraView.left > destPos.X + bx * imgRatio || cameraView.right < destPos.X) return false;
	if (cameraView.top > destPos.Y + by * imgRatio || cameraView.bottom < destPos.Y) return false;

	int destOffsetX = -44;
	int destOffsetY = -12;
	int xStart[FrameCount_RollingBomb] = { 0,1,2,3,4,5,6,7,8,9 };
	int slowRatio = 3;
	Color color(RGB(248, 0, 248));

	int frame = (frameRollingBomb / slowRatio) % FrameCount_RollingBomb;
	frameRollingBomb++;
	if ((frameRollingBomb / slowRatio) >= FrameCount_RollingBomb)
	{
		bPlayRollingBomb = false;
		frameRollingBomb = 0;
	}

	if (bFlipX == false)
	{
		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hRollingBombImg);

		TransparentBlt(hdc, destPos.X - cameraView.left + destOffsetX, destPos.Y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}
	else
	{
		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)SelectObject(hMemDC, GetImages()->rebelSoldierBitmap.hRollingBombFlipImg);

		TransparentBlt(hdc, destPos.X - cameraView.left + destOffsetX, destPos.Y - cameraView.top + destOffsetY, w * imgRatio, h * imgRatio, hMemDC,
			w * xStart[frame], 0, w, h, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);

	return true;
}