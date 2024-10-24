#pragma once

namespace metalSlug
{
	enum EWeaponType
	{
		Pistol,
	};

	class WeaponSFX
	{
	public:
		WeaponSFX();
		~WeaponSFX();
	private:
#define FrameCount_PistolHit 10

		RECT cameraView;

		float ratio;
		int pistolHitFrame = 0;

	private:
		void Init();

	public:
		bool DrawBullet(HWND hWnd, HDC hdc, EWeaponType type, bool bHit, bool bLookUp, POINT destPos);

	private:
		bool DrawPistol(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, POINT destPos);
		bool DrawPistolHit(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, POINT destPos);

	};
}

