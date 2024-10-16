#include "framework.h"
#include "Game.h"
#include "Collision.h"
#include "Geometry.h"

metalSlug::Geometry::Geometry()
{
	Init();
}

metalSlug::Geometry::~Geometry()
{
	Delete();
}

void metalSlug::Geometry::Init()
{
	// Bitmap
	CreateBitmap(hBackgroundImg, bitBackground, _T("images/Metal-Slug-3-Mission-1_BackGround.bmp"));

	CreateBitmap(hCoastBackImg, bitCoastBack, _T("images/Metal-Slug-3-Mission-1_Back_ver2.bmp"));
	CreateBitmap(hCoastWaterImg, bitCoastWater, _T("images/Metal-Slug-3-Mission-1_Coast_Water.bmp"));
	CreateBitmap(hCoastPart1Img, bitCoastPart1, _T("images/Metal-Slug-3-Mission-1_Coast_part1.bmp"));
	CreateBitmap(hCoastPart2Img, bitCoastPart2, _T("images/Metal-Slug-3-Mission-1_Coast_part2.bmp"));
	CreateBitmap(hCoastPart3Img, bitCoastPart3, _T("images/Metal-Slug-3-Mission-1_Coast_part3.bmp"));
	CreateBitmap(hFishBone1Img, bitFishBone1, _T("images/Metal-Slug-3-Mission-1_FishBone1.bmp"));
	CreateBitmap(hFishBone2Img, bitFishBone2, _T("images/Metal-Slug-3-Mission-1_FishBone2.bmp"));
	CreateBitmap(hFishHeadImg, bitFishHead, _T("images/Metal-Slug-3-Mission-1_Fishhead.bmp"));

	CreateBitmap(hRuinBlockImg, bitRuinBlock, _T("images/Metal-Slug-3-Mission-1_Ruinblock.bmp"));
	CreateBitmap(hRuinPartFrontImg, bitRuinPartFront, _T("images/Metal-Slug-3-Mission-1_Ruin_partFront.bmp"));
	CreateBitmap(hRuinPartBackImg, bitRuinPartBack, _T("images/Metal-Slug-3-Mission-1_Ruin_partBack.bmp"));
	CreateBitmap(hRuinDestroyImg, bitRuinDestroy, _T("images/Metal-Slug-3-Mission-1_RuinDestroy.bmp"));

	CreateBitmap(hLakeImg, bitLake, _T("images/Metal-Slug-3-Mission-1_Lake.bmp"));
	
	// Collision
	CreateGroundCollision();
	
	// Other
	camera = GetCamera();
	ratio = GetGlobalRatio();
}

void metalSlug::Geometry::Delete()
{
	DeleteObject(hBackgroundImg);

	DeleteObject(hCoastBackImg);
	DeleteObject(hCoastWaterImg);
	DeleteObject(hCoastPart1Img);
	DeleteObject(hCoastPart2Img);
	DeleteObject(hCoastPart3Img);
	DeleteObject(hFishHeadImg);

	DeleteObject(hRuinBlockImg);
	DeleteObject(hRuinPartFrontImg);
	DeleteObject(hRuinPartBackImg);
	DeleteObject(hRuinDestroyImg);

	DeleteObject(hLakeImg);
}

void metalSlug::Geometry::CreateBitmap(HBITMAP& hBitmap, BITMAP& bitmap, LPCWSTR filePath)
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

void metalSlug::Geometry::DrawBackBitmap(HWND hWnd, HDC hdc)
{
	// 유적건물이 부셔지면 DrawRuinDestroy()는 활성화, DrawRuinBlock()와 DrawRuinPartBack()은 비활성화
	HDC hMemDC;
	HBITMAP hOldBitmap;
	cameraView = GetCamera()->GetCameraViewport();
	// TODO:
	// 주석처리된 함수들은 알파값 블랜드되서 테두리부분이 남음
	DrawBackGround(hdc, hMemDC, hOldBitmap, hBackgroundImg, bitBackground);
	DrawCoastBack(hdc, hMemDC, hOldBitmap, hCoastBackImg, bitCoastBack);
	if (isRuinDestroy == true) DrawRuinDestroy(hdc, hMemDC, hOldBitmap,hRuinDestroyImg, bitRuinDestroy);
	if (isRuinDestroy == false) DrawRuinBlock(hdc, hMemDC, hOldBitmap, hRuinBlockImg, bitRuinBlock);
	if (isRuinDestroy == false) DrawRuinPartBack(hdc, hMemDC, hOldBitmap, hRuinPartBackImg, bitRuinPartBack);
}

