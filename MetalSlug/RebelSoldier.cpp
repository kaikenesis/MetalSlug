#include "framework.h"
#include "Collision.h"
#include "AnimRebelSoldier.h"
#include "Geometry.h"
#include "RebelProjectile.h"
#include "Player.h"
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

bool metalSlug::RebelSoldier::IsTargetLeft()
{
	return GetPlayer()->GetWorldPlayerPos().X <= worldPos.X;
}

bool metalSlug::RebelSoldier::IsAroundMovePos()
{
	float offset = 5.0f;
	if (worldPos.X > movePos.X - offset && worldPos.X < movePos.X + offset) return true;
	return false;
}

PointF metalSlug::RebelSoldier::CheckDistanceToPlayer()
{
	float x = worldPos.X - GetPlayer()->GetWorldPlayerPos().X;
	float y = worldPos.Y - GetPlayer()->GetWorldPlayerPos().Y;

	x = sqrt(x * x);
	y = sqrt(y * y);

	PointF res = { x,y };

	return res;
}

PointF metalSlug::RebelSoldier::RandomPos()
{
	RECT rt = GetCamera()->GetCameraViewport();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distX(rt.left, rt.right);
	std::uniform_int_distribution<int> distY(rt.top, rt.bottom);
	
	PointF res = { (float)distX(gen),(float)distY(gen) };

	return res;
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
	if (currentState == Run && IsAroundMovePos() == false)
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

void metalSlug::RebelSoldier::UpdateCollision()
{
	int w = collision->GetWidth();
	int h = collision->GetHeight();
	collision->SetInfo(worldPos.X - w / 2, worldPos.Y - h / 2, w, h, ERenderType::RWorld);
}

void metalSlug::RebelSoldier::UpdateState()
{
	PointF distance = CheckDistanceToPlayer();
	switch (currentState)
	{
	case Idle:
	{
		if (distance.X <= 400)
		{
			if (IsTargetLeft()) animRebelSoldier->SetFlipX(false);
			else animRebelSoldier->SetFlipX(true);

			ChangeState(Surprise);
		}
	}
		break;
	case Run:
	{
		if (IsAroundMovePos() == true)
		{
			if (IsTargetLeft()) animRebelSoldier->SetFlipX(false);
			else animRebelSoldier->SetFlipX(true);

			if (IsCanSpawnProjectile() == true)
			{
				ChangeState(RollingBomb);
			}
			else
			{
				movePos = RandomPos();

				if (movePos.X <= worldPos.X) animRebelSoldier->SetFlipX(false);
				else animRebelSoldier->SetFlipX(true);

				ChangeState(Run);
			}
		}
	}
		break;
	case Surprise:
	{
		//sound->PlayingEnemyScream();
		if (animRebelSoldier->IsPlaySurprise() == false)
		{
			if (IsTargetLeft()) animRebelSoldier->SetFlipX(false);
			else animRebelSoldier->SetFlipX(true);

			ChangeState(RollingBomb);
		}
	}
		break;
	case RollingBomb:
	{
		if (animRebelSoldier->IsPlayRollingBomb() == false)
		{
			ActivateProjectile();
			movePos = RandomPos();

			if(movePos.X <= worldPos.X) animRebelSoldier->SetFlipX(false);
			else animRebelSoldier->SetFlipX(true);

			ChangeState(Run);
		}
	}
		break;
	default:
		break;
	}
}

void metalSlug::RebelSoldier::ActivateProjectile()
{
	std::vector<RebelProjectile*> projectiles = GetEnemyProjectiles();
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->IsActive() == false)
		{
			SetInfoProjectile(projectiles[i]);
			break;
		}
	}
}

void metalSlug::RebelSoldier::SetInfoProjectile(RebelProjectile* object)
{
	PointF axis;
	POINT collisionOffset = { 0,0 };

	switch (currentState)
	{
	case RollingBomb:
		if(animRebelSoldier->IsFlipX() == true) axis = { 1.0f,0.0f };
		else axis = { -1.0f,0.0f };
		
		object->Activate(worldPos.X, worldPos.Y, axis, collisionOffset, EWeaponType::RebelBomb);
		break;
	default:
		break;
	}
}

void metalSlug::RebelSoldier::ChangeState(EState type)
{
	currentState = type;

	animRebelSoldier->ResetFrame();
	switch (currentState)
	{
	case Surprise:
		animRebelSoldier->PlayStartSurprise();
		break;
	case RollingBomb:
		animRebelSoldier->PlayStartRollingBomb();
		break;
	}
}

void metalSlug::RebelSoldier::Update()
{
	UpdateLocation();
	UpdateCollision();
	UpdateState();
}

void metalSlug::RebelSoldier::UpdateProjectiles(HWND hWnd, HDC hdc)
{
	std::vector<RebelProjectile*> projectiles = GetEnemyProjectiles();
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->IsActive() == true)
			projectiles[i]->Update(hWnd, hdc);
	}
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
	case RollingBomb:
		animRebelSoldier->PlayRollingBomb(hdc, hMemDC, hOldBitmap, imgPos);
		break;
	case Death:
		animRebelSoldier->PlayDeath(hdc, hMemDC, hOldBitmap, imgPos);
		break;
	case Surprise:
		animRebelSoldier->PlaySurprise(hdc, hMemDC, hOldBitmap, imgPos);
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
	animRebelSoldier->SetFlipX(!animRebelSoldier->IsFlipX());
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
	case RollingBomb:
		animRebelSoldier->PlayStartRollingBomb();
		break;
	}
}

void metalSlug::RebelSoldier::Hide()
{
	bActive = false;
	SetEnemyCount(GetEnemyCount() - 1);
}
