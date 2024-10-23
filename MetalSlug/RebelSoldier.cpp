#include "framework.h"
#include "Game.h"
#include "Collision.h"
#include "AnimRebelSoldier.h"
#include "RebelSoldier.h"

metalSlug::RebelSoldier::RebelSoldier()
	:Enemy()
{
	
}

metalSlug::RebelSoldier::RebelSoldier(POINT WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth)
	:Enemy(WorldPos, CollisionRect, Speed, MaxHealth)
{
}

metalSlug::RebelSoldier::~RebelSoldier()
{
}

void metalSlug::RebelSoldier::DoAction()
{

}

void metalSlug::RebelSoldier::MoveTo()
{
}

void metalSlug::RebelSoldier::Dead()
{
}

void metalSlug::RebelSoldier::Encounter()
{
}

void metalSlug::RebelSoldier::Update()
{

}

bool metalSlug::RebelSoldier::PlayAnimation(HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	switch (currentState)
	{
	case Idle:
		GetAnimRebelSoldier()->PlayIdle(hdc, hMemDC, hOldBitmap, worldPos);
		break;
	case Run:
		break;
	case Action:
		break;
	case Death:
		break;
	case Surprise:
		break;

	default: break;
	}

	return false;
}

void metalSlug::RebelSoldier::SetInfo(POINT WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth)
{
	UpdateWorldPos(WorldPos);
	speed = Speed;
	maxHealth = MaxHealth;
	InitHealth();
	collision->SetInfo(CollisionRect.X, CollisionRect.Y, CollisionRect.Width, CollisionRect.Height, ERenderType::RWorld);
}
