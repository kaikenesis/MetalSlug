#pragma once

namespace metalSlug
{
	class Geometry
	{
#define GEOMETRY_Coast1 10
#define GEOMETRY_RuinBlock 12
#define GEOMETRY_RuinDestroy 8
#define wOffset_X 0
#define wOffset_Y 4

	public:
		Geometry();
		~Geometry();

	private:
		int xOriginDest_BackGround = 0;
		int yOriginDest_BackGround = 0;

		// x, y
		Point dataCoast1[GEOMETRY_Coast1] =
		{
			{ -100,560 },
			{890,560},
			{1100,510},
			{1690,510},
			{1980,440},
			{1980,540},
			{1690,610},
			{1100,610},
			{890,660},
			{ -100,660 },
		};

		Point dataRuinBlock[GEOMETRY_RuinBlock] =
		{
			{1980,440},
			{2210,440},
			{2270,390},
			{2440,390},
			{2480,370},
			{2700,370},
			{2700,470},
			{2480,470},
			{2440,490},
			{2270,490},
			{2210,540},
			{1980,540},
		};

		Point dataRuinDestroy[GEOMETRY_RuinDestroy] =
		{
			{1980,440},
			{2300,440},
			{2360,470},
			{2870,560},
			{2870,660},
			{2360,570},
			{2300,540},
			{1980,540},
		};

		// RectData - x, y, w, h
		Rect dataRuinBuild = { 2480,0,300,370 };

	private:
		Camera* camera;
		RECT cameraView;
		std::vector<Collision*> collisions;

		float ratio;
		bool isRuinDestroy = false;

	public:
		void Init();

		void DrawBackBitmap(HWND hWnd, HDC hdc);
		void DrawFrontBitmap(HWND hWnd, HDC hdc);
		void DestroyRuin(bool inValue);

		std::vector<Collision*> GetGeometryCollisions() { return collisions; }

	private:
		//Back
		void DrawBackGround(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg,BITMAP& bitmapImg);
		void DrawCoastBack(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawRuinDestroy(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawRuinBlock(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawRuinPartBack(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);

		//Front
		void DrawCoastWater(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawCoastPart1(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawCoastPart2(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawCoastPart3(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawFishBone1(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawFishBone2(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawFishHead(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawRuinPartFront(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawLake(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);

		void CreateGroundCollision();
	};
}
