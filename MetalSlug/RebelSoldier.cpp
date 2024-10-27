#include "framework.h"
#include "Collision.h"
#include "AnimRebelSoldier.h"
#include "Geometry.h"
#include "RebelSoldier.h"

metalSlug::RebelSoldier::RebelSoldier()
	:Enemy()
{
	animRebelSoldier = new AnimRebelSoldier();
	
}

metalSlug::RebelSoldier::RebelSoldier(PointF WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth)
	:Enemy(WorldPos, CollisionRect, Speed, MaxHealth)
{
	animRebelSoldier = new AnimRebelSoldier();
}

metalSlug::RebelSoldier::~RebelSoldier()
{
	delete animRebelSoldier;
}

bool metalSlug::RebelSoldier::IsInAir(POINT inPoint, float& outPosY)
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

bool metalSlug::RebelSoldier::IsInScreen(PointF point)
{
	RECT cameraView = GetCamera()->GetCameraViewport();
	if (cameraView.left > worldPos.X + collision->GetWidth() || cameraView.right < worldPos.X - collision->GetWidth()) return false;
	if (cameraView.top > worldPos.Y + collision->GetHeight() || cameraView.bottom < worldPos.Y - collision->GetHeight()) return false;

	return true;
}

void metalSlug::RebelSoldier::UpdateCollision()
{
	int w = collision->GetWidth();
	int h = collision->GetHeight();
	collision->SetInfo(worldPos.X - w / 2, worldPos.Y - h / 2, w, h, ERenderType::RWorld);

	
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

void metalSlug::RebelSoldier::UpdateLocation()
{
	if (IsInScreen(worldPos) == false)
	{
		Hide();
		return;
	}

	if (IsAlive() == false)
	{
		bDead = true;
		currentState = Death;
		if (animRebelSoldier->GetBlinkCount() > 10)
			Hide();
	}

	UpdatePositionX(worldPos.X, worldPos.Y);
	UpdatePositionY(worldPos.X, worldPos.Y);

	UpdatePos();
}

void metalSlug::RebelSoldier::UpdatePositionX(int posX, int posY)
{
	if (currentState == Run)
	{
		if (animRebelSoldier->IsFlipX() == true)
			worldPos.X += speed.X * ratio;
		else
			worldPos.X -= speed.X * ratio;
	}
}

void metalSlug::RebelSoldier::UpdatePositionY(int posX, int posY)
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
				worldPos.Y = (collisions[i]->GetWolrdPositionY(point.x, point.y) - (collision->GetHeight() / 2 + 1));
			}
		}
	}
	else
	{
		POINT point = { posX,posY + collision->GetHeight() / 2 - jumpValue_y };
		float posY = 0.0f;
		if (IsInAir(point, posY) == true)
		{
			worldPos.Y -= jumpValue_y;
		}
		else
		{
			worldPos.Y = posY - (collision->GetHeight() / 2 + 1);
			bJumping = false;
		}

		if (jumpValue_y > -(JUMP_HEIGHT * ratio))
			jumpValue_y -= gravity;
	}
}

void metalSlug::RebelSoldier::Update()
{
	UpdateLocation();
	UpdateCollision();
}

bool metalSlug::RebelSoldier::PlayAnimation(HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	switch (currentState)
	{
	case Idle:
		animRebelSoldier->PlayIdle(hdc, hMemDC, hOldBitmap, imgPos);
		break;
	case Run:
		animRebelSoldier->PlayRun(hdc, hMemDC, hOldBitmap, imgPos);
		break;
	case Action:
		animRebelSoldier->PlayRollingBomb(hdc, hMemDC, hOldBitmap, imgPos);
		if (animRebelSoldier->IsPlayRollingBomb() == false)
			currentState = Idle;
		break;
	case Death:
		animRebelSoldier->PlayDeath(hdc, hMemDC, hOldBitmap, imgPos);
		break;
	case Surprise:
		animRebelSoldier->PlaySurprise(hdc, hMemDC, hOldBitmap, imgPos);
		if (animRebelSoldier->IsPlaySurprise() == false)
			currentState = Idle;
		break;

	default: break;
	}

	return false;
}

void metalSlug::RebelSoldier::SetInfo(PointF WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth)
{
	collision->SetInfo(CollisionRect.X, CollisionRect.Y, CollisionRect.Width, CollisionRect.Height, ERenderType::RWorld);
	UpdateWorldPos(WorldPos);
	speed = Speed;
	maxHealth = MaxHealth;
	InitHealth();
	currentState = Idle;
	bDead = false;
	jumpValue_y = 0.0f;
	bJumping = false;
	animRebelSoldier->ResetBlinkCount();
	animRebelSoldier->ResetFrame();

	SetEnemyCount(GetEnemyCount() + 1);
}

void metalSlug::RebelSoldier::SetFlip()
{
	animRebelSoldier->SetFlipX();
}

void metalSlug::RebelSoldier::DebugChangeState()
{
	currentState = (EState)((currentState + 1) % 5);

	animRebelSoldier->ResetFrame();
	switch (currentState)
	{
	case Surprise:
		animRebelSoldier->PlayStartSurprise();
		break;
	case Action:
		animRebelSoldier->PlayStartRollingBomb();
		break;
	}
}

void metalSlug::RebelSoldier::Hide()
{
	bActive = false;
	SetEnemyCount(GetEnemyCount() - 1);
}
