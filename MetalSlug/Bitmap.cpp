#include "framework.h"
#include "Game.h"
#include "Player.h"
#include "Collision.h"
#include "Geometry.h"
#include "Bitmap.h"

using namespace std;
using namespace metalSlug;

ULONG_PTR g_GdiplusToken;

HBITMAP hDoubleBufferImg;
RECT rectView;

Geometry* geometry;

int curFrame = 0;
int FrameMax = 0;
int FrameMin = 0;

void UpdateRectView(RECT rect)
{
	rectView = rect;
}

void CreateBitmap()
{
	geometry = new Geometry();
}

void DrawBitmap(HWND hWnd, HDC hdc)
{
	geometry->DrawBackBitmap(hWnd, hdc);
	
	Gdi_Draw(hdc);

	geometry->DrawFrontBitmap(hWnd, hdc);

	if (IsDebugMode() == true)
		Gdi_DrawDebug(hdc);
}

void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
	HDC hDoubleBufferDC;
	HBITMAP hOldDoubleBufferBitmap;

	hDoubleBufferDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImg == NULL)
	{
		hDoubleBufferImg = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
	}
	hOldDoubleBufferBitmap = (HBITMAP)SelectObject(hDoubleBufferDC, hDoubleBufferImg);

	DrawBitmap(hWnd, hDoubleBufferDC);

	BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hDoubleBufferDC, 0, 0, SRCCOPY);
	SelectObject(hDoubleBufferDC, hOldDoubleBufferBitmap);
	DeleteDC(hDoubleBufferDC);
}

void DeleteBitmap()
{
}

void Gdi_Init()
{
	GdiplusStartupInput gpsi;
	GdiplusStartup(&g_GdiplusToken, &gpsi, NULL);
	
	CreateObject();
	//=====================================================================================================================
	// EnemyCharacter
	//=====================================================================================================================

}

void Gdi_Draw(HDC hdc)
{
	Graphics graphics(hdc);

	DrawObject(&graphics);
}

void Gdi_DrawDebug(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0));
	if (GetPlayer() != NULL)
	{
		Collision* pCollision = GetPlayer()->GetCollider();
		graphics.DrawRectangle(&pen, pCollision->GetCollisionBox());
	}
}

void Gdi_End()
{
	DeleteObject();

	GdiplusShutdown(g_GdiplusToken);
}

void UpdateFrame(HWND hWnd)
{
	curFrame++;
	if (curFrame > FrameMax)
		curFrame = FrameMin;
}
