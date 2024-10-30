#include "framework.h"
#include "AnimEri.h"
#include "Collision.h"
#include "Geometry.h"
#include "WeaponSFX.h"
#include "Bullet.h"
#include "Player.h"

metalSlug::Player::Player()
{
    Init();
}

metalSlug::Player::~Player()
{
    delete collision;
}

void metalSlug::Player::Update()
{
    if (bActive == false) return;

    InputKey();
    ActivateProjectile();
}

void metalSlug::Player::Init()
{
    ratio = GetGlobalRatio();

    playerLocalPos = playerWorldPos;
    InitPlayerImage();
    gravity *= ratio;
    jumpValue_y *= ratio;
    playerSpeed *= ratio;
    collisionOffsetX *= ratio;
    int w = COLLISION_IDLE_X * ratio;
    int h = COLLISION_IDLE_Y * ratio;
    collision = new Collision((INT)playerWorldPos.X - w / 2, (INT)playerWorldPos.Y - h / 2, w, h, ERenderType::RWorld);
    bAlive = true;
    bActive = true;
}

void metalSlug::Player::InputKey()
{
    if (bAlive == false) return;

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
                jumpValue_y = JUMP_HEIGHT * ratio;
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

    UpdateLocation(axisValue_x, axisValue_y, playerSpeed);
}

void metalSlug::Player::InitPlayerImage()
{
    playerImgPos = { playerLocalPos.X,playerLocalPos.Y };
    animEri = new AnimEri();
    animEri->SetImageRatio(ratio);
}

bool metalSlug::Player::IsCanMove(int posX)
{
    if (posX < 0) return false;

    return true;
}

