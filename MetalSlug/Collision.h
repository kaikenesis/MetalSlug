#pragma once

namespace metalSlug
{
	enum CollisionType
	{
		Character,
		Bullet,
		Platform,
	};

	class Collision
	{
	private:
		Rect collisionBox;
		POINT* collisionPolygon;
		CollisionType type;
		int pointCount = -1;

	public:
		Collision();
		Collision(INT posX, INT posY, int inWidth, int inHeight, CollisionType inType);
		Collision(POINT* inPoints, int size, CollisionType inType);
		Collision(std::vector<POINT> inPoints, int size, CollisionType inType);
		~Collision();

		Rect const GetCollisionBox() { return collisionBox; }
		POINT* const GetCollisionPolygon() { return collisionPolygon; }
		int const GetPointCount() { return pointCount; }
		void UpdateCollisionBox(INT posX, INT posY, int inWidth, int inHeight);
		void Contain();
	};
}

