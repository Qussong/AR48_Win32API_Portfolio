#include "vanPlayer.h"
#include "vanInput.h"
#include "vanTransform.h"	// Update()���� Player ��ü�� ��ġ �Ű��ش�. ������ Transform ��ü�� ���� ������ �� �־�� �Ѵ�.
#include "vanAnimator.h"

#include "vanObject.h"

namespace van
{
	Player::Player()
		: mState(PlayerState::Idle)
		, mDirection(PlayerDirection::Left)
	{
		AddComponent<Animator>();
	}

	Player::~Player()
	{
		// nothing
	}

	void Player::Init()
	{
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Animator>();
	}

	void Player::Update()
	{
		GameObject::Update();

		//StillSameState();

		switch (mState)
		{
		case Player::PlayerState::Walk:
			Walk();
			break;
		case Player::PlayerState::Idle:
			Idle();
			break;
		default:
			break;
		}
	}

	void Player::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Player::ChangeState(PlayerState _state)
	{
		if (_state == mState)
		{
			return;
		}

		// ���¿��� �������� �� ���� �������� �Ѵٸ�... ���⼭ Ư���Լ� ȣ��
		switch (mState)
		{
		case van::Player::PlayerState::Walk:
			break;
		case van::Player::PlayerState::Idle:
			break;
		default:
			break;
		}

		mState = _state;

		// Ư�� ���¿� �� �� �������� �Ѵٸ� ���⼭ Ư���Լ� ȣ��
		switch (_state)
		{
		case van::Player::PlayerState::Walk:

			break;
		case van::Player::PlayerState::Idle:

			break;
		default:
			break;
		}
	}

	void Player::StillSameState()
	{
		// �ش� ������ �� �� �� ����� �ϸ� ���⼭ Ư���Լ� ȣ��
		switch (mState)
		{
		case van::Player::PlayerState::Walk:

			break;
		case van::Player::PlayerState::Idle:

			break;
		default:
			break;
		}
	}

	void Player::Idle()
	{
		// Skul_Walk_Left
		// Skul_Walk_Right
		Animator* animator = GetComponent<Animator>();
		
		if (Input::GetKey(eKeyCode::A))
		{
			animator->PlayAnimation(L"Skul_Walk_Left", true);
			ChangeState(PlayerState::Walk);
		}
		if (Input::GetKey(eKeyCode::D))
		{
			animator->PlayAnimation(L"Skul_Walk_Right", true);
			mState = PlayerState::Walk;
		}
	}

	void Player::Walk()
	{
		// Idle_Left
		// Idle_Right
		Animator* animator = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= SPEED * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += SPEED * Time::DeltaTime();
		}

		if (Input::GetKeyUp(eKeyCode::A))
		{
			animator->PlayAnimation(L"Idle_Left", true);
			mState = PlayerState::Idle;
		}
		if(Input::GetKeyUp(eKeyCode::D))
		{
			animator->PlayAnimation(L"Idle_Right", true);
			mState = PlayerState::Idle;
		}

		tr->SetPosition(pos);
	}
}