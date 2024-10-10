#include "framework.h"
#include "Collision.h"

metalSlug::Collision::Collision()
{
	collisionBox = { 0,0,50,100 };
}

metalSlug::Collision::Collision(INT posX, INT posY, int inWidth, int inHeight)
{
	collisionBox = { posX,posY,inWidth,inHeight };
}

metalSlug::Collision::~Collision()
{
}

void metalSlug::Collision::UpdateCollisionBox(INT posX, INT posY, int inWidth, int inHeight)
{
	collisionBox = { posX,posY,inWidth,inHeight };
}
