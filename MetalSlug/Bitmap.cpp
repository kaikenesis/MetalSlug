#include "framework.h"
#include "Player.h"
#include "Collision.h"
#include "Geometry.h"
#include "WeaponSFX.h"
#include "Bullet.h"
#include "RebelSoldier.h"
#include "RebelProjectile.h"
#include "SelectScreen.h"
#include "Bitmap.h"

using namespace std;
using namespace metalSlug;

ULONG_PTR g_GdiplusToken;

HBITMAP hDoubleBufferImg;
RECT rectView;

int curFrame = 0;
int FrameMax = 0;
int FrameMin = 0;
int fadeAlpha = 0;
int fadeDelay = 100;

bool bFadeIn = true;

void UpdateRectView(RECT rect)
{
	rectView = rect;
}

void InitBitmap()
{
	CreateImages();
	CreateGeometry();
	CreateSelectScreenUI();
}

void DrawBitmap(HWND hWnd, HDC hdc)
{
	switch (GetGameMode())
	{
	case EGameMode::Title:
	{
		GetSelectScreen()->Update(hWnd, hdc);
	}
		break;
	case EGameMode::InGame:
	{
		GetGeometry()->DrawBackBitmap(hWnd, hdc); // 뒷배경
		DrawCharacter(hWnd, hdc); // 캐릭터
		GetGeometry()->DrawFrontBitmap(hWnd, hdc); // 앞에 가리는 배경
		DrawProjectile(hWnd, hdc); // 투사체

		if (IsDebugMode() == true)
		{
			DrawDebugText(hdc);
			Gdi_DrawDebug(hdc);
		}
	}
		break;
	}
	
	DrawFadeInOut(hdc);
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

void DrawCharacter(HWND hWnd, HDC hdc)
{
	// 적 캐릭터
	std::vector<Enemy*> enemys = GetEnemys();
	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i]->IsActive() == true)
			enemys[i]->PlayAnimation(hdc);
	}

	// 플레이어 캐릭터
	Gdi_Draw(hdc);
}

void DrawProjectile(HWND hWnd, HDC hdc)
{
	// 적 투사체
	std::vector<RebelProjectile*> projectiles = GetEnemyProjectiles();
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->IsActive() == true)
			projectiles[i]->Update(hWnd, hdc);
	}
		

	// 플레이어 투사체
	std::vector<Bullet*> bullets = GetPlayerProjectiles();
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->IsActive() == true)
			bullets[i]->Update(hWnd, hdc);
	}
}

void DrawFadeInOut(HDC hdc)
{
	if (IsPlayFadeInOut() == false) return;

	int speed = 10;
	Graphics graphics(hdc);
	int alpha = fadeAlpha;
	if (bFadeIn == true)
	{
		fadeAlpha += speed;
		if (fadeAlpha > 255)
		{
			fadeAlpha = 255;
			SetGameMode(EGameMode::InGame);
			GetSelectScreen()->Init();
			PlayBGM();

			fadeDelay--;
			if (fadeDelay < 0)
			{
				fadeDelay = 100;
				bFadeIn = false;
			}
		}
	}
	else
	{
		fadeAlpha -= speed;
		if (fadeAlpha < 0)
		{
			fadeAlpha = 0;
			SetPlayFadeInOut(false);
		}
	}
	SolidBrush brush(Color(alpha, 0, 0, 0));

	RECT rt = GetCamera()->GetCameraViewport();
	graphics.FillRectangle(&brush, Rect(rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top));
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

	memset(buffer, 0, sizeof(buffer));
	sprintf_s(buffer, "active EnemyCount : %d", GetEnemyCount());
	TextOutA(hdc, 0, 100, buffer, strlen(buffer));

	memset(buffer, 0, sizeof(buffer));
	sprintf_s(buffer, "active EnemyProjectileCount : %d", GetEnemyProjectileCount());
	TextOutA(hdc, 0, 120, buffer, strlen(buffer));
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

	GetPlayer()->PlayAnimation(&graphics);
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

	std::vector<Enemy*> enemys = GetEnemys();
	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i]->IsActive())
		{
			if (enemys[i]->IsDead() == true) pen.SetColor(Color(0, 255, 0));
			else pen.SetColor(Color(255, 0, 0));
			
			graphics.DrawRectangle(&pen, enemys[i]->GetCollision()->GetLocalRect());
		}
	}
	
	if (GetPlayer() != NULL)
	{
		Collision* pCollision = GetPlayer()->GetCollider();
		if(pCollision->IsActive() == true) pen.SetColor(Color(255, 0, 0));
		else pen.SetColor(Color(0, 255, 0));

		graphics.DrawRectangle(&pen, pCollision->GetLocalRect());
	}

	std::vector<RebelProjectile*> projectiles = GetEnemyProjectiles();
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->IsActive() == true)
		{
			if (projectiles[i]->IsHit() == true) pen.SetColor(Color(0, 255, 0));
			else pen.SetColor(Color(255, 0, 0));

			graphics.DrawRectangle(&pen, projectiles[i]->GetCollision()->GetLocalRect());
		}
	}

	std::vector<Bullet*> bullets = GetPlayerProjectiles();
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->IsActive() == true)
		{
			if (bullets[i]->IsHit() == true) pen.SetColor(Color(0, 255, 0));
			else pen.SetColor(Color(255, 0, 0));

			graphics.DrawRectangle(&pen, bullets[i]->GetCollision()->GetLocalRect());
		}
	}
}

void Gdi_End()
{
	DeleteObject();

	GdiplusShutdown(g_GdiplusToken);
}
