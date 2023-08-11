#include "vanCamera.h"
#include "vanApplication.h"
#include "vanTransform.h"

#define CAMERA_SPEED	500.0f

extern van::Application application;	// Client.cpp�� ����Ǿ� �ִ� ��������������

namespace van
{

	math::Vector2 Camera::mResolution = math::Vector2::Zero;
	math::Vector2 Camera::mLookPosition = math::Vector2::Zero;
	math::Vector2 Camera::mDistance = math::Vector2::Zero;
	math::Vector2 Camera::mWidthLimit = math::Vector2::Zero;
	math::Vector2 Camera::mHeightLimit = math::Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

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
			Transform* tr = mTarget->GetComponent<Transform>();	// Target�� ��ġ���� �����´�
			mLookPosition = tr->GetPosition();					// ī�޶� �Ĵٺ�����ġ�� ����
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
}