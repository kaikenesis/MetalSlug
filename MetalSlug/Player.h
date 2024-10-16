#pragma once

namespace metalSlug
{
#define JUMP_HEIGHT 15
#define COLLISION_IDLE_X 20
#define COLLISION_IDLE_Y 35
#define COLLISION_JUMPING_OFFSET_Y -6
#define COLLISION_CROUCH_X 20
#define COLLISION_CROUCH_Y 24

	class Player
	{
	public:
		Player();
		~Player();

	private:
		PointF playerPos = { 0,350 };
		int playerSpeed = 4;
		int axisValue_x = 0;
		int axisValue_y = 0;
		float jumpValue_y = JUMP_HEIGHT;
		float gravity = 0.98f;
		int jumpStartY = 0;

		bool bJumping = false;
		bool bJumpIdle = false; // ¸ØÃá»óÅÂ·Î Á¡ÇÁÇß´ÂÁö

		bool bCtrlKeyPressed = false;
		bool bLShiftKeyPressed = false;
		bool bUpKeyPressed = false;
		bool bDownKeyPressed = false;

		PlayerDir pDir = Right;
		PlayerState state = Idle;
		CharacterType characterType = Eri;
		class AnimEri* animEri;
		class Collision* collision;
		Rect collisionBox;
		INT collisionOffsetX = 7;
	
	public:
		void Update();
		void InputKey();

		void InitPlayerImage();

		PointF const GetPlayerPos() { return playerPos; }
		int const GetAxisX() { return axisValue_x; }
		int const GetAxisY() { return axisValue_y; }
		PlayerDir const GetDirection(){ return pDir; }
		Rect const GetCollisionBox() { return collisionBox; }
		class Collision* GetCollider() { return collision; }
		Rect const GetCollisionBoxWorldPos();

		BOOL IsCanMove(int posX);

		void UpdatePlayerPos(int axisX, int axisY, int speed);
		void PlayAnimation(Graphics* graphics);
		void PlayDebugAnimation(Graphics* graphics);
		void PlayEriAnimation(Graphics* graphics);
	};
}

