#include "framework.h"
#include "WeaponSFX.h"

metalSlug::WeaponSFX::WeaponSFX()
{
	Init();
}

metalSlug::WeaponSFX::~WeaponSFX()
{
	
}

void metalSlug::WeaponSFX::Init()
{
	ratio = GetGlobalRatio();
}

bool metalSlug::WeaponSFX::DrawBullet(HWND hWnd, HDC hdc, EWeaponType type, bool bHit, bool bLookUp, POINT destPos)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	cameraView = GetCamera()->GetCameraViewport();

	switch (type)
	{
	case Pistol:
	{
		if (bHit == false)
		{
			if (bLookUp)
			{
				return DrawPistol(hdc, hMemDC, hOldBitmap, GetImages()->pistolBitmap.hBulletRotate90Img,
					GetImages()->pistolBitmap.bitBulletRotate90, destPos);
			}
			else
			{
				return DrawPistol(hdc, hMemDC, hOldBitmap, GetImages()->pistolBitmap.hBulletImg,
					GetImages()->pistolBitmap.bitBullet, destPos);
			}
		}
		else
		{
			return DrawPistolHit(hdc, hMemDC, hOldBitmap, GetImages()->pistolBitmap.hHitImg,
				GetImages()->pistolBitmap.bitHit, destPos);
		}
	}
		break;
	case RebelBomb:
	{
		if (bHit == false)
		{
			return DrawRebelBomb(hdc, hMemDC, hOldBitmap, GetImages()->rebelBombBitmap.hBombImg,
				GetImages()->rebelBombBitmap.bitBomb, destPos);
		}
		else
		{
			return DrawFireBombExplosion(hdc, hMemDC, hOldBitmap, GetImages()->explosionBitmap.hFireBombImg,
				GetImages()->explosionBitmap.bitFireBomb, destPos);
		}
	}
		break;
	default:
		break;
	}
}

void metalSlug::WeaponSFX::ResetFrame()
{
	pistolHitFrame = 0;
	rebelBombMoveFrame = 0;
}

bool metalSlug::WeaponSFX::DrawPistol(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, POINT destPos)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int srcOffsetY = 6;
	float imgSizeOffset = 3.0f;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destPos.x + bx * ratio || cameraView.right < destPos.x) return false;
	if (cameraView.top > destPos.y + by * ratio || cameraView.bottom < destPos.y) return false;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);
	
	TransparentBlt(hdc, destPos.x - cameraView.left, destPos.y - cameraView.top, bx * ratio / imgSizeOffset, by * ratio / imgSizeOffset, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
	return true;
}

bool metalSlug::WeaponSFX::DrawPistolHit(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, POINT destPos)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;
	int w = 17;
	int h = 18;
	float imgSizeOffset = 2.0f;
	int frame = pistolHitFrame % FrameCount_PistolHit;
	pistolHitFrame++;
	if (pistolHitFrame >= FrameCount_PistolHit)
	{
		pistolHitFrame = 0;
		return false;
	}

	Color color(RGB(248, 0, 248));

	if (cameraView.left > destPos.x + bx * ratio || cameraView.right < destPos.x) return false;
	if (cameraView.top > destPos.y + by * ratio || cameraView.bottom < destPos.y) return false;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, destPos.x - cameraView.left, destPos.y - cameraView.top, w * imgSizeOffset, h * imgSizeOffset, hMemDC,
		w * frame, 0, w, h, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
	return true;
}

bool metalSlug::WeaponSFX::DrawRebelBomb(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, POINT destPos)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;
	int w = 16;
	int h = 16;
	float imgSizeOffset = 3.0f;
	int slowRatio = 3;
	int frame = (rebelBombMoveFrame / slowRatio) % FrameCount_RebelBombMove;

	if (bFlipX == false)
	{
		rebelBombMoveFrame++;
		if ((rebelBombMoveFrame / slowRatio) >= FrameCount_RebelBombMove)
			rebelBombMoveFrame = 0;
	}
	else
	{
		rebelBombMoveFrame--;
		if ((rebelBombMoveFrame / slowRatio) < 0)
			rebelBombMoveFrame = FrameCount_RebelBombMove * slowRatio;
	}

	Color color(RGB(248, 0, 248));

	if (cameraView.left > destPos.x + bx * ratio || cameraView.right < destPos.x) return false;
	if (cameraView.top > destPos.y + by * ratio || cameraView.bottom < destPos.y) return false;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, destPos.x - cameraView.left, destPos.y - cameraView.top, w * imgSizeOffset, h * imgSizeOffset, hMemDC,
		w * frame, 0, w, h, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
	return true;
}

bool metalSlug::WeaponSFX::DrawFireBombExplosion(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, POINT destPos)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;
	int w = 36;
	int h = 64;
	float imgSizeOffset = 3.0f;
	int offsetX = 23 + (-18 * imgSizeOffset);
	int offsetY = 46 + (-64 * imgSizeOffset);
	int slowRatio = 2;
	int xFrame = (fireBombExplosionFrame / slowRatio) % (FrameCount_FireBombExplosion / 2);
	int yFrame = (fireBombExplosionFrame / slowRatio) / (FrameCount_FireBombExplosion / 2);
	fireBombExplosionFrame++;
	if ((fireBombExplosionFrame / slowRatio) >= FrameCount_FireBombExplosion)
	{
		fireBombExplosionFrame = 0;
		return false;
	}

	Color color(RGB(0, 248, 0));

	if (cameraView.left > destPos.x + bx * ratio || cameraView.right < destPos.x) return false;
	if (cameraView.top > destPos.y + by * ratio || cameraView.bottom < destPos.y) return false;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, destPos.x - cameraView.left + offsetX, destPos.y - cameraView.top + offsetY, w * imgSizeOffset, h * imgSizeOffset, hMemDC,
		w * xFrame, h * yFrame, w, h, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
	return true;
}
