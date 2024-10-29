#include "framework.h"
#include "Game.h"
#include "Camera.h"
#include "Player.h"
#include "Geometry.h"
#include "Bullet.h"
#include "RebelSoldier.h"
#include "RebelProjectile.h"
#include "SelectScreen.h"

using namespace std;

#define Enemy_Count 10
#define PlayerProjectile_Count 30
#define EnemyProjectile_Count 5

EGameMode gameMode = Title;
Player* player;
Camera* camera;
Geometry* geometry;
std::vector<Enemy*> enemys;
std::vector<Bullet*> playerProjectiles;
std::vector<RebelProjectile*> rebelProjectiles;
POINT mousePos = { 0,0 };
POINT clickPos = { 0,0 };
Images* images;
SelectScreen* selectScreen;
MySound* sound;

float g_ratio = 3.0f;
bool bDebug = false;
bool bRuinDestroy = false;
bool bPlayFadeInOut = false;
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

void metalSlug::CreateSelectScreenUI()
{
	selectScreen = new SelectScreen();
}

void metalSlug::CreateSound()
{
	sound = new MySound();
}

void metalSlug::UpdateKeyInput()
{
	DWORD newTime = GetTickCount();
	static DWORD oldTime = newTime;

	if (newTime - oldTime < 20)
		return;
	oldTime = newTime;

	switch (gameMode)
	{
	case Title:
		break;
	case InGame:
		break;
	}

	player->Update();
}

void metalSlug::UpdateObject()
{
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

void metalSlug::SelectSoldier()
{
	GetSelectScreen()->SelectCharacter();
}

void metalSlug::PlayBGM()
{
	sound->PlayingBGM();
}

float metalSlug::GetGlobalRatio() { return g_ratio; }
EGameMode metalSlug::GetGameMode() { return gameMode; }
Camera* metalSlug::GetCamera() { return camera; }
Player* metalSlug::GetPlayer() { return player; }
Images* metalSlug::GetImages() { return images; }
Geometry* metalSlug::GetGeometry() { return geometry; }
SelectScreen* metalSlug::GetSelectScreen() { return selectScreen; }
MySound* metalSlug::GetSound() { return sound; }
std::vector<class Enemy*> metalSlug::GetEnemys() { return enemys; }
std::vector<class Bullet*> metalSlug::GetPlayerProjectiles() { return playerProjectiles; }
std::vector<class RebelProjectile*> metalSlug::GetEnemyProjectiles() { return rebelProjectiles; }

bool metalSlug::IsCanSpawnProjectile() { return ActiveEnemyProjectileCount < Enemy_Count * EnemyProjectile_Count; }
bool metalSlug::IsSelectSoldier() { return selectScreen->IsSelect(); }
bool metalSlug::IsPlayFadeInOut() { return bPlayFadeInOut; }

bool metalSlug::IsDebugMode() { return bDebug; }
POINT metalSlug::GetMouseClickPos() { return clickPos; }
POINT metalSlug::GetMousePos() { return mousePos; }
int metalSlug::GetBulletCount() { return ActiveBulletCount; }
int metalSlug::GetEnemyCount() { return ActiveEnemyCount; }
int metalSlug::GetEnemyProjectileCount() { return ActiveEnemyProjectileCount; }

void metalSlug::SetDebugMode(bool inValue) { bDebug = inValue; }
void metalSlug::SetMouseClickPos(POINT point) { clickPos = point; }
void metalSlug::SetMousePos(POINT point) { mousePos = point; }
void metalSlug::SetBulletCount(int value) { ActiveBulletCount = value; }
void metalSlug::SetEnemyCount(int value) { ActiveEnemyCount = value; }
void metalSlug::SetEnemyProjectileCount(int value) { ActiveEnemyProjectileCount = value; }
void metalSlug::SetGameMode(EGameMode newGameMode) { gameMode = newGameMode; }
void metalSlug::SetPlayFadeInOut(bool value) { bPlayFadeInOut = value; }

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
