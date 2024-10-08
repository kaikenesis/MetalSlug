#include "framework.h"
#include "Game.h"
#include "Player.h"
#include "AnimEri.h"

using namespace metalSlug;

metalSlug::Player::Player()
{
    animEri = new AnimEri();
}

metalSlug::Player::~Player()
{
}

void metalSlug::Player::Update()
{
    InputKey();
}

void metalSlug::Player::InputKey()
{
    axisValue_x = 0;
    axisValue_y = 0;

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        axisValue_x--;
        if (axisValue_x < 1) axisValue_x = -1;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        axisValue_x++;
        if (axisValue_x > 1) axisValue_x = 1;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000) // 위 방향키를 뗏을때 lookup frame만 따로 초기화로 변경 필요
    {
        axisValue_y--;
        if (axisValue_y < -1) axisValue_y = -1;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        axisValue_y++;
        if (axisValue_y > 1) axisValue_y = 1;
    }

    if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
    {
        if (bCtrlKeyPressed == false)
        {
            if (animEri->IsCanShoot())
            {
                animEri->PlayShootAnim();
            }

            bCtrlKeyPressed = true;
        }
    }
    else
    {
        if (bCtrlKeyPressed == true)
        {
            bCtrlKeyPressed = false;
        }
    }

    if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
    {
        if (bLShiftKeyPressed == false)
        {
            if (bJumping == false)
            {
                if (axisValue_x == 0) bJumpIdle = true;
                else bJumpIdle = false;
                jumpStartY = playerPos.Y;
            }

            bJumping = true;
            bLShiftKeyPressed = true;
        }
    }
    else
    {
        if (bLShiftKeyPressed == true)
        {
            

            bLShiftKeyPressed = false;
        }
    }

    UpdatePlayerPos(axisValue_x, axisValue_y, playerSpeed);
}

PointF const metalSlug::Player::GetPlayerPos()
{
	return playerPos;
}

int const metalSlug::Player::GetAxisX()
{
	return axisValue_x;
}

int const metalSlug::Player::GetAxisY()
{
	return axisValue_y;
}

PlayerDir const metalSlug::Player::GetDirection()
{
	return pDir;
}

void metalSlug::Player::UpdatePlayerPos(int axisX, int axisY, int speed)
{
    if (axisX < 0 && pDir != Left)
    {
        if (bJumping == false || (bJumping == true && animEri->IsShoot() == true))
        {
            animEri->SetCanFlip(true);
            pDir = Left;
        }
        
        if (animEri->IsCrouch() == true && animEri->IsShoot() == true)
        {
            animEri->SetCanFlip(true);
            pDir = Left;
        }
    }
    else if (axisX > 0 && pDir != Right)
    {
        if (bJumping == false || (bJumping == true && animEri->IsShoot() == true))
        {
            animEri->SetCanFlip(true);
            pDir = Right;
        }
        
        if (animEri->IsCrouch() == true && animEri->IsShoot() == true)
        {
            animEri->SetCanFlip(true);
            pDir = Right;
        }
    }

    if (animEri->IsCrouch() == true && animEri->IsShoot() == true) axisX = 0;

    if (axisY < 0)
    {
        animEri->SetLookUp(true);
        if (animEri->IsCrouch() == true)
        {
            animEri->ResetFrame();
            animEri->SetCrouch(false);
            animEri->SetCrouchLoop(false);
        }

        animEri->SetPressedLookDown(false);
    }
    else if (axisY > 0)
    {
        if (bJumping == true)
        {
            animEri->SetPressedLookDown(true);
            animEri->SetLookDown(true);
            
            if (animEri->IsLookUp() == true)
            {
                animEri->ResetFrame();
                animEri->SetLookUp(false);
                animEri->SetLookUpLoop(false);
            }
            
            if (animEri->IsCrouch() == true)
            {
                animEri->ResetFrame();
                animEri->SetCrouch(false);
                animEri->SetCrouchLoop(false);
            }
        }
        else
        {
            animEri->SetCrouch(true);
            speed -= 2;

            if (animEri->IsLookUp() == true)
            {
                animEri->ResetFrame();
                animEri->SetLookUp(false);
                animEri->SetLookUpLoop(false);
            }

            animEri->SetPressedLookDown(false);
        }
    }
    else
    {
        if (animEri->IsLookUp() == true)
        {
            animEri->ResetFrame();
            animEri->SetLookUp(false);
            animEri->SetLookUpLoop(false);
        }

        if (animEri->IsCrouch() == true)
        {
            animEri->ResetFrame();
            animEri->SetCrouch(false);
            animEri->SetCrouchLoop(false);
        }

        animEri->SetPressedLookDown(false);
    }

    playerPos.X += axisX * speed;
    //playerPos.Y += axisY * speed;

    

    if (bJumping)
    {
        // 현재는 지형에 올라가는걸 신경쓰지 않고, 점프할때 시작 높이까지만 이동함
        jumpValue_y -= gravity;
        if ((playerPos.Y - jumpValue_y) < jumpStartY)
            playerPos.Y -= jumpValue_y;
        else
        {
            playerPos.Y = jumpStartY;
            animEri->ResetFrame();
            bJumping = false;
            jumpValue_y = JUMP_HEIGHT;
        }
    }
}

void metalSlug::Player::PlayAnimation(Graphics* graphics)
{
    switch (characterType)
    {
    case Eri:
    {
        PlayEriAnimation(graphics);
        break;
    }
    default: break;
    }
}

void metalSlug::Player::PlayDebugAnimation(Graphics* graphics)
{
    if (animEri->IsCanFlip() == true)
    {
        animEri->FlipXBitmap();
    }

    animEri->AniEriIdle(graphics, PointF(100, 100), NULL, 0, animEri->IsFlip());
    animEri->AniEriJumpIdle(graphics, PointF(150, 100), NULL, 0, animEri->IsFlip());
    animEri->AniEriJumpRun(graphics, PointF(200, 100), NULL, 0, animEri->IsFlip());
    animEri->AniEriStop(graphics, PointF(250, 100), NULL, 0, animEri->IsFlip());
    animEri->AniEriRun(graphics, PointF(300, 100), NULL, 0, animEri->IsFlip());
}

void metalSlug::Player::PlayEriAnimation(Graphics* graphics)
{
    if (animEri->IsCanFlip() == true)
    {
        animEri->FlipXBitmap();
    }

    if (GetAxisX() == 0)
    {
        if (bJumping)
        {
            if (bJumpIdle)
                animEri->AniEriJumpIdle(graphics, GetPlayerPos(), NULL, 0, animEri->IsFlip());
            else
                animEri->AniEriJumpRun(graphics, GetPlayerPos(), NULL, 0, animEri->IsFlip());
        }
        else
        {
            animEri->AniEriIdle(graphics, GetPlayerPos(), NULL, 0, animEri->IsFlip());
        }
    }
    else
    {
        if (bJumping)
        {
            if(bJumpIdle)
                animEri->AniEriJumpIdle(graphics, GetPlayerPos(), NULL, 0, animEri->IsFlip());
            else
                animEri->AniEriJumpRun(graphics, GetPlayerPos(), NULL, 0, animEri->IsFlip());
        }
        else
        {
            animEri->AniEriRun(graphics, GetPlayerPos(), NULL, 0, animEri->IsFlip());
        }
    }
}
