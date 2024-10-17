#include "framework.h"
#include "Collision.h"

metalSlug::Collision::Collision()
{
	rect = { 0,0,50,100 };
	w_rect = { 0,0,50,100 };
	collisionType = CRect;
	objectType = CWorld;
}

metalSlug::Collision::Collision(INT posX, INT posY, int inWidth, int inHeight, ObjectType inType)
{
	rect = { posX,posY,inWidth,inHeight };
	w_rect = { posX,posY,inWidth,inHeight };
	collisionType = CRect;
	objectType = inType;
}

metalSlug::Collision::Collision(Rect inRect, ObjectType inType)
{
	rect = { inRect.X,inRect.Y,inRect.Width,inRect.Height };
	w_rect = { inRect.X,inRect.Y,inRect.Width,inRect.Height };
	collisionType = CRect;
	objectType = inType;
}

metalSlug::Collision::Collision(Point* inPoints, int size, ObjectType inType)
{
	polygon = new Point[size]();
	w_polygon = new Point[size]();
	for (int i = 0; i < size; i++)
	{
		polygon[i] = inPoints[i];
		w_polygon[i] = inPoints[i];
	}
	collisionType = CPolygon;
	pointCount = size;
	objectType = inType;
}

metalSlug::Collision::Collision(std::vector<Point> inPoints, int size, ObjectType inType)
{
	polygon = new Point[size]();
	w_polygon = new Point[size]();
	for (int i = 0; i < size; i++)
	{
		polygon[i] = inPoints[i];
		w_polygon[i] = inPoints[i];
	}
	collisionType = CPolygon;
	pointCount = size;
	objectType = inType;
}

metalSlug::Collision::~Collision()
{
	if (collisionType == CPolygon)
		delete[] polygon;
}

float const metalSlug::Collision::GetWolrdPositionY(int inX)
{
	switch (collisionType)
	{
	case CPolygon:
	{
		int i;
		int n = pointCount;
		for (i = 0; i < n;)
		{
			if (inX >= polygon[i].X && inX < polygon[i + 1].X) break;
			i++;
		}

		if (polygon[i].Y == polygon[i + 1].Y) return polygon[i].Y;
		else
		{
			float dx = (polygon[i + 1].X - inX);
			float xx = (polygon[i + 1].X - polygon[i].X);
			float yy = (polygon[i + 1].Y - polygon[i].Y);
			dx = sqrt(dx * dx);
			xx = sqrt(xx * xx);
			yy = sqrt(yy * yy);

			if (polygon[i].Y < (polygon[i + 1].Y))
				return (float)polygon[i].Y + (yy * ((xx - dx) / xx));
			else if (polygon[i].Y > (polygon[i + 1].Y))
				return (float)polygon[i].Y - (yy * ((xx - dx) / xx));
		}
	}
		break;

	case CRect:
	{
		if (inX >= rect.X && inX < rect.X + rect.Width) break;
		
		return rect.Y;
	}
		break;
	}
	
}

bool const metalSlug::Collision::IsContain(POINT inPos)
{
	if (bActive == false) return false;

	switch (collisionType)
	{
	case CRect:
		return IsOverlapRectToPoint(inPos);
		break;
	case CPolygon:
		return IsOverlapPolygonToPoint(inPos);
		break;
	default:
		break;
	}
}

bool const metalSlug::Collision::IsContain(RECT inRect)
{
	switch (collisionType)
	{
	case CRect:
		return IsOverlapRectToRect(inRect);
		break;
	default:
		break;
	}
}

void metalSlug::Collision::UpdateLocalLocation(INT posX, INT posY)
{
	switch (collisionType)
	{
	case CPolygon:
		for (int i = 0; i < pointCount; i++)
		{
			polygon[i].X = posX;
			polygon[i].Y = posY;
		}
		break;

	case CRect:
		rect.X = posX;
		rect.Y = posY;
	}
}

void metalSlug::Collision::UpdateWorldLocation(INT posX, INT posY)
{
	switch (collisionType)
	{
	case CPolygon:
		for (int i = 0; i < pointCount; i++)
		{
			w_polygon[i].X = polygon[i].X - posX;
			w_polygon[i].Y = polygon[i].Y - posY;
		}
		break;

	case CRect:
		switch (objectType)
		{
		case CWorld:
			w_rect.X = rect.X - posX;
			w_rect.Y = rect.Y - posY;
			break;
		case CLocal:
			w_rect.X = rect.X + posX;
			w_rect.Y = rect.Y + posY;
			break;
		}
	}
}

void metalSlug::Collision::UpdateLocalScale(int inWidth, INT inHeight)
{
	if (collisionType == CRect)
	{
		rect.Width = inWidth;
		rect.Height = inHeight;
	}
}

