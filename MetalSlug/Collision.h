#pragma once

namespace metalSlug
{
	enum ECollisionType
	{
		CRect,
		CPolygon,
	};

	enum ERenderType
	{
		RWorld,
		RLocal,
	};

	class Collision
	{
	private:
		Rect rect;
		Rect w_rect;
		Point* polygon;
		Point* w_polygon;
		ECollisionType collisionType;
		ERenderType renderType;
		int pointCount = -1;

		bool bActive = true;

	public:
		Collision();
		Collision(INT posX, INT posY, int inWidth, int inHeight, ERenderType inType);
		Collision(Rect inRect, ERenderType inType);
		Collision(Point* inPoints, int size, ERenderType inType);
		Collision(std::vector<Point> inPoints, int size, ERenderType inType);
		~Collision();

		Rect const GetLocalRect() { return rect; }
		Rect const GetWorldRect() { return w_rect; }
		Point* const GetLocalPolygon() { return polygon; }
		Point* const GetWorldPolygon() { return w_polygon; }
		INT const GetWidth() { if (collisionType == CRect) return rect.Width; }
		INT const GetHeight() { if (collisionType == CRect) return rect.Height; }
		int const GetPointCount() { return pointCount; }
		ECollisionType const GetType() { return collisionType; }
		float const GetWolrdPositionY(int X, int inY);
		float const GetWolrdPositionX(int X, int inY);

		bool const IsActive() { return bActive; }
		bool const IsContain(POINT inPoint);
		bool const IsContain(Rect inRect);
		bool const IsInFrame(POINT inPoint);
		bool const IsInRange(POINT inPoint); // WorldÁÂÇ¥
		bool const IsInRange(Rect inRect); // WorldÁÂÇ¥

		void SetActive(bool inValue) { bActive = inValue; }

		void UpdateLocalLocation(INT posX, INT posY);
		void UpdateWorldLocation(INT posX, INT posY);
		void UpdateLocalScale(INT inWidth, INT inHeight);
		void UpdateWorldScale(INT inWidth, INT inHeight);

		void SetInfo(INT posX, INT posY, int inWidth, int inHeight, ERenderType inType);
		void SetInfo(Rect inRect, ERenderType inType);

	private:
		bool IsOverlapRectToPoint(POINT inPoint);
		bool IsOverlapRectToRect(Rect inRect);
		bool IsOverlapPolygonToPoint(POINT inPoint);
	};
}

