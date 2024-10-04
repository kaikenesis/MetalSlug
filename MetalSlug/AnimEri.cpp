#include "AnimEri.h"

#define FrameCount_Idle 16
#define FrameCount_JumpIdleStart 16
#define FrameCount_JumpRunStart 16
#define FrameCount_Stop 12
#define FrameCount_RunStart 4
#define FrameCount_Run 16
#define FrameCount_LookUpStart 2
#define FrameCount_LookUp 4

int frame_stop;

bool bRunLoop = false;
bool bLookUpLoop = false;

//Test
int lookUpFrame = 0;

int GetEriIdleFrame() { return FrameCount_Idle; }
int GetEriJumpIdleStartFrame() { return FrameCount_JumpIdleStart; }
int GetEriJumpRunStartFrame() { return FrameCount_JumpRunStart; }
int GetEriStopFrame() { return FrameCount_Stop; }
int GetEriRunStartFrame() { return FrameCount_RunStart; }
int GetEriRunFrame() { return FrameCount_Run; }
int GetEriLooUpStartFrame() { return FrameCount_LookUpStart; }
int GetEriLooUpFrame() { return FrameCount_LookUp; }
BOOL IsRunLoop() { return bRunLoop; }

void SetRunLoop(bool inValue) { bRunLoop = inValue; }

void AniEriIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	int w = 36;
	int h = 36;
	int upperBody_yStart = 0;
	int lowerBody_yStart = upperBody_yStart + h;
	int upperBody_Yoffset = 10;
	int upperBody_Xoffset = 4;
	int frame = curFrame % FrameCount_Idle;

	if (bFlipX == false)
	{
		int xStart[FrameCount_Idle] = { 0,0,1,1,2,2,3,3,3,3,2,2,1,1,0,0 };
		Rect rtLower(pPos.X, pPos.Y, 50, 50);
		Rect rtUpper(rtLower.X + upperBody_Xoffset, rtLower.Y - upperBody_Yoffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, 4 * w, 0, w, h, UnitPixel);
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
	else
	{
		int xStart[FrameCount_Idle] = { 17,17,16,16,15,15,14,14,14,14,15,15,16,16,17,17 };
		Rect rtLower(pPos.X, pPos.Y, 50, 50);
		Rect rtUpper(rtLower.X - upperBody_Xoffset, rtLower.Y - upperBody_Yoffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, 13 * w, 0, w, h, UnitPixel);
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
}

void AniEriJumpIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	int w = 36;
	int h = 36;
	int upperBody_yStart = 0;
	int lowerBody_yStart = upperBody_yStart + h;
	int Yoffset = 23;
	int frame = curFrame % FrameCount_JumpIdleStart;

	if (bFlipX == false)
	{
		int xStart[FrameCount_JumpIdleStart] = { 0,1,2,3,4,5,5,4,4,3,3,3,3,3,3,3 };
		Rect rtLower(pPos.X, pPos.Y, 50, 50);
		Rect rtUpper(rtLower.X, rtLower.Y - Yoffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, xStart[frame] * w, lowerBody_yStart, w, h, UnitPixel);
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
	else
	{
		int xStart[FrameCount_JumpIdleStart] = { 5,4,3,2,1,0,0,1,1,2,2,2,2,2,2,2 };
		Rect rtLower(pPos.X, pPos.Y, 50, 50);
		Rect rtUpper(rtLower.X, rtLower.Y - Yoffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, xStart[frame] * w, lowerBody_yStart, w, h, UnitPixel);
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
}

void AniEriJumpRun(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	int w = 36;
	int h = 36;
	int upperBody_yStart = 0;
	int lowerBody_yStart = upperBody_yStart + h;
	int Yoffset = 10;
	int upperBody_Xoffset = -4;
	int frame = curFrame % FrameCount_JumpIdleStart;
	
	if (bFlipX == false)
	{
		int xStart[FrameCount_JumpIdleStart] = { 0,1,2,2,2,2,2,3,3,4,4,5,5,5,5,5 };
		Rect rtLower(pPos.X, pPos.Y, 50, 50);
		Rect rtUpper(rtLower.X + upperBody_Xoffset, rtLower.Y - Yoffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, xStart[frame] * w, lowerBody_yStart, w, h, UnitPixel);
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
	else
	{
		int xStart[FrameCount_JumpIdleStart] = { 5,4,3,3,3,3,3,2,2,1,1,0,0,0,0,0 };
		Rect rtLower(pPos.X, pPos.Y, 50, 50);
		Rect rtUpper(rtLower.X - upperBody_Xoffset, rtLower.Y - Yoffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, xStart[frame] * w, lowerBody_yStart, w, h, UnitPixel);
		graphics->DrawImage(bitmap, rtUpper, xStart[frame] * w, upperBody_yStart, w, h, UnitPixel);
	}
}

void AniEriStop(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	int Body_yStart = 0;
	int w = 36;
	int h = 36;
	int frame = curFrame % FrameCount_Stop;
	if (frame >= 11) bRunLoop = false;
	
	if (bFlipX == false)
	{
		int xStart[FrameCount_Stop] = { 0,1,2,3,3,2,2,1,1,0,0,0 };
		Rect rt(pPos.X, pPos.Y, 50, 50);

		graphics->DrawImage(bitmap, rt, xStart[frame] * w, Body_yStart, w, h, UnitPixel);
	}
	else
	{
		int xStart[FrameCount_Stop] = { 3,2,1,0,0,1,1,2,2,3,3,3 };
		Rect rt(pPos.X, pPos.Y, 50, 50);

		graphics->DrawImage(bitmap, rt, xStart[frame] * w, Body_yStart, w, h, UnitPixel);
	}
}

void AniEriRun(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	int w = 36;
	int h = 36;
	int upperBody_yStart = 0;
	int lowerBody_yStart = upperBody_yStart + h;
	int upperBody_yOffset = 10;
	int upperBody_xOffset = 4;
	int frame;
	int xStart_Upper;
	int xStart_Lower;

	if (bFlipX == false)
	{
		if (bRunLoop == true)
		{
			frame = curFrame % (FrameCount_Run - FrameCount_RunStart);
			xStart_Upper = w * frame; // 0 ~ 11
			xStart_Lower = w * (frame + FrameCount_RunStart); // 4 ~ 15
		}
		else
		{
			frame = curFrame % FrameCount_RunStart;
			xStart_Upper = w * frame; // 0 ~ 3
			xStart_Lower = w * frame; // 0 ~ 3
			if (frame >= 3) bRunLoop = true;
		}

		Rect rtLower(pPos.X, pPos.Y, 50, 50);
		Rect rtUpper(rtLower.X + upperBody_xOffset, rtLower.Y - upperBody_yOffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, xStart_Lower, lowerBody_yStart, w, h, UnitPixel);
		graphics->DrawImage(bitmap, rtUpper, xStart_Upper, upperBody_yStart, w, h, UnitPixel);
	}
	else
	{
		if (bRunLoop == true)
		{
			frame = (FrameCount_Run - FrameCount_RunStart - 1) - (curFrame % (FrameCount_Run - FrameCount_RunStart));
			xStart_Upper = w * (frame + FrameCount_RunStart); // 15 ~ 4
			xStart_Lower = w * frame; // 11 ~ 0
		}
		else
		{
			frame = (FrameCount_Run - 1) - (curFrame % FrameCount_RunStart);
			xStart_Upper = w * frame; // 15 ~ 12
			xStart_Lower = w * frame; // 15 ~ 12
			if (frame <= 12) bRunLoop = true;
		}

		Rect rtLower(pPos.X, pPos.Y, 50, 50);
		Rect rtUpper(rtLower.X - upperBody_xOffset, rtLower.Y - upperBody_yOffset, rtLower.Width, rtLower.Height);

		graphics->DrawImage(bitmap, rtLower, xStart_Lower, lowerBody_yStart, w, h, UnitPixel);
		graphics->DrawImage(bitmap, rtUpper, xStart_Upper, upperBody_yStart, w, h, UnitPixel);
	}
}

void AniEriLooUp(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
	int w = 36;
	int h = 36;
	int upperBody_yStart = 0;
	int upperBody_yOffset = 10;
	int frame;

	// TODO : 
	if (bFlipX == false)
	{
		
	}
	else
	{
		if (bLookUpLoop == true)
		{
			frame = lookUpFrame % FrameCount_LookUpStart;
			lookUpFrame++;
			if (frame >= 1)
			{
				bLookUpLoop = true;
				lookUpFrame = 0;
			}
		}
		else
		{

		}
	}
}

void AniEriTurn(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX)
{
}
