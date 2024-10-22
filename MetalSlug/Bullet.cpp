#include "framework.h"
#include "Game.h"
#include "Collision.h"
#include "WeaponSFX.h"
#include "Geometry.h"
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
	if (IsHit() == true) bHit = true;

	if (GetWeaponSFX()->DrawBullet(hWnd, hdc, weaponType, bHit, bLookUp, BulletImgPos) == false)
		Hide();

	collision->SetInfo(BulletWorldPos.x, BulletWorldPos.y + collisionOffset.y, collision->GetWidth(), collision->GetHeight(), ERenderType::RWorld);
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

void metalSlug::Bullet::SetInfo(INT posX, INT posY, int inWidth, int inHeight, PointF inSpeed, POINT inCollisionOffset, EWeaponType inWeaponType)
{
	//TODO:
	RECT rtView = GetCamera()->GetCameraViewport();
	weaponType = inWeaponType;
	collisionOffset = inCollisionOffset;
	BulletWorldPos = { posX, posY };
	BulletLocalPos = { BulletWorldPos.x - rtView.left, BulletWorldPos.y - rtView.top };
	BulletImgPos = BulletWorldPos;
	speed = inSpeed;

	switch (weaponType)
	{
	case Pistol: SetPistolInfo(posX, posY, inWidth, inHeight, inSpeed, inCollisionOffset);
		break;
	}
	
}

void metalSlug::Bullet::UpdatePos()
{
	RECT rtView = GetCamera()->GetCameraViewport();
	BulletLocalPos.x = BulletWorldPos.x - rtView.left;
	BulletLocalPos.y = BulletWorldPos.y - rtView.top;
	BulletImgPos = BulletLocalPos;
}

void metalSlug::Bullet::SetPistolInfo(INT posX, INT posY, int inWidth, int inHeight, PointF inSpeed, POINT inCollisionOffset)
{
	collision->SetInfo(posX * ratio, posY * ratio, inWidth * ratio, inHeight * ratio, ERenderType::RWorld);
}

bool metalSlug::Bullet::IsHit()
{
	POINT point = { BulletLocalPos.x + speed.X,BulletLocalPos.y + speed.Y };
	std::vector<Collision*> geometryCollisions = GetGeometry()->GetGeometryCollisions();
	for (int i = 0; i < geometryCollisions.size(); i++)
	{
		if (geometryCollisions[i]->IsContain(point))
		{
			if(point.y != 0)
				BulletWorldPos.y = geometryCollisions[i]->GetWolrdPositionY(point.x);
			if(point.x != 0)
				BulletWorldPos.x = geometryCollisions[i]->GetWolrdPositionX(point.y);
			return true;
		}
	}

	return false;
}
