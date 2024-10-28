#pragma once

#include "Enemy.h"

namespace metalSlug
{
	class RebelSoldier : public Enemy
	{
		enum EState
		{
			Idle,
			Run,
			RollingBomb,
			Death,
			Surprise,
		};

	public:
		RebelSoldier();
		RebelSoldier(PointF WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth);
		~RebelSoldier();
	
	private:
		EState currentState = Idle;
		class AnimRebelSoldier* animRebelSoldier;

		int axisValue_x = 0;
		int axisValue_y = 0;
		bool bJumping = false;
		PointF movePos = { 0,0 };
		
	private:

		bool IsInAir(POINT inPoint, float& outPosY);
		bool IsInScreen(PointF point);
		bool IsTargetLeft();
		bool IsAroundMovePos();

		PointF CheckDistanceToPlayer();
		PointF RandomPos();

		void DoAction();
		void MoveTo();
		void Dead();
		void Encounter();

		void UpdateLocation();
		void UpdatePositionX(int posX, int posY);
		void UpdatePositionY(int posX, int posY);
		void UpdateCollision();
		void UpdateState();

		void ActivateProjectile();
		void SetInfoProjectile(class RebelProjectile* object);
		void ChangeState(EState type);

	public:
		void Update() override;
		void UpdateProjectiles(HWND hWnd, HDC hdc);
		bool PlayAnimation(HDC hdc) override;
		void SetInfo(PointF WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth) override;
		void SetFlip() override;

		void DebugChangeState();

		void Hide();
	};
}



