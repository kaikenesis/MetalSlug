#include "framework.h"
#include "Game.h"
#include "AnimEri.h"
#include "Collision.h"
#include "Geometry.h"
#include "Player.h"

using namespace metalSlug;

metalSlug::Player::Player()
{
    InitPlayerImage();
    gravity *= GetGlobalRatio();
    jumpValue_y *= GetGlobalRatio();
    playerSpeed *= GetGlobalRatio();
    collisionOffsetX *= GetGlobalRatio();
    int w = COLLISION_IDLE_X * GetGlobalRatio();
    int h = COLLISION_IDLE_Y * GetGlobalRatio();
    collision = new Collision((INT)playerImgPos.X + collisionOffsetX, (INT)playerImgPos.Y, w, h, ObjectType::CLocal);
}

metalSlug::Player::~Player()
{
    delete collision;
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
                jumpValue_y = JUMP_HEIGHT * GetGlobalRatio();
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

void metalSlug::Player::InitPlayerImage()
{
    animEri = new AnimEri();
    animEri->SetImageRatio(GetGlobalRatio());
}

bool metalSlug::Player::IsCanMove(int posX)
{
    if (posX < 0) return false;

    return true;
}

bool metalSlug::Player::IsInAir(POINT inPoint)
{
    std::vector<Collision*> collisions = GetGeometry()->GetGeometryCollisions();
    for (int i = 0; i < collisions.size(); i++)
    {
        if (collisions[i]->IsContain(inPoint) == true) return false;
    }

    if (bJumping == false)
    {
        if (axisValue_x == 0) bJumpIdle = true;
        else bJumpIdle = false;
        jumpValue_y = gravity;
        bJumping = true;
        bLShiftKeyPressed = true;
    }

    return true;
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
            if (animEri->IsShoot() == true) animEri->SetCrouchLoop(true);
            speed -= (2 * GetGlobalRatio());

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

    double width = GetCamera()->GetWidth();
    RECT rtView = GetCamera()->GetCameraViewport();
    if (width / 2 - (playerPos.X + axisX * speed) <= 0)
    {
        GetCamera()->UpdatePosition(rtView.left + (axisX * speed), rtView.top);
    }
    else
    {
        if (IsCanMove(playerPos.X + axisX * speed - collision->GetWidth() / 2) == true)
            playerImgPos.X += axisX * speed;
    }
    //playerPos.Y += axisY * speed;

    UpdatePositionY(playerPos.X, playerPos.Y + gravity);
    //if (bJumping)
    //{
    //    // 떨어질때 충돌처리가 된 Polygon의 y top위치에 멈출수 있도록 함
    //    
    //    POINT point = { playerPos.X,playerPos.Y - jumpValue_y };
    //    if (IsInAir(point) == true)    
    //    {
    //        playerImgPos.Y -= jumpValue_y;
    //    }
    //    else
    //    {
    //        while (1)
    //        {
    //            jumpValue_y++;
    //            POINT p = { playerPos.X,playerPos.Y - jumpValue_y };
    //            if (IsInAir(p) == true)
    //            {
    //                jumpValue_y++;
    //                playerImgPos.Y -= jumpValue_y;
    //                break;
    //            }
    //        }
    //        animEri->ResetFrame();
    //        bJumping = false;
    //    }
    //    if (jumpValue_y > -(JUMP_HEIGHT * GetGlobalRatio()))
    //        jumpValue_y -= gravity;
    //}

    if (animEri->IsCrouch() == true)
    {
        int w = COLLISION_CROUCH_X * GetGlobalRatio();
        int h = COLLISION_CROUCH_Y * GetGlobalRatio();
        int offsetY = (COLLISION_IDLE_Y - COLLISION_CROUCH_Y) * GetGlobalRatio();
        collision->UpdateLocalLocation(playerImgPos.X+ collisionOffsetX, playerImgPos.Y + offsetY);
        collision->UpdateLocalScale(w, h);
    }
    else if (bJumping == true)
    {
        int w = COLLISION_IDLE_X * GetGlobalRatio();
        int h = COLLISION_IDLE_Y * GetGlobalRatio();
        collision->UpdateLocalLocation(playerImgPos.X + collisionOffsetX, playerImgPos.Y);
        collision->UpdateLocalScale(w, h);
    }
    else
    {
        int w = COLLISION_IDLE_X * GetGlobalRatio();
        int h = COLLISION_IDLE_Y * GetGlobalRatio();
        collision->UpdateLocalLocation(playerImgPos.X + collisionOffsetX, playerImgPos.Y);
        collision->UpdateLocalScale(w, h);
    }

    collision->UpdateWorldLocation(rtView.left, rtView.top);
    playerPos = { (float)(collision->GetWorldRect().X + collision->GetWidth() / 2),(float)(collision->GetWorldRect().Y + collision->GetHeight()) };
}

void metalSlug::Player::UpdatePositionY(int posX, int posY)
{
    POINT point = { posX, posY };
    if (bJumping == false)
    {
        std::vector<Collision*> collisions = GetGeometry()->GetGeometryCollisions();
        for (int i = 0; i < collisions.size(); i++)
        {
            if (collisions[i]->IsInRange(point) == false) continue;
            if (collisions[i]->IsActive() == false) continue;
            playerImgPos.Y = (collisions[i]->GetWolrdPositionY(point.x) - 105);
        }
    }
    else
    {
        // 떨어질때 충돌처리가 된 Polygon의 y top위치에 멈출수 있도록 함

        POINT point = { playerPos.X,playerPos.Y - jumpValue_y };
        if (IsInAir(point) == true)
        {
            playerImgPos.Y -= jumpValue_y;
        }
        else
        {
            animEri->ResetFrame();
            bJumping = false;
        }

        if (jumpValue_y > -(JUMP_HEIGHT * GetGlobalRatio()))
            jumpValue_y -= gravity;
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

    animEri->AniEriIdle(graphics, PointF(100 * GetGlobalRatio(), 100), NULL, 0, animEri->IsFlip());
    animEri->AniEriJumpIdle(graphics, PointF(150 * GetGlobalRatio(), 100), NULL, 0, animEri->IsFlip());
    animEri->AniEriJumpRun(graphics, PointF(200 * GetGlobalRatio(), 100), NULL, 0, animEri->IsFlip());
    animEri->AniEriStop(graphics, PointF(250 * GetGlobalRatio(), 100), NULL, 0, animEri->IsFlip());
    animEri->AniEriRun(graphics, PointF(300 * GetGlobalRatio(), 100), NULL, 0, animEri->IsFlip());
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
                animEri->AniEriJumpIdle(graphics, GetPlayerImgPos(), NULL, 0, animEri->IsFlip());
            else
                animEri->AniEriJumpRun(graphics, GetPlayerImgPos(), NULL, 0, animEri->IsFlip());
        }
        else
        {
            animEri->AniEriIdle(graphics, GetPlayerImgPos(), NULL, 0, animEri->IsFlip());
        }
    }
    else
    {
        if (bJumping)
        {
            if(bJumpIdle)
                animEri->AniEriJumpIdle(graphics, GetPlayerImgPos(), NULL, 0, animEri->IsFlip());
            else
                animEri->AniEriJumpRun(graphics, GetPlayerImgPos(), NULL, 0, animEri->IsFlip());
        }
        else
        {
            animEri->AniEriRun(graphics, GetPlayerImgPos(), NULL, 0, animEri->IsFlip());
        }
    }
}