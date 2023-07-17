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
		if (Input::GetKey(eKeyCode::W))			// top
			pos.y -= SPEED * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::S))			// down
			pos.y += SPEED * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::A))			// left
			pos.x -= SPEED * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::D))			// right
			pos.x += SPEED * Time::DeltaTime();

		// 3. Ű �Է¿� ���� �ִϸ��̼� ����
		if (Input::GetKeyDown(eKeyCode::A))		// left_walk
			ani->PlayAnimation(L"Skul_Walk_Left", true);
		if (Input::GetKeyDown(eKeyCode::D))		// right_walk
			ani->PlayAnimation(L"Skul_Walk_Right", true);
		if (Input::GetKeyUp(eKeyCode::A))		// left_idle
			ani->PlayAnimation(L"Skul_Idle_Weapon_Left", true);
		if (Input::GetKeyUp(eKeyCode::D))		// right_idle
			ani->PlayAnimation(L"Skul_Idle_Weapon_Right", true);

		// 4. ������ ��ġ���� Transfer Component�� �־��ش�.
		tr->SetPosition(pos);
	}

	void Player::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}
}