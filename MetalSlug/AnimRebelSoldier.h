#pragma once

namespace metalSlug
{
	class AnimRebelSoldier
	{
#define FrameCount_Idle 8
#define FrameCount_Run 12
#define FrameCount_Death 11
#define FrameCount_Surprise 10
#define FrameCount_RollingBomb 10

	public:
		AnimRebelSoldier();
		~AnimRebelSoldier();

	private:
		float imgRatio = 1.0f;
		RECT cameraView;

		int frameIdle = 0;
		int frameRun = 0;
		int frameDeath = 0;
		int frameSurprise = 0;
		int frameRollingBomb = 0;

		bool bFlipX = false;

	private:
		void Init();

		void ResetFrame();
	
	public:
		void SetImageRatio(float ratio) { imgRatio = ratio; }
		void SetCameraView(RECT CameraView) { cameraView = CameraView; }
		void SetFlip() { bFlipX = !bFlipX; }

		bool PlayIdle(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos);
		bool PlayRun(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos);
		bool PlayDeath(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos);
		bool PlaySurprise(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos);
		bool PlayRollingBomb(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, POINT destPos);
	};
}
