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

#define IMGPOSX_OFFSET -52
#define IMGPOSY_OFFSET -50

	class Player
	{
	public:
		Player();
		~Player();

	private:
		PointF playerLocalPos;  // 화면상의 플레이어 중심 좌표
		PointF playerWorldPos = { 100,300 }; // 맵상의 플레이어 중심 좌표
		PointF playerImgPos;
		int playerSpeed = 3;
		int axisValue_x = 0;
		int axisValue_y = 0;
		float jumpValue_y = JUMP_HEIGHT;
		float gravity = 0.98f;
		int jumpStartY = 0;
		float ratio;

		bool bJumping = false;
		bool bJumpIdle = false; // 멈춘상태로 점프했는지

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
		INT collisionOffsetX = 7;
	
	public:
		void Update();

		PointF const GetPlayerImgPos() { return playerImgPos; }
		PointF const GetWorldPlayerPos() { return playerWorldPos; }
		PointF const GetLocalPlayerPos();
		int const GetAxisX() { return axisValue_x; }
		int const GetAxisY() { return axisValue_y; }
		PlayerDir const GetDirection(){ return pDir; }
		class Collision* GetCollider() { return collision; }
		std::vector<class Bullet*> const GetBullets() { return bullets; }

		void UpdatePlayerPos(int axisX, int axisY, int speed);
		void UpdateBullets(HWND hWnd, HDC hdc);
		void PlayAnimation(Graphics* graphics);
		void PlayDebugAnimation(Graphics* graphics);

		void SetBullet();

	private:
		void InputKey();
		
		void InitPlayerImage();
		void CreateBullet();

		bool IsCanMove(int posX);
		bool IsInAir(POINT inPoint, float& outPosY);

		void UpdatePositionX(int posX, int posY, int axisX, int speed);
		void UpdatePositionY(int posX, int posY);
		void UpdatePos();
		void PlayEriAnimation(Graphics* graphics);
		void ActivatePistol();
	};
}

