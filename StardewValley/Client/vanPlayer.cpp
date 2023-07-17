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
			ani->PlayAnimation(L"Skul_Idle_Weapon", true);
			pos.y -= SPEED * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::S))	// down
		{
			ani->PlayAnimation(L"Skul_Idle_Weapon", true);
			pos.y += SPEED * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::A))	// left
		{
			ani->PlayAnimation(L"Skul_Walk_Left", true);
			pos.x -= SPEED * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::D))	// right
		{
			ani->PlayAnimation(L"Skul_Walk_Right", true);
			pos.x += SPEED * Time::DeltaTime();
		}

		// 3. ������ ��ġ���� Transfer Component�� �־��ش�.
		tr->SetPosition(pos);
	}

	void Player::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}
}