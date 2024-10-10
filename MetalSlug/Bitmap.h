#pragma once

void UpdateRectView(RECT rect);
void CreateBitmap();
void DrawBitmap(HWND hWnd, HDC hdc);
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
void DeleteBitmap();

void Gdi_Init();
void Gdi_Draw(HDC hdc);
void Gdi_DrawDebug(HDC hdc);
void Gdi_End();

void UpdateFrame(HWND hWnd);