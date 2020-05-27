#include "Player.h"

void Player::Load()
{
	MoveSpeed = Settings::Camera::CameraSpeed;
}

void Player::Update()
{
	if (isRunning)
	{
		MoveSpeed = Settings::Camera::CameraSpeed * 1.33f;
	}
	else
	{
		MoveSpeed = Settings::Camera::CameraSpeed;
	}
}