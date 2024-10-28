#include "framework.h"
#include "AnimEri.h"

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
	EriRun = new Bitmap(_T("images/Eri Kasamoto_Run.png"));
	EriStop = new Bitmap(_T("images/Eri Kasamoto_JumpEnd.png"));
	EriTurn = new Bitmap(_T("images/Eri Kasamoto_Turn.png"));
	EriJumpIdle = new Bitmap(_T("images/Eri Kasamoto_JumpIdle.png"));
	EriJumpRun = new Bitmap(_T("images/Eri Kasamoto_JumpRun.png"));
	EriCrouch = new Bitmap(_T("images/Eri Kasamoto_Crouch.png"));
	EriLookUp = new Bitmap(_T("images/Eri Kasamoto_LookUp.png"));
	EriShootForward = new Bitmap(_T("images/Eri Kasamoto_ShootForward.png"));
	EriShootUp = new Bitmap(_T("images/Eri Kasamoto_ShootUp.png"));
	EriShootDown = new Bitmap(_T("images/Eri Kasamoto_ShootDown.png"));
	EriShootCrouch = new Bitmap(_T("images/Eri Kasamoto_ShootCrouch.png"));
	EriThrowBomb = new Bitmap(_T("images/Eri Kasamoto_ThrowBomb.png"));
}

void metalSlug::AnimEri::Delete()
{
	delete EriIdle;
	delete EriRun;
	delete EriStop;
	delete EriTurn;
	delete EriJumpIdle;
	delete EriJumpRun;
	delete EriCrouch;
	delete EriLookUp;
	delete EriShootForward;
	delete EriShootUp;
	delete EriShootDown;
	delete EriShootCrouch;
	delete EriThrowBomb;
}

void metalSlug::AnimEri::FlipXBitmap()
{
	EriIdle->RotateFlip(RotateNoneFlipX);
	EriRun->RotateFlip(RotateNoneFlipX);
	EriStop->RotateFlip(RotateNoneFlipX);
	EriTurn->RotateFlip(RotateNoneFlipX);
	EriJumpIdle->RotateFlip(RotateNoneFlipX);
	EriJumpRun->RotateFlip(RotateNoneFlipX);
	EriCrouch->RotateFlip(RotateNoneFlipX);
	EriLookUp->RotateFlip(RotateNoneFlipX);
	EriShootForward->RotateFlip(RotateNoneFlipX);
	EriShootUp->RotateFlip(RotateNoneFlipX);
	EriShootDown->RotateFlip(RotateNoneFlipX);
	EriShootCrouch->RotateFlip(RotateNoneFlipX);
	EriThrowBomb->RotateFlip(RotateNoneFlipX);

	bEriFlipX = !bEriFlipX;
	bCanFlip = false;
}

void metalSlug::AnimEri::UpdateShootFrame()
{
	shootForwardFrame++;
	shootUpFrame++;
	shootDownFrame++;
	shootCrouchFrame++;
}

void metalSlug::AnimEri::ResetFrame()
{
	stopFrame = 0;
	jumpIdleFrame = 0;
	jumpRunFrame = 0;
	crouchFrame = 0;
	lookUpFrame = 0;
	lookDownFrame = 0;
}

void metalSlug::AnimEri::ResetShootFrame()
{
	shootForwardFrame = 0;
	shootUpFrame = 0;
	shootDownFrame = 0;
	shootCrouchFrame = 0;
}

void metalSlug::AnimEri::PlayShootAnim()
{
	bPlayedShoot = true;
	bCanShoot = false;
	ResetShootFrame();
}

