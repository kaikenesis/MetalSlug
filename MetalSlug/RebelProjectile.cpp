#include "framework.h"
#include "Collision.h"
#include "Geometry.h"
#include "WeaponSFX.h"
#include "Player.h"
#include "RebelProjectile.h"

metalSlug::RebelProjectile::RebelProjectile()
{
	collision = new Collision();
	weaponSFX = new WeaponSFX();
	ratio = GetGlobalRatio();
}

metalSlug::RebelProjectile::~RebelProjectile()
{
	delete weaponSFX;
	delete collision;
}

void metalSlug::RebelProjectile::Update(HWND hWnd, HDC hdc)
{
	if (bActive == false) return;

	UpdateImage(hWnd, hdc);

	if (bHit == true) return;
	UpdateCollision();
	UpdateLocation();
}

void metalSlug::RebelProjectile::Hide()
{
	bActive = false;
	bHit = false;
	SetEnemyProjectileCount(GetEnemyProjectileCount() - 1);
}

void metalSlug::RebelProjectile::Activate(INT posX, INT posY, PointF inSpeed, POINT inCollisionOffset, EWeaponType inWeaponType)
{
	RECT rtView = GetCamera()->GetCameraViewport();
	weaponType = inWeaponType;
	switch (weaponType)
	{
	case EWeaponType::RebelBomb: SetRebelBombInfo(posX * ratio, posY * ratio, inCollisionOffset);
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
	SetEnemyProjectileCount(GetEnemyProjectileCount() + 1);
}

void metalSlug::RebelProjectile::UpdateLocation()
{
	UpdatePositionX(worldPos.x, worldPos.y);
	UpdatePositionY(worldPos.x, worldPos.y);
	UpdatePos();
}

void metalSlug::RebelProjectile::UpdateImage(HWND hWnd, HDC hdc)
{
	bool bLookUp = false;
	if (speed.Y != 0) bLookUp = true;
	if (bHit == false && CheckHit() == true) bHit = true;

	if (weaponSFX->DrawBullet(hWnd, hdc, weaponType, bHit, bLookUp, imgPos) == false)
		Hide();
}

void metalSlug::RebelProjectile::UpdateCollision()
{
	int w = collision->GetWidth();
	int h = collision->GetHeight();
	collision->SetInfo(worldPos.x - w / 2, worldPos.y + collisionOffset.y - h / 2, w, h, ERenderType::RWorld);
}

void metalSlug::RebelProjectile::UpdatePos()
{
	RECT rtView = GetCamera()->GetCameraViewport();
	localPos.x = worldPos.x - rtView.left;
	localPos.y = worldPos.y - rtView.top;
	imgPos.x = worldPos.x - collision->GetWidth() / 2;
	imgPos.y = worldPos.y - collision->GetHeight() / 2;
}

void metalSlug::RebelProjectile::UpdatePositionX(int posX, int posY)
{
	if (bJumping == true) return;

	worldPos.x += speed.X * ratio;
}

void metalSlug::RebelProjectile::UpdatePositionY(int posX, int posY)
{
	if (bJumping == false)
	{
		POINT point = { posX,posY + collision->GetHeight() / 2 - jumpValue_y };
		float posY = 0.0f;
		if (IsInAir(point, posY) == false)
		{
			std::vector<Collision*> collisions = GetGeometry()->GetGeometryCollisions();
			for (int i = 0; i < collisions.size(); i++)
			{
				if (collisions[i]->IsActive() == false) continue;
				if (collisions[i]->IsInRange(point) == false) continue;
				worldPos.y = (collisions[i]->GetWolrdPositionY(point.x, point.y) - (collision->GetHeight() / 2 + 1));
			}
		}
	}
	else
	{
		POINT point = { posX,posY + collision->GetHeight() / 2 - jumpValue_y };
		float posY = 0.0f;
		if (IsInAir(point, posY) == true)
		{
			worldPos.y -= jumpValue_y;
		}
		else
		{
			worldPos.y = posY - (collision->GetHeight() / 2 + 1);
			bJumping = false;
		}

		if (jumpValue_y > -(JUMP_HEIGHT * ratio))
			jumpValue_y -= gravity;
	}
}

void metalSlug::RebelProjectile::SetRebelBombInfo(INT posX, INT posY, POINT inCollisionOffset)
{
	POINT size = { 15 * ratio,15 * ratio };
	collision->SetInfo(posX - size.x / 2, posY - size.y / 2, size.x, size.y, ERenderType::RWorld);
	power = 2;
	speed.X = 1.0f;
	weaponSFX->ResetFrame();
}

bool metalSlug::RebelProjectile::CheckHit()
{
	std::vector<Collision*> collisions = GetGeometry()->GetGeometryCollisions();
	Rect collisionRect = { collision->GetWorldRect().X + (INT)speed.X,collision->GetWorldRect().Y,
		collision->GetWorldRect().Width,collision->GetWorldRect().Height };

	for (int i = 0; i < collisions.size(); i++)
	{
		if (collisions[i]->IsActive() == false) continue;
		if (collisions[i]->IsContain(collisionRect) == true)
		{
			if (worldPos.x < collisions[i]->GetWorldRect().GetLeft())
				worldPos.x = collisions[i]->GetWorldRect().GetLeft() - collision->GetWidth() / 2;
			else
				worldPos.x = collisions[i]->GetWorldRect().GetRight() + collision->GetWidth() / 2;
			UpdatePos();
			return true;
		}
	}

	POINT point = { worldPos.x + speed.X,worldPos.y + speed.Y };
	Collision* playerCollision = GetPlayer()->GetCollider();
	if (playerCollision->IsContain(point))
	{
		if (speed.Y != 0)
			worldPos.y = playerCollision->GetWolrdPositionY(point.x, point.y);
		if (speed.X != 0)
			worldPos.x = playerCollision->GetWolrdPositionX(point.x, point.y);
		UpdatePos();
		GetPlayer()->TakeDamage();
		return true;
	}

	return false;
}

bool metalSlug::RebelProjectile::IsInAir(POINT inPoint, float& outPosY)
{
	std::vector<Collision*> collisions = GetGeometry()->GetGeometryCollisions();
	for (int i = 0; i < collisions.size(); i++)
	{
		outPosY = collisions[i]->GetWolrdPositionY(inPoint.x, inPoint.y);
		if (collisions[i]->IsContain(inPoint) == true) return false;
		if (collisions[i]->IsContain(collision->GetLocalRect()) == true) return false;
	}

	if (bJumping == false)
	{
		jumpValue_y = gravity;
		bJumping = true;
	}

	return true;
}

bool metalSlug::RebelProjectile::IsInScreen(PointF point)
{
	RECT cameraView = GetCamera()->GetCameraViewport();
	if (cameraView.left > worldPos.x + collision->GetWidth() || cameraView.right < worldPos.x - collision->GetWidth()) return false;
	if (cameraView.top > worldPos.y + collision->GetHeight() || cameraView.bottom < worldPos.y - collision->GetHeight()) return false;

	return true;
}
