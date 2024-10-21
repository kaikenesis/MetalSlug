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
		HBITMAP hPistolImg;
		BITMAP bitPistol;
		HBITMAP hPistolHitImg;
		BITMAP bitPistolHit;

		RECT cameraView;

		float ratio;

	private:
		void Init();
		void CreateBitmap(HBITMAP& hBitmap, BITMAP& bitmap, LPCWSTR filePath);
		void Delete();

	public:
		bool DrawBullet(HWND hWnd, HDC hdc, EWeaponType type, bool bHit, POINT destPos);
		bool DrawPistol(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, POINT destPos);
		bool DrawPistolHit(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, POINT destPos);

	};
}

