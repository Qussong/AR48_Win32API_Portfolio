#include "vanPlayer.h"
#include "vanInput.h"
#include "vanTransform.h"	// Update()���� Player ��ü�� ��ġ �Ű��ش�. ������ Transform ��ü�� ���� ������ �� �־�� �Ѵ�.
#include "vanAnimator.h"

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

		// Player ��ü�� ��ġ ����
		
		// 1. Player ��ü�� Tranfer Component�� ���� ��ġ�� ���´�.
		Transform* tr = GetComponent<Transform>();	
		math::Vector2 pos = tr->GetPosition();
		Animator* ani = GetComponent<Animator>();

		// 2. Ű �Է��� �޾� ��ġ�� ����
		if (Input::GetKey(eKeyCode::W))	// top
		{
			//if (pos.y > 0)
				pos.y -= SPEED * Time::DeltaTime();
			//else
			//	__noop;
		}
		if (Input::GetKey(eKeyCode::S))	// down
		{
			//if (pos.y < Window_Y - DIAMETER)
				pos.y += SPEED * Time::DeltaTime();
			//else
			//	__noop;
		}
		if (Input::GetKey(eKeyCode::A))	// left
		{
			//if (pos.x > 0)
				pos.x -= SPEED * Time::DeltaTime();
			//else
			//	__noop;
		}
		if (Input::GetKey(eKeyCode::D))	// right
		{
			//if (pos.x < Window_X - DIAMETER)
				pos.x += SPEED * Time::DeltaTime();
			//else
			//	__noop;
		}

		// 3. ������ ��ġ���� Transfer Component�� �־��ش�.
		tr->SetPosition(pos);
	}

	void Player::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}
}