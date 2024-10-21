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
	void UpdateObject();
	void DrawObject(Graphics* graphics);
	void DeleteObject();

	float GetGlobalRatio();
	BOOL IsDebugMode();
	class Player* GetPlayer();
	class Geometry* GetGeometry();
	class WeaponSFX* GetWeaponSFX();
	void SetMouseClickPos(POINT point);
	POINT GetMouseClickPos();

	void SetDebugMode(bool inValue);
	void DebugDestroyRuin();

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
