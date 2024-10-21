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
		POINT Bulletpos;
		POINT collisionOffset;

		bool bActive = false;
		bool bHit = false;
		PointF speed;
		float ratio;
	
	public:
		bool IsActive() { return bActive; }

		void Update(HWND hWnd, HDC hdc);
		void Activate() { bActive = true; }
		void Hit() { bHit = true; }
		void Hide();

		class Collision* const GetCollision() { return collision; }
		
		void SetInfo(INT posX, INT posY, int inWidth, int inHeight, PointF inSpeed, POINT inCollisionOffset, EWeaponType inWeaponType = EWeaponType::Pistol);
	
	private:
		void SetPistolInfo(INT posX, INT posY, int inWidth, int inHeight, PointF inSpeed, POINT inCollisionOffset);
	};
}


