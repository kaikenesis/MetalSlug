#pragma once

namespace metalSlug
{
#define JUMP_HEIGHT 15
#define COLLISION_IDLE_X 20
#define COLLISION_IDLE_Y 35
#define COLLISION_JUMPING_OFFSET_Y -6
#define COLLISION_CROUCH_X 20
#define COLLISION_CROUCH_Y 24
#define BULLET_COUNT 50

	class Player
	{
	public:
		Player();
		~Player();

	private:
		PointF playerImgPos = { 0,350 };
		PointF playerPos;
		int playerSpeed = 3;
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
		std::vector<class Bullet*> bullets;
		int ActiveBulletCount = 0;
		INT collisionOffsetX = 7;
	
	public:
		void Update();

		PointF const GetPlayerImgPos() { return playerImgPos; }
		PointF const GetWorldPlayerPos() { return playerPos; }
		int const GetAxisX() { return axisValue_x; }
		int const GetAxisY() { return axisValue_y; }
		PlayerDir const GetDirection(){ return pDir; }
		class Collision* GetCollider() { return collision; }
		std::vector<class Bullet*> const GetBullets() { return bullets; }
		int GetBulletCount() { return ActiveBulletCount; }

		PointF const GetLocalPlayerPos();

		void UpdatePlayerPos(int axisX, int axisY, int speed);
		void UpdatePositionY(int posX, int posY);
		void UpdateBullets(HWND hWnd, HDC hdc);
		void PlayAnimation(Graphics* graphics);
		void PlayDebugAnimation(Graphics* graphics);

		void ActivateBullet();

	private:
		void InputKey();
		
		void InitPlayerImage();
		void CreateBullet();

		bool IsCanMove(int posX);
		bool IsInAir(POINT inPoint, float& outPosY);

		void PlayEriAnimation(Graphics* graphics);
	};
}

