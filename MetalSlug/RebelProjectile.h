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
		EWeaponType weaponType = EWeaponType::Pistol;
		POINT worldPos = { 0,0 }; // ¸Ê»óÀÇ ÃÑ¾Ë À§Ä¡
		POINT localPos = { 0,0 }; // È­¸é»óÀÇ ÃÑ¾Ë À§Ä¡
		POINT imgPos = { 0,0 };
		POINT collisionOffset = { 0,0 };

		bool bActive = false;
		bool bHit = false;
		bool bJumping = false;
		PointF speed = { 0.0f,0.0f };
		float ratio = 0;
		float power = 0;
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
