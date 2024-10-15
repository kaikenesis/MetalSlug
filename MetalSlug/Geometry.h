#pragma once

/*
	지형 관련된 bitmap생성 및 처리
	지형 Collision을 어떻게 처리하지?

	전체 지형을 하나 깔아두고 플레이어를 가리게되는 지형을 한번 더 그리기
	Collision은 라인을 그려서 해보기? -> Line을 그리고 플레이어의 위치와 해당위치의 Line의 y값을 비교해서
	밑으로 내려가지않게하면 되지않을까?

	발판지형은 나중으로
*/
namespace metalSlug
{
//#define BACKSKYIMG_RATIO 1.0f
#define BACKSKYIMG_RATIO 6.0f

	class Geometry
	{
	public:
		Geometry();
		~Geometry();

	private:
		int xOriginDest_BackGround = 0;
		int yOriginDest_BackGround = 0;

	private:
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
		HBITMAP hFishBoneImg;
		BITMAP bitFishBone;
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

		Camera* camera;
		RECT cameraView;

		float ratio;

	public:
		void Init();
		void Delete();

		void CreateBitmap(HBITMAP& hBitmap, BITMAP& bitmap, LPCWSTR filePath);
		void DrawBackBitmap(HWND hWnd, HDC hdc);
		void DrawFrontBitmap(HWND hWnd, HDC hdc);

		//Back
		void DrawBackGround(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap);
		void DrawCoastBack(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap);
		void DrawRuinDestroy(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap);
		void DrawRuinBlock(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap);
		void DrawRuinPartBack(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap);

		//Front
		void DrawCoastWater(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap);
		void DrawCoastPart1(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap);
		void DrawCoastPart2(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap);
		void DrawCoastPart3(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap);
		void DrawFishHead(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap);
		void DrawRuinPartFront(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap);
		void DrawLake(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap);

	};
}
