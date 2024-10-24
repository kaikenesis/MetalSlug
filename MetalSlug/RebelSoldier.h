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
		EState currentState;
		class AnimRebelSoldier* animRebelSoldier;
		
	private:
		void DoAction();
		void MoveTo();
		void Dead();
		void Encounter();

	public:
		void Update() override;
		bool PlayAnimation(HDC hdc) override;
		void SetInfo(POINT WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth) override;
		void SetFlip();
	};
}



