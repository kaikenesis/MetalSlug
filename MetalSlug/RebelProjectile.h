#pragma once

namespace metalSlug
{
	class RebelProjectile
	{
	public:
		RebelProjectile();
		~RebelProjectile();

	private:
#define JUMP_HEIGHT 14

		class Collision* collision;
		class WeaponSFX* weaponSFX;
		EWeaponType weaponType;
		POINT worldPos; // ¸Ê»óÀÇ ÃÑ¾Ë À§Ä¡
		POINT localPos; // È­¸é»óÀÇ ÃÑ¾Ë À§Ä¡
		POINT imgPos;
		POINT collisionOffset;

		bool bActive = false;
		bool bHit = false;
		bool bJumping = false;
		PointF speed;
		float ratio;
		float power;
		float jumpValue_y = JUMP_HEIGHT;
		float gravity = 0.98f;

	public:
		bool IsActive() { return bActive; }
		bool IsHit() { return bHit; }

		void Update(HWND hWnd, HDC hdc);
		void Hide();

		class Collision* const GetCollision() { return collision; }

		void Activate(INT posX, INT posY, PointF inSpeed, POINT inCollisionOffset, EWeaponType inWeaponType = EWeaponType::Pistol);

	private:
		void UpdateLocation();
		void UpdateImage(HWND hWnd, HDC hdc);
		void UpdateCollision();
		void UpdatePos();
		void UpdatePositionX(int posX, int posY);
		void UpdatePositionY(int posX, int posY);

		void SetRebelBombInfo(INT posX, INT posY, POINT inCollisionOffset);
		bool CheckHit();
		bool IsInAir(POINT inPoint, float& outPosY);
		bool IsInScreen(PointF point);
	};
}
