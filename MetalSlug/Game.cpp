#include "Game.h"
#include "Player.h"

using namespace std;
using namespace metalSlug;

Player* player;
Player* testPlayer;

void metalSlug::CreateObject()
{
	player = new Player();
	testPlayer = new Player();
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