void metalSlug::AnimEri::AniEriIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriIdle;
	int w = 36;
	int h = 36;
	int upperBody_yStart = 0;
	int lowerBody_yStart = upperBody_yStart + h;
	INT upperBody_Yoffset = (INT)(imgRatio * -6);
	INT upperBody_Xoffset = (INT)(imgRatio * 2);
	int frame = idleFrame % FrameCount_Idle;
	INT rtW = (INT)(imgRatio * w);
	INT rtH = (INT)(imgRatio * h);
	
	idleFrame++;
	if (idleFrame % FrameCount_Idle == 0) idleFrame = 0;

	if (bFlipX == false)
	{
		int xStart[FrameCount_Idle] = { 0,0,1,1,2,2,3,3,3,3,2,2,1,1,0,0 };
		Rect rtLower((INT)pPos.X, (INT)pPos.Y, rtW, rtH);
		Rect rtUpper(rtLower.X + upperBody_Xoffset, rtLower.Y + upperBody_Yoffset, rtLower.Width, rtLower.Height);

		if (bLookUp == true)
		{
			graphics->DrawImage(bitmap, rtLower, 4 * w, 0, w, h, UnitPixel);
			if (bPlayedShoot == true)
				AniEriShootUp(graphics, PointF((float)rtUpper.X, (float)rtUpper.Y), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF((float)rtUpper.X, (float)rtUpper.Y), NULL, 0, bFlipX);
		}
		else if (bCrouch == true)
		{
			if (bPlayedShoot == true)
				AniEriShootCrouch(graphics, PointF((float)rtUpper.X + (imgRatio * -13), (float)rtUpper.Y + (imgRatio * -4)), NULL, 0, bFlipX);
			else
				AniEriCrouchIdle(graphics, PointF((float)rtUpper.X + (imgRatio * -4), (float)rtUpper.Y + (imgRatio * -4)), NULL, 0, bFlipX);
		}
		else
		{
			graphics->DrawImage(bitmap, rtLower, 4 * w, 0, w, h, UnitPixel);
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF((float)rtUpper.X, (float)rtUpper.Y), NULL, 0, bFlipX);
			else
				graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
		}
	}
	else
	{
		int xStart[FrameCount_Idle] = { 17,17,16,16,15,15,14,14,14,14,15,15,16,16,17,17 };
		Rect rtLower((INT)pPos.X, (INT)pPos.Y, rtW, rtH);
		Rect rtUpper(rtLower.X - upperBody_Xoffset, rtLower.Y + upperBody_Yoffset, rtLower.Width, rtLower.Height);

		if (bLookUp == true)
		{
			graphics->DrawImage(bitmap, rtLower, 13 * w, 0, w, h, UnitPixel);
			if (bPlayedShoot == true)
				AniEriShootUp(graphics, PointF((float)rtUpper.X, (float)rtUpper.Y), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF((float)rtUpper.X, (float)rtUpper.Y), NULL, 0, bFlipX);
		}
		else if (bCrouch == true)
		{
			if (bPlayedShoot == true)
				AniEriShootCrouch(graphics, PointF((float)rtUpper.X + (imgRatio * -20), (float)rtUpper.Y + (imgRatio * -4)), NULL, 0, bFlipX);
			else
				AniEriCrouchIdle(graphics, PointF((float)rtUpper.X + (imgRatio * -8), (float)rtUpper.Y + (imgRatio * -4)), NULL, 0, bFlipX);
		}
		else
		{
			graphics->DrawImage(bitmap, rtLower, 13 * w, 0, w, h, UnitPixel);
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF((float)rtUpper.X, (float)rtUpper.Y), NULL, 0, bFlipX);
			else
				graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
		}
	}
}