bool metalSlug::Player::IsInAir(POINT inPoint, float& outPosY)
{
    std::vector<Collision*> collisions = GetGeometry()->GetGeometryCollisions();
    for (int i = 0; i < collisions.size(); i++)
    {
        outPosY = collisions[i]->GetWolrdPositionY(inPoint.x, inPoint.y);
        if (collisions[i]->IsContain(inPoint) == true) return false;
        if (collisions[i]->IsContain(collision->GetLocalRect()) == true) return false;
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

PointF const metalSlug::Player::GetLocalPlayerPos()
{
    PointF point;
    point.X = playerWorldPos.X - GetCamera()->GetCameraViewport().left;
    point.Y = playerWorldPos.Y - GetCamera()->GetCameraViewport().top;

    return point;
}

void metalSlug::Player::UpdateLocation(int axisX, int axisY, int speed)
{
    if (axisX < 0 && pDir != EPlayerDir::Left)
    {
        if (bJumping == false || (bJumping == true && animEri->IsShoot() == true))
        {
            animEri->SetCanFlip(true);
            pDir = EPlayerDir::Left;
        }
        
        if (animEri->IsCrouch() == true && animEri->IsShoot() == true)
        {
            animEri->SetCanFlip(true);
            pDir = EPlayerDir::Left;
        }
    }
    else if (axisX > 0 && pDir != EPlayerDir::Right)
    {
        if (bJumping == false || (bJumping == true && animEri->IsShoot() == true))
        {
            animEri->SetCanFlip(true);
            pDir = EPlayerDir::Right;
        }
        
        if (animEri->IsCrouch() == true && animEri->IsShoot() == true)
        {
            animEri->SetCanFlip(true);
            pDir = EPlayerDir::Right;
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
            speed -= (2 * ratio);

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
    if (width / 2 - (playerLocalPos.X + +axisX * speed) <= 0)
    {
        GetCamera()->UpdatePosition(rtView.left + (axisX * speed), rtView.top);
        playerWorldPos.X += axisX * speed;
    }
    else
    {
        if (IsCanMove(playerLocalPos.X + axisX * speed - collision->GetWidth() / 2) == true)
            playerWorldPos.X += axisX * speed;
    }

    UpdatePositionX(playerWorldPos.X, playerWorldPos.Y, axisX, speed);
    UpdatePositionY(playerWorldPos.X, playerWorldPos.Y + gravity);

    if (animEri->IsCrouch() == true)
    {
        int w = COLLISION_CROUCH_X * ratio;
        int h = COLLISION_CROUCH_Y * ratio;
        collision->UpdateWorldLocation(playerWorldPos.X - w / 2, playerWorldPos.Y - h / 2);
        collision->UpdateWorldScale(w, h);
        collision->UpdateLocalScale(w, h);
    }
    else if (bJumping == true)
    {
        int w = COLLISION_IDLE_X * ratio;
        int h = COLLISION_IDLE_Y * ratio;
        collision->UpdateWorldLocation(playerWorldPos.X  - w / 2, playerWorldPos.Y - h / 2);
        collision->UpdateWorldScale(w, h);
        collision->UpdateLocalScale(w, h);
    }
    else
    {
        int w = COLLISION_IDLE_X * ratio;
        int h = COLLISION_IDLE_Y * ratio;
        collision->UpdateWorldLocation(playerWorldPos.X  - w / 2, playerWorldPos.Y - h / 2);
        collision->UpdateWorldScale(w, h);
        collision->UpdateLocalScale(w, h);
    }

    collision->UpdateLocalLocation(rtView.left, rtView.top);

    UpdatePos();
}

void metalSlug::Player::PlayAnimation(Graphics* graphics)
{
    switch (characterType)
    {
    case ECharacterType::Eri:
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

    animEri->AniEriIdle(graphics, PointF(100 * ratio, 100), NULL, 0, animEri->IsFlip());
    animEri->AniEriJumpIdle(graphics, PointF(150 * ratio, 100), NULL, 0, animEri->IsFlip());
    animEri->AniEriJumpRun(graphics, PointF(200 * ratio, 100), NULL, 0, animEri->IsFlip());
    animEri->AniEriStop(graphics, PointF(250 * ratio, 100), NULL, 0, animEri->IsFlip());
    animEri->AniEriRun(graphics, PointF(300 * ratio, 100), NULL, 0, animEri->IsFlip());
}

void metalSlug::Player::TakeDamage()
{
    bAlive = false;
    bActive = false;
    collision->SetActive(false);
}

void metalSlug::Player::Activate()
{
    RECT rt = GetCamera()->GetCameraViewport();
    PointF point = { (float)rt.left + 200, 0.0f };

    playerWorldPos = point;
    bActive = true;
    bAlive = true;
    collision->SetActive(true);
}

void metalSlug::Player::ActivateProjectile()
{
    if (bAlive == false) return;
    if (animEri->IsCanSpawnProjectile() == false) return;

    SetInfoPistol();
    animEri->FinishSpawnProjectile();
}

void metalSlug::Player::UpdatePositionX(int posX, int posY, int axisX, int speed)
{
    std::vector<Collision*> collisions = GetGeometry()->GetGeometryCollisions();
    Rect collisionRect = { collision->GetWorldRect().X + axisX * speed,collision->GetWorldRect().Y,
        collision->GetWorldRect().Width,collision->GetWorldRect().Height };

    for (int i = 0; i < collisions.size(); i++)
    {
        if (collisions[i]->IsActive() == false) continue;
        if (collisions[i]->IsContain(collisionRect) == true)
        {
            if (posX < collisions[i]->GetWorldRect().GetLeft())
                playerWorldPos.X = collisions[i]->GetWorldRect().GetLeft() - collision->GetWidth() / 2;
            else
                playerWorldPos.X = collisions[i]->GetWorldRect().GetRight() + collision->GetWidth() / 2;
            return;
        }
    }
}

void metalSlug::Player::UpdatePositionY(int posX, int posY)
{
    if (bJumping == false)
    {
        POINT point = { posX,posY + collision->GetHeight() / 2 - jumpValue_y };
        float posY = 0.0f;
        if (IsInAir(point, posY) == false)
        {
            std::vector<Collision*> collisions = GetGeometry()->GetGeometryCollisions();
            for (int i = 0; i < collisions.size(); i++)
            {
                if (collisions[i]->IsActive() == false) continue;
                if (collisions[i]->IsInRange(point) == false) continue;
                playerWorldPos.Y = (collisions[i]->GetWolrdPositionY(point.x, point.y) - (collision->GetHeight() / 2 + 1));
            }
        }
    }
    else
    {
        // 떨어질때 충돌처리가 된 Polygon의 y top위치에 멈출수 있도록 함

        POINT point = { posX,posY + collision->GetHeight() / 2 - jumpValue_y };
        float posY = 0.0f;
        if (IsInAir(point, posY) == true)
        {
            playerWorldPos.Y -= jumpValue_y;
        }
        else
        {
            playerWorldPos.Y = posY - (collision->GetHeight() / 2 + 1);
            animEri->ResetFrame();
            bJumping = false;
        }

        if (jumpValue_y > -(JUMP_HEIGHT * ratio))
            jumpValue_y -= gravity;
    }
}

void metalSlug::Player::UpdatePos()
{
    playerLocalPos.X = playerWorldPos.X - (float)GetCamera()->GetCameraViewport().left;
    playerLocalPos.Y = playerWorldPos.Y - (float)GetCamera()->GetCameraViewport().top;
    if (animEri->IsCrouch() == true)
    {
        playerImgPos.X = playerLocalPos.X + (float)IMGPOSX_OFFSET;
        playerImgPos.Y = playerLocalPos.Y + (float)IMGPOSY_OFFSET - collision->GetHeight() / 4;
    }
    else
    {
        playerImgPos.X = playerLocalPos.X + (float)IMGPOSX_OFFSET;
        playerImgPos.Y = playerLocalPos.Y + (float)IMGPOSY_OFFSET;
    }
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

void metalSlug::Player::SetInfoPistol()
{
    PointF axis;
    POINT collisionOffset = { 0,-3 };
    POINT imgOffset;

    std::vector<Bullet*> bullets = GetPlayerProjectiles();
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->IsActive() == false)
        {
            if (animEri->IsFlip() == false)
            {
                if (animEri->IsLookUp() == true)
                {
                    imgOffset = { 2,-114 };
                    axis = { 0.0f,-1.0f };

                    bullets[i]->Activate(playerWorldPos.X + imgOffset.x, playerWorldPos.Y + imgOffset.y,
                        axis, collisionOffset, EWeaponType::Pistol);
                    
                }
                else if (animEri->IsCrouch() == true)
                {
                    imgOffset = { 86,-10 };
                    axis = { 1.0f,0.0f };

                    bullets[i]->Activate(playerWorldPos.X + imgOffset.x, playerWorldPos.Y + imgOffset.y,
                        axis, collisionOffset, EWeaponType::Pistol);
                }
                else if (bJumping == true && animEri->IsLookDown() == true)
                {
                    imgOffset = { 10,80 };
                    axis = { 0.0f,1.0f };

                    bullets[i]->Activate(playerWorldPos.X + imgOffset.x, playerWorldPos.Y + imgOffset.y,
                        axis, collisionOffset, EWeaponType::Pistol);
                }
                else
                {
                    imgOffset = { 86,-26 };
                    axis = { 1.0f,0.0f };

                    bullets[i]->Activate(playerWorldPos.X + imgOffset.x, playerWorldPos.Y + imgOffset.y,
                        axis, collisionOffset, EWeaponType::Pistol);
                }
            }
            else
            {
                if (animEri->IsLookUp() == true)
                {
                    imgOffset = { -2,-114 };
                    axis = { 0.0f,-1.0f };

                    bullets[i]->Activate(playerWorldPos.X + imgOffset.x, playerWorldPos.Y + imgOffset.y,
                        axis, collisionOffset, EWeaponType::Pistol);
                    
                }
                else if (animEri->IsCrouch() == true)
                {
                    imgOffset = { -86,-10 };
                    axis = { -1.0f,0.0f };

                    bullets[i]->Activate(playerWorldPos.X + imgOffset.x, playerWorldPos.Y + imgOffset.y,
                        axis, collisionOffset, EWeaponType::Pistol);
                }
                else if (bJumping == true && animEri->IsLookDown() == true)
                {
                    imgOffset = { -12,80 };
                    axis = { 0.0f,1.0f };

                    bullets[i]->Activate(playerWorldPos.X + imgOffset.x, playerWorldPos.Y + imgOffset.y,
                        axis, collisionOffset, EWeaponType::Pistol);
                }
                else
                {
                    imgOffset = { -86,-26 };
                    axis = { -1.0f,0.0f };

                    bullets[i]->Activate(playerWorldPos.X + imgOffset.x, playerWorldPos.Y + imgOffset.y,
                        axis, collisionOffset, EWeaponType::Pistol);
                }
            }
            break;
        }
    }
}
