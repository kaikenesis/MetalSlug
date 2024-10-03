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

void UpdateFrame(HWND hWnd);
void DrawBackGround(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap);

void SetFlip();

void PlayEriAnimation(Graphics* graphics);

int Gcd(int a, int b);
int Lcm(std::vector<int> arr);