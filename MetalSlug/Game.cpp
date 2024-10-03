#include "Game.h"
#include "Bitmap.h"

int playerSpeed = 2;
PointF playerPos = { 100,200 };
int axisValue_x;
int axisValue_y;
PlayerDir pDir = Right;

void InputKey()
{
    DWORD newTime = GetTickCount();
    static DWORD oldTime = newTime;

    if (newTime - oldTime < 20)
        return;
    oldTime = newTime;

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
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        axisValue_y--;
        if (axisValue_y < -1) axisValue_y = -1;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        axisValue_y++;
        if (axisValue_y > 1) axisValue_y = 1;
    }

    UpdatePlayerPos(axisValue_x, axisValue_y, playerSpeed);
}

PointF const GetPlayerPos()
{
    return playerPos;
}

int const GetAxisX()
{
    return axisValue_x;
}

int const GetAxisY()
{
    return axisValue_y;
}

PlayerDir const GetDirection()
{
    return pDir;
}

void UpdatePlayerPos(int axisX, int axisY, int speed)
{
    if (axisX < 0 && pDir != Left)
    {
        SetFlip();
        pDir = Left;
    }
    else if (axisX > 0 && pDir != Right)
    {
        SetFlip();
        pDir = Right;
    }

    playerPos.X += axisX * speed;
    playerPos.Y += axisY * speed;
}