void metalSlug::Geometry::DrawFrontBitmap(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	cameraView = GetCamera()->GetCameraViewport();
	DrawCoastWater(hdc, hMemDC, hOldBitmap, hCoastWaterImg, bitCoastWater);
	if (isRuinDestroy == true) DrawCoastPart3(hdc, hMemDC, hOldBitmap, hCoastPart3Img, bitCoastPart3);
	DrawFishHead(hdc, hMemDC, hOldBitmap, hFishHeadImg, bitFishHead);
	DrawFishBone1(hdc, hMemDC, hOldBitmap, hFishBone1Img, bitFishBone1);
	DrawFishBone2(hdc, hMemDC, hOldBitmap, hFishBone2Img, bitFishBone2);
	if (isRuinDestroy == false) DrawRuinPartFront(hdc, hMemDC, hOldBitmap, hRuinPartFrontImg, bitRuinPartFront);
	DrawLake(hdc, hMemDC, hOldBitmap, hLakeImg, bitLake);
}

void metalSlug::Geometry::DrawBackGround(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	/*
		범위: 화면 사이즈(카메라) - 고정
		어디서 부터 그릴지 : 카메라 left, top - 변수
	*/

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = -2 * ratio;
	int destY = -206;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (by * ratio > camera->GetHeight())
	{
		TransparentBlt(hdc, destX, destY, camera->GetWidth() - destX, by * ratio, hMemDC, 
			cameraView.left / (ratio * 2), cameraView.top + srcOffsetY, bx / (ratio * 2), by - srcOffsetY, color.GetValue());
	}
	else
	{
		TransparentBlt(hdc, destX, destY, camera->GetWidth() - destX, camera->GetHeight(), hMemDC,
			cameraView.left / (ratio * 2), cameraView.top + srcOffsetY, bx / (ratio * 2), by - srcOffsetY, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawCoastBack(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = -2 * ratio;
	int destY = -90;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (by * ratio > camera->GetHeight())
	{
		TransparentBlt(hdc, destX, destY, camera->GetWidth()- destX, by * ratio, hMemDC,
			cameraView.left/ ratio, cameraView.top + srcOffsetY, camera->GetWidth() / ratio, by - srcOffsetY, color.GetValue());
	}
	else
	{
		TransparentBlt(hdc, destX, destY, camera->GetWidth()- destX, camera->GetHeight(), hMemDC,
			cameraView.left/ ratio, cameraView.top + srcOffsetY, camera->GetWidth() / ratio, camera->GetHeight() / ratio, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawRuinDestroy(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = 1876;
	int destY = 160;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());
	/*TransparentBlt(hdc, destX, destY, (bx - cameraView.left) * ratio, by * ratio, hMemDC,
		cameraView.left, cameraView.top + srcOffsetY, bx - cameraView.left, by - srcOffsetY, color.GetValue());*/

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawRuinBlock(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = 1992;
	int destY = 27;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawRuinPartBack(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = 2433;
	int destY = 26;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawCoastWater(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = -4;
	int destY = 540;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawCoastPart1(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = 0;
	int destY = 0;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawCoastPart2(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = 1650;
	int destY = 570;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawCoastPart3(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = 1946;
	int destY = 408;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawFishBone1(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = 1724;
	int destY = 482;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawFishBone2(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = 1960;
	int destY = 496;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawFishHead(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = 1462;
	int destY = 446;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawRuinPartFront(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = 2478;
	int destY = 28;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawLake(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = -2 * ratio;
	int destY = 0;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (by * ratio > camera->GetHeight())
	{
		TransparentBlt(hdc, destX, destY, camera->GetWidth() - destX, by * ratio, hMemDC,
			cameraView.left / ratio, cameraView.top + srcOffsetY, camera->GetWidth() / ratio, by - srcOffsetY, color.GetValue());
	}
	else
	{
		TransparentBlt(hdc, destX, destY, camera->GetWidth() - destX, camera->GetHeight(), hMemDC,
			cameraView.left / ratio, cameraView.top + srcOffsetY, camera->GetWidth() / ratio, camera->GetHeight() / ratio, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::CreateGroundCollision()
{
	/*
		지형은 Polygon으로 구성, 많은 양의 Point정보를 데이터로 만들고, 초기 맵 구성시 이 값을 통해서 Polygon을 생성
		플레이어의 CollisionBox의 Bottom 중앙위치가 지형 Polygon에 포함될 경우 포함되지 않거나 인접할때 까지 플레이어의 Y위치를 감소
	*/
	
	Collision coast1(dataCoast1, GEOMETRY_Coast1, CollisionType::Platform);
	Collision ruinBlock(dataRuinBlock, GEOMETRY_RuinBlock, CollisionType::Platform);
	Collision ruinDestroy(dataRuinDestroy, GEOMETRY_RuinDestroy, CollisionType::Platform);

	collisions.push_back(coast1);
	collisions.push_back(ruinBlock);
	collisions.push_back(ruinDestroy);
}
