#pragma once

/*
	���� ���õ� bitmap���� �� ó��
	���� Collision�� ��� ó������?

	��ü ������ �ϳ� ��Ƶΰ� �÷��̾ �����ԵǴ� ������ �ѹ� �� �׸���
	Collision�� ������ �׷��� �غ���? -> Line�� �׸��� �÷��̾��� ��ġ�� �ش���ġ�� Line�� y���� ���ؼ�
	������ ���������ʰ��ϸ� ����������?

	���������� ��������
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
