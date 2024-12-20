#pragma once

namespace metalSlug
{
	class Bullet
	{
	public:
		Bullet();
		~Bullet();
		
	private:
		class Collision* collision;
		EWeaponType weaponType;
		POINT worldPos; // �ʻ��� �Ѿ� ��ġ
		POINT localPos; // ȭ����� �Ѿ� ��ġ
		POINT imgPos;
		POINT collisionOffset;
		class WeaponSFX* weaponSFX;

		bool bActive = false;
		bool bHit = false;
		PointF speed;
		float ratio;
		float power;
	
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

		void SetPistolInfo(INT posX, INT posY, POINT inCollisionOffset);
		bool CheckHit();
	};
}


