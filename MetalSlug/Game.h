#pragma once

namespace metalSlug
{
	enum PlayerDir
	{
		Left,
		Right,
	};

	enum PlayerState
	{
		Idle,
		Attack,
		Jump,
		Death,
	};

	enum CharacterType
	{
		Eri,
	};

	void CreateObject();
	void CreateCamera(RECT rect);
	void CreateGeometry();
	void CreateWeaponSFX();
	void CreateImages();
	void UpdateObject();
	void DeleteObject();

	float GetGlobalRatio();
	class Player* GetPlayer();
	class Images* GetImages();
	class Geometry* GetGeometry();
	class WeaponSFX* GetWeaponSFX();
	std::vector<class RebelSoldier*> GetRebelSoldiers();

	//Debug
	//=============================================
	BOOL IsDebugMode();

	POINT GetMouseClickPos();
	int GetBulletCount();
	
	void SetDebugMode(bool inValue);
	void SetMouseClickPos(POINT point);
	void SetBulletCount(int value);
	void SetEnmeyCount(int value);
	
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
