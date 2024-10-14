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
	CreateBitmap(hBackgroundImg, bitBackground, _T("images/Metal-Slug-3-Mission-1_backGround.bmp"));

	CreateBitmap(hCoastBackImg, bitCoastBack, _T("images/Metal-Slug-3-Mission-1_back.bmp"));
	CreateBitmap(hCoastWaterImg, bitCoastWater, _T("images/Metal-Slug-3-Mission-1_Coast_Water.bmp"));
	CreateBitmap(hCoastPart3Img, bitCoastPart3, _T("images/Metal-Slug-3-Mission-1_Coast_part3.bmp"));
	CreateBitmap(hFishHeadImg, bitFishHead, _T("images/Metal-Slug-3-Mission-1_fishhead.bmp"));

	CreateBitmap(hRuinBlockImg, bitRuinBlock, _T("images/Metal-Slug-3-Mission-1_Ruinblock.bmp"));
	CreateBitmap(hRuinPartFrontImg, bitRuinPartFront, _T("images/Metal-Slug-3-Mission-1_Ruin_partFront.bmp"));
	CreateBitmap(hRuinPartBackImg, bitRuinPartBack, _T("images/Metal-Slug-3-Mission-1_Ruin_partBack.bmp"));
	CreateBitmap(hRuinDestroyImg, bitRuinDestroy, _T("images/Metal-Slug-3-Mission-1_RuinDestroy.bmp"));

	CreateBitmap(hLakeImg, bitLake, _T("images/Metal-Slug-3-Mission-1_Lake.bmp"));
}

void metalSlug::Geometry::Delete()
{
	DeleteObject(hBackgroundImg);

	DeleteObject(hCoastBackImg);
	DeleteObject(hCoastWaterImg);
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

	rtView = GetCamera()->GetCameraViewport();
	
	// TODO:
	// 주석처리된 함수들은 알파값 블랜드되서 테두리부분이 남음
	DrawBackGround(hdc, hMemDC, hOldBitmap);
	DrawCoastBack(hdc, hMemDC, hOldBitmap);
	DrawRuinDestroy(hdc, hMemDC, hOldBitmap);
	//DrawRuinBlock(hdc, hMemDC, hOldBitmap);
	//DrawRuinPartBack(hdc, hMemDC, hOldBitmap);
}

void metalSlug::Geometry::DrawFrontBitmap(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	rtView = GetCamera()->GetCameraViewport();

	//DrawCoastWater(hdc, hMemDC, hOldBitmap);
	//DrawCoastPart3(hdc, hMemDC, hOldBitmap);
	//DrawFishHead(hdc, hMemDC, hOldBitmap);
	//DrawRuinPartFront(hdc, hMemDC, hOldBitmap);
	//DrawLake(hdc, hMemDC, hOldBitmap);
}

void metalSlug::Geometry::DrawBackGround(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBackgroundImg);
	int bx = bitBackground.bmWidth;
	int by = bitBackground.bmHeight;

	if (rtView.left >= 0 && rtView.right <= bx * BACKSKYIMG_RATIO)
	{
		xOriginDest_BackGround = rtView.left/2;
		yOriginDest_BackGround = rtView.top/2;
	}

	int offsetX = -3 * BACKSKYIMG_RATIO;
	int offsetY = -67 * BACKSKYIMG_RATIO;

	TransparentBlt(hdc, -xOriginDest_BackGround + offsetX, -yOriginDest_BackGround + offsetY,
		bx * BACKSKYIMG_RATIO, by * BACKSKYIMG_RATIO, hMemDC, 0, 0, bx, by, RGB(248, 0, 248));

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawCoastBack(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hCoastBackImg);
	int bx = bitCoastBack.bmWidth;
	int by = bitCoastBack.bmHeight;

	if (rtView.left >= 0 && rtView.right <= bx * BACKSKYIMG_RATIO)
	{
		xOriginDest_BackGround = rtView.left;
		yOriginDest_BackGround = rtView.top;
	}

	int offsetX = -3 * BACKSKYIMG_RATIO;
	int offsetY = -43 * BACKSKYIMG_RATIO;

	TransparentBlt(hdc, -xOriginDest_BackGround + offsetX, -yOriginDest_BackGround + offsetY,
		bx * BACKSKYIMG_RATIO, by * BACKSKYIMG_RATIO, hMemDC, 0, 0, bx, by, RGB(248, 0, 248));

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawRuinDestroy(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hRuinDestroyImg);
	int bx = bitRuinDestroy.bmWidth;
	int by = bitRuinDestroy.bmHeight;

	if (rtView.left >= 0 && rtView.right <= bx * BACKSKYIMG_RATIO)
	{
		xOriginDest_BackGround = rtView.left;
		yOriginDest_BackGround = rtView.top;
	}

	int offsetX = 620 * BACKSKYIMG_RATIO;
	int offsetY = 55 * BACKSKYIMG_RATIO;

	TransparentBlt(hdc, -xOriginDest_BackGround + offsetX, -yOriginDest_BackGround + offsetY,
		bx * BACKSKYIMG_RATIO, by * BACKSKYIMG_RATIO, hMemDC, 0, 0, bx, by, RGB(248, 0, 248));

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawRuinBlock(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hRuinBlockImg);
	int bx = bitRuinBlock.bmWidth;
	int by = bitRuinBlock.bmHeight;

	if (rtView.left >= 0 && rtView.right <= bx * BACKSKYIMG_RATIO)
	{
		xOriginDest_BackGround = rtView.left;
		yOriginDest_BackGround = rtView.top;
	}

	int offsetX = 620 * BACKSKYIMG_RATIO;
	int offsetY = 55 * BACKSKYIMG_RATIO;

	TransparentBlt(hdc, -xOriginDest_BackGround + offsetX, -yOriginDest_BackGround + offsetY,
		bx * BACKSKYIMG_RATIO, by * BACKSKYIMG_RATIO, hMemDC, 0, 0, bx, by, RGB(248, 0, 248));

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawRuinPartBack(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hRuinPartBackImg);
	int bx = bitRuinPartBack.bmWidth;
	int by = bitRuinPartBack.bmHeight;

	if (rtView.left >= 0 && rtView.right <= bx * BACKSKYIMG_RATIO)
	{
		xOriginDest_BackGround = rtView.left;
		yOriginDest_BackGround = rtView.top;
	}

	int offsetX = 620 * BACKSKYIMG_RATIO;
	int offsetY = 55 * BACKSKYIMG_RATIO;

	TransparentBlt(hdc, -xOriginDest_BackGround + offsetX, -yOriginDest_BackGround + offsetY,
		bx * BACKSKYIMG_RATIO, by * BACKSKYIMG_RATIO, hMemDC, 0, 0, bx, by, RGB(248, 0, 248));

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawCoastWater(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hCoastWaterImg);
	int bx = bitCoastWater.bmWidth;
	int by = bitCoastWater.bmHeight;

	if (rtView.left >= 0 && rtView.right <= bx * BACKSKYIMG_RATIO)
	{
		xOriginDest_BackGround = rtView.left;
		yOriginDest_BackGround = rtView.top;
	}

	int offsetX = 0 * BACKSKYIMG_RATIO;
	int offsetY = 0 * BACKSKYIMG_RATIO;

	TransparentBlt(hdc, -xOriginDest_BackGround + offsetX, -yOriginDest_BackGround + offsetY,
		bx * BACKSKYIMG_RATIO, by * BACKSKYIMG_RATIO, hMemDC, 0, 0, bx, by, RGB(248, 0, 248));

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawCoastPart3(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hCoastPart3Img);
	int bx = bitCoastPart3.bmWidth;
	int by = bitCoastPart3.bmHeight;

	if (rtView.left >= 0 && rtView.right <= bx * BACKSKYIMG_RATIO)
	{
		xOriginDest_BackGround = rtView.left;
		yOriginDest_BackGround = rtView.top;
	}

	int offsetX = 0 * BACKSKYIMG_RATIO;
	int offsetY = 0 * BACKSKYIMG_RATIO;

	TransparentBlt(hdc, -xOriginDest_BackGround + offsetX, -yOriginDest_BackGround + offsetY,
		bx * BACKSKYIMG_RATIO, by * BACKSKYIMG_RATIO, hMemDC, 0, 0, bx, by, RGB(248, 0, 248));

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::Geometry::DrawFishHead(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hFishHeadImg);
	int bx = bitFishHead.bmWidth;
	int by = bitFishHead.bmHeight;

	if (rtView.left >= 0 && rtView.right <= bx * BACKSKYIMG_RATIO)
	{
		xOriginDest_BackGround = rtView.left;
		yOriginDest_BackGround = rtView.top;
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

	if (rtView.left >= 0 && rtView.right <= bx * BACKSKYIMG_RATIO)
	{
		xOriginDest_BackGround = rtView.left;
		yOriginDest_BackGround = rtView.top;
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

	if (rtView.left >= 0 && rtView.right <= bx * BACKSKYIMG_RATIO)
	{
		xOriginDest_BackGround = rtView.left;
		yOriginDest_BackGround = rtView.top;
	}

	int offsetX = 1360 * BACKSKYIMG_RATIO;
	int offsetY = 135 * BACKSKYIMG_RATIO;

	TransparentBlt(hdc, -xOriginDest_BackGround + offsetX, -yOriginDest_BackGround + offsetY,
		bx * BACKSKYIMG_RATIO, by * BACKSKYIMG_RATIO, hMemDC, 0, 0, bx, by, RGB(248, 0, 248));

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}
