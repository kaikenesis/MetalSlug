#pragma once

#include "framework.h"

int GetEriIdleFrame();
int GetEriJumpIdleStartFrame();
int GetEriJumpRunStartFrame();
int GetEriStopFrame();
int GetEriRunStartFrame();
int GetEriRunFrame();
int GetEriLooUpStartFrame();
int GetEriLooUpFrame();
BOOL IsRunLoop();

void SetRunLoop(bool inValue);

void AniEriIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
void AniEriJumpIdle(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
void AniEriJumpRun(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
void AniEriStop(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
void AniEriRun(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
void AniEriLooUp(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);
void AniEriTurn(Graphics* graphics, PointF pPos, Bitmap* bitmap, int curFrame, bool bFlipX = false);