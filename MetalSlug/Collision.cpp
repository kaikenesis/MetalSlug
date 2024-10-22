#include "framework.h"
#include "Game.h"
#include "WeaponSFX.h"
#include "Collision.h"

metalSlug::Collision::Collision()
{
	rect = { 0,0,50,100 };
	w_rect = { 0,0,50,100 };
	collisionType = CRect;
	renderType = RWorld;
}

metalSlug::Collision::Collision(INT posX, INT posY, int inWidth, int inHeight, ERenderType inType)
{
	w_rect = { posX,posY,inWidth,inHeight };
	rect = { posX,posY,inWidth,inHeight };
	collisionType = CRect;
	renderType = inType;
}

metalSlug::Collision::Collision(Rect inRect, ERenderType inType)
{
	w_rect = { inRect.X,inRect.Y,inRect.Width,inRect.Height };
	rect = { inRect.X,inRect.Y,inRect.Width,inRect.Height };
	collisionType = CRect;
	renderType = inType;
}

metalSlug::Collision::Collision(Point* inPoints, int size, ERenderType inType)
{
	w_polygon = new Point[size]();
	polygon = new Point[size]();
	for (int i = 0; i < size; i++)
	{
		w_polygon[i] = inPoints[i];
		polygon[i] = inPoints[i];
	}
	collisionType = CPolygon;
	pointCount = size;
	renderType = inType;
}

metalSlug::Collision::Collision(std::vector<Point> inPoints, int size, ERenderType inType)
{
	w_polygon = new Point[size]();
	polygon = new Point[size]();
	for (int i = 0; i < size; i++)
	{
		w_polygon[i] = inPoints[i];
		polygon[i] = inPoints[i];
	}
	collisionType = CPolygon;
	pointCount = size;
	renderType = inType;
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
			if (inX >= w_polygon[i].X && inX < w_polygon[i + 1].X) break;
			i++;
		}

		if (w_polygon[i].Y == w_polygon[i + 1].Y) return w_polygon[i].Y;
		else
		{
			float dx = (w_polygon[i + 1].X - inX);
			float xx = (w_polygon[i + 1].X - w_polygon[i].X);
			float yy = (w_polygon[i + 1].Y - w_polygon[i].Y);
			dx = sqrt(dx * dx);
			xx = sqrt(xx * xx);
			yy = sqrt(yy * yy);

			if (w_polygon[i].Y < (w_polygon[i + 1].Y))
				return (float)w_polygon[i].Y + (yy * ((xx - dx) / xx));
			else if (w_polygon[i].Y > (w_polygon[i + 1].Y))
				return (float)w_polygon[i].Y - (yy * ((xx - dx) / xx));
		}
	}
		break;

	case CRect:
	{
		if (inX >= w_rect.X && inX < w_rect.X + w_rect.Width) break;
		
		return w_rect.Y;
	}
		break;
	}
	
}

float const metalSlug::Collision::GetWolrdPositionX(int inY)
{
	switch (collisionType)
	{
	case CPolygon:
	{
		int i;
		int n = pointCount;
		for (i = 0; i < n;)
		{
			if (inY >= w_polygon[i].Y && inY < w_polygon[i + 1].Y) break;
			i++;
		}

		if (w_polygon[i].X == w_polygon[i + 1].X) return w_polygon[i].X;
		else
		{
			float dy = (w_polygon[i + 1].Y - inY);
			float xx = (w_polygon[i + 1].X - w_polygon[i].X);
			float yy = (w_polygon[i + 1].Y - w_polygon[i].Y);
			dy = sqrt(dy * dy);
			xx = sqrt(xx * xx);
			yy = sqrt(yy * yy);

			if (w_polygon[i].X < (w_polygon[i + 1].X))
				return (float)w_polygon[i].X + (xx * ((yy - dy) / yy));
			else if (w_polygon[i].X > (w_polygon[i + 1].X))
				return (float)w_polygon[i].X - (xx * ((yy - dy) / yy));
		}
	}
	break;

	case CRect:
	{
		if (inY >= w_rect.Y && inY < w_rect.Y + w_rect.Height) break;

		return w_rect.X;
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

bool const metalSlug::Collision::IsContain(Rect inRect)
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
			polygon[i].X = w_polygon[i].X - posX;
			polygon[i].Y = w_polygon[i].Y - posY;
		}
		break;

	case CRect:
		switch (renderType)
		{
		case RWorld:
			rect.X = w_rect.X - posX;
			rect.Y = w_rect.Y - posY;
			break;
		case RLocal:
			rect.X = w_rect.X + posX;
			rect.Y = w_rect.Y + posY;
			break;
		}
	}
	
}

