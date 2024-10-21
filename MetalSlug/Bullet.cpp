#include "framework.h"
#include "Game.h"
#include "Collision.h"
#include "WeaponSFX.h"
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
	
	if (GetWeaponSFX()->DrawBullet(hWnd, hdc, weaponType, bHit, Bulletpos) == false)
		Hide();

	collision->SetInfo(Bulletpos.x, Bulletpos.y + collisionOffset.y, collision->GetWidth(), collision->GetHeight(), ERenderType::RWorld);
	Bulletpos.x += (int)speed.X;
	Bulletpos.y += (int)speed.Y;
}

void metalSlug::Bullet::Hide()
{
	bActive = false;
	bHit = false;
	SetBulletCount(GetBulletCount() - 1);
}

void metalSlug::Bullet::SetInfo(INT posX, INT posY, int inWidth, int inHeight, PointF inSpeed, POINT inCollisionOffset, EWeaponType inWeaponType)
{
	weaponType = inWeaponType;
	collisionOffset = inCollisionOffset;
	Bulletpos = { posX, posY };
	speed = inSpeed;

	switch (weaponType)
	{
	case Pistol: SetPistolInfo(posX, posY, inWidth, inHeight, inSpeed, inCollisionOffset);
		break;
	}
	
}

void metalSlug::Bullet::SetPistolInfo(INT posX, INT posY, int inWidth, int inHeight, PointF inSpeed, POINT inCollisionOffset)
{
	collision->SetInfo(posX * ratio, posY * ratio, inWidth * ratio, inHeight * ratio, ERenderType::RWorld);
}