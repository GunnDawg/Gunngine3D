#pragma once

struct Player
{
	void Load();
	void Update();

	u8 Health = 100;

	float MoveSpeed = Settings::Camera::CameraSpeed;
	bool isCrouched = false;
	bool isRunning = false;
};