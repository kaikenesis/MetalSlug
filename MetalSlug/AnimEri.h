#pragma once

#include "framework.h"

namespace Eri
{
	int GetEriIdleFrame();
	int GetEriJumpIdleStartFrame();
	int GetEriJumpRunStartFrame();
	int GetEriStopFrame();
	int GetEriRunStartFrame();
	int GetEriRunFrame();
	int GetEriLooUpStartFrame();
	int GetEriLooUpFrame();
	BOOL IsRunLoop();

	void Init();
	void Delete();

	void SetRunLoop(bool inValue);
	void SetLookUp(bool inValue);
	void SetFlip(bool inValue);

	void PlayEriAnimation(Graphics* graphics);
	void AniEriIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
	void AniEriJumpIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
	void AniEriJumpRun(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
	void AniEriStop(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
	void AniEriRun(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
	void AniEriLooUp(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
	void AniEriTurn(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
}

