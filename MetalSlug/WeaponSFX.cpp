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
	DeleteObject(hPistolHitImg);
}

bool metalSlug::WeaponSFX::DrawBitmap(HWND hWnd, HDC hdc, EWeaponType type, bool bHit, int destX, int destY)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	cameraView = GetCamera()->GetCameraViewport();

	switch (type)
	{
	case Pistol:
	{
		if (bHit == false) return DrawBullet(hdc, hMemDC, hOldBitmap, hPistolImg, bitPistol, destX, destY);
		else return DrawBulletHit(hdc, hMemDC, hOldBitmap, hPistolHitImg, bitPistolHit, destX, destY);
	}
		break;
	default:
		break;
	}
}

bool metalSlug::WeaponSFX::DrawBullet(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, int destX, int destY)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return false;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);
	
	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
	return true;
}

bool metalSlug::WeaponSFX::DrawBulletHit(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, int destX, int destY)
{
	return true;
}
