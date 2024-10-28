#pragma once

namespace metalSlug
{
	class Player
	{
	public:
		Player();
		~Player();

	private:
#define JUMP_HEIGHT 14
#define COLLISION_IDLE_X 20
#define COLLISION_IDLE_Y 35
#define COLLISION_JUMPING_OFFSET_Y -6
#define COLLISION_CROUCH_X 20
#define COLLISION_CROUCH_Y 24

#define IMGPOSX_OFFSET -52
#define IMGPOSY_OFFSET -50

		PointF playerLocalPos;  // 화면상의 플레이어 중심 좌표
		PointF playerWorldPos = { 100,300 }; // 맵상의 플레이어 중심 좌표
		PointF playerImgPos;
		int playerSpeed = 3;
		int axisValue_x = 0;
		int axisValue_y = 0;
		float jumpValue_y = JUMP_HEIGHT;
		float gravity = 0.98f;
		float ratio;
		
		bool bJumping = false;
		bool bJumpIdle = false; // 멈춘상태로 점프했는지

		bool bCtrlKeyPressed = false;
		bool bLShiftKeyPressed = false;
		bool bUpKeyPressed = false;
		bool bDownKeyPressed = false;

		EPlayerDir pDir = Right;
		EPlayerState state = Idle;
		ECharacterType characterType = Eri;
		class AnimEri* animEri;
		class Collision* collision;
		INT collisionOffsetX = 7;
	
	public:
		void Update();

		PointF const GetPlayerImgPos() { return playerImgPos; }
		PointF const GetWorldPlayerPos() { return playerWorldPos; }
		PointF const GetLocalPlayerPos();
		int const GetAxisX() { return axisValue_x; }
		int const GetAxisY() { return axisValue_y; }
		EPlayerDir const GetDirection(){ return pDir; }
		class Collision* GetCollider() { return collision; }

		void UpdateLocation(int axisX, int axisY, int speed);
		void PlayAnimation(Graphics* graphics);
		void PlayDebugAnimation(Graphics* graphics);

		void ActivateProjectile();

	private:
		void InputKey();
		
		void InitPlayerImage();

		bool IsCanMove(int posX);
		bool IsInAir(POINT inPoint, float& outPosY);

		void UpdatePositionX(int posX, int posY, int axisX, int speed);
		void UpdatePositionY(int posX, int posY);
		void UpdatePos();
		void PlayEriAnimation(Graphics* graphics);
		void SetInfoPistol();
	};
}

