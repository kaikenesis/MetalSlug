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
			if(bLookUp)
				return DrawPistol(hdc, hMemDC, hOldBitmap, GetImages()->pistolBitmap.hBulletRotate90Img, GetImages()->pistolBitmap.bitBulletRotate90, destPos);
			else
				return DrawPistol(hdc, hMemDC, hOldBitmap, GetImages()->pistolBitmap.hBulletImg, GetImages()->pistolBitmap.bitBullet, destPos);
		}
		else return DrawPistolHit(hdc, hMemDC, hOldBitmap, GetImages()->pistolBitmap.hHitImg, GetImages()->pistolBitmap.bitHit, destPos);
	}
		break;
	default:
		break;
	}
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