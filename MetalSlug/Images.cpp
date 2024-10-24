#include "framework.h"
#include "Images.h"

metalSlug::Images::Images()
{
	Init();
}

metalSlug::Images::~Images()
{
	Destroy();
}

void metalSlug::Images::Init()
{
	//Geometry Mission1
	CreateBitmap(m1Geometry.hBackgroundImg, m1Geometry.bitBackground, _T("images/Metal-Slug-3-Mission-1_BackGround.bmp"));

	CreateBitmap(m1Geometry.hCoastBackImg, m1Geometry.bitCoastBack, _T("images/Metal-Slug-3-Mission-1_Back_ver2.bmp"));
	CreateBitmap(m1Geometry.hCoastWaterImg, m1Geometry.bitCoastWater, _T("images/Metal-Slug-3-Mission-1_Coast_Water.bmp"));
	CreateBitmap(m1Geometry.hCoastPart1Img, m1Geometry.bitCoastPart1, _T("images/Metal-Slug-3-Mission-1_Coast_part1.bmp"));
	CreateBitmap(m1Geometry.hCoastPart2Img, m1Geometry.bitCoastPart2, _T("images/Metal-Slug-3-Mission-1_Coast_part2.bmp"));
	CreateBitmap(m1Geometry.hCoastPart3Img, m1Geometry.bitCoastPart3, _T("images/Metal-Slug-3-Mission-1_Coast_part3.bmp"));
	CreateBitmap(m1Geometry.hFishBone1Img, m1Geometry.bitFishBone1, _T("images/Metal-Slug-3-Mission-1_FishBone1.bmp"));
	CreateBitmap(m1Geometry.hFishBone2Img, m1Geometry.bitFishBone2, _T("images/Metal-Slug-3-Mission-1_FishBone2.bmp"));
	CreateBitmap(m1Geometry.hFishHeadImg, m1Geometry.bitFishHead, _T("images/Metal-Slug-3-Mission-1_Fishhead.bmp"));

	CreateBitmap(m1Geometry.hRuinBlockImg, m1Geometry.bitRuinBlock, _T("images/Metal-Slug-3-Mission-1_Ruinblock.bmp"));
	CreateBitmap(m1Geometry.hRuinPartFrontImg, m1Geometry.bitRuinPartFront, _T("images/Metal-Slug-3-Mission-1_Ruin_partFront.bmp"));
	CreateBitmap(m1Geometry.hRuinPartBackImg, m1Geometry.bitRuinPartBack, _T("images/Metal-Slug-3-Mission-1_Ruin_partBack.bmp"));
	CreateBitmap(m1Geometry.hRuinDestroyImg, m1Geometry.bitRuinDestroy, _T("images/Metal-Slug-3-Mission-1_RuinDestroy.bmp"));

	CreateBitmap(m1Geometry.hLakeImg, m1Geometry.bitLake, _T("images/Metal-Slug-3-Mission-1_Lake.bmp"));

	//RebelSoldier
	CreateBitmap(rebelSoldierBitmap.hIdleImg, rebelSoldierBitmap.bitIdle, _T("images/Metal-Slug-3-Rebel-Soldier_Idle.bmp"));
	CreateBitmap(rebelSoldierBitmap.hRunImg, rebelSoldierBitmap.bitRun, _T("images/Metal-Slug-3-Rebel-Soldier_Run.bmp"));
	CreateBitmap(rebelSoldierBitmap.hDeathImg, rebelSoldierBitmap.bitDeath, _T("images/Metal-Slug-3-Rebel-Soldier_Death.bmp"));
	CreateBitmap(rebelSoldierBitmap.hSurpriseImg, rebelSoldierBitmap.bitSurprise, _T("images/Metal-Slug-3-Rebel-Soldier_Surprise.bmp"));
	CreateBitmap(rebelSoldierBitmap.hRollingBombImg, rebelSoldierBitmap.bitRollingBomb, _T("images/Metal-Slug-3-Rebel-Soldier_RollingBomb.bmp"));

	CreateBitmap(rebelSoldierBitmap.hIdleFlipImg, rebelSoldierBitmap.bitIdleFlip, _T("images/Metal Slug 3 - Rebel Soldier_Idle_Flip.bmp"));
	CreateBitmap(rebelSoldierBitmap.hRunFlipImg, rebelSoldierBitmap.bitRunFlip, _T("images/Metal Slug 3 - Rebel Soldier_Run_Flip.bmp"));
	CreateBitmap(rebelSoldierBitmap.hDeathFlipImg, rebelSoldierBitmap.bitDeathFlip, _T("images/Metal Slug 3 - Rebel Soldier_Death_Flip.bmp"));
	CreateBitmap(rebelSoldierBitmap.hSurpriseFlipImg, rebelSoldierBitmap.bitSurpriseFlip, _T("images/Metal Slug 3 - Rebel Soldier_Surprise_Flip.bmp"));
	CreateBitmap(rebelSoldierBitmap.hRollingBombFlipImg, rebelSoldierBitmap.bitRollingBombFlip, _T("images/Metal Slug 3 - Rebel Soldier_RollingBomb_Flip.bmp"));

	//Pistol
	CreateBitmap(pistolBitmap.hBulletImg, pistolBitmap.bitBullet, _T("images/Metal-Slug-3-Weapon-SFX_Pistol_Bullet.bmp"));
	CreateBitmap(pistolBitmap.hBulletRotate90Img, pistolBitmap.bitBulletRotate90, _T("images/Metal-Slug-3-Weapon-SFX_Pistol_Bullet_Rotate90.bmp"));
	CreateBitmap(pistolBitmap.hHitImg, pistolBitmap.bitHit, _T("images/Metal-Slug-3-Weapon-SFX_Pistol_Hit.bmp"));
}

void metalSlug::Images::Destroy()
{
	//Geometry Mission1
	DeleteObject(m1Geometry.hBackgroundImg);

	DeleteObject(m1Geometry.hCoastBackImg);
	DeleteObject(m1Geometry.hCoastWaterImg);
	DeleteObject(m1Geometry.hCoastPart1Img);
	DeleteObject(m1Geometry.hCoastPart2Img);
	DeleteObject(m1Geometry.hCoastPart3Img);
	DeleteObject(m1Geometry.hFishHeadImg);

	DeleteObject(m1Geometry.hRuinBlockImg);
	DeleteObject(m1Geometry.hRuinPartFrontImg);
	DeleteObject(m1Geometry.hRuinPartBackImg);
	DeleteObject(m1Geometry.hRuinDestroyImg);

	DeleteObject(m1Geometry.hLakeImg);

	//RebelSoldier
	DeleteObject(rebelSoldierBitmap.hIdleImg);
	DeleteObject(rebelSoldierBitmap.hRunImg);
	DeleteObject(rebelSoldierBitmap.hDeathImg);
	DeleteObject(rebelSoldierBitmap.hSurpriseImg);
	DeleteObject(rebelSoldierBitmap.hRollingBombImg);

	//Pistol
	DeleteObject(pistolBitmap.hBulletImg);
	DeleteObject(pistolBitmap.hBulletRotate90Img);
	DeleteObject(pistolBitmap.hHitImg);
}

void metalSlug::Images::CreateBitmap(HBITMAP& hBitmap, BITMAP& bitmap, LPCWSTR filePath)
{
	hBitmap = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hBitmap == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("이미지 로드 에러"), _T("Error"), MB_OK);
	}
	else
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
}
