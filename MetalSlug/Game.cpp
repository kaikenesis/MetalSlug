#include "framework.h"
#include "Game.h"
#include "Player.h"
#include "Geometry.h"
#include "Bullet.h"
#include "RebelSoldier.h"
#include "RebelProjectile.h"

using namespace std;

#define Enemy_Count 10
#define PlayerProjectile_Count 30
#define EnemyProjectile_Count 5

Player* player;
Camera* camera;
Geometry* geometry;
std::vector<Enemy*> enemys;
std::vector<Bullet*> playerProjectiles;
std::vector<RebelProjectile*> rebelProjectiles;
POINT clickPos = { 0,0 };
Images* images;

float g_ratio = 3.0f;
bool bDebug = true;
bool bRuinDestroy = false;
int ActiveBulletCount = 0;
int ActiveEnemyProjectileCount = 0;
int ActiveEnemyCount = 0;

void metalSlug::CreateObject()
{
	player = new Player();
	
	for (int i = 0; i < PlayerProjectile_Count; i++)
	{
		Bullet* object = new Bullet();
		playerProjectiles.push_back(object);
	}

	for (int i = 0; i < Enemy_Count; i++)
	{
		RebelSoldier* object = new RebelSoldier();
		enemys.push_back(object);
	}

	for (int i = 0; i < Enemy_Count * EnemyProjectile_Count; i++)
	{
		RebelProjectile* object = new RebelProjectile();
		rebelProjectiles.push_back(object);
	}
}

void metalSlug::CreateCamera(RECT rect)
{
	camera = new Camera(rect);
}

void metalSlug::CreateGeometry()
{
	geometry = new Geometry();
}

void metalSlug::CreateImages()
{
	images = new Images();
}

void metalSlug::UpdateObject()
{
	DWORD newTime = GetTickCount();
	static DWORD oldTime = newTime;

	if (newTime - oldTime < 20)
		return;
	oldTime = newTime;

	player->Update();
	for (int i = 0; i < Enemy_Count; i++)
	{
		if (enemys[i]->IsActive() == true)
			enemys[i]->Update();
	}
}

void metalSlug::DeleteObject()
{
	delete player;
	delete geometry;
	delete images;

	for (int i = 0; i < Enemy_Count; i++)
		delete enemys[i];
	for (int i = 0; i < Enemy_Count * EnemyProjectile_Count; i++)
		delete rebelProjectiles[i];
}

float metalSlug::GetGlobalRatio() { return g_ratio; }
Player* metalSlug::GetPlayer() { return player; }
Images* metalSlug::GetImages() { return images; }
Geometry* metalSlug::GetGeometry() { return geometry; }
std::vector<class Enemy*> metalSlug::GetEnemys() { return enemys; }
std::vector<class Bullet*> metalSlug::GetPlayerProjectiles() { return playerProjectiles; }
std::vector<class RebelProjectile*> metalSlug::GetEnemyProjectiles() { return rebelProjectiles; }

bool metalSlug::IsCanSpawnProjectile() { return ActiveEnemyProjectileCount < Enemy_Count * EnemyProjectile_Count; }

bool metalSlug::IsDebugMode() { return bDebug; }
POINT metalSlug::GetMouseClickPos() { return clickPos; }
int metalSlug::GetBulletCount() { return ActiveBulletCount; }
int metalSlug::GetEnemyCount() { return ActiveEnemyCount; }
int metalSlug::GetEnemyProjectileCount() { return ActiveEnemyProjectileCount; }

void metalSlug::SetDebugMode(bool inValue) { bDebug = inValue; }
void metalSlug::SetMouseClickPos(POINT point) { clickPos = point; }
void metalSlug::SetBulletCount(int value) { ActiveBulletCount = value; }
void metalSlug::SetEnemyCount(int value) { ActiveEnemyCount = value; }
void metalSlug::SetEnemyProjectileCount(int value) { ActiveEnemyProjectileCount = value; }

void metalSlug::DebugDestroyRuin()
{
	bRuinDestroy = !bRuinDestroy;
	geometry->DestroyRuin(bRuinDestroy);
}

void metalSlug::DebugSpawnEnemy()
{
	for (int i = 0; i < Enemy_Count; i++)
	{
		if (enemys[i]->IsActive() == false)
		{
			RebelSoldier* rebelSoldier = (RebelSoldier*)enemys[i];
			if (rebelSoldier != NULL)
			{
				PointF point = { player->GetWorldPlayerPos().X + 500, player->GetWorldPlayerPos().Y - 300 };
				int w = 54;
				int h = 114;
				Rect rt(point.X - w / 2, point.Y - h / 2, w, h);
				PointF speed = { 2.0f,0.0f };
				rebelSoldier->SetInfo(point, rt, speed, 1);

				rebelSoldier->SetActivate(true);
				break;
			}
		}
	}
}

void metalSlug::DebugFlipEnemys()
{
	for (int i = 0; i < Enemy_Count; i++)
	{
		if (enemys[i]->IsActive() == true)
		{
			enemys[i]->SetFlip();
			break;
		}
	}
}

void metalSlug::DebugChangeEnemysState()
{
	for (int i = 0; i < Enemy_Count; i++)
	{
		if (enemys[i]->IsActive() == true)
		{
			RebelSoldier* rebelSoldier = (RebelSoldier*)enemys[i];
			if (rebelSoldier != NULL)
			{
				rebelSoldier->DebugChangeState();
				break;
			}
		}
	}
}

Camera* metalSlug::GetCamera()
{
	return camera;
}

metalSlug::Camera::Camera()
{
}

metalSlug::Camera::Camera(RECT rect)
{
	Init(rect);
}

metalSlug::Camera::~Camera()
{
	
}

void metalSlug::Camera::Init(RECT rect)
{
	UpdateScale(rect.right - rect.left, rect.bottom - rect.top);
	UpdatePosition(rect.left, rect.top);
}

void metalSlug::Camera::Update()
{

}

void metalSlug::Camera::UpdatePosition(int inX, int inY)
{
	rectView.left = inX;
	rectView.right = inX + width;
	rectView.top = inY;
	rectView.bottom = inY + height;
}

void metalSlug::Camera::UpdateScale(double inWidth, double inHeight)
{
	width = inWidth;
	height = inHeight;
}
