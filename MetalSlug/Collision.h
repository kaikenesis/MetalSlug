#pragma once

namespace metalSlug
{
	enum CollisionType
	{
		CRect,
		CPolygon,
	};

	enum ObjectType
	{
		CWorld,
		CLocal,
	};

	class Collision
	{
	private:
		Rect rect;
		Rect w_rect;
		Point* polygon;
		Point* w_polygon;
		CollisionType collisionType;
		ObjectType objectType;
		int pointCount = -1;

		bool bActive = true;

	public:
		Collision();
		Collision(INT posX, INT posY, int inWidth, int inHeight, ObjectType inType);
		Collision(Rect inRect, ObjectType inType);
		Collision(Point* inPoints, int size, ObjectType inType);
		Collision(std::vector<Point> inPoints, int size, ObjectType inType);
		~Collision();

		Rect const GetLocalRect() { return rect; }
		Rect const GetWorldRect() { return w_rect; }
		Point* const GetLocalPolygon() { return polygon; }
		Point* const GetWorldPolygon() { return w_polygon; }
		INT const GetWidth() { if (collisionType == CRect) return rect.Width; }
		INT const GetHeight() { if (collisionType == CRect) return rect.Height; }
		int const GetPointCount() { return pointCount; }
		CollisionType const GetType() { return collisionType; }
		float const GetWolrdPositionY(int inX);

		bool const IsActive() { return bActive; }
		bool const IsContain(POINT inPoint);
		bool const IsContain(RECT inRect);
		bool const IsInFrame(POINT inPoint);
		bool const IsInRange(POINT inPoint);

		void SetActive(bool inValue) { bActive = inValue; }

		void UpdateLocalLocation(INT posX, INT posY);
		void UpdateWorldLocation(INT posX, INT posY);
		void UpdateLocalScale(int inWidth, INT inHeight);
		void UpdateWorldScale(int inWidth, INT inHeight);

	private:
		bool IsOverlapRectToPoint(POINT inPoint);
		bool IsOverlapRectToRect(RECT inRect);
		bool IsOverlapPolygonToPoint(POINT inPoint);
	};
}

