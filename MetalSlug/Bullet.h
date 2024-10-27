#pragma once

namespace metalSlug
{
	class Bullet
	{
	public:
		Bullet();
		Bullet(INT posX, INT posY, int inWidth, int inHeight, ERenderType inType);
		Bullet(Rect inRect, ERenderType inType);
		~Bullet();
		
	private:
		class Collision* collision;
		EWeaponType weaponType;
		POINT BulletWorldPos; // ¸Ê»óÀÇ ÃÑ¾Ë À§Ä¡
		POINT BulletLocalPos; // È­¸é»óÀÇ ÃÑ¾Ë À§Ä¡
		POINT BulletImgPos;
		POINT collisionOffset;

		bool bActive = false;
		bool bHit = false;
		PointF speed;
		float ratio;
		float power;
	
	public:
		bool IsActive() { return bActive; }
		bool IsHit() { return bHit; }

		void Update(HWND hWnd, HDC hdc);
		void Activate() { bActive = true; }
		void Hide();

		class Collision* const GetCollision() { return collision; }
		
		void SetInfo(INT posX, INT posY, PointF inSpeed, POINT inCollisionOffset, EWeaponType inWeaponType = EWeaponType::Pistol);
	
	private:
		void UpdatePos();

		void SetPistolInfo(INT posX, INT posY, POINT inCollisionOffset);
		bool CheckHit();
	};
}


