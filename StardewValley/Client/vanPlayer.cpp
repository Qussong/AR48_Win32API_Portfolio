#include "vanPlayer.h"
#include "vanInput.h"
#include "vanTransform.h"	// Update()���� Player ��ü�� ��ġ �Ű��ش�. ������ Transform ��ü�� ���� ������ �� �־�� �Ѵ�.

namespace van
{
	Player::Player()
	{
		// nothing
	}

	Player::~Player()
	{
		// nothing
	}

	void Player::Init()
	{
		// nothing
	}

	void Player::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();	// ���� ���������� ������ �� �־�� �ϱ⿡ �ּҰ����� �����´�.
		math::Vector2 pos = tr->GetPosition();

		// Ű �Է�
		if (Input::GetKey(eKeyCode::W))	// top
		{
			if (pos.y > 0)
				pos.y -= SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::S))	// down
		{
			if (pos.y < FHD_Y - DIAMETER)
				pos.y += SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::A))	// left
		{
			if (pos.x > 0)
				pos.x -= SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::D))	// right
		{
			if (pos.x < FHD_X - DIAMETER)
				pos.x += SPEED * Time::DeltaTime();
			else
				__noop;
		}
	}

	void Player::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}
}