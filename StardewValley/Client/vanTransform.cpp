#include "vanTransform.h"
#include "vanInput.h"
#include "vanTime.h"

namespace van
{
	Transform::Transform()
		: Component(enums::eComponentType::Transform)
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Init()
	{
		// nothing
	}
	void Transform::Update()
	{
		// Ű �Է�
		if (Input::GetKey(eKeyCode::W))	// ��
		{
			if (mPosition.y > 0)
				mPosition.y -= SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::S))	// ��
		{
			if (mPosition.y < FHD_Y - DIAMETER)
				mPosition.y += SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::A))	// ��
		{
			if (mPosition.x > 0)
				mPosition.x -= SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::D))	// ��
		{
			if (mPosition.x < FHD_X - DIAMETER)
				mPosition.x += SPEED * Time::DeltaTime();
			else
				__noop;
		}
	}
	void Transform::Render(HDC _hdc)
	{
		// nothing
	}
	void Transform::SetPosition(math::Vector2 position)
	{
		mPosition = position;
	}
	math::Vector2 Transform::GetPosition()
	{
		return mPosition;
	}
}