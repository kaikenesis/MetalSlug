#include "framework.h"
#include "Game.h"
#include "Player.h"
#include "Geometry.h"
#include "WeaponSFX.h"
#include "RebelSoldier.h"
#include "AnimRebelSoldier.h"

using namespace std;
using namespace metalSlug;

#define RebelSoldier_Count 10

Player* player;
Player* testPlayer;
Camera* camera;
Geometry* geometry;
WeaponSFX* weaponSFX;
AnimRebelSoldier* animRebelSoldier;
std::vector<RebelSoldier*> rebelSoldiers;
POINT clickPos = { 0,0 };

float g_ratio = 3.0f;
bool bDebug = true;
bool bRuinDestroy = false;
int ActiveBulletCount = 0;

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

void metalSlug::CreateAnimData()
{
	animRebelSoldier = new AnimRebelSoldier();
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
	delete geometry;
	delete weaponSFX;

	for (int i = 0; i < RebelSoldier_Count; i++)
		delete rebelSoldiers[i];
}

float metalSlug::GetGlobalRatio()
{
	return g_ratio;
}

BOOL metalSlug::IsDebugMode()
{
	return bDebug;
}

Player* metalSlug::GetPlayer()
{
	return player;
}

Geometry* metalSlug::GetGeometry()
{
	return geometry;
}

WeaponSFX* metalSlug::GetWeaponSFX()
{
	return weaponSFX;
}

AnimRebelSoldier* metalSlug::GetAnimRebelSoldier()
{
	return animRebelSoldier;
}

std::vector<class RebelSoldier*> metalSlug::GetRebelSoldiers()
{
	return rebelSoldiers;
}

void metalSlug::SetMouseClickPos(POINT point)
{
	clickPos = point;
}

void metalSlug::SetBulletCount(int value)
{
	ActiveBulletCount = value;
}

POINT metalSlug::GetMouseClickPos()
{
	return clickPos;
}

int metalSlug::GetBulletCount()
{
	return ActiveBulletCount;
}

void metalSlug::SetDebugMode(bool inValue)
{
	bDebug = inValue;
}

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
			Rect rt(point.x, point.y, 100, 200);
			PointF speed = { 1.0f,0.0f };
			rebelSoldiers[i]->SetInfo(point, rt, speed, 10);

			rebelSoldiers[i]->SetActivate(true);
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
