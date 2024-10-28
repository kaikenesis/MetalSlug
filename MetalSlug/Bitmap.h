#pragma once

void UpdateRectView(RECT rect);
void InitBitmap();
void DrawBitmap(HWND hWnd, HDC hdc);
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);

void DrawCharacter(HWND hWnd, HDC hdc);
void DrawProjectile(HWND hWnd, HDC hdc);

void DrawDebugText(HDC hdc);
void DestroyBitmap();

void Gdi_Init();
void Gdi_Draw(HDC hdc);
void Gdi_DrawDebug(HDC hdc);
void Gdi_End();