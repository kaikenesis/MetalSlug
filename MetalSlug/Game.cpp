#include "framework.h"
#include "Game.h"
#include "Player.h"
#include "Geometry.h"

using namespace std;
using namespace metalSlug;

Player* player;
Player* testPlayer;
Camera* camera;
Geometry* geometry;
POINT clickPos = { 0,0 };

float g_ratio = 3.0f;
bool bDebug = true;
bool bRuinDestroy = false;

void metalSlug::CreateObject()
{
	player = new Player();
	//testPlayer = new Player();
}

void metalSlug::CreateCamera(RECT rect)
{
	camera = new Camera(rect);
}

void metalSlug::CreateGeometry()
{
	geometry = new Geometry();
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

void metalSlug::DrawObject(Graphics* graphics)
{
	player->PlayAnimation(graphics);
	//testPlayer->PlayDebugAnimation(graphics);
}

void metalSlug::DeleteObject()
{
	delete player;
	//delete testPlayer;
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

void metalSlug::SetMouseClickPos(POINT point)
{
	clickPos = point;
}

POINT metalSlug::GetMouseClickPos()
{
	return clickPos;
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
