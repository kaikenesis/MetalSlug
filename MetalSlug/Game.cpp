#include "framework.h"
#include "Game.h"
#include "Player.h"

using namespace std;
using namespace metalSlug;

Player* player;
Player* testPlayer;
Camera* camera;

void metalSlug::CreateObject()
{
	player = new Player();
	testPlayer = new Player();
	camera = new Camera();
}

void metalSlug::UpdateObject()
{
	DWORD newTime = GetTickCount();
	static DWORD oldTime = newTime;

	if (newTime - oldTime < 20)
		return;
	oldTime = newTime;

	player->Update();
	testPlayer->Update();
}

void metalSlug::DrawObject(Graphics* graphics)
{
	player->PlayAnimation(graphics);
	testPlayer->PlayDebugAnimation(graphics);
}

void metalSlug::DeleteObject()
{
	delete player;
	delete testPlayer;
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
