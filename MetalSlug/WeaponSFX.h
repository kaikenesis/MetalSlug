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
		bool DrawBitmap(HWND hWnd, HDC hdc, EWeaponType type, bool bHit, int destX, int destY);
		bool DrawBullet(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, int destX, int destY);
		bool DrawBulletHit(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg, int destX, int destY);

	};
}

