#include "framework.h"
#include "Game.h"
#include "WeaponSFX.h"

metalSlug::WeaponSFX::WeaponSFX()
{
	Init();
}

metalSlug::WeaponSFX::~WeaponSFX()
{
	Delete();
}

void metalSlug::WeaponSFX::Init()
{
	CreateBitmap(hPistolImg, bitPistol, _T("images/Metal-Slug-3-Weapon-SFX_Pistol_Bullet.bmp"));
	CreateBitmap(hPistolRotate90Img, bitPistolRotate90, _T("images/Metal-Slug-3-Weapon-SFX_Pistol_Bullet_Rotate90.bmp"));
	CreateBitmap(hPistolHitImg, bitPistolHit, _T("images/Metal-Slug-3-Weapon-SFX_Pistol_Hit.bmp"));

	ratio = GetGlobalRatio();
}

void metalSlug::WeaponSFX::CreateBitmap(HBITMAP& hBitmap, BITMAP& bitmap, LPCWSTR filePath)
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

void metalSlug::WeaponSFX::Delete()
{
	DeleteObject(hPistolImg);
	DeleteObject(hPistolRotate90Img);
	DeleteObject(hPistolHitImg);
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
				return DrawPistol(hdc, hMemDC, hOldBitmap, hPistolRotate90Img, bitPistolRotate90, destPos);
			else
				return DrawPistol(hdc, hMemDC, hOldBitmap, hPistolImg, bitPistol, destPos);
		}
		else return DrawPistolHit(hdc, hMemDC, hOldBitmap, hPistolHitImg, bitPistolHit, destPos);
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