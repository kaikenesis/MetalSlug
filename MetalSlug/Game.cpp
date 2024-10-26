#include "framework.h"
#include "Game.h"
#include "Player.h"
#include "Geometry.h"
#include "WeaponSFX.h"
#include "RebelSoldier.h"

using namespace std;

#define RebelSoldier_Count 10

Player* player;
Player* testPlayer;
Camera* camera;
Geometry* geometry;
WeaponSFX* weaponSFX;
std::vector<RebelSoldier*> rebelSoldiers;
POINT clickPos = { 0,0 };
Images* images;

float g_ratio = 3.0f;
bool bDebug = true;
bool bRuinDestroy = false;
int ActiveBulletCount = 0;
int ActiveEnemyCount = 0;

void metalSlug::CreateObject()
{
	player = new Player();
	for (int i = 0; i < RebelSoldier_Count; i++)
	{
		RebelSoldier* object = new RebelSoldier();
		rebelSoldiers.push_back(object);
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

void metalSlug::CreateWeaponSFX()
{
	weaponSFX = new WeaponSFX();
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
	//testPlayer->Update();
}

void metalSlug::DeleteObject()
{
	delete player;
	//delete testPlayer;
	delete weaponSFX;
	delete geometry;
	delete images;

	for (int i = 0; i < RebelSoldier_Count; i++)
		delete rebelSoldiers[i];
}

float metalSlug::GetGlobalRatio() { return g_ratio; }
Player* metalSlug::GetPlayer() { return player; }
Images* metalSlug::GetImages() { return images; }
Geometry* metalSlug::GetGeometry() { return geometry; }
WeaponSFX* metalSlug::GetWeaponSFX() { return weaponSFX; }
std::vector<class RebelSoldier*> metalSlug::GetRebelSoldiers() { return rebelSoldiers; }

BOOL metalSlug::IsDebugMode() { return bDebug; }
POINT metalSlug::GetMouseClickPos() { return clickPos; }
int metalSlug::GetBulletCount() { return ActiveBulletCount; }

void metalSlug::SetDebugMode(bool inValue) { bDebug = inValue; }
void metalSlug::SetMouseClickPos(POINT point) { clickPos = point; }
void metalSlug::SetBulletCount(int value) { ActiveBulletCount = value; }
void metalSlug::SetEnmeyCount(int value) { ActiveEnemyCount = value; }

void metalSlug::DebugDestroyRuin()
{
	bRuinDestroy = !bRuinDestroy;
	geometry->DestroyRuin(bRuinDestroy);
}

void metalSlug::DebugSpawnEnemy()
{
	for (int i = 0; i < RebelSoldier_Count; i++)
	{
		if (rebelSoldiers[i]->IsActive() == false)
		{
			POINT point = { 500,300 };
			Rect rt(point.x, point.y, 54, 114);
			PointF speed = { 1.0f,0.0f };
			rebelSoldiers[i]->SetInfo(point, rt, speed, 10);

			rebelSoldiers[i]->SetActivate(true);
		}
	}
}

void metalSlug::DebugFlipEnemys()
{
	for (int i = 0; i < RebelSoldier_Count; i++)
	{
		if (rebelSoldiers[i]->IsActive() == true)
		{
			rebelSoldiers[i]->SetFlip();
		}
	}
}

void metalSlug::DebugChangeEnemysState()
{
	for (int i = 0; i < RebelSoldier_Count; i++)
	{
		if (rebelSoldiers[i]->IsActive() == true)
		{
			rebelSoldiers[i]->DebugChangeState();
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
