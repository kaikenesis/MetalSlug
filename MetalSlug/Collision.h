#pragma once

namespace metalSlug
{
	enum CollisionType
	{
		CRect,
		CPolygon,
	};

	class Collision
	{
	private:
		Rect rect;
		Point* polygon;
		Point* w_polygon;
		CollisionType type;
		int pointCount = -1;

		bool bActive = true;

	public:
		Collision();
		Collision(INT posX, INT posY, int inWidth, int inHeight);
		Collision(Point* inPoints, int size);
		Collision(std::vector<Point> inPoints, int size);
		~Collision();

		Rect const GetRect() { return rect; }
		Point* const GetPolygon() { return w_polygon; }
		int const GetPointCount() { return pointCount; }
		bool const IsActive() { return bActive; }

		void SetActive(bool inValue) { bActive = inValue; }

		void UpdateCollision(INT posX, INT posY, int inWidth, int inHeight);
		void Contain();
	};
}

