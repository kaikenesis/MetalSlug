#include "framework.h"
#include "Collision.h"
#include "WeaponSFX.h"
#include "Geometry.h"
#include "Enemy.h"
#include "Bullet.h"

metalSlug::Bullet::Bullet()
{
	collision = new Collision();
	ratio = GetGlobalRatio();
}

metalSlug::Bullet::Bullet(INT posX, INT posY, int inWidth, int inHeight, ERenderType inType)
{
	collision = new Collision(posX, posY, inWidth, inHeight, inType);
	ratio = GetGlobalRatio();
}

metalSlug::Bullet::Bullet(Rect inRect, ERenderType inType)
{
	collision = new Collision(inRect, inType);
	ratio = GetGlobalRatio();
}

metalSlug::Bullet::~Bullet()
{
	delete collision;
}

void metalSlug::Bullet::Update(HWND hWnd, HDC hdc)
{
	if (bActive == false) return;

	bool bLookUp = false;
	if (speed.Y != 0) bLookUp = true;
	if (bHit == false && CheckHit() == true) bHit = true;

	if (GetWeaponSFX()->DrawBullet(hWnd, hdc, weaponType, bHit, bLookUp, BulletImgPos) == false)
		Hide();

	int w = collision->GetWidth();
	int h = collision->GetHeight();
	collision->SetInfo(BulletWorldPos.x - w / 2, BulletWorldPos.y + collisionOffset.y - h / 2, w, h, ERenderType::RWorld);
	if (bHit == false)
	{
		BulletWorldPos.x += (int)speed.X;
		BulletWorldPos.y += (int)speed.Y;
		UpdatePos();
	}
}

void metalSlug::Bullet::Hide()
{
	bActive = false;
	bHit = false;
	SetBulletCount(GetBulletCount() - 1);
}

void metalSlug::Bullet::SetInfo(INT posX, INT posY, PointF inSpeed, POINT inCollisionOffset, EWeaponType inWeaponType)
{
	//TODO:
	RECT rtView = GetCamera()->GetCameraViewport();
	weaponType = inWeaponType;
	switch (weaponType)
	{
	case Pistol: SetPistolInfo(posX * ratio, posY * ratio, inCollisionOffset);
		break;
	}

	collisionOffset = inCollisionOffset;
	BulletWorldPos = { posX, posY };
	BulletLocalPos = { BulletWorldPos.x - rtView.left, BulletWorldPos.y - rtView.top };
	BulletImgPos.x = BulletWorldPos.x - collision->GetWidth() / 2;
	BulletImgPos.y = BulletWorldPos.y - collision->GetHeight() / 2;
	speed.X *= inSpeed.X;
	speed.Y *= inSpeed.Y;

	SetBulletCount(GetBulletCount() + 1);
}

void metalSlug::Bullet::UpdatePos()
{
	RECT rtView = GetCamera()->GetCameraViewport();
	BulletLocalPos.x = BulletWorldPos.x - rtView.left;
	BulletLocalPos.y = BulletWorldPos.y - rtView.top;
	BulletImgPos.x = BulletWorldPos.x - collision->GetWidth() / 2;
	BulletImgPos.y = BulletWorldPos.y - collision->GetHeight() / 2;
}

void metalSlug::Bullet::SetPistolInfo(INT posX, INT posY, POINT inCollisionOffset)
{
	POINT size = { 10 * ratio,10 * ratio };
	collision->SetInfo(posX - size.x / 2, posY - size.y / 2, size.x, size.y, ERenderType::RWorld);
	power = 1;
	speed.X = 30.0f;
	speed.Y = 30.0f;
}

bool metalSlug::Bullet::CheckHit()
{
	POINT point = { BulletWorldPos.x + speed.X,BulletWorldPos.y + speed.Y };
	std::vector<Collision*> geometryCollisions = GetGeometry()->GetGeometryCollisions();
	for (int i = 0; i < geometryCollisions.size(); i++)
	{
		if (geometryCollisions[i]->IsContain(point))
		{
			if(speed.Y != 0)
				BulletWorldPos.y = geometryCollisions[i]->GetWolrdPositionY(point.x, point.y);
			if(speed.X != 0)
				BulletWorldPos.x = geometryCollisions[i]->GetWolrdPositionX(point.x, point.y);
			UpdatePos();
			return true;
		}
	}

	std::vector<Enemy*> enemys = GetEnemys();
	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i]->IsDead() == false && enemys[i]->GetCollision()->IsContain(point))
		{
			if (speed.Y != 0)
				BulletWorldPos.y = enemys[i]->GetCollision()->GetWolrdPositionY(point.x, point.y);
			if (speed.X != 0)
				BulletWorldPos.x = enemys[i]->GetCollision()->GetWolrdPositionX(point.x, point.y);
			UpdatePos();

			enemys[i]->TakeDamage(power);
			return true;
		}
	}

	return false;
}
