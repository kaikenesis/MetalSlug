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
		
		HBITMAP hPistolImg;
		BITMAP bitPistol;
		HBITMAP hPistolRotate90Img;
		BITMAP bitPistolRotate90;
		HBITMAP hPistolHitImg;
		BITMAP bitPistolHit;

		RECT cameraView;

		float ratio;
		int pistolHitFrame = 0;

	private:
		void Init();
		void CreateBitmap(HBITMAP& hBitmap, BITMAP& bitmap, LPCWSTR filePath);
		void Delete();

	public:
		bool DrawBullet(HWND hWnd, HDC hdc, EWeaponType type, bool bHit, bool bLookUp, POINT destPos);
		bool DrawPistol(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, POINT destPos);
		bool DrawPistolHit(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, POINT destPos);

	};
}

