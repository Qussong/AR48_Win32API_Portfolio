#include "vanCamera.h"
#include "vanApplication.h"
#include "vanTransform.h"


extern van::Application application;	// Client.cpp�� ����Ǿ� �ִ� ��������������

namespace van
{
	math::Vector2 Camera::mResolution = math::Vector2::Zero;
	math::Vector2 Camera::mLookPosition = math::Vector2::Zero;
	math::Vector2 Camera::mDistance = math::Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	void Camera::Init()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = mResolution / 2.0f;
	}
	void Camera::Update()
	{
		if (mTarget)	// Camera�� �Ĵٺ� Target�� ������ ��
		{
			Transform* tr = mTarget->GetComponent<Transform>();	// Target�� ��ġ���� �����´�
			mLookPosition = tr->GetPosition();					// ī�޶� �Ĵٺ�����ġ�� ����
		}

		mDistance = mLookPosition - (mResolution / 2.0f);		// ī�޶� ���� ��ġ ����
	}
}