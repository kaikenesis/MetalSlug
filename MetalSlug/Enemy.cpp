#include "framework.h"
#include "Collision.h"
#include "Enemy.h"

metalSlug::Enemy::Enemy()
{
	worldPos = { 0,0 };
	UpdatePos();
	Rect rt = { worldPos.x,worldPos.y,10,20 };
	collision = new Collision(rt, ERenderType::RWorld);
}

metalSlug::Enemy::Enemy(POINT WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth)
{
	UpdateWorldPos(WorldPos);
	speed = Speed;
	maxHealth = MaxHealth;
	InitHealth();
	collision = new Collision(CollisionRect, ERenderType::RWorld);
}

metalSlug::Enemy::~Enemy()
{
	delete collision;
}

void metalSlug::Enemy::UpdateWorldPos(POINT point)
{
	worldPos = point;
	UpdatePos();
	UpdateCollision();
}

void metalSlug::Enemy::UpdatePos()
{
	RECT rtView = GetCamera()->GetCameraViewport();
	localPos.x = worldPos.x - rtView.left;
	localPos.y = worldPos.y - rtView.top;
	imgPos.x = localPos.x;
	imgPos.y = localPos.y;
}

void metalSlug::Enemy::UpdateCollision()
{
	int w = collision->GetWidth();
	int h = collision->GetHeight();
	collision->SetInfo(worldPos.x, worldPos.y, w, h, ERenderType::RWorld);
}

bool metalSlug::Enemy::PlayAnimation(HDC hdc)
{
	return false;
}

void metalSlug::Enemy::SetInfo(POINT WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth)
{
}

void metalSlug::Enemy::InitHealth()
{
	currentHealth = maxHealth;
}
