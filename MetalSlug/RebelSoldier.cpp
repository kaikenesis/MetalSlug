#include "framework.h"
#include "Collision.h"
#include "AnimRebelSoldier.h"
#include "RebelSoldier.h"

metalSlug::RebelSoldier::RebelSoldier()
	:Enemy()
{
	animRebelSoldier = new AnimRebelSoldier();
}

metalSlug::RebelSoldier::RebelSoldier(POINT WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth)
	:Enemy(WorldPos, CollisionRect, Speed, MaxHealth)
{
	animRebelSoldier = new AnimRebelSoldier();
}

metalSlug::RebelSoldier::~RebelSoldier()
{
	delete animRebelSoldier;
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
		animRebelSoldier->PlayIdle(hdc, hMemDC, hOldBitmap, worldPos);
		break;
	case Run:
		animRebelSoldier->PlayRun(hdc, hMemDC, hOldBitmap, worldPos);
		break;
	case Action:
		animRebelSoldier->PlayRollingBomb(hdc, hMemDC, hOldBitmap, worldPos);
		break;
	case Death:
		animRebelSoldier->PlayDeath(hdc, hMemDC, hOldBitmap, worldPos);
		break;
	case Surprise:
		animRebelSoldier->PlaySurprise(hdc, hMemDC, hOldBitmap, worldPos);
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

void metalSlug::RebelSoldier::SetFlip()
{
	animRebelSoldier->SetFlip();
}
