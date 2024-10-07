#include "AnimEri.h"

using namespace metalSlug;

metalSlug::AnimEri::AnimEri()
{
	Init();
}

metalSlug::AnimEri::~AnimEri()
{
	Delete();
}

void metalSlug::AnimEri::Init()
{
	EriIdle = new Bitmap(_T("images/Eri Kasamoto_Idle.png"));
	EriJumpIdle = new Bitmap(_T("images/Eri Kasamoto_JumpIdle.png"));
	EriJumpRun = new Bitmap(_T("images/Eri Kasamoto_JumpRun.png"));
	EriStop = new Bitmap(_T("images/Eri Kasamoto_JumpEnd.png"));
	EriRun = new Bitmap(_T("images/Eri Kasamoto_Run.png"));
	EriTurn = new Bitmap(_T("images/Eri Kasamoto_Turn.png"));
	EriLookUp = new Bitmap(_T("images/Eri Kasamoto_LookUp.png"));
	EriShootForward = new Bitmap(_T("images/Eri Kasamoto_ShootForward.png"));
	EriShootUp = new Bitmap(_T("images/Eri Kasamoto_ShootUp.png"));
}

void metalSlug::AnimEri::Delete()
{
	delete EriIdle;
	delete EriJumpIdle;
	delete EriJumpRun;
	delete EriStop;
	delete EriRun;
	delete EriTurn;
	delete EriLookUp;
	delete EriShootForward;
	delete EriShootUp;
}

void metalSlug::AnimEri::FlipXBitmap()
{
	EriIdle->RotateFlip(RotateNoneFlipX);
	EriRun->RotateFlip(RotateNoneFlipX);
	EriJumpIdle->RotateFlip(RotateNoneFlipX);
	EriJumpRun->RotateFlip(RotateNoneFlipX);
	EriStop->RotateFlip(RotateNoneFlipX);
	EriLookUp->RotateFlip(RotateNoneFlipX);
	EriShootForward->RotateFlip(RotateNoneFlipX);
	EriShootUp->RotateFlip(RotateNoneFlipX);

	bEriFlipX = !bEriFlipX;
	bCanFlip = false;
}

void metalSlug::AnimEri::UpdateShootFrame()
{
	shootForwardFrame++;
	shootUpFrame++;
}

void metalSlug::AnimEri::ResetFrame()
{
	jumpIdleFrame = 0;
	jumpRunFrame = 0;
	stopFrame = 0;
	lookUpFrame = 0;
}

void metalSlug::AnimEri::ResetShootFrame()
{
	shootForwardFrame = 0;
	shootUpFrame = 0;
}

void metalSlug::AnimEri::PlayShootAnim()
{
	bPlayedShoot = true;
	ResetShootFrame();
}

void metalSlug::AnimEri::AniEriIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriIdle;
	int w = 36;
	int h = 36;
	int upperBody_yStart = 0;
	int lowerBody_yStart = upperBody_yStart + h;
	int upperBody_Yoffset = -10;
	int upperBody_Xoffset = 4;
	int frame = idleFrame % FrameCount_Idle;
	int rtW = (int)(1.5f * w);
	int rtH = (int)(1.5f * h);
	
	idleFrame++;
	if (idleFrame % FrameCount_Idle == 0) idleFrame = 0;

	if (bFlipX == false)
	{
		int xStart[FrameCount_Idle] = { 0,0,1,1,2,2,3,3,3,3,2,2,1,1,0,0 };
		Rect rtLower(pPos.X, pPos.Y, rtW, rtH);
		Rect rtUpper(rtLower.X + upperBody_Xoffset, rtLower.Y + upperBody_Yoffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, 4 * w, 0, w, h, UnitPixel);
		if (bLookUp == true)
		{
			if (bPlayedShoot == true)
				AniEriShootUp(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
		}
		else
		{
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
			else
				graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
		}
	}
	else
	{
		int xStart[FrameCount_Idle] = { 17,17,16,16,15,15,14,14,14,14,15,15,16,16,17,17 };
		Rect rtLower(pPos.X, pPos.Y, rtW, rtH);
		Rect rtUpper(rtLower.X - upperBody_Xoffset, rtLower.Y + upperBody_Yoffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, 13 * w, 0, w, h, UnitPixel);
		if (bLookUp == true)
		{
			if (bPlayedShoot == true)
				AniEriShootUp(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
		}
		else
		{
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
			else
				graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
		}
	}
}

void metalSlug::AnimEri::AniEriJumpIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriJumpIdle;
	int w = 36;
	int h = 36;
	int upperBody_yStart = 0;
	int lowerBody_yStart = upperBody_yStart + h;
	int Yoffset = 23;
	int frame = jumpIdleFrame % FrameCount_JumpIdleStart;
	int rtW = (int)(1.5f * w);
	int rtH = (int)(1.5f * h);
	
	jumpIdleFrame++;
	if (jumpIdleFrame % FrameCount_JumpIdleStart == 0) jumpIdleFrame = FrameCount_JumpIdleStart - 1;

	if (bFlipX == false)
	{
		int xStart[FrameCount_JumpIdleStart] = { 0,1,2,3,4,5,5,4,4,3,3,3,3,3,3,3 };
		Rect rtLower(pPos.X, pPos.Y, rtW, rtH);
		Rect rtUpper(rtLower.X, rtLower.Y - Yoffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, xStart[frame] * w, lowerBody_yStart, w, h, UnitPixel);
		if (bLookUp == true)
		{
			if (bPlayedShoot == true)
				AniEriShootUp(graphics, PointF(rtUpper.X + 5, rtUpper.Y + 3), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF(rtUpper.X + 5, rtUpper.Y + 3), NULL, 0, bFlipX);
		}
		else
		{
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF(rtUpper.X + 5, rtUpper.Y + 3), NULL, 0, bFlipX);
			else
				graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
		}
	}
	else
	{
		int xStart[FrameCount_JumpIdleStart] = { 5,4,3,2,1,0,0,1,1,2,2,2,2,2,2,2 };
		Rect rtLower(pPos.X, pPos.Y, rtW, rtH);
		Rect rtUpper(rtLower.X, rtLower.Y - Yoffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, xStart[frame] * w, lowerBody_yStart, w, h, UnitPixel);
		if (bLookUp == true)
		{
			if (bPlayedShoot == true)
				AniEriShootUp(graphics, PointF(rtUpper.X - 5, rtUpper.Y + 3), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF(rtUpper.X - 5, rtUpper.Y + 3), NULL, 0, bFlipX);
		}
		else
		{
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF(rtUpper.X - 5, rtUpper.Y + 3), NULL, 0, bFlipX);
			else
				graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
		}
	}
}

