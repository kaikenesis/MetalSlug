#pragma once

namespace metalSlug
{
#define JUMP_HEIGHT 15
	class Enemy
	{
	public:
		Enemy();
		Enemy(PointF WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth);
		~Enemy();

	protected:
		bool bInvincible = false;
		bool bActive = false;
		bool bDead = false;

		float ratio;
		float maxHealth;
		float currentHealth;


		class Collision* collision;
		PointF worldPos;
		PointF localPos;
		PointF imgPos;
		PointF speed;
		float jumpValue_y = JUMP_HEIGHT;
		float gravity = 0.98f;

	protected:
		void UpdateWorldPos(PointF point);
		void UpdatePos();
		void UpdateCollision();

	public:
		bool IsActive() { return bActive; }
		bool IsInvincible() { return bInvincible; }
		bool IsDead() { return bDead; }
		bool IsAlive() { return currentHealth > 0; }
		float GetCurrentHealth() { return currentHealth; }
		PointF GetWorldPos() { return worldPos; }
		PointF GetLocalPos() { return localPos; }
		PointF GetImgPos() { return imgPos; }
		class Collision* GetCollision() { return collision; }

		void SetActivate(bool value) { bActive = value; }
		void SetInvincible(bool value) { bInvincible = value; }
		void SetCurrentHealth(float value) { currentHealth = value; }

		virtual void Update() = 0;
		virtual bool PlayAnimation(HDC hdc);
		virtual void SetInfo(PointF WorldPos, Rect CollisionRect, PointF Speed, float MaxHealth);
		virtual void SetFlip();
		virtual void TakeDamage(float value);

		void InitHealth();
	};
}