void metalSlug::AnimEri::AniEriRun(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriRun;
	int w = 36;
	int h = 36;
	INT upperBody_yStart = 0;
	INT lowerBody_yStart = upperBody_yStart + h;
	INT upperBody_yOffset = (INT)(imgRatio * -6);
	INT upperBody_xOffset = (INT)(imgRatio * 3);
	int frame;
	INT xStart_Upper;
	INT xStart_Lower;
	INT rtW = (INT)(imgRatio * w);
	INT rtH = (INT)(imgRatio * h);

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

		Rect rtLower((INT)pPos.X, (INT)pPos.Y, rtW, rtH);
		Rect rtUpper(rtLower.X + upperBody_xOffset, rtLower.Y + upperBody_yOffset, rtLower.Width, rtLower.Height);

		if (bLookUp == true)
		{
			graphics->DrawImage(bitmap, rtLower, xStart_Lower, lowerBody_yStart, w, h, UnitPixel);
			if (bPlayedShoot == true)
				AniEriShootUp(graphics, PointF((float)rtUpper.X, (float)rtUpper.Y), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF((float)rtUpper.X, (float)rtUpper.Y), NULL, 0, bFlipX);
		}
		else if (bCrouch == true)
		{
			if (bPlayedShoot == true)
				AniEriShootCrouch(graphics, PointF((float)rtUpper.X + (imgRatio * -13), (float)rtUpper.Y + (imgRatio * -4)), NULL, 0, bFlipX);
			else
				AniEriCrouchMove(graphics, PointF((float)rtUpper.X + (imgRatio * -4), (float)rtUpper.Y + (imgRatio * -4)), NULL, 0, bFlipX);
		}
		else
		{
			graphics->DrawImage(bitmap, rtLower, xStart_Lower, lowerBody_yStart, w, h, UnitPixel);
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF((float)rtUpper.X, (float)rtUpper.Y), NULL, 0, bFlipX);
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

		Rect rtLower((INT)pPos.X, (INT)pPos.Y, rtW, rtH);
		Rect rtUpper(rtLower.X - upperBody_xOffset, rtLower.Y + upperBody_yOffset, rtLower.Width, rtLower.Height);

		if (bLookUp == true)
		{
			graphics->DrawImage(bitmap, rtLower, xStart_Lower, lowerBody_yStart, w, h, UnitPixel);
			if (bPlayedShoot == true)
				AniEriShootUp(graphics, PointF((float)rtUpper.X, (float)rtUpper.Y), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF((float)rtUpper.X, (float)rtUpper.Y), NULL, 0, bFlipX);
		}
		else if (bCrouch == true)
		{
			if (bPlayedShoot == true)
				AniEriShootCrouch(graphics, PointF((float)rtUpper.X + (imgRatio * -20), (float)rtUpper.Y + (imgRatio * -4)), NULL, 0, bFlipX);
			else
				AniEriCrouchMove(graphics, PointF((float)rtUpper.X + (imgRatio * -8), (float)rtUpper.Y + (imgRatio * -4)), NULL, 0, bFlipX);
		}
		else
		{
			graphics->DrawImage(bitmap, rtLower, xStart_Lower, lowerBody_yStart, w, h, UnitPixel);
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF((float)rtUpper.X, (float)rtUpper.Y), NULL, 0, bFlipX);
			else
				graphics->DrawImage(bitmap, rtUpper, xStart_Upper, upperBody_yStart, w, h, UnitPixel);
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
	int rtW = (int)(imgRatio * w);
	int rtH = (int)(imgRatio * h);

	stopFrame++;
	if (stopFrame % FrameCount_Stop == 0) stopFrame = FrameCount_Stop - 1;

	if (bFlipX == false)
	{
		int xStart[FrameCount_Stop] = { 0,1,2,3,3,2,2,1,1,0,0,0 };
		Rect rt((INT)pPos.X, (INT)pPos.Y, rtW, rtH);

		graphics->DrawImage(bitmap, rt, xStart[frame] * w, Body_yStart, w, h, UnitPixel);
	}
	else
	{
		int xStart[FrameCount_Stop] = { 3,2,1,0,0,1,1,2,2,3,3,3 };
		Rect rt((INT)pPos.X, (INT)pPos.Y, rtW, rtH);

		graphics->DrawImage(bitmap, rt, xStart[frame] * w, Body_yStart, w, h, UnitPixel);
	}
}

void metalSlug::AnimEri::AniEriTurn(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
}