void metalSlug::Collision::UpdateWorldScale(int inWidth, INT inHeight)
{
	if(collisionType == CRect)
	{
		w_rect.Width = inWidth;
		w_rect.Height = inHeight;
	}
}

bool metalSlug::Collision::IsOverlapRectToPoint(POINT inPoint)
{
	if (inPoint.x < w_rect.GetLeft() || inPoint.x > w_rect.GetRight()) return false;
	if (inPoint.y < w_rect.GetTop() || inPoint.y > w_rect.GetBottom()) return false;
	
	return true;
}

bool metalSlug::Collision::IsOverlapRectToRect(RECT inRect)
{
	double xx = (inRect.left + (inRect.right - inRect.left) / 2) - (w_rect.X + w_rect.Width / 2);
	double yy = (inRect.top + (inRect.bottom - inRect.top) / 2) - (w_rect.Y + w_rect.Height / 2);
	xx = sqrt(xx * xx);
	yy = sqrt(yy * yy);

	if (xx >= ((inRect.right - inRect.left) / 2) + (w_rect.Width / 2)) return false;
	if (yy >= ((inRect.bottom - inRect.top) / 2) + (w_rect.Height / 2)) return false;

	return true;
}

bool metalSlug::Collision::IsOverlapPolygonToPoint(POINT inPoint)
{
	int maxY = polygon[0].Y;
	int minY = polygon[0].Y;
	int n = pointCount;
	for (int i = 0; i < n; i++)
	{
		if (polygon[i].Y > maxY) maxY = polygon[i].Y;
		else if (polygon[i].Y < minY) minY = polygon[i].Y;
	}

	if (inPoint.y > maxY || inPoint.y < minY) return false;

	int crossCount = 0;
	for (int i = 0; i < n; i++)
	{
		Point p1 = polygon[i];
		Point p2 = polygon[(i + 1) % n];

		if ((inPoint.y > min(p1.Y, p2.Y)) && (inPoint.y <= max(p1.Y, p2.Y)) && (inPoint.x <= max(p1.X, p2.X)))
		{
			double xIntersect = (inPoint.y - p1.Y) * (p2.X - p1.X) / (p2.Y - p1.Y) + p1.X;
			if (p1.X == p2.X || inPoint.x <= xIntersect)
			{
				crossCount++;
			}
		}
	}

	return crossCount % 2 == 1;
}

bool const metalSlug::Collision::IsInFrame(POINT inPoint)
{
	int maxY = polygon[0].Y;
	int minY = polygon[0].Y;
	int n = pointCount / 2;
	for (int i = 0; i < n; i++)
	{
		if (polygon[i].Y > maxY) maxY = polygon[i].Y;
		else if (polygon[i].Y < minY) minY = polygon[i].Y;
	}

	if (inPoint.y > maxY || inPoint.y < minY) return false;

	int crossCount = 0;
	for (int i = 0; i < n; i++)
	{
		Point p1 = polygon[i];
		Point p2 = polygon[(i + 1) % n];

		if ((inPoint.x == p1.X && inPoint.x == p2.X) && ((inPoint.y <= p1.Y && inPoint.y > p2.Y) || (inPoint.y < p2.Y && inPoint.y >= p1.Y)))
			return true;
		else if ((inPoint.y == p1.Y && inPoint.y == p2.Y) && ((inPoint.x <= p1.X && inPoint.x > p2.X) || (inPoint.x < p2.X && inPoint.x >= p1.X)))
			return true;
	}

	return false;
}

bool const metalSlug::Collision::IsInRange(POINT inPoint)
{
	switch(collisionType)
	{
	case CPolygon:
	{
		int maxX = polygon[0].X;
		int minX = polygon[0].X;
		int maxY = polygon[0].Y;
		int minY = polygon[0].Y;
		int n = pointCount;
		for (int i = 0; i < n; i++)
		{
			if (polygon[i].X > maxX) maxX = polygon[i].X;
			else if (polygon[i].X < minX) minX = polygon[i].X;

			if (polygon[i].Y > maxY) maxY = polygon[i].Y;
			else if (polygon[i].Y < minY) minY = polygon[i].Y;
		}

		if (inPoint.x < minX || inPoint.x > maxX) return false;
		if (inPoint.y < minY || inPoint.y > maxY) return false;
		return true;
	}
		break;
	case CRect:
	{
		int maxX = rect.X + rect.Width;
		int minX = rect.X;
		int maxY = rect.Y + rect.Height;
		int minY = rect.Y;

		if (inPoint.x < minX || inPoint.x > maxX) return false;
		if (inPoint.y < minY || inPoint.y > maxY) return false;
		return true;
	}
		break;
	}
}
