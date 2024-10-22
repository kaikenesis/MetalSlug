#include "framework.h"
#include "Game.h"
#include "Player.h"
#include "Collision.h"
#include "Geometry.h"
#include "WeaponSFX.h"
#include "Bullet.h"
#include "Bitmap.h"

using namespace std;
using namespace metalSlug;

ULONG_PTR g_GdiplusToken;

HBITMAP hDoubleBufferImg;
RECT rectView;

int curFrame = 0;
int FrameMax = 0;
int FrameMin = 0;

void UpdateRectView(RECT rect)
{
	rectView = rect;
}

void InitBitmap()
{
	CreateGeometry();
	CreateWeaponSFX();
}

void DrawBitmap(HWND hWnd, HDC hdc)
{
	GetGeometry()->DrawBackBitmap(hWnd, hdc);
	
	Gdi_Draw(hdc);

	GetGeometry()->DrawFrontBitmap(hWnd, hdc);
	GetPlayer()->UpdateBullets(hWnd, hdc);

	if (IsDebugMode() == true)
	{
		DrawDebugText(hdc);
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

void DrawDebugText(HDC hdc)
{
	char buffer[100];
	sprintf_s(buffer, "camera worldPos ( x : %d, y : %d)", GetCamera()->GetCameraViewport().left, GetCamera()->GetCameraViewport().top);
	TextOutA(hdc, 0, 0, buffer, strlen(buffer));

	memset(buffer, 0, sizeof(buffer));
	sprintf_s(buffer, "player localPos ( x : %.2f, y : %.2f )", GetPlayer()->GetLocalPlayerPos().X, GetPlayer()->GetLocalPlayerPos().Y);
	TextOutA(hdc, 0, 20, buffer, strlen(buffer));

	memset(buffer, 0, sizeof(buffer));
	sprintf_s(buffer, "player worldPos ( x : %.2f, y : %.2f )", GetPlayer()->GetWorldPlayerPos().X, GetPlayer()->GetWorldPlayerPos().Y);
	TextOutA(hdc, 0, 40, buffer, strlen(buffer));

	// 마우스 클릭할때마다 해당 월드 위치 좌표값 출력
	memset(buffer, 0, sizeof(buffer));
	sprintf_s(buffer, "click worldPos ( x : %d, y : %d )", GetMouseClickPos().x, GetMouseClickPos().y);
	TextOutA(hdc, 0, 60, buffer, strlen(buffer));

	memset(buffer, 0, sizeof(buffer));
	sprintf_s(buffer, "active bulletCount : %d", GetBulletCount());
	TextOutA(hdc, 0, 80, buffer, strlen(buffer));
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

	if (GetGeometry() != NULL)
	{
		std::vector<Collision*> collisions = GetGeometry()->GetGeometryCollisions();
		for (int i = 0; i < collisions.size(); i++)
		{
			if (collisions[i]->IsActive() == false) pen.SetColor(Color(0, 255, 0));
			else pen.SetColor(Color(255, 0, 0));

			switch (collisions[i]->GetType())
			{
			case CPolygon:
				graphics.DrawPolygon(&pen, collisions[i]->GetLocalPolygon(), collisions[i]->GetPointCount());
				break;
			case CRect:
				graphics.DrawRectangle(&pen, collisions[i]->GetLocalRect());
				break;
			default:
				break;
			}
		}
	}

	pen.SetColor(Color(255, 0, 0));
	if (GetPlayer() != NULL)
	{
		Collision* pCollision = GetPlayer()->GetCollider();
		graphics.DrawRectangle(&pen, pCollision->GetLocalRect());

		std::vector<Bullet*> bullets = GetPlayer()->GetBullets();
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i]->IsActive() == true)
			{
				graphics.DrawRectangle(&pen, bullets[i]->GetCollision()->GetWorldRect());
			}
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
