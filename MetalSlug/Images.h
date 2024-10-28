#pragma once

namespace metalSlug
{
	class Images
	{
	public:
		Images();
		~Images();

	private:
		// Geometry - Mission1
		struct Mission1Geometry
		{
			HBITMAP hBackgroundImg;
			BITMAP bitBackground;

			HBITMAP hCoastBackImg;
			BITMAP bitCoastBack;
			HBITMAP hCoastWaterImg;
			BITMAP bitCoastWater;
			HBITMAP hCoastPart1Img;
			BITMAP bitCoastPart1;
			HBITMAP hCoastPart2Img;
			BITMAP bitCoastPart2;
			HBITMAP hCoastPart3Img;
			BITMAP bitCoastPart3;
			HBITMAP hFishBone1Img;
			BITMAP bitFishBone1;
			HBITMAP hFishBone2Img;
			BITMAP bitFishBone2;
			HBITMAP hFishHeadImg;
			BITMAP bitFishHead;
			
			HBITMAP hRuinBlockImg;
			BITMAP bitRuinBlock;
			HBITMAP hRuinPartFrontImg;
			BITMAP bitRuinPartFront;
			HBITMAP hRuinPartBackImg;
			BITMAP bitRuinPartBack;
			HBITMAP hRuinDestroyImg;
			BITMAP bitRuinDestroy;

			HBITMAP hLakeImg;
			BITMAP bitLake;
		};

		// RebelSoldier
		struct RebelSoldierBitmap
		{
			HBITMAP hIdleImg;
			BITMAP bitIdle;
			HBITMAP hRunImg;
			BITMAP bitRun;
			HBITMAP hDeathImg;
			BITMAP bitDeath;
			HBITMAP hSurpriseImg;
			BITMAP bitSurprise;
			HBITMAP hRollingBombImg;
			BITMAP bitRollingBomb;

			HBITMAP hIdleFlipImg;
			BITMAP bitIdleFlip;
			HBITMAP hRunFlipImg;
			BITMAP bitRunFlip;
			HBITMAP hDeathFlipImg;
			BITMAP bitDeathFlip;
			HBITMAP hSurpriseFlipImg;
			BITMAP bitSurpriseFlip;
			HBITMAP hRollingBombFlipImg;
			BITMAP bitRollingBombFlip;
		};

		//Pistol
		struct PistolBitmap
		{
			HBITMAP hBulletImg;
			BITMAP bitBullet;
			HBITMAP hBulletRotate90Img;
			BITMAP bitBulletRotate90;
			HBITMAP hHitImg;
			BITMAP bitHit;
		};

		//RebelBomb
		struct RebelBombBitmap
		{
			HBITMAP hBombImg;
			BITMAP bitBomb;
		};

		//Explosion
		struct Explosion
		{
			HBITMAP hFireBombImg;
			BITMAP bitFireBomb;
		};

	public:
		RebelSoldierBitmap rebelSoldierBitmap;
		PistolBitmap pistolBitmap;
		RebelBombBitmap rebelBombBitmap;
		Explosion explosionBitmap;
		Mission1Geometry m1Geometry;

	private:
		void Init();
		void Destroy();

		void CreateBitmap(HBITMAP& hBitmap, BITMAP& bitmap, LPCWSTR filePath);
	};
}
