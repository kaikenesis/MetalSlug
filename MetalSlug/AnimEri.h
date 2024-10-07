#pragma once

#include "framework.h"

namespace metalSlug
{
#define FrameCount_Idle 16
#define FrameCount_JumpIdleStart 16
#define FrameCount_JumpRunStart 16
#define FrameCount_Stop 12
#define FrameCount_RunStart 4
#define FrameCount_Run 16
#define FrameCount_LookUpStart 2
#define FrameCount_LookUp 16
#define FrameCount_ShootForward 16
#define FrameCount_ShootUp 16

	class AnimEri
	{
	public:
		AnimEri();
		~AnimEri();

	private:
		Bitmap* EriIdle;
		Bitmap* EriJumpIdle;
		Bitmap* EriJumpRun;
		Bitmap* EriStop;
		Bitmap* EriRun;
		Bitmap* EriTurn;
		Bitmap* EriLookUp;
		Bitmap* EriShootForward;
		Bitmap* EriShootUp;

		bool bRunLoop = false;
		bool bLookUpLoop = false;
		bool bLookUp = false;

		bool bEriFlipX = false;
		bool bCanFlip = false;
		bool bCanShoot = true;
		bool bPlayedShoot = false;

		int idleFrame = 0;
		int jumpIdleFrame = 0;
		int jumpRunFrame = 0;
		int stopFrame = 0;
		int runFrame = 0;
		int lookUpFrame = 0;
		int shootForwardFrame = 0;
		int shootUpFrame = 0;

	public:
		BOOL IsRunLoop() { return bRunLoop; }
		BOOL IsCanFlip() { return bCanFlip; }
		BOOL IsFlip() { return bEriFlipX; }
		BOOL IsCanShoot() { return bCanShoot; }

		void SetLookUp(bool inValue) { bLookUp = inValue; }
		void SetLookUpLoop(bool inValue) { bLookUpLoop = inValue; }
		void SetCanFlip(bool inValue) { bCanFlip = inValue; }

	public:
		void Init();
		void Delete();

		void FlipXBitmap();
		void UpdateShootFrame();
		void ResetFrame();
		void ResetShootFrame();
		void PlayShootAnim();

		void AniEriIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriJumpIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriJumpRun(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriStop(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriRun(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriLookUp(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriTurn(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriShootFront(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriShootUp(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		// crouchIdle, crouchMove, shoot(forward, up, crouch), throwBomb
	};
}

