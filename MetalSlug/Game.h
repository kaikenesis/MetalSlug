#pragma once

namespace metalSlug
{
	enum EGameMode
	{
		Title,
		InGame
	};

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
	void CreateSelectScreenUI();
	void CreateSound();
	void UpdateKeyInput();
	void UpdateObject();
	void DeleteObject();
	void SelectSoldier();
	void PlayBGM();

	float GetGlobalRatio();
	EGameMode GetGameMode();
	class Camera* GetCamera();
	class Player* GetPlayer();
	class Images* GetImages();
	class Geometry* GetGeometry();
	class SelectScreen* GetSelectScreen();
	class MySound* GetSound();
	std::vector<class Enemy*> GetEnemys();
	std::vector<class Bullet*> GetPlayerProjectiles();
	std::vector<class RebelProjectile*> GetEnemyProjectiles();

	bool IsCanSpawnProjectile();
	bool IsSelectSoldier();
	bool IsPlayFadeInOut();

	POINT GetMouseClickPos();
	POINT GetMousePos();
	int GetBulletCount();
	int GetEnemyCount();
	int GetEnemyProjectileCount();

	void SetMouseClickPos(POINT point);
	void SetMousePos(POINT point);
	void SetBulletCount(int value);
	void SetEnemyCount(int value);
	void SetEnemyProjectileCount(int value);
	void SetGameMode(EGameMode newGameMode);
	void SetPlayFadeInOut(bool value);

	//Debug
	//=============================================
	bool IsDebugMode();
	
	void SetDebugMode(bool inValue);
	
	void DebugDestroyRuin();
	void DebugSpawnEnemy();
	void DebugFlipEnemys();
	void DebugChangeEnemysState();
	//=============================================
}
