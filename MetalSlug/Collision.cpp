#include "framework.h"
#include "Collision.h"

metalSlug::Collision::Collision()
{
	collisionBox = { 0,0,50,100 };
	type = Character;
}

metalSlug::Collision::Collision(INT posX, INT posY, int inWidth, int inHeight, CollisionType inType)
{
	type = inType;
	collisionBox = { posX,posY,inWidth,inHeight };
}

metalSlug::Collision::Collision(POINT* inPoints, int size, CollisionType inType)
{
	collisionPolygon = new POINT[size]();
	for (int i = 0; i < size; i++)
	{
		collisionPolygon[i] = inPoints[i];
	}
	type = inType;
	pointCount = size;
}

metalSlug::Collision::Collision(std::vector<POINT> inPoints, int size, CollisionType inType)
{
	collisionPolygon = new POINT[size]();
	for (int i = 0; i < size; i++)
	{
		collisionPolygon[i] = inPoints[i];
	}
	type = inType;
	pointCount = size;
}

metalSlug::Collision::~Collision()
{
	if (type == Platform)
		delete[] collisionPolygon;
}

void metalSlug::Collision::UpdateCollisionBox(INT posX, INT posY, int inWidth, int inHeight)
{
	collisionBox = { posX,posY,inWidth,inHeight };
}