void metalSlug::AnimEri::AniEriJumpIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriJumpIdle;
	int w = 36;
	int h = 36;
	int upperBody_yStart = 0;
	int lowerBody_yStart = upperBody_yStart + h;
	int Yoffset = (int)(imgRatio * 15);
	int frame = jumpIdleFrame % FrameCount_JumpIdleStart;
	int rtW = (int)(imgRatio * w);
	int rtH = (int)(imgRatio * h);
	
	jumpIdleFrame++;
	if (jumpIdleFrame % FrameCount_JumpIdleStart == 0) jumpIdleFrame = FrameCount_JumpIdleStart - 1;

	if (bFlipX == false)
	{
		int xStart[FrameCount_JumpIdleStart] = { 0,1,2,3,4,5,5,4,4,3,3,3,3,3,3,3 };
		Rect rtLower((INT)pPos.X, (INT)pPos.Y, rtW, rtH);
		Rect rtUpper(rtLower.X, rtLower.Y - Yoffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, xStart[frame] * w, lowerBody_yStart, w, h, UnitPixel);
		if (bLookUp == true)
		{
			if (bPlayedShoot == true)
				AniEriShootUp(graphics, PointF((float)rtUpper.X + (imgRatio * 3), (float)rtUpper.Y + (imgRatio * 2)), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF((float)rtUpper.X + (imgRatio * 3), (float)rtUpper.Y + (imgRatio * 2)), NULL, 0, bFlipX);
		}
		else if (bLookDown == true)
		{
			if (bPlayedShoot == true)
				AniEriShootDown(graphics, PointF((float)rtUpper.X + (imgRatio * 3), (float)rtUpper.Y), NULL, 0, bFlipX);
			else
				AniEriLookDown(graphics, PointF((float)rtUpper.X + (imgRatio * 3), (float)rtUpper.Y), NULL, 0, bFlipX);
		}
		else
		{
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF((float)rtUpper.X + (imgRatio * 3), (float)rtUpper.Y + (imgRatio * 2)), NULL, 0, bFlipX);
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
				AniEriShootUp(graphics, PointF(rtUpper.X + (int)(imgRatio * -3), rtUpper.Y + (int)(imgRatio * 2)), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF(rtUpper.X + (int)(imgRatio * -3), rtUpper.Y + (int)(imgRatio * 2)), NULL, 0, bFlipX);
		}
		else if (bLookDown == true)
		{
			if (bPlayedShoot == true)
				AniEriShootDown(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
			else
				AniEriLookDown(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
		}
		else
		{
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF(rtUpper.X + (int)(imgRatio * -3), rtUpper.Y + (int)(imgRatio * 2)), NULL, 0, bFlipX);
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
	int Yoffset = (int)(imgRatio * 6);
	int upperBody_Xoffset = (int)(imgRatio * -2);
	int frame = jumpRunFrame % FrameCount_JumpIdleStart;
	int rtW = (int)(imgRatio * w);
	int rtH = (int)(imgRatio * h);
	
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
				AniEriShootUp(graphics, PointF(rtUpper.X + (int)(imgRatio * 3), rtUpper.Y + (int)(imgRatio * -1)), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF(rtUpper.X + (int)(imgRatio * 3), rtUpper.Y + (int)(imgRatio * -1)), NULL, 0, bFlipX);
		}
		else if (bLookDown == true)
		{
			if (bPlayedShoot == true)
				AniEriShootDown(graphics, PointF(rtUpper.X + (int)(imgRatio * 3), rtUpper.Y), NULL, 0, bFlipX);
			else
				AniEriLookDown(graphics, PointF(rtUpper.X + (int)(imgRatio * 3), rtUpper.Y), NULL, 0, bFlipX);
		}
		else
		{
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF(rtUpper.X + (int)(imgRatio * 3), rtUpper.Y + (int)(imgRatio * -1)), NULL, 0, bFlipX);
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
				AniEriShootUp(graphics, PointF(rtUpper.X + (int)(imgRatio * -3), rtUpper.Y + (int)(imgRatio * -1)), NULL, 0, bFlipX);
			else
				AniEriLookUp(graphics, PointF(rtUpper.X + (int)(imgRatio * -3), rtUpper.Y + (int)(imgRatio * -1)), NULL, 0, bFlipX);
		}
		else if (bLookDown == true)
		{
			if (bPlayedShoot == true)
				AniEriShootDown(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
			else
				AniEriLookDown(graphics, PointF(rtUpper.X, rtUpper.Y), NULL, 0, bFlipX);
		}
		else
		{
			if (bPlayedShoot == true)
				AniEriShootFront(graphics, PointF(rtUpper.X + (int)(imgRatio * -3), rtUpper.Y + (int)(imgRatio * -1)), NULL, 0, bFlipX);
			else
				graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
		}
	}
}

