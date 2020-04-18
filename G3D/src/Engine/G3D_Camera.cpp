#include "G3D_Camera.h"

using namespace DirectX;

namespace G3D
{
	Camera::Camera()
	{
		mPos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		mPosVector = DirectX::XMLoadFloat3(&mPos);
		mRot = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		mRotVector = DirectX::XMLoadFloat3(&mRot);

		UpdateViewMatrix();
	}

	void Camera::Load()
	{
		//@NOTE: We may need to remove the 'local_persist' / 'static' specifier from these values if we ever want to re-load
		//the camera or window in the future.
		local_persist float fovRadians = (Settings::Camera::FOV / 360.0f) * DirectX::XM_2PI;
		local_persist float aspectRatio = (static_cast<float>(Settings::Display::Width) / static_cast<float>(Settings::Display::Height));
		local_persist float nearZ = 0.1f;
		local_persist float farZ = Settings::Graphics::DrawDistance;

		mProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
	}

	void Camera::SetPosition(const DirectX::XMVECTOR& pos)
	{
		DirectX::XMStoreFloat3(&mPos, pos);
		mPosVector = pos;

		UpdateViewMatrix();
	}

	void Camera::SetPosition(float x, float y, float z)
	{
		mPos = DirectX::XMFLOAT3(x, y, z);
		mPosVector = DirectX::XMLoadFloat3(&mPos);

		UpdateViewMatrix();
	}

	void Camera::AdjustPosition(const DirectX::XMVECTOR& pos)
	{
		mPosVector += pos;
		DirectX::XMStoreFloat3(&mPos, mPosVector);

		UpdateViewMatrix();
	}

	void Camera::AdjustPosition(float x, float y, float z)
	{
		mPos.x += x;
		mPos.y += y;
		mPos.z += z;
		mPosVector = DirectX::XMLoadFloat3(&mPos);

		UpdateViewMatrix();
	}

	void Camera::SetRotation(const DirectX::XMVECTOR& rot)
	{
		mRotVector = rot;
		DirectX::XMStoreFloat3(&mRot, rot);

		UpdateViewMatrix();
	}

	void Camera::SetRotation(float x, float y, float z)
	{
		mRot = DirectX::XMFLOAT3(x, y, z);
		mRotVector = DirectX::XMLoadFloat3(&mRot);

		UpdateViewMatrix();
	}

	void Camera::AdjustRotation(const DirectX::XMVECTOR& rot)
	{
		mRotVector += rot;
		DirectX::XMStoreFloat3(&mRot, mRotVector);

		UpdateViewMatrix();
	}

	void Camera::AdjustRotation(float x, float y, float z)
	{
		mRot.x += x;
		mRot.y += y;
		mRot.z += z;
		mRotVector = DirectX::XMLoadFloat3(&mRot);

		UpdateViewMatrix();
	}

	void Camera::SetLookAtPos(DirectX::XMFLOAT3 lookAtPos)
	{
		if (lookAtPos.x == mPos.x && lookAtPos.y == mPos.y && lookAtPos.z == mPos.z)
			return;

		lookAtPos.x = mPos.x - lookAtPos.x;
		lookAtPos.y = mPos.y - lookAtPos.y;
		lookAtPos.z = mPos.z - lookAtPos.z;

		float pitch = 0.0f;
		if (lookAtPos.y != 0.0f)
		{
			const float distance = sqrt((double)lookAtPos.x * lookAtPos.x + (double)lookAtPos.z * lookAtPos.z);
			pitch = atan(lookAtPos.y / distance);
		}

		float yaw = 0.0f;
		if (lookAtPos.x != 0.0f)
			yaw = atan(lookAtPos.x / lookAtPos.z);

		if (lookAtPos.z > 0)
			yaw += XM_PI;

		SetRotation(pitch, yaw, 0.0f);
	}

	void Camera::UpdateViewMatrix()
	{
		//Calculate camera rotation matrix
		DirectX::XMMATRIX camRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(mRot.x, mRot.y, mRot.z);

		//Adjust cam target to be offset by the cameras current position
		DirectX::XMVECTOR camTarget = XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, camRotationMatrix);
		camTarget += mPosVector;

		//Calculate up direction based on current rotation
		DirectX::XMVECTOR upDir = DirectX::XMVector3TransformCoord(DEFAULT_UP_VECTOR, camRotationMatrix);

		//Rebuild view matrix
		mViewMatrix = DirectX::XMMatrixLookAtLH(mPosVector, camTarget, upDir);

		if (Settings::Camera::FreeRoam)
		{
			//@NOTE Use this for a more free-roam style camera.
			mVecRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(mRot.x, mRot.y, 0.0f);
		}
		else
		{
			//@NOTE: Use this for a more FPS style camera.
			mVecRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(0.0f, mRot.y, 0.0f);
		}

		vec_forward = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, mVecRotationMatrix);
		vec_backward = DirectX::XMVector3TransformCoord(DEFAULT_BACKWARD_VECTOR, mVecRotationMatrix);
		vec_left = DirectX::XMVector3TransformCoord(DEFAULT_LEFT_VECTOR, mVecRotationMatrix);
		vec_right = DirectX::XMVector3TransformCoord(DEFAULT_RIGHT_VECTOR, mVecRotationMatrix);
	}
}