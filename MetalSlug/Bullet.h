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
		class Collision* collider;
		EWeaponType weaponType;
		POINT Bulletpos;

		bool bActive = false;
		bool bHit = false;
		float speedX;
		float speedY;

	public:
		bool IsActive() { return bActive; }

		void Update(HWND hWnd, HDC hdc);

		void Activate() { bActive = true; }
		void Hit() { bHit = true; }
		void Hide();

		void SetInfo(INT posX, INT posY, int inWidth, int inHeight, EWeaponType inWeaponType = EWeaponType::Pistol, float inSpeedX = 0.0f, float inSpeedY = 0.0f);

	private:

	};
}


