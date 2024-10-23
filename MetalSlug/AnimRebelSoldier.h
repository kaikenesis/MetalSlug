#pragma once

namespace metalSlug
{
	class AnimRebelSoldier
	{
#define FrameCount_Idle 8

	public:
		AnimRebelSoldier();
		~AnimRebelSoldier();

	private:
		HBITMAP hIdleImg;
		BITMAP bitIdle;
		HBITMAP hRunImg;
		BITMAP bitRun;
		HBITMAP hDeathImg;
		BITMAP bitDeath;
		HBITMAP hSurpriseImg;
		BITMAP bitSurprise;
		HBITMAP hRollingBombImg;
		BITMAP bitRollingBomb;

		float imgRatio = 1.0f;
		RECT cameraView;

		int frameIdle = 0;

		bool bFlipX = false;

	private:
		void Init();
		void Delete();

		void CreateBitmap(HBITMAP& hBitmap, BITMAP& bitmap, LPCWSTR filePath);
		void ResetFrame();
	
	public:
		void SetImageRatio(float ratio) { imgRatio = ratio; }
		void SetCameraView(RECT CameraView) { cameraView = CameraView; }

		bool PlayIdle(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos);
		bool PlayRun(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos);
		bool PlayDeath(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos);
		bool PlaySurprise(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos);
		bool PlayRollingBomb(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos);
	};
}
