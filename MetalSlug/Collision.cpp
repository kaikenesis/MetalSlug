#include "framework.h"
#include "Collision.h"

metalSlug::Collision::Collision()
{
	rect = { 0,0,50,100 };
	type = CRect;
}

metalSlug::Collision::Collision(INT posX, INT posY, int inWidth, int inHeight)
{
	type = CRect;
	rect = { posX,posY,inWidth,inHeight };
}

metalSlug::Collision::Collision(Point* inPoints, int size)
{
	polygon = new Point[size]();
	w_polygon = new Point[size]();
	for (int i = 0; i < size; i++)
	{
		polygon[i] = inPoints[i];
		w_polygon[i] = inPoints[i];
	}
	type = CPolygon;
	pointCount = size;
}

metalSlug::Collision::Collision(std::vector<Point> inPoints, int size)
{
	polygon = new Point[size]();
	w_polygon = new Point[size]();
	for (int i = 0; i < size; i++)
	{
		polygon[i] = inPoints[i];
		w_polygon[i] = inPoints[i];
	}
	type = CPolygon;
	pointCount = size;
}

metalSlug::Collision::~Collision()
{
	if (type == CPolygon)
		delete[] polygon;
}

void metalSlug::Collision::UpdateCollision(INT posX, INT posY, int inWidth, int inHeight)
{
	if (type == CPolygon)
	{
		for (int i = 0; i < pointCount; i++)
		{
			w_polygon[i].X = polygon[i].X - posX;
			w_polygon[i].Y = polygon[i].Y - posY;
		}
	}
	else
	{
		rect = { posX,posY,inWidth,inHeight };
	}
}
