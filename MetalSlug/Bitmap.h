#pragma once

#include "framework.h"

void InitRectView(RECT rect);
void CreateBitmap();
void DrawBitmap(HWND hWnd, HDC hdc);
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
void DeleteBitmap();

void Gdi_Init();
void Gdi_Draw(HDC hdc);
void Gdi_End();

CachedBitmap* ImageToCachedBitmap(Image* pImg, int ImgWidth, int ImgHeight);

void UpdateFrame(HWND hWnd);

void DrawBackGround(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap);

void AniEriIdle(Graphics* graphics);
void AniEriJump(Graphics* graphics);
