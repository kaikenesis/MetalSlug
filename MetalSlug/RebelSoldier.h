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
			Action,
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
		
	private:
		bool IsInAir(POINT inPoint, float& outPosY);
		bool IsInScreen(PointF point);

		void UpdateCollision();
		void DoAction();
		void MoveTo();
		void Dead();
		void Encounter();

		void UpdateLocation();
		void UpdatePositionX(int posX, int posY);
		void UpdatePositionY(int posX, int posY);

	public:
		void Update() override;
		bool PlayAnimation(HDC hdc) override;
		void SetInfo(PointF WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth) override;
		void SetFlip() override;
		void DebugChangeState();

		void Hide();
	};
}



