#include "framework.h"
#include "SelectScreen.h"

metalSlug::SelectScreen::SelectScreen()
{
	Init();
}

metalSlug::SelectScreen::~SelectScreen()
{
}

void metalSlug::SelectScreen::Init()
{
	ratio = GetGlobalRatio();
	startPanelframe = -382;
	delay = 100;
	bSelect = false;
	currentSelectCharacter = None;
}

void metalSlug::SelectScreen::Update(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	camera = GetCamera()->GetCameraViewport();

	DrawCharacterImg(hdc, hMemDC, hOldBitmap, GetImages()->titleUI.hSelectScreenImg, GetImages()->titleUI.bitSelectScreen);
	if (bSelect == true)
	{
		DrawPanel(hdc, hMemDC, hOldBitmap, GetImages()->titleUI.hSelectScreenImg, GetImages()->titleUI.bitSelectScreen);
	}
	DrawBackGround(hdc, hMemDC, hOldBitmap, GetImages()->titleUI.hSelectScreenImg, GetImages()->titleUI.bitSelectScreen);
	DrawPlayerNum(hdc, hMemDC, hOldBitmap, GetImages()->titleUI.hSelectScreenImg, GetImages()->titleUI.bitSelectScreen);
	DrawLetter(hdc, hMemDC, hOldBitmap, GetImages()->titleUI.hSelectScreenImg, GetImages()->titleUI.bitSelectScreen);
}

void metalSlug::SelectScreen::SelectCharacter()
{
	if (bSelect == true) return;

	float imgRatio = 2.9f;
	int SrcWidth = 66;
	int SrcHeight = 124;
	int offsetDestX = camera.right / 2 - SrcWidth / 2 * imgRatio;
	int offsetDestY = 200;
	int posX[4] = { -296,-99,99,296 };

	for (int i = 0; i < 4; i++)
	{
		int left = offsetDestX + posX[i];
		int top = offsetDestY;
		int right = left + SrcWidth * imgRatio;
		int bottom = top + SrcHeight * imgRatio;
		RECT rt = { left, top, right, bottom };
		if (IsMousePosInRange(GetMouseClickPos(), rt) == true)
		{
			currentSelectCharacter = (ECharacter)(i + 1);
			bSelect = true;
		}
	}
}

bool metalSlug::SelectScreen::IsMousePosInRange(POINT point, RECT rect)
{
	if (point.x < rect.left || point.x > rect.right) return false;
	if (point.y < rect.top || point.y > rect.bottom) return false;
	return true;
}

void metalSlug::SelectScreen::DrawBackGround(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	float imgRatio = 2.9f;
	int SrcWidth = 304;
	int SrcHeight = 224;
	int offsetDestX = camera.right / 2 - SrcWidth / 2 * imgRatio;
	int offsetDestY = 0;
	int offsetSrcX = 3;
	int offsetSrcY = 108;

	Color color(RGB(255, 0, 255));

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, offsetDestX, offsetDestY, SrcWidth * imgRatio, SrcHeight * imgRatio, hMemDC,
		offsetSrcX, offsetSrcY, SrcWidth, SrcHeight, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::SelectScreen::DrawCharacterImg(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	float imgRatio = 2.9f;
	int SrcWidth = 66;
	int SrcHeight = 124;
	int offsetDestX = camera.right / 2 - SrcWidth / 2 * imgRatio;
	int offsetDestY = 200;
	int offsetSrcX = 309;
	int offsetSrcY = 0;
	int nextX = 67;
	int nextY = 123;
	int posX[4] = { -296,-99,99,296 };

	Color color(RGB(255, 0, 255));

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	for (int i = 0; i < 4; i++)
	{
		RECT rt = { offsetDestX + posX[i], offsetDestY, offsetDestX + posX[i] + SrcWidth * imgRatio, offsetDestY + SrcHeight * imgRatio };
		if (IsMousePosInRange(GetMousePos(), rt) == false)
		{
			TransparentBlt(hdc, offsetDestX + posX[i], offsetDestY, SrcWidth * imgRatio, SrcHeight * imgRatio, hMemDC,
				offsetSrcX + nextX * i, offsetSrcY, SrcWidth, SrcHeight, color.GetValue());
		}
		else if (currentSelectCharacter == (ECharacter)(i + 1))
		{
			TransparentBlt(hdc, offsetDestX + posX[i], offsetDestY, SrcWidth * imgRatio, SrcHeight * imgRatio, hMemDC,
				offsetSrcX + nextX * i, offsetSrcY + nextY * 2, SrcWidth, SrcHeight, color.GetValue());
		}
		else
		{
			TransparentBlt(hdc, offsetDestX + posX[i], offsetDestY, SrcWidth * imgRatio, SrcHeight * imgRatio, hMemDC,
				offsetSrcX + nextX * i, offsetSrcY + nextY, SrcWidth, SrcHeight, color.GetValue());
		}
	}
	
	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::SelectScreen::DrawPlayerNum(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	float imgRatio = 2.9f;
	int SrcWidth = 50;
	int SrcHeight = 34;
	int offsetDestX = camera.right / 2 - SrcWidth / 2 * imgRatio;
	int offsetDestY = 113;
	int offsetSrcX = 2;
	int offsetSrcY = 37;
	int posX[4] = { -302,-116,116,302 };
	int scrX[4] = { 2,53,104,155 };

	Color color(RGB(255, 0, 255));

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	if (bSelect == true)
	{
		TransparentBlt(hdc, offsetDestX + posX[(int)currentSelectCharacter - 1], offsetDestY, SrcWidth * imgRatio, SrcHeight * imgRatio, hMemDC,
			scrX[(int)currentSelectCharacter - 1], offsetSrcY, SrcWidth, SrcHeight, color.GetValue());
	}

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::SelectScreen::DrawLetter(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	float imgRatio = 2.9f;
	int SrcWidth = 246;
	int SrcHeight = 36;
	int offsetDestX = camera.right / 2 - SrcWidth / 2 * imgRatio + 1;
	int offsetDestY = 20;
	int offsetSrcX = 3;
	int offsetSrcY = 0;

	Color color(RGB(255, 0, 255));

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, offsetDestX, offsetDestY, SrcWidth* imgRatio, SrcHeight* imgRatio, hMemDC,
		offsetSrcX, offsetSrcY, SrcWidth, SrcHeight, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}

void metalSlug::SelectScreen::DrawPanel(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg)
{
	float imgRatio = 2.9f;
	int SrcWidth = 66;
	int SrcHeight = 136;
	int offsetDestX = camera.right / 2 - SrcWidth / 2 * imgRatio;
	int offsetDestY = 200;
	int offsetSrcX = 2;
	int offsetSrcY = 334;
	int posX[4] = { -296,-99,99,296 };
	int frame = startPanelframe;
	int speed = 10;
	
	if (startPanelframe < 0)
		startPanelframe += speed;
	else
		delay--;
	
	if (delay <= 0)
		SetPlayFadeInOut(true);

	Color color(RGB(255, 0, 255));

	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmapImg);

	TransparentBlt(hdc, offsetDestX + posX[(int)currentSelectCharacter - 1], offsetDestY + frame, SrcWidth * imgRatio, SrcHeight * imgRatio, hMemDC,
		offsetSrcX, offsetSrcY + 0, SrcWidth, SrcHeight, color.GetValue());

	SelectObject(hMemDC, hBitmap);
	DeleteDC(hMemDC);
}
