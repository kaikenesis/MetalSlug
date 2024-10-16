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

void InitBitmap()
{
	geometry = new Geometry();
}

void DrawBitmap(HWND hWnd, HDC hdc)
{
	geometry->DrawBackBitmap(hWnd, hdc);
	
	Gdi_Draw(hdc);

	geometry->DrawFrontBitmap(hWnd, hdc);

	if (IsDebugMode() == true)
	{
		DrawDebug(hdc);
		Gdi_DrawDebug(hdc);
	}
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

void DrawDebug(HDC hdc)
{
	char buffer[100];
	sprintf_s(buffer, "%d", GetCamera()->GetCameraViewport().left);
	TextOutA(hdc, 0, 0, buffer, strlen(buffer));

	memset(buffer, 0, sizeof(buffer));
	sprintf_s(buffer, "player pos ( x : %d, y : %d )", GetPlayer()->GetCollisionBoxWorldPos().X, GetPlayer()->GetCollisionBoxWorldPos().Y);
	TextOutA(hdc, 0, 20, buffer, strlen(buffer));

	// 마우스 클릭할때마다 해당 월드 위치 좌표값 출력
	memset(buffer, 0, sizeof(buffer));
	sprintf_s(buffer, "click point ( x : %d, y : %d )", GetMouseClickPos().x, GetMouseClickPos().y);
	TextOutA(hdc, 0, 40, buffer, strlen(buffer));
}

void DestroyBitmap()
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
		graphics.DrawRectangle(&pen, pCollision->GetRect());
	}

	if (geometry != NULL)
	{
		std::vector<Collision*> collisions = geometry->GetGeometryCollisions();
		for (int i = 0; i < collisions.size(); i++)
		{
			graphics.DrawPolygon(&pen, collisions[i]->GetPolygon(), collisions[i]->GetPointCount());
		}
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
