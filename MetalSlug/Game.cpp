#include "framework.h"
#include "Game.h"
#include "Player.h"

using namespace std;
using namespace metalSlug;

Player* player;
Player* testPlayer;
Camera* camera;

float g_ratio = 2.0f;
bool bDebug = true;

void metalSlug::CreateObject()
{
	player = new Player();
	//testPlayer = new Player();
}

void metalSlug::CreateCamera(RECT rect)
{
	camera = new Camera(rect);
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

void metalSlug::SetDebugMode(bool inValue)
{
	bDebug = inValue;
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
	UpdatePosition(rect.left, rect.top);
	UpdateScale(rect.right - rect.left, rect.bottom - rect.top);
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
