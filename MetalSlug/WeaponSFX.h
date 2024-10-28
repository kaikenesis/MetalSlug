#pragma once

namespace metalSlug
{
	class WeaponSFX
	{
	public:
		WeaponSFX();
		~WeaponSFX();
	private:
#define FrameCount_PistolHit 10
#define FrameCount_RebelBombMove 8
#define FrameCount_FireBombExplosion 26

		RECT cameraView;

		float ratio;
		int pistolHitFrame = 0;
		int rebelBombMoveFrame = 0;
		int fireBombExplosionFrame = 0;
		
		bool bFlipX = true;

	private:
		void Init();

	public:
		bool DrawBullet(HWND hWnd, HDC hdc, EWeaponType type, bool bHit, bool bLookUp, POINT destPos);

		void ResetFrame();

	private:
		bool DrawPistol(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, POINT destPos);
		bool DrawPistolHit(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, POINT destPos);
		bool DrawRebelBomb(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, POINT destPos);
		bool DrawFireBombExplosion(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, POINT destPos);
	};
}

