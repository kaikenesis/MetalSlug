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
		RebelSoldier(POINT WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth);
		~RebelSoldier();
	
	private:
		EState currentState = Surprise;
		class AnimRebelSoldier* animRebelSoldier;

		int axisValue_x = 0;
		int axisValue_y = 0;
		
	private:
		bool IsInAir(POINT inPoint, float& outPosY);

		void UpdateCollision();
		void DoAction();
		void MoveTo();
		void Dead();
		void Encounter();

	public:
		void Update() override;
		bool PlayAnimation(HDC hdc) override;
		void SetInfo(POINT WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth) override;
		void SetFlip();
		void DebugChangeState();
	};
}