void metalSlug::Collision::UpdateWorldLocation(INT posX, INT posY)
{
	switch (collisionType)
	{
	case CPolygon:
		for (int i = 0; i < pointCount; i++)
		{
			w_polygon[i].X = posX;
			w_polygon[i].Y = posY;
		}
		break;

	case CRect:
		w_rect.X = posX;
		w_rect.Y = posY;
		break;
	}
}

void metalSlug::Collision::UpdateLocalScale(INT inWidth, INT inHeight)
{
	if (collisionType == CRect)
	{
		rect.Width = inWidth;
		rect.Height = inHeight;
	}
}

void metalSlug::Collision::UpdateWorldScale(INT inWidth, INT inHeight)
{
	if(collisionType == CRect)
	{
		w_rect.Width = inWidth;
		w_rect.Height = inHeight;
	}
}

void metalSlug::Collision::SetInfo(INT posX, INT posY, int inWidth, int inHeight, ERenderType inType)
{
	collisionType = CRect;
	renderType = inType;

	UpdateWorldLocation(posX, posY);
	UpdateWorldScale(inWidth, inHeight);
	RECT rt = GetCamera()->GetCameraViewport();
	UpdateLocalLocation(rt.left, rt.top);
	UpdateLocalScale(inWidth, inHeight);
}

void metalSlug::Collision::SetInfo(Rect inRect, ERenderType inType)
{
	w_rect = { inRect.X,inRect.Y,inRect.Width,inRect.Height };
	rect = { inRect.X,inRect.Y,inRect.Width,inRect.Height };
	collisionType = CRect;
	renderType = inType;
}

bool metalSlug::Collision::IsOverlapRectToPoint(POINT inPoint)
{
	if (inPoint.x < rect.GetLeft() || inPoint.x > rect.GetRight()) return false;
	if (inPoint.y < rect.GetTop() || inPoint.y > rect.GetBottom()) return false;
	
	return true;
}

bool metalSlug::Collision::IsOverlapRectToRect(Rect inRect)
{
	double xx = (inRect.GetLeft() + (inRect.GetRight() - inRect.GetLeft()) / 2) - (rect.X + rect.Width / 2);
	double yy = (inRect.GetTop() + (inRect.GetBottom() - inRect.GetTop()) / 2) - (rect.Y + rect.Height / 2);
	xx = sqrt(xx * xx);
	yy = sqrt(yy * yy);

	if (xx >= ((inRect.GetRight() - inRect.GetLeft()) / 2) + (rect.Width / 2)) return false;
	if (yy >= ((inRect.GetBottom() - inRect.GetTop()) / 2) + (rect.Height / 2)) return false;

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

bool const metalSlug::Collision::IsInRange(Rect inRect)
{
	switch (collisionType)
	{
	case CRect:
	{
		int maxX = rect.X + rect.Width;
		int minX = rect.X;
		int maxY = rect.Y + rect.Height;
		int minY = rect.Y;

		if (inRect.GetRight() < minX || inRect.GetLeft() > maxX) return false;
		if (inRect.GetBottom() < minY || inRect.GetTop() > maxY) return false;
		return true;
	}
		break;
	default:
		return false;
	}
}
