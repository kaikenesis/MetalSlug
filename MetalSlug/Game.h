#pragma once

#include "framework.h"

namespace metalSlug
{
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

	enum CharacterType
	{
		Eri,
	};

	void CreateObject();
	void UpdateObject();
	void DrawObject(Graphics* graphics);
	void DeleteObject();
}
