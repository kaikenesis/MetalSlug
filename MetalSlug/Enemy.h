#pragma once

namespace metalSlug
{
	class Enemy
	{
	public:
		Enemy();
		Enemy(POINT WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth);
		~Enemy();

	protected:
		bool bInvincible = false;
		bool bActive = false;
		bool bHit = false;

		float ratio;
		float maxHealth;
		float currentHealth;

		class Collision* collision;
		POINT worldPos;
		POINT localPos;
		POINT imgPos;
		PointF speed;

	protected:
		void UpdateWorldPos(POINT point);
		void UpdatePos();

	public:
		bool IsActive() { return bActive; }
		bool IsInvincible() { return bInvincible; }
		bool IsHit() { return bHit; }
		float GetCurrentHealth() { return currentHealth; }
		POINT GetWorldPos() { return worldPos; }
		POINT GetLocalPos() { return localPos; }
		POINT GetImgPos() { return imgPos; }
		class Collision* GetCollision() { return collision; }

		void SetActivate(bool value) { bActive = value; }
		void SetInvincible(bool value) { bInvincible = value; }
		void SetHit(bool value) { bHit = value; }
		void SetCurrentHealth(float value) { currentHealth = value; }

		virtual void Update();
		virtual bool PlayAnimation(HDC hdc);
		virtual void SetInfo(POINT WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth);

		void InitHealth();
	};
}
