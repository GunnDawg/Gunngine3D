#pragma once
#include <DirectXMath.h>

namespace G3D
{
	struct Camera
	{
		inline void Load();
		void Load(float x, float y, float z, float rX, float rY, float rZ);

		inline const DirectX::XMMATRIX& GetViewMatrix() const
		{
			return mViewMatrix;
		}

		inline const DirectX::XMMATRIX& GetProjectionMatrix() const
		{
			return mProjectionMatrix;
		}

		inline const DirectX::XMVECTOR& GetPositionVector() const
		{
			return mPosVector;
		}

		inline const DirectX::XMFLOAT3& GetCameraPos() const
		{
			return mPos;
		}

		inline const DirectX::XMVECTOR& GetRotationVector() const
		{
			return mRotVector;
		}

		inline const DirectX::XMFLOAT3& GetRotationFloat3() const
		{
			return mRot;
		}

		inline const DirectX::XMVECTOR& GetForwardVector() const
		{
			return vec_forward;
		}

		inline const DirectX::XMVECTOR& GetBackVector() const
		{
			return vec_backward;
		}

		inline const DirectX::XMVECTOR& GetLeftVector() const
		{
			return vec_left;
		}

		inline const DirectX::XMVECTOR& GetRightVector() const
		{
			return vec_right;
		}

		void SetPosition(const DirectX::XMVECTOR& pos);
		void SetPosition(float x, float y, float z);
		void AdjustPosition(const DirectX::XMVECTOR& pos);
		void AdjustPosition(float x, float y, float z);
		void ResetLastLoadPosition();
		void SetRotation(const DirectX::XMVECTOR& rot);
		void SetRotation(float x, float y, float z);
		void AdjustRotation(const DirectX::XMVECTOR& rot);
		void AdjustRotation(float x, float y, float z);
		//void SetLookAtPos(DirectX::XMFLOAT3 lookAtPos);

	private:
		void UpdateViewMatrix();

		const DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		const DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		const DirectX::XMVECTOR DEFAULT_BACKWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
		const DirectX::XMVECTOR DEFAULT_LEFT_VECTOR = DirectX::XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
		const DirectX::XMVECTOR DEFAULT_RIGHT_VECTOR = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

		DirectX::XMVECTOR vec_forward;
		DirectX::XMVECTOR vec_left;
		DirectX::XMVECTOR vec_right;
		DirectX::XMVECTOR vec_backward;
		DirectX::XMVECTOR mPosVector;
		DirectX::XMVECTOR mRotVector;

		s32 defaultX = 0u;
		s32 defaultY = 0u;
		s32 defaultZ = 0u;
		DirectX::XMFLOAT3 mPos;

		u8 defaultRotX = 0u;
		u8 defaultRotY = 0u;
		u8 defaultRotZ = 0u;
		DirectX::XMFLOAT3 mRot;

		DirectX::XMMATRIX mViewMatrix;
		DirectX::XMMATRIX mProjectionMatrix;
		DirectX::XMMATRIX mVecRotationMatrix;
	};
}