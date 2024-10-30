#include "framework.h"
#include "SoundRes.h"
#include "Collision.h"
#include "Enemy.h"

metalSlug::Enemy::Enemy()
{
	ratio = GetGlobalRatio();
	Rect rt = { (INT)worldPos.X,(INT)worldPos.Y,10,20 };
	collision = new Collision(rt, ERenderType::RWorld);
	worldPos = { 0,0 };
	UpdatePos();
}

metalSlug::Enemy::Enemy(PointF WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth)
{
	collision = new Collision(CollisionRect, ERenderType::RWorld);
	UpdateWorldPos(WorldPos);
	speed = Speed;
	maxHealth = MaxHealth;
	InitHealth();
}

metalSlug::Enemy::~Enemy()
{
	delete collision;
}

void metalSlug::Enemy::UpdateWorldPos(PointF point)
{
	worldPos = point;
	UpdatePos();
	UpdateCollision();
}

void metalSlug::Enemy::UpdatePos()
{
	RECT rtView = GetCamera()->GetCameraViewport();
	localPos.X = worldPos.X - rtView.left;
	localPos.Y = worldPos.Y - rtView.top;
	imgPos.X = worldPos.X - collision->GetWidth()/2;
	imgPos.Y = worldPos.Y - collision->GetHeight()/2;
}

void metalSlug::Enemy::UpdateCollision()
{
	int w = collision->GetWidth();
	int h = collision->GetHeight();
	collision->SetInfo(worldPos.X - w / 2, worldPos.Y - h / 2, w, h, ERenderType::RWorld);
}


bool metalSlug::Enemy::PlayAnimation(HDC hdc)
{
	return false;
}

void metalSlug::Enemy::SetInfo(PointF WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth)
{
}

void metalSlug::Enemy::SetFlip()
{
}

void metalSlug::Enemy::TakeDamage(float value)
{
	currentHealth -= value;
}

void metalSlug::Enemy::InitHealth()
{
	currentHealth = maxHealth;
}
