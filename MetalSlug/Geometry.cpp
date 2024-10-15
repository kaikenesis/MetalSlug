#include "framework.h"
#include "Game.h"
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
	CreateBitmap(hBackgroundImg, bitBackground, _T("images/Metal-Slug-3-Mission-1_BackGround.bmp"));

	CreateBitmap(hCoastBackImg, bitCoastBack, _T("images/Metal-Slug-3-Mission-1_Back_ver2.bmp"));
	CreateBitmap(hCoastWaterImg, bitCoastWater, _T("images/Metal-Slug-3-Mission-1_Coast_Water.bmp"));
	CreateBitmap(hCoastPart1Img, bitCoastPart1, _T("images/Metal-Slug-3-Mission-1_Coast_part1.bmp"));
	CreateBitmap(hCoastPart2Img, bitCoastPart2, _T("images/Metal-Slug-3-Mission-1_Coast_part2.bmp"));
	CreateBitmap(hCoastPart3Img, bitCoastPart3, _T("images/Metal-Slug-3-Mission-1_Coast_part3.bmp"));
	CreateBitmap(hFishBoneImg, bitFishBone, _T("images/Metal-Slug-3-Mission-1_FishBone.bmp"));
	CreateBitmap(hFishHeadImg, bitFishHead, _T("images/Metal-Slug-3-Mission-1_Fishhead.bmp"));

	CreateBitmap(hRuinBlockImg, bitRuinBlock, _T("images/Metal-Slug-3-Mission-1_Ruinblock.bmp"));
	CreateBitmap(hRuinPartFrontImg, bitRuinPartFront, _T("images/Metal-Slug-3-Mission-1_Ruin_partFront.bmp"));
	CreateBitmap(hRuinPartBackImg, bitRuinPartBack, _T("images/Metal-Slug-3-Mission-1_Ruin_partBack.bmp"));
	CreateBitmap(hRuinDestroyImg, bitRuinDestroy, _T("images/Metal-Slug-3-Mission-1_RuinDestroy.bmp"));

	CreateBitmap(hLakeImg, bitLake, _T("images/Metal-Slug-3-Mission-1_Lake.bmp"));

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
	HDC hMemDC;
	HBITMAP hOldBitmap;
	cameraView = GetCamera()->GetCameraViewport();
	// TODO:
	// 주석처리된 함수들은 알파값 블랜드되서 테두리부분이 남음
	DrawBackGround(hdc, hMemDC, hOldBitmap);
	DrawCoastBack(hdc, hMemDC, hOldBitmap);
	DrawRuinDestroy(hdc, hMemDC, hOldBitmap);
	DrawRuinBlock(hdc, hMemDC, hOldBitmap);
	DrawCoastPart2(hdc, hMemDC, hOldBitmap);
	DrawRuinPartBack(hdc, hMemDC, hOldBitmap);
}

void metalSlug::Geometry::DrawFrontBitmap(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	cameraView = GetCamera()->GetCameraViewport();
	DrawCoastWater(hdc, hMemDC, hOldBitmap);
	DrawCoastPart3(hdc, hMemDC, hOldBitmap);
	//DrawFishHead(hdc, hMemDC, hOldBitmap);
	//DrawRuinPartFront(hdc, hMemDC, hOldBitmap);
	//DrawLake(hdc, hMemDC, hOldBitmap);

	char buffer[100];
	sprintf_s(buffer, "%d", cameraView.left);
	TextOutA(hdc, 0, 0, buffer, strlen(buffer));
}

void metalSlug::Geometry::DrawBackGround(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	/*
		범위: 화면 사이즈(카메라) - 고정
		어디서 부터 그릴지 : 카메라 left, top - 변수
	*/

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBackgroundImg);
	int bx = bitBackground.bmWidth;
	int by = bitBackground.bmHeight;

	int destX = -2 * ratio;
	int destY = 0;
	int srcOffsetY = 66;
	Color color(RGB(248, 0, 248));

	if (by * ratio < camera->GetHeight())
	{
		TransparentBlt(hdc, destX, destY, camera->GetWidth() - destX, by * ratio - destY, hMemDC, 
			cameraView.left / (ratio * 2), cameraView.top + srcOffsetY, bx / (ratio * 2), by - srcOffsetY, color.GetValue());
	}
	else
	{
		TransparentBlt(hdc, destX, destY, camera->GetWidth() - destX, camera->GetHeight() - destY, hMemDC,
			cameraView.left / (ratio * 2), cameraView.top + srcOffsetY, bx / (ratio * 2), by - srcOffsetY, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawCoastBack(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hCoastBackImg);
	int bx = bitCoastBack.bmWidth;
	int by = bitCoastBack.bmHeight;

	int destX = -2 * ratio;
	int destY = 40;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (by * ratio < camera->GetHeight())
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

void metalSlug::Geometry::DrawRuinDestroy(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	
	int bx = bitRuinDestroy.bmWidth;
	int by = bitRuinDestroy.bmHeight;

	int destX = 1876;
	int destY = 290;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hRuinDestroyImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());
	/*TransparentBlt(hdc, destX, destY, (bx - cameraView.left) * ratio, by * ratio, hMemDC,
		cameraView.left, cameraView.top + srcOffsetY, bx - cameraView.left, by - srcOffsetY, color.GetValue());*/

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawRuinBlock(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	int bx = bitRuinBlock.bmWidth;
	int by = bitRuinBlock.bmHeight;

	int destX = 1994;
	int destY = 159;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hRuinBlockImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawRuinPartBack(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	int bx = bitRuinPartBack.bmWidth;
	int by = bitRuinPartBack.bmHeight;

	int destX = 2435;
	int destY = 159;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hRuinPartBackImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawCoastWater(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	int bx = bitCoastWater.bmWidth;
	int by = bitCoastWater.bmHeight;

	int destX = -6;
	int destY = 670;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hCoastWaterImg);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawCoastPart1(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	int bx = bitCoastPart1.bmWidth;
	int by = bitCoastPart1.bmHeight;

	int destX = 0;
	int destY = 0;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hCoastPart1Img);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawCoastPart2(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	int bx = bitCoastPart2.bmWidth;
	int by = bitCoastPart2.bmHeight;

	int destX = 1650;
	int destY = 570;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hCoastPart2Img);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawCoastPart3(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	int bx = bitCoastPart3.bmWidth;
	int by = bitCoastPart3.bmHeight;

	int destX = 2000;
	int destY = 470;
	int srcOffsetY = 0;
	Color color(RGB(248, 0, 248));

	if (cameraView.left > destX + bx * ratio || cameraView.right < destX) return;

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hCoastPart3Img);

	TransparentBlt(hdc, destX - cameraView.left, destY, bx * ratio, by * ratio, hMemDC,
		0, 0 + srcOffsetY, bx, by - srcOffsetY, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawFishHead(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hFishHeadImg);
	int bx = bitFishHead.bmWidth;
	int by = bitFishHead.bmHeight;

	if (cameraView.left >= 0 && cameraView.right <= bx * BACKSKYIMG_RATIO)
	{
		xOriginDest_BackGround = cameraView.left;
		yOriginDest_BackGround = cameraView.top;
	}

	int offsetX = 0 * BACKSKYIMG_RATIO;
	int offsetY = 0 * BACKSKYIMG_RATIO;

	TransparentBlt(hdc, -xOriginDest_BackGround + offsetX, -yOriginDest_BackGround + offsetY,
		bx * BACKSKYIMG_RATIO, by * BACKSKYIMG_RATIO, hMemDC, 0, 0, bx, by, RGB(248, 0, 248));

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawRuinPartFront(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hRuinPartFrontImg);
	int bx = bitRuinPartFront.bmWidth;
	int by = bitRuinPartFront.bmHeight;

	if (cameraView.left >= 0 && cameraView.right <= bx * BACKSKYIMG_RATIO)
	{
		xOriginDest_BackGround = cameraView.left;
		yOriginDest_BackGround = cameraView.top;
	}

	int offsetX = 821 * BACKSKYIMG_RATIO;
	int offsetY = 11 * BACKSKYIMG_RATIO;

	TransparentBlt(hdc, -xOriginDest_BackGround + offsetX, -yOriginDest_BackGround + offsetY,
		bx * BACKSKYIMG_RATIO, by * BACKSKYIMG_RATIO, hMemDC, 0, 0, bx, by, RGB(248, 0, 248));

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawLake(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hLakeImg);
	int bx = bitLake.bmWidth;
	int by = bitLake.bmHeight;

	if (cameraView.left >= 0 && cameraView.right <= bx * BACKSKYIMG_RATIO)
	{
		xOriginDest_BackGround = cameraView.left;
		yOriginDest_BackGround = cameraView.top;
	}

	int offsetX = 1360 * BACKSKYIMG_RATIO;
	int offsetY = 135 * BACKSKYIMG_RATIO;

	TransparentBlt(hdc, -xOriginDest_BackGround + offsetX, -yOriginDest_BackGround + offsetY,
		bx * BACKSKYIMG_RATIO, by * BACKSKYIMG_RATIO, hMemDC, 0, 0, bx, by, RGB(248, 0, 248));

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}
