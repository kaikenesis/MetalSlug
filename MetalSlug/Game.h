#pragma once

namespace metalSlug
{
	enum EPlayerDir
	{
		Left,
		Right,
	};

	enum EPlayerState
	{
		Idle,
		Attack,
		Jump,
		Death,
	};

	enum ECharacterType
	{
		Eri,
	};

	enum EWeaponType
	{
		Pistol,
		RebelBomb,
	};

	void CreateObject();
	void CreateCamera(RECT rect);
	void CreateGeometry();
	void CreateImages();
	void UpdateObject();
	void DeleteObject();

	float GetGlobalRatio();
	class Player* GetPlayer();
	class Images* GetImages();
	class Geometry* GetGeometry();
	std::vector<class Enemy*> GetEnemys();
	std::vector<class Bullet*> GetPlayerProjectiles();
	std::vector<class RebelProjectile*> GetEnemyProjectiles();

	bool IsCanSpawnProjectile();

	int GetBulletCount();
	int GetEnemyCount();
	int GetEnemyProjectileCount();

	void SetBulletCount(int value);
	void SetEnemyCount(int value);
	void SetEnemyProjectileCount(int value);

	//Debug
	//=============================================
	bool IsDebugMode();

	POINT GetMouseClickPos();
	
	void SetDebugMode(bool inValue);
	void SetMouseClickPos(POINT point);
	
	void DebugDestroyRuin();
	void DebugSpawnEnemy();
	void DebugFlipEnemys();
	void DebugChangeEnemysState();
	//=============================================

	class Camera
	{
	public:
		Camera();
		Camera(RECT rect);
		~Camera();

	private:
		RECT rectView;

		PointF position;
		double width;
		double height;

	public:
		RECT GetCameraViewport() { return rectView; }
		double GetWidth() { return width; }
		double GetHeight() { return height; }

		void Init(RECT rect);
		void Update();
		
		void UpdatePosition(int inX, int inY);
		void UpdateScale(double inWidth, double inHeight);
	};

	Camera* GetCamera();
}
