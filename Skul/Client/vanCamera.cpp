#include "vanCamera.h"
#include "vanApplication.h"
#include "vanTransform.h"

#define CAMERA_SPEED			500.0f
#define CAMERA_OFFSET_SPEED		10.0f	// Camera�� offset ���� 10�� ������ �����Ѵ�.

extern van::Application application;	// Client.cpp�� ����Ǿ� �ִ� ��������������

namespace van
{

	math::Vector2 Camera::mResolution = math::Vector2::Zero;
	math::Vector2 Camera::mLookPosition = math::Vector2::Zero;
	math::Vector2 Camera::mDistance = math::Vector2::Zero;
	math::Vector2 Camera::mCameraOffset = math::Vector2::Zero;

	GameObject* Camera::mTarget = nullptr;

	math::Vector2 Camera::mWidthLimit = math::Vector2::Zero;
	math::Vector2 Camera::mHeightLimit = math::Vector2::Zero;

	void Camera::Init()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = mResolution / 2.0f;
	}

	void Camera::Update()
	{
		// ī�޶� �Ĵٺ� Ÿ���� �����ϸ� �ش� Ÿ���� ����ٴѴ�.
		if (mTarget)	
		{
			Transform* tr = mTarget->GetComponent<Transform>();		// Target�� ��ġ���� �����´�
			mLookPosition = (tr->GetPosition()) + mCameraOffset;	// ī�޶� �Ĵٺ�����ġ�� ����
		}
		// ī�޶��� Ÿ���� ���ٸ� ī�޶� ������ �� �ִ�.
		else
		{
			if (Input::GetKey(eKeyCode::Up))
			{
				mLookPosition.y -= CAMERA_SPEED * Time::GetDeltaTime();
			}
			if (Input::GetKey(eKeyCode::Left))
			{
				mLookPosition.x -= CAMERA_SPEED * Time::GetDeltaTime();
			}
			if (Input::GetKey(eKeyCode::Down))
			{
				mLookPosition.y += CAMERA_SPEED * Time::GetDeltaTime();
			}
			if (Input::GetKey(eKeyCode::Right))
			{
				mLookPosition.x += CAMERA_SPEED * Time::GetDeltaTime();
			}
		}

		// ī�޶� Ÿ���� �߽����� ���� ���� �̵��� �Ÿ�
		mDistance = mLookPosition - (mResolution / 2.0f);		
		
		// [ ī�޶� �̵� ���� ]
		// ī�޶� �̹����� �Ѿ�� ������ ������ �ʰ��Ѵ�.
		// x��
		if (mDistance.x <= mWidthLimit.x)
		{
			mDistance.x = mWidthLimit.x;
		}
		if (mDistance.x >= mWidthLimit.y)
		{
			mDistance.x = mWidthLimit.y;
		}
		// y��
		if (mDistance.y <= mHeightLimit.x)
		{
			mDistance.y = mHeightLimit.x;
		}
		if (mDistance.y >= mHeightLimit.y)
		{
			mDistance.y = mHeightLimit.y;
		}
	}

	void Camera::SetCameraOffsetSmooth(math::Vector2 _offset, int _doubleSpeed)
	{
		bool flagX = true;
		bool flagY = true;

		// ���� offset ���� ��ǥġ offset ���� ���̰� 10���� ������ Ȯ��
		if (fabs(_offset.x - mCameraOffset.x) < 10.0f)
		{
			flagX = false;
		}
		if (fabs(_offset.y - mCameraOffset.y) < 10.0f)
		{
			flagY = false;
		}

		// offset x�� ����
		if (mCameraOffset.x != _offset.x)
		{
			if (_offset.x > 0 && flagX)
			{
				mCameraOffset.x += CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
			}
			else if (_offset.x < 0 && flagX)
			{
				mCameraOffset.x -= CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
			}
			else if (!flagX)
			{
				mCameraOffset.x = _offset.x;
			}
		}

		// offset y�� ����
		if (mCameraOffset.y != _offset.y)
		{
			if (_offset.y > 0 && flagY)
			{
				mCameraOffset.y += CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
			}
			else if (_offset.y < 0 && flagY)
			{
				mCameraOffset.y -= CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
			}
			else if (!flagY)
			{
				mCameraOffset.y = _offset.y;
			}
		}

	}

	void Camera::ClearCameraOffsetSmooth(int _doubleSpeed)
	{
		bool flagX = true;
		bool flagY = true;

		// offset ���� 10���� ������ Ȯ��
		if (fabs(mCameraOffset.x) < 10.0f)
		{
			flagX = false;
		}
		if (fabs(mCameraOffset.y) < 10.0f)
		{
			flagY = false;
		}

		// offset x�� ����
		if (mCameraOffset.x > 0
			&& flagX)
		{
			mCameraOffset.x -= CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
		}
		else if (mCameraOffset.x < 0
			&& flagX)
		{
			mCameraOffset.x += CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
		}
		else if (!flagX)
		{
			mCameraOffset.x = 0.0f;
		}

		// offset y�� ����
		if (mCameraOffset.y > 0
			&& flagY)
		{
			mCameraOffset.y -= CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
		}
		else if (mCameraOffset.y < 0
			&& flagY)
		{
			mCameraOffset.y += CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
		}
		else if (!flagY)
		{
			mCameraOffset.y = 0.0f;
		}
	}

}