void metalSlug::AnimEri::AniEriCrouchIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriCrouch;
	int w = 48;
	int h = 48;
	int Body_yStart = 0;
	int frame;
	int rtW = (int)(imgRatio * w);
	int rtH = (int)(imgRatio * h);

	if (bFlipX == false)
	{
		Rect rt(pPos.X, pPos.Y, rtW, rtH);
		frame = crouchFrame % FrameCount_CrouchIdle;
		crouchFrame++;
		
		if (bCrouchLoop == true)
		{
			int xStart[FrameCount_CrouchIdle] = { 4,4,5,5,6,6,7,7,7,7,6,6,5,5,4,4 };

			graphics->DrawImage(bitmap, rt, xStart[frame] * w, Body_yStart, w, h, UnitPixel);
		}
		else
		{
			Body_yStart = h;
			if (crouchFrame >= 3) bCrouchLoop = true;
			graphics->DrawImage(bitmap, rt, frame * w, Body_yStart, w, h, UnitPixel);
		}

		if (crouchFrame % FrameCount_CrouchIdle == 0) crouchFrame = 0;
	}
	else
	{
		Rect rt(pPos.X, pPos.Y, rtW, rtH);
		frame = crouchFrame % FrameCount_CrouchIdle;
		crouchFrame++;

		if (bCrouchLoop == true)
		{
			int xStart[FrameCount_CrouchIdle] = { 5,5,4,4,3,3,2,2,2,2,3,3,4,4,5,5 };
			graphics->DrawImage(bitmap, rt, xStart[frame] * w, Body_yStart, w, h, UnitPixel);
		}
		else
		{
			Body_yStart = h;
			if (crouchFrame >= 3) bCrouchLoop = true;
			graphics->DrawImage(bitmap, rt, (9 - frame) * w, Body_yStart, w, h, UnitPixel);
		}

		if (crouchFrame % FrameCount_CrouchIdle == 0) crouchFrame = 0;
	}
}

void metalSlug::AnimEri::AniEriCrouchMove(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriCrouch;
	int w = 48;
	int h = 48;
	int Body_yStart = h;
	int frame;
	int rtW = (int)(imgRatio * w);
	int rtH = (int)(imgRatio * h);

	if (bFlipX == false)
	{
		Rect rt(pPos.X, pPos.Y, rtW, rtH);
		frame = crouchFrame % FrameCount_CrouchMove;
		crouchFrame++;

		if (bCrouchLoop == true)
		{
			int xStart[FrameCount_CrouchMove] = { 3,3,4,4,5,5,6,6,7,7,8,8,9,9};

			graphics->DrawImage(bitmap, rt, xStart[frame] * w, Body_yStart, w, h, UnitPixel);
		}
		else
		{
			if (crouchFrame >= 3) bCrouchLoop = true;
			graphics->DrawImage(bitmap, rt, frame * w, Body_yStart, w, h, UnitPixel);
		}

		if (crouchFrame % FrameCount_CrouchMove == 0) crouchFrame = 0;
	}
	else
	{
		Rect rt(pPos.X, pPos.Y, rtW, rtH);
		frame = crouchFrame % FrameCount_CrouchMove;
		crouchFrame++;

		if (bCrouchLoop == true)
		{
			int xStart[FrameCount_CrouchMove] = { 6,6,5,5,4,4,3,3,2,2,1,1,0,0 };
			graphics->DrawImage(bitmap, rt, xStart[frame] * w, Body_yStart, w, h, UnitPixel);
		}
		else
		{
			if (crouchFrame >= 3) bCrouchLoop = true;
			graphics->DrawImage(bitmap, rt, frame * w, Body_yStart, w, h, UnitPixel);
		}

		if (crouchFrame % FrameCount_CrouchIdle == 0) crouchFrame = 0;
	}
}

void metalSlug::AnimEri::AniEriLookUp(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriLookUp;
	int w = 36;
	int h = 36;
	int upperBody_yStart = 0;
	int upperBody_yOffset = (int)(imgRatio * -2);
	int upperBody_xOffset = (int)(imgRatio * 2);
	int xStart_Upper = 0;
	int frame;
	int rtW = (int)(imgRatio * w);
	int rtH = (int)(imgRatio * h);

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

void metalSlug::AnimEri::AniEriLookDown(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriShootDown;
	int w = 32;
	int h = 64;
	int upperBody_yStart = 0;
	int upperBody_yOffset = 0;
	int upperBody_xOffset = 0;
	int frame;
	int rtW = (int)(imgRatio * w);
	int rtH = (int)(imgRatio * h);

	if (bFlipX == false)
	{
		Rect rtUpper(pPos.X + upperBody_xOffset, pPos.Y + upperBody_yOffset, rtW, rtH);
		frame = lookDownFrame % FrameCount_LookDown;

		if (bPressedLookDown == true)
		{
			lookDownFrame++;
			if (lookDownFrame >= FrameCount_LookDown) lookDownFrame = FrameCount_LookDown - 1;
		}
		else
		{
			lookDownFrame--;
			if (lookDownFrame < 0)
			{
				lookDownFrame = 0;
				bLookDown = false;
			}
		}
		
		graphics->DrawImage(bitmap, rtUpper, frame * w, upperBody_yStart, w, h, UnitPixel);
	}
	else
	{
		Rect rtUpper(pPos.X - upperBody_xOffset, pPos.Y + upperBody_yOffset, rtW, rtH);
		frame = (FrameCount_LookDown - 1) - lookDownFrame % FrameCount_LookDown;

		if (bPressedLookDown == true)
		{
			lookDownFrame++;
			if (lookDownFrame >= FrameCount_LookDown) lookDownFrame = FrameCount_LookDown - 1;
		}
		else
		{
			lookDownFrame--;
			if (lookDownFrame < 0)
			{
				lookDownFrame = 0;
				bLookDown = false;
			}
		}

		graphics->DrawImage(bitmap, rtUpper, frame * w, upperBody_yStart, w, h, UnitPixel);
	}
}

void metalSlug::AnimEri::AniEriShootFront(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriShootForward;
	int w = 64;
	int h = 32;
	int upperBody_yStart = 0;
	int upperBody_yOffset = (int)(imgRatio * -1);
	int upperBody_xOffset = (int)(imgRatio * -7);
	int xStart_Upper = 0;
	int frame;
	int rtW = (int)(imgRatio * w);
	int rtH = (int)(imgRatio * h);

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
		else if (shootForwardFrame >= fireColdown && bCanShoot == false)
		{
			bCanShoot = true;
			bCanSpawnProjectile = true;
		}
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
		else if (shootForwardFrame >= fireColdown && bCanShoot == false)
		{
			bCanShoot = true;
			bCanSpawnProjectile = true;
		}
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
	int upperBody_yOffset = (int)(imgRatio * -45);
	int upperBody_xOffset = (int)(imgRatio * -2);
	int xStart_Upper = 0;
	int frame;
	int rtW = (int)(imgRatio * w);
	int rtH = (int)(imgRatio * h);

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
		else if (shootUpFrame >= fireColdown && bCanShoot == false)
		{
			bCanShoot = true;
			bCanSpawnProjectile = true;
		}
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
		else if (shootUpFrame >= fireColdown && bCanShoot == false)
		{
			bCanShoot = true;
			bCanSpawnProjectile = true;
		}
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
}

void metalSlug::AnimEri::AniEriShootDown(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriShootDown;
	int w = 32;
	int h = 64;
	int upperBody_yStart = 0;
	int upperBody_yOffset = 0;
	int upperBody_xOffset = 0;
	int xStart_Upper = 0;
	int frame;
	int rtW = (int)(imgRatio * w);
	int rtH = (int)(imgRatio * h);

	if (bFlipX == false)
	{
		Rect rtUpper(pPos.X + upperBody_xOffset, pPos.Y + upperBody_yOffset, rtW, rtH);
		int xStart[FrameCount_ShootDown] = { 0,1,2,3,4,4,5,5};

		frame = shootDownFrame % FrameCount_ShootDown;

		UpdateShootFrame();
		if (shootDownFrame % FrameCount_ShootDown == 0)
		{
			ResetShootFrame();
			bPlayedShoot = false;
		}
		else if (shootDownFrame >= fireColdown && bCanShoot == false)
		{
			bCanShoot = true;
			bCanSpawnProjectile = true;
		}
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
	else
	{
		Rect rtUpper(pPos.X - upperBody_xOffset, pPos.Y + upperBody_yOffset, rtW, rtH);
		int xStart[FrameCount_ShootDown] = { 0,1,2,3,4,4,5,5};
		frame = (FrameCount_ShootDown - 1) - shootDownFrame % FrameCount_ShootDown;

		UpdateShootFrame();
		if (shootDownFrame % FrameCount_ShootDown == 0)
		{
			ResetShootFrame();
			bPlayedShoot = false;
		}
		else if (shootDownFrame >= fireColdown && bCanShoot == false)
		{
			bCanShoot = true;
			bCanSpawnProjectile = true;
		}
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
}

void metalSlug::AnimEri::AniEriShootCrouch(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	if (bitmap == NULL) bitmap = EriShootCrouch;
	int w = 72;
	int h = 36;
	int upperBody_yStart = 0;
	int upperBody_yOffset = (int)(imgRatio * 12);
	int upperBody_xOffset = 0;
	int xStart_Upper = 0;
	int frame;
	int rtW = (int)(imgRatio * w);
	int rtH = (int)(imgRatio * h);

	// TODO :
	if (bFlipX == false)
	{
		Rect rtUpper(pPos.X + upperBody_xOffset, pPos.Y + upperBody_yOffset, rtW, rtH);
		int xStart[FrameCount_ShootCrouch] = { 0,1,2,3,4,4,5,5,6,6,7,7,8,8 };

		frame = shootCrouchFrame % FrameCount_ShootCrouch;

		UpdateShootFrame();
		if (shootCrouchFrame % FrameCount_ShootCrouch == 0)
		{
			ResetShootFrame();
			bPlayedShoot = false;
		}
		else if (shootCrouchFrame >= fireColdown && bCanShoot == false)
		{
			bCanShoot = true;
			bCanSpawnProjectile = true;
		}
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
	else
	{
		Rect rtUpper(pPos.X - upperBody_xOffset, pPos.Y + upperBody_yOffset, rtW, rtH);
		int xStart[FrameCount_ShootCrouch] = { 8,7,6,5,4,4,3,3,2,2,1,1,0,0 };

		frame = shootCrouchFrame % FrameCount_ShootCrouch;

		UpdateShootFrame();
		if (shootCrouchFrame % FrameCount_ShootCrouch == 0)
		{
			ResetShootFrame();
			bPlayedShoot = false;
		}
		else if (shootCrouchFrame >= fireColdown && bCanShoot == false)
		{
			bCanShoot = true;
			bCanSpawnProjectile = true;
		}
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
}

void metalSlug::AnimEri::AniEriThrowBomb(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
}
