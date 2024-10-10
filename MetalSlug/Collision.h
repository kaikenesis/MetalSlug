#pragma once

namespace metalSlug
{
	class Collision
	{
	private:
		Rect collisionBox;

	public:
		Collision();
		Collision(INT posX, INT posY, int inWidth, int inHeight);
		~Collision();

		Rect const GetCollisionBox() { return collisionBox; }
		void UpdateCollisionBox(INT posX, INT posY, int inWidth, int inHeight);
	};
}

