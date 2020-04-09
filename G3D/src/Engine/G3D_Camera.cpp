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

	void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
	{
		float fovRadians = (fovDegrees / 360.0f) * DirectX::XM_2PI;
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

	void Camera::UpdateViewMatrix()
	{
		//Calculate camera rotation matrix
		DirectX::XMMATRIX camRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(mRot.x, mRot.y, mRot.z);

		//Calculate unit vector of cam target based off camera forward value transformed by cam rotation.
		//DirectX::XMVECTOR camDir = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, camRotationMatrix);

		//Adjust cam target to be offset by the cameras current position
		DirectX::XMVECTOR camTarget = XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, camRotationMatrix);
		camTarget += mPosVector;

		//Calculate up direction based on current rotation
		DirectX::XMVECTOR upDir = DirectX::XMVector3TransformCoord(DEFAULT_UP_VECTOR, camRotationMatrix);

		//Rebuild view matrix
		mViewMatrix = DirectX::XMMatrixLookAtLH(mPosVector, camTarget, upDir);

		DirectX::XMMATRIX vecRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(0.0f, mRot.y, 0.0f);
		vec_forward = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
		vec_backward = DirectX::XMVector3TransformCoord(DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
		vec_left = DirectX::XMVector3TransformCoord(DEFAULT_LEFT_VECTOR, vecRotationMatrix);
		vec_right = DirectX::XMVector3TransformCoord(DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
	}
}