void metalSlug::AnimEri::AniEriJumpRun(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriJumpRun;
	int w = 36;
	int h = 36;
	int upperBody_yStart = 0;
	int lowerBody_yStart = upperBody_yStart + h;
	int Yoffset = 10;
	int upperBody_Xoffset = -4;
	int frame = jumpRunFrame % FrameCount_JumpIdleStart;
	int rtW = (int)(1.5f * w);
	int rtH = (int)(1.5f * h);
	
	jumpRunFrame++;
	if (jumpRunFrame % FrameCount_JumpIdleStart == 0) jumpRunFrame = FrameCount_JumpIdleStart - 1;
	
	if (bFlipX == false)
	{
		int xStart[FrameCount_JumpIdleStart] = { 0,1,2,2,2,2,2,3,3,4,4,5,5,5,5,5 };
		Rect rtLower(pPos.X, pPos.Y, rtW, rtH);
		Rect rtUpper(rtLower.X + upperBody_Xoffset, rtLower.Y - Yoffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, xStart[frame] * w, lowerBody_yStart, w, h, UnitPixel);
		if (bLookUp == true)
		{
			if (bPlayedShoot == true)
				AniEriShootUp(graphics, PointF(rtUpper.X + 5, rtUpper.Y - 1), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF(rtUpper.X + 5, rtUpper.Y - 1), NULL, 0, bFlipX);
		}
		else
		{
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF(rtUpper.X + 5, rtUpper.Y - 1), NULL, 0, bFlipX);
			else
				graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
		}
		
	}
	else
	{
		int xStart[FrameCount_JumpIdleStart] = { 5,4,3,3,3,3,3,2,2,1,1,0,0,0,0,0 };
		Rect rtLower(pPos.X, pPos.Y, rtW, rtH);
		Rect rtUpper(rtLower.X - upperBody_Xoffset, rtLower.Y - Yoffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, xStart[frame] * w, lowerBody_yStart, w, h, UnitPixel);
		if (bLookUp == true)
		{
			if (bPlayedShoot == true)
				AniEriShootUp(graphics, PointF(rtUpper.X - 5, rtUpper.Y - 1), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF(rtUpper.X - 5, rtUpper.Y - 1), NULL, 0, bFlipX);
		}
		else
		{
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF(rtUpper.X - 5, rtUpper.Y - 1), NULL, 0, bFlipX);
			else
				graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
		}
	}
}

void metalSlug::AnimEri::AniEriStop(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriStop;
	int Body_yStart = 0;
	int w = 36;
	int h = 36;
	int frame = stopFrame % FrameCount_Stop;
	int rtW = (int)(1.5f * w);
	int rtH = (int)(1.5f * h);
	
	stopFrame++;
	if (stopFrame % FrameCount_Stop == 0) stopFrame = FrameCount_Stop - 1;

	if (bFlipX == false)
	{
		int xStart[FrameCount_Stop] = { 0,1,2,3,3,2,2,1,1,0,0,0 };
		Rect rt(pPos.X, pPos.Y, rtW, rtH);

		graphics->DrawImage(bitmap, rt, xStart[frame] * w, Body_yStart, w, h, UnitPixel);
	}
	else
	{
		int xStart[FrameCount_Stop] = { 3,2,1,0,0,1,1,2,2,3,3,3 };
		Rect rt(pPos.X, pPos.Y, rtW, rtH);

		graphics->DrawImage(bitmap, rt, xStart[frame] * w, Body_yStart, w, h, UnitPixel);
	}
}

void metalSlug::AnimEri::AniEriRun(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriRun;
	int w = 36;
	int h = 36;
	int upperBody_yStart = 0;
	int lowerBody_yStart = upperBody_yStart + h;
	int upperBody_yOffset = -10;
	int upperBody_xOffset = 4;
	int frame;
	int xStart_Upper;
	int xStart_Lower;
	int rtW = (int)(1.5f * w);
	int rtH = (int)(1.5f * h);

	if (bFlipX == false)
	{
		if (bRunLoop == true)
		{
			frame = runFrame % (FrameCount_Run - FrameCount_RunStart);
			xStart_Upper = w * frame; // 0 ~ 11
			xStart_Lower = w * (frame + FrameCount_RunStart); // 4 ~ 15

			runFrame++;
			if (runFrame % (FrameCount_Run - FrameCount_RunStart) == 0) runFrame = 0;
		}
		else
		{
			frame = runFrame % FrameCount_RunStart;
			xStart_Upper = w * frame; // 0 ~ 3
			xStart_Lower = w * frame; // 0 ~ 3
			if (frame >= 3) bRunLoop = true;
			
			runFrame++;
		}

		Rect rtLower(pPos.X, pPos.Y, rtW, rtH);
		Rect rtUpper(rtLower.X + upperBody_xOffset, rtLower.Y + upperBody_yOffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, xStart_Lower, lowerBody_yStart, w, h, UnitPixel);
		if (bLookUp == true)
		{
			if (bPlayedShoot == true)
				AniEriShootUp(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
		}
		else
		{
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
			else
				graphics->DrawImage(bitmap, rtUpper, xStart_Upper, upperBody_yStart, w, h, UnitPixel);
		}
	}
	else
	{
		if (bRunLoop == true)
		{
			frame = (FrameCount_Run - FrameCount_RunStart - 1) - (runFrame % (FrameCount_Run - FrameCount_RunStart));
			xStart_Upper = w * (frame + FrameCount_RunStart); // 15 ~ 4
			xStart_Lower = w * frame; // 11 ~ 0

			runFrame++;
			if (runFrame % (FrameCount_Run - FrameCount_RunStart) == 0) runFrame = 0;
		}
		else
		{
			frame = (FrameCount_Run - 1) - (runFrame % FrameCount_RunStart);
			xStart_Upper = w * frame; // 15 ~ 12
			xStart_Lower = w * frame; // 15 ~ 12
			if (frame <= 12) bRunLoop = true;

			runFrame++;
		}

		Rect rtLower(pPos.X, pPos.Y, rtW, rtH);
		Rect rtUpper(rtLower.X - upperBody_xOffset, rtLower.Y + upperBody_yOffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, xStart_Lower, lowerBody_yStart, w, h, UnitPixel);
		if (bLookUp == true)
		{
			if (bPlayedShoot == true)
				AniEriShootUp(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
		}
		else
		{
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
			else
				graphics->DrawImage(bitmap, rtUpper, xStart_Upper, upperBody_yStart, w, h, UnitPixel);
		}
	}
}

void metalSlug::AnimEri::AniEriLookUp(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriLookUp;
	int w = 36;
	int h = 36;
	int upperBody_yStart = 0;
	int upperBody_yOffset = -4;
	int upperBody_xOffset = 4;
	int xStart_Upper = 0;
	int frame;
	int rtW = (int)(1.5f * w);
	int rtH = (int)(1.5f * h);

	if (bFlipX == false)
	{
		Rect rtUpper(pPos.X + upperBody_xOffset, pPos.Y + upperBody_yOffset, rtW, rtH);

		if (bLookUpLoop == true)
		{
			int xStart[FrameCount_LookUp] = { 0,0,1,1,2,2,3,3,3,3,2,2,1,1,0,0 };
			frame = lookUpFrame % FrameCount_LookUp;

			lookUpFrame++;
			if (lookUpFrame % FrameCount_LookUp == 0) lookUpFrame = 0;
			graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart + h, w, h, UnitPixel);
		}
		else
		{
			frame = lookUpFrame % FrameCount_LookUpStart;
			xStart_Upper = w * frame;
			lookUpFrame++;

			if (lookUpFrame >= FrameCount_LookUpStart)
			{
				bLookUpLoop = true;
				lookUpFrame = 0;
			}
			graphics->DrawImage(bitmap, rtUpper, xStart_Upper, upperBody_yStart, w, h, UnitPixel);
		}
	}
	else
	{
		Rect rtUpper(pPos.X - upperBody_xOffset, pPos.Y + upperBody_yOffset, rtW, rtH);

		if (bLookUpLoop == true)
		{
			int xStart[FrameCount_LookUp] = { 0,0,1,1,2,2,3,3,3,3,2,2,1,1,0,0 };
			frame = (FrameCount_LookUp - 1) - lookUpFrame % FrameCount_LookUp;
			
			lookUpFrame++;
			if (lookUpFrame % FrameCount_LookUp == 0) lookUpFrame = 0;
			graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart + h, w, h, UnitPixel);
		}
		else
		{
			frame = (FrameCount_LookUpStart - 1) - lookUpFrame % FrameCount_LookUpStart;
			xStart_Upper = w * frame;
			if (frame >= 1)
			{
				bLookUpLoop = true;
				lookUpFrame = 0;
			}

			lookUpFrame++;
			graphics->DrawImage(bitmap, rtUpper, xStart_Upper, upperBody_yStart, w, h, UnitPixel);
		}
	}
}

void metalSlug::AnimEri::AniEriTurn(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
}

void metalSlug::AnimEri::AniEriShootFront(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriShootForward;
	int w = 64;
	int h = 32;
	int upperBody_yStart = 0;
	int upperBody_yOffset = -1;
	int upperBody_xOffset = -10;
	int xStart_Upper = 0;
	int frame;
	int rtW = (int)(1.5f * w);
	int rtH = (int)(1.5f * h);

	if (bFlipX == false)
	{
		Rect rtUpper(pPos.X + upperBody_xOffset, pPos.Y + upperBody_yOffset, rtW, rtH);
		int xStart[FrameCount_ShootForward] = { 0,1,2,3,4,4,5,5,6,6,7,7,8,8,9,9 };

		frame = shootForwardFrame % FrameCount_ShootForward;

		UpdateShootFrame();
		if (shootForwardFrame % FrameCount_ShootForward == 0)
		{
			ResetShootFrame();
			bPlayedShoot = false;
		}
		else if (shootForwardFrame >= 6) bCanShoot = true;
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
	else
	{
		Rect rtUpper(pPos.X + (upperBody_xOffset * 3 - 1), pPos.Y + upperBody_yOffset, rtW, rtH);
		int xStart[FrameCount_ShootForward] = { 0,1,2,3,4,4,5,5,6,6,7,7,8,8,9,9 };
		frame = (FrameCount_ShootForward - 1) - shootForwardFrame % FrameCount_ShootForward;

		UpdateShootFrame();
		if (shootForwardFrame % FrameCount_ShootForward == 0)
		{
			ResetShootFrame();
			bPlayedShoot = false;
		}
		else if (shootForwardFrame >= 6) bCanShoot = true;
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
}

// 쏘는 도중에는 쏘는방향을 전환 불가능하게 수정필요
void metalSlug::AnimEri::AniEriShootUp(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriShootUp;
	int w = 36;
	int h = 72;
	int upperBody_yStart = 0;
	int upperBody_yOffset = -68;
	int upperBody_xOffset = -4;
	int xStart_Upper = 0;
	int frame;
	int rtW = (int)(1.5f * w);
	int rtH = (int)(1.5f * h);

	if (bFlipX == false)
	{
		Rect rtUpper(pPos.X + upperBody_xOffset, pPos.Y + upperBody_yOffset, rtW, rtH);
		int xStart[FrameCount_ShootUp] = { 0,1,2,3,4,4,5,5,6,6,7,7,8,8,9,9 };

		frame = shootUpFrame % FrameCount_ShootUp;

		UpdateShootFrame();
		if (shootUpFrame % FrameCount_ShootUp == 0)
		{
			ResetShootFrame();
			bPlayedShoot = false;
		}
		else if (shootUpFrame >= 6) bCanShoot = true;
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
	else
	{
		Rect rtUpper(pPos.X - upperBody_xOffset, pPos.Y + upperBody_yOffset, rtW, rtH);
		int xStart[FrameCount_ShootUp] = { 0,1,2,3,4,4,5,5,6,6,7,7,8,8,9,9 };
		frame = (FrameCount_ShootUp - 1) - shootUpFrame % FrameCount_ShootUp;

		UpdateShootFrame();
		if (shootUpFrame % FrameCount_ShootUp == 0)
		{
			ResetShootFrame();
			bPlayedShoot = false;
		}
		else if (shootUpFrame >= 6) bCanShoot = true;
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
}
