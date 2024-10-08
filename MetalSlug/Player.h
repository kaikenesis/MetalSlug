#pragma once



namespace metalSlug
{
#define JUMP_HEIGHT 15

	class Player
	{
	public:
		Player();
		~Player();

	private:
		PointF playerPos = { 100,170 };
		int playerSpeed = 4;
		int axisValue_x = 0;
		int axisValue_y = 0;
		float jumpValue_y = JUMP_HEIGHT;
		float gravity = 0.98f;
		int jumpStartY = 0;

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

	public:
		void Update();
		void InputKey();

		PointF const GetPlayerPos();
		int const GetAxisX();
		int const GetAxisY();
		PlayerDir const GetDirection();

		void UpdatePlayerPos(int axisX, int axisY, int speed);
		void PlayAnimation(Graphics* graphics);
		void PlayDebugAnimation(Graphics* graphics);
		void PlayEriAnimation(Graphics* graphics);
	};
}

