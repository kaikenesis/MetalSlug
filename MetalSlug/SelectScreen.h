#pragma once

namespace metalSlug
{
	class SelectScreen
	{
	public:
		SelectScreen();
		~SelectScreen();

	private:
		enum ECharacter
		{
			None,
			Marco,
			Eri,
			Tarma,
			Fiolina
		};

		float ratio;
		int startPanelframe;
		int delay;
		bool bSelect = false;
		RECT camera;
		ECharacter currentSelectCharacter = None;

	public:
		void Init();
		void Update(HWND hWnd, HDC hdc);

		bool IsSelect() { return bSelect; }

		void SelectCharacter();

	private:
		bool IsMousePosInRange(POINT point, RECT rect);

		void DrawBackGround(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawCharacterImg(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawPlayerNum(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawLetter(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
		void DrawPanel(HDC hdc, HDC& hMemDC, HBITMAP& hBitmap, HBITMAP& hBitmapImg, BITMAP& bitmapImg);
	};
}
