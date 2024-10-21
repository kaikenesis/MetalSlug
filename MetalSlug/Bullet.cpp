#include "framework.h"
#include "Game.h"
#include "Collision.h"
#include "WeaponSFX.h"
#include "Bullet.h"

metalSlug::Bullet::Bullet()
{
	collider = new Collision();
}

metalSlug::Bullet::Bullet(INT posX, INT posY, int inWidth, int inHeight, ERenderType inType)
{
	collider = new Collision(posX, posY, inWidth, inHeight, inType);
}

metalSlug::Bullet::Bullet(Rect inRect, ERenderType inType)
{
	collider = new Collision(inRect, inType);
}

metalSlug::Bullet::~Bullet()
{
	delete collider;
}

void metalSlug::Bullet::Update(HWND hWnd, HDC hdc)
{
	if (bActive == false) return;
	
	int destX = Bulletpos.x;
	int destY = Bulletpos.y;
	if (GetWeaponSFX()->DrawBitmap(hWnd, hdc, weaponType, bHit, destX, destY) == false)
		Hide();

	collider->SetInfo(destX - collider->GetWidth()/2, destY - collider->GetHeight()/2, collider->GetWidth(), collider->GetHeight(), ERenderType::RWorld);
	Bulletpos.x += speedX;
	Bulletpos.y += speedY;
}

void metalSlug::Bullet::Hide()
{
	bActive = false;
	bHit = false;
}

void metalSlug::Bullet::SetInfo(INT posX, INT posY, int inWidth, int inHeight, EWeaponType inWeaponType, float inSpeedX, float inSpeedY)
{
	Bulletpos = { posX, posY };
	collider->SetInfo(posX - inWidth / 2, posY - inHeight / 2, inWidth, inHeight, ERenderType::RWorld);
	weaponType = inWeaponType;
	speedX = inSpeedX;
	speedY = inSpeedY;
}

