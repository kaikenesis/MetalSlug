#include "framework.h"
#include "Collision.h"
#include "Geometry.h"

metalSlug::Geometry::Geometry()
{
	Init();
}

metalSlug::Geometry::~Geometry()
{
}

void metalSlug::Geometry::Init()
{
	// Collision
	CreateGroundCollision();
	
	// Other
	camera = GetCamera();
	ratio = GetGlobalRatio();
}

void metalSlug::Geometry::DrawBackBitmap(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	cameraView = GetCamera()->GetCameraViewport();

	DrawBackGround(hdc, hMemDC, hOldBitmap, GetImages()->m1Geometry.hBackgroundImg, GetImages()->m1Geometry.bitBackground);
	DrawCoastBack(hdc, hMemDC, hOldBitmap, GetImages()->m1Geometry.hCoastBackImg, GetImages()->m1Geometry.bitCoastBack);
	if (isRuinDestroy == true) DrawRuinDestroy(hdc, hMemDC, hOldBitmap, GetImages()->m1Geometry.hRuinDestroyImg, GetImages()->m1Geometry.bitRuinDestroy);
	if (isRuinDestroy == false) DrawRuinBlock(hdc, hMemDC, hOldBitmap, GetImages()->m1Geometry.hRuinBlockImg, GetImages()->m1Geometry.bitRuinBlock);
	if (isRuinDestroy == false) DrawRuinPartBack(hdc, hMemDC, hOldBitmap, GetImages()->m1Geometry.hRuinPartBackImg, GetImages()->m1Geometry.bitRuinPartBack);
}

void metalSlug::Geometry::DrawFrontBitmap(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	cameraView = GetCamera()->GetCameraViewport();
	DrawCoastWater(hdc, hMemDC, hOldBitmap, GetImages()->m1Geometry.hCoastWaterImg, GetImages()->m1Geometry.bitCoastWater);
	if (isRuinDestroy == true) DrawCoastPart3(hdc, hMemDC, hOldBitmap, GetImages()->m1Geometry.hCoastPart3Img, GetImages()->m1Geometry.bitCoastPart3);
	DrawFishHead(hdc, hMemDC, hOldBitmap, GetImages()->m1Geometry.hFishHeadImg, GetImages()->m1Geometry.bitFishHead);
	DrawFishBone1(hdc, hMemDC, hOldBitmap, GetImages()->m1Geometry.hFishBone1Img, GetImages()->m1Geometry.bitFishBone1);
	DrawFishBone2(hdc, hMemDC, hOldBitmap, GetImages()->m1Geometry.hFishBone2Img, GetImages()->m1Geometry.bitFishBone2);
	if (isRuinDestroy == false) DrawRuinPartFront(hdc, hMemDC, hOldBitmap, GetImages()->m1Geometry.hRuinPartFrontImg, GetImages()->m1Geometry.bitRuinPartFront);
	DrawLake(hdc, hMemDC, hOldBitmap, GetImages()->m1Geometry.hLakeImg, GetImages()->m1Geometry.bitLake);

	for (int i = 0; i < collisions.size(); i++)
	{
		collisions[i]->UpdateLocalLocation(cameraView.left, cameraView.top);
	}
}

void metalSlug::Geometry::DestroyRuin(bool inValue)
{
	isRuinDestroy = inValue;
	collisions[1]->SetActive(!inValue);
	collisions[2]->SetActive(inValue);
	collisions[3]->SetActive(!inValue);
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

	int destX = wOffset_X + (-2 * ratio);
	int destY = wOffset_Y + (-206);
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

	int destX = wOffset_X + (-2 * ratio);
	int destY = wOffset_Y + (-90);
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

	int destX = wOffset_X + 1876;
	int destY = wOffset_Y + 160;
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

void metalSlug::Geometry::DrawRuinBlock(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	int bx = bitmapImg.bmWidth;
	int by = bitmapImg.bmHeight;

	int destX = wOffset_X + 1992;
	int destY = wOffset_Y + 27;
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

	int destX = wOffset_X + 2433;
	int destY = wOffset_Y + 26;
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

	int destX = wOffset_X + (-4);
	int destY = wOffset_Y + 540;
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

	int destX = wOffset_X;
	int destY = wOffset_Y;
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

	int destX = wOffset_X + 1650;
	int destY = wOffset_Y + 570;
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

	int destX = wOffset_X + 1946;
	int destY = wOffset_Y + 408;
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

	int destX = wOffset_X + 1724;
	int destY = wOffset_Y + 482;
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

	int destX = wOffset_X + 1960;
	int destY = wOffset_Y + 496;
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

	int destX = wOffset_X + 1462;
	int destY = wOffset_Y + 446;
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

	int destX = wOffset_X + 2478;
	int destY = wOffset_Y + 28;
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

	int destX = wOffset_X + (-2 * ratio);
	int destY = wOffset_Y;
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
		플레이어의 CollisionBox의 Bottom 중앙위치가 지형 Polygon에 포함될 경우 해당 지형 Polygon의 Top Y위치 적용
	*/
	
	Collision* coast1 = new Collision(dataCoast1, GEOMETRY_Coast1, ERenderType::RWorld);
	Collision* ruinBlock = new Collision(dataRuinBlock, GEOMETRY_RuinBlock, ERenderType::RWorld);
	Collision* ruinDestroy = new Collision(dataRuinDestroy, GEOMETRY_RuinDestroy, ERenderType::RWorld);
	ruinDestroy->SetActive(false);
	Collision* ruinBuild = new Collision(dataRuinBuild, ERenderType::RWorld);

	collisions.push_back(coast1);
	collisions.push_back(ruinBlock);
	collisions.push_back(ruinDestroy);
	collisions.push_back(ruinBuild);
}
