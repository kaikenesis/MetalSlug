#include "framework.h"
#include "Collision.h"
#include "WeaponSFX.h"
#include "Geometry.h"
#include "Enemy.h"
#include "Bullet.h"

metalSlug::Bullet::Bullet()
{
	collision = new Collision();
	weaponSFX = new WeaponSFX();
	ratio = GetGlobalRatio();
}

metalSlug::Bullet::~Bullet()
{
	delete collision;
}

void metalSlug::Bullet::Update(HWND hWnd, HDC hdc)
{
	if (bActive == false) return;

	UpdateImage(hWnd, hdc);
	UpdateCollision();
	UpdateLocation();
}

void metalSlug::Bullet::Hide()
{
	bActive = false;
	bHit = false;
	SetBulletCount(GetBulletCount() - 1);
}

void metalSlug::Bullet::Activate(INT posX, INT posY, PointF inSpeed, POINT inCollisionOffset, EWeaponType inWeaponType)
{
	RECT rtView = GetCamera()->GetCameraViewport();
	weaponType = inWeaponType;
	switch (weaponType)
	{
	case Pistol: SetPistolInfo(posX * ratio, posY * ratio, inCollisionOffset);
		break;
	}

	collisionOffset = inCollisionOffset;
	worldPos = { posX, posY };
	localPos = { worldPos.x - rtView.left, worldPos.y - rtView.top };
	imgPos.x = worldPos.x - collision->GetWidth() / 2;
	imgPos.y = worldPos.y - collision->GetHeight() / 2;
	speed.X *= inSpeed.X;
	speed.Y *= inSpeed.Y;

	bActive = true;
	SetBulletCount(GetBulletCount() + 1);
}

void metalSlug::Bullet::UpdateLocation()
{
	if (bHit == false)
	{
		worldPos.x += (int)speed.X;
		worldPos.y += (int)speed.Y;
		UpdatePos();
	}
}

void metalSlug::Bullet::UpdateImage(HWND hWnd, HDC hdc)
{
	bool bLookUp = false;
	if (speed.Y != 0) bLookUp = true;
	if (bHit == false && CheckHit() == true) bHit = true;

	if (weaponSFX->DrawBullet(hWnd, hdc, weaponType, bHit, bLookUp, imgPos) == false)
		Hide();
}

void metalSlug::Bullet::UpdateCollision()
{
	int w = collision->GetWidth();
	int h = collision->GetHeight();
	collision->SetInfo(worldPos.x - w / 2, worldPos.y + collisionOffset.y - h / 2, w, h, ERenderType::RWorld);
}

void metalSlug::Bullet::UpdatePos()
{
	RECT rtView = GetCamera()->GetCameraViewport();
	localPos.x = worldPos.x - rtView.left;
	localPos.y = worldPos.y - rtView.top;
	imgPos.x = worldPos.x - collision->GetWidth() / 2;
	imgPos.y = worldPos.y - collision->GetHeight() / 2;
}

void metalSlug::Bullet::SetPistolInfo(INT posX, INT posY, POINT inCollisionOffset)
{
	POINT size = { 10 * ratio,10 * ratio };
	collision->SetInfo(posX - size.x / 2, posY - size.y / 2, size.x, size.y, ERenderType::RWorld);
	power = 1;
	speed.X = 20.0f;
	speed.Y = 20.0f;
	weaponSFX->ResetFrame();
}

bool metalSlug::Bullet::CheckHit()
{
	POINT point = { worldPos.x + speed.X,worldPos.y + speed.Y };
	std::vector<Collision*> geometryCollisions = GetGeometry()->GetGeometryCollisions();
	for (int i = 0; i < geometryCollisions.size(); i++)
	{
		if (geometryCollisions[i]->IsContain(point))
		{
			if(speed.Y != 0)
				worldPos.y = geometryCollisions[i]->GetWolrdPositionY(point.x, point.y);
			if(speed.X != 0)
				worldPos.x = geometryCollisions[i]->GetWolrdPositionX(point.x, point.y);
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
				worldPos.y = enemys[i]->GetCollision()->GetWolrdPositionY(point.x, point.y);
			if (speed.X != 0)
				worldPos.x = enemys[i]->GetCollision()->GetWolrdPositionX(point.x, point.y);
			UpdatePos();

			enemys[i]->TakeDamage(power);
			return true;
		}
	}

	return false;
}
