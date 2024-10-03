#pragma once

#include "framework.h"

enum PlayerDir
{
	Left,
	Right,
};

enum PlayerState
{
	Idle,
	Attack,
	Jump,
	Death,
};

void InputKey();

PointF const GetPlayerPos();
int const GetAxisX();
int const GetAxisY();
PlayerDir const GetDirection();

void UpdatePlayerPos(int axisX, int axisY, int speed);