#pragma once

namespace metalSlug
{
#define FrameCount_Idle 16
#define FrameCount_RunStart 4
#define FrameCount_Run 16
#define FrameCount_Stop 12
#define FrameCount_JumpIdleStart 16
#define FrameCount_JumpRunStart 16
#define FrameCount_CrouchStart 1
#define FrameCount_CrouchIdle 16
#define FrameCount_CrouchMove 14
#define FrameCount_LookUpStart 2
#define FrameCount_LookUp 16
#define FrameCount_LookDown 3
#define FrameCount_ShootForward 16
#define FrameCount_ShootUp 16
#define FrameCount_ShootDown 8
#define FrameCount_ShootCrouch 14
#define FrameCount_ThrowBomb 1

	class AnimEri
	{
	public:
		AnimEri();
		~AnimEri();

	private:
		Bitmap* EriIdle;
		Bitmap* EriRun;
		Bitmap* EriStop;
		Bitmap* EriTurn;
		Bitmap* EriJumpIdle;
		Bitmap* EriJumpRun;
		Bitmap* EriCrouch;
		Bitmap* EriLookUp;
		Bitmap* EriShootForward;
		Bitmap* EriShootUp;
		Bitmap* EriShootDown;
		Bitmap* EriShootCrouch;
		Bitmap* EriThrowBomb;

		bool bRunLoop = false;
		bool bLookUpLoop = false;
		bool bLookUp = false;
		bool bPressedLookDown = false;
		bool bLookDown = false;
		bool bCrouchLoop = false;
		bool bCrouch = false;

		bool bEriFlipX = false;
		bool bCanFlip = false;
		bool bCanShoot = true;
		bool bPlayedShoot = false;

		int idleFrame = 0;
		int runFrame = 0;
		int stopFrame = 0;
		int jumpIdleFrame = 0;
		int jumpRunFrame = 0;
		int crouchFrame = 0;
		int lookUpFrame = 0;
		int lookDownFrame = 0;
		int shootForwardFrame = 0;
		int shootUpFrame = 0;
		int shootDownFrame = 0;
		int shootCrouchFrame = 0;
		int throwBombFrame = 0;

		int fireColdown = 3;
		float imgRatio = 1.0f;

	public:
		BOOL IsRunLoop() { return bRunLoop; }
		BOOL IsCanFlip() { return bCanFlip; }
		BOOL IsFlip() { return bEriFlipX; }
		BOOL IsCanShoot() { return bCanShoot; }
		BOOL IsShoot() { return bPlayedShoot; }
		BOOL IsLookUp() { return bLookUp; }
		BOOL IsLookDown() { return bLookDown; }
		BOOL IsCrouch() { return bCrouch; }

		void SetLookUp(bool inValue) { bLookUp = inValue; }
		void SetLookUpLoop(bool inValue) { bLookUpLoop = inValue; }
		void SetLookDown(bool inValue) { bLookDown = inValue; }
		void SetPressedLookDown(bool inValue) { bPressedLookDown = inValue; }
		void SetCrouch(bool inValue) { bCrouch = inValue; }
		void SetCrouchLoop(bool inValue) { bCrouchLoop = inValue; }
		void SetCanFlip(bool inValue) { bCanFlip = inValue; }

	public:
		void Init();
		void Delete();

		void SetImageRatio(float ratio) { imgRatio = ratio; }

		void FlipXBitmap();
		void UpdateShootFrame();
		void ResetFrame();
		void ResetShootFrame();
		void PlayShootAnim();

		void AniEriIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriRun(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriStop(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriTurn(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriJumpIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriJumpRun(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriCrouchIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriCrouchMove(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriLookUp(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriLookDown(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriShootFront(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriShootUp(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriShootDown(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriShootCrouch(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		void AniEriThrowBomb(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
		// crouchIdle, crouchMove, shoot(forward, up, crouch), throwBomb
	};
}

