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
		int blinkCount = 0;

		int frameIdle = 0;
		int frameRun = 0;
		int frameDeath = 0;
		int frameSurprise = 0;
		int frameRollingBomb = 0;

		bool bPlaySurprise = false;
		bool bPlayRollingBomb = false;

		bool bFlipX = false;
		bool bBlink = false;

	private:
		void Init();
	
	public:
		bool IsFlipX() { return bFlipX; }
		bool IsPlaySurprise() { return bPlaySurprise; }
		bool IsPlayRollingBomb() { return bPlayRollingBomb; }

		int GetBlinkCount() { return blinkCount; }

		void SetImageRatio(float ratio) { imgRatio = ratio; }
		void SetCameraView(RECT CameraView) { cameraView = CameraView; }
		void SetFlipX(bool value) { bFlipX = value; }

		void PlayStartSurprise() { bPlaySurprise = true; }
		void PlayStartRollingBomb() { bPlayRollingBomb = true; }

		void ResetFrame();
		void ResetBlinkCount() { blinkCount = 0; }

		bool PlayIdle(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, PointF destPos);
		bool PlayRun(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, PointF destPos);
		bool PlayDeath(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, PointF destPos);
		bool PlaySurprise(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, PointF destPos);
		bool PlayRollingBomb(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, PointF destPos);
	};
}
