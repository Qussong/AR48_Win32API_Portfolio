#include "vanPlayer.h"
#include "vanInput.h"
#include "vanTransform.h"	// Update()���� Player ��ü�� ��ġ �Ű��ش�. ������ Transform ��ü�� ���� ������ �� �־�� �Ѵ�.
#include "vanAnimator.h"
#include "vanObject.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanRigidBody.h"
#include "vanCollider.h"
#include "vanFloor.h"
#include "vanTime.h"

namespace van
{
	Player::Player()
		: mState(PlayerState::Idle)
		, mDirection(PlayerDirection::Right)
		, mbDoubleKey(false)
		, mJumpCnt(0)
	{
		RigidBody* rb = AddComponent<RigidBody>();
		rb->SetMass(50.0f);
		AddComponent<Collider>()->SetSize(math::Vector2(50.0f, 70.0f));;
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
		
		//math::Vector2 pos = GetComponent<Transform>()->GetPosition();	// ������ Player ��ü ��ġ Ȯ�ο�
		//StillSameState();

		// z : Dash, x : Attack , c : Jump
		switch (mState)
		{
		case Player::PlayerState::Idle:
			Idle();
			break;
		case Player::PlayerState::Walk:
			Walk();
			break;
		case Player::PlayerState::Jump:
			Jump();
			break;
		case Player::PlayerState::Dash:
			Dash();
			break;
		case Player::PlayerState::AttackA:
			AttackA();
			break;
		case Player::PlayerState::AttackB:
			AttackB();
			break;
		case Player::PlayerState::JumpAttack:
			JumpAttack();
			break;
		case Player::PlayerState::DoubleJump:
			DoubleJump();
			break;
		case Player::PlayerState::DoubleDash:
			DoubleDash();
			break;
		case Player::PlayerState::Fall:
			Fall();
			break;
		default:
			__noop;
		}
	}

	void Player::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
		ShowStatus(_hdc);
	}

	void Player::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void Player::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Player::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void Player::MakeAnimation()
	{
		Animator* animator = GetComponent<Animator>();
		math::Vector2 offset = GetOffset();	// �⺻�� math::Vector2::Zero

		// Idle_L
		animator->CreateAnimation(L"Idle_Weapon_L", ResourceManager::Find<Texture>(L"Idle_Weapon_L"), math::Vector2::Zero, math::Vector2(44.0f, 37.0f), 4, offset);
		animator->CreateAnimation(L"Idle_Weapon_R", ResourceManager::Find<Texture>(L"Idle_Weapon_R"), math::Vector2::Zero, math::Vector2(44.0f, 37.0f), 4, offset);
		animator->CreateAnimation(L"Walk_Weapon_L", ResourceManager::Find<Texture>(L"Walk_Weapon_L"), math::Vector2::Zero, math::Vector2(44.0f, 36.0f), 8, offset);
		animator->CreateAnimation(L"Walk_Weapon_R", ResourceManager::Find<Texture>(L"Walk_Weapon_R"), math::Vector2::Zero, math::Vector2(44.0f, 36.0f), 8, offset);
		animator->CreateAnimation(L"Attack_A_L", ResourceManager::Find<Texture>(L"Attack_A_L"), math::Vector2::Zero, math::Vector2(63.0f, 65.0f), 5, offset);
		animator->CreateAnimation(L"Attack_A_R", ResourceManager::Find<Texture>(L"Attack_A_R"), math::Vector2::Zero, math::Vector2(63.0f, 65.0f), 5, offset);
		animator->CreateAnimation(L"Attack_B_L", ResourceManager::Find<Texture>(L"Attack_B_L"), math::Vector2::Zero, math::Vector2(62.0f, 59.0f), 4, offset);
		animator->CreateAnimation(L"Attack_B_R", ResourceManager::Find<Texture>(L"Attack_B_R"), math::Vector2::Zero, math::Vector2(62.0f, 59.0f), 4, offset);
		animator->CreateAnimation(L"Jump_L", ResourceManager::Find<Texture>(L"Jump_L"), math::Vector2::Zero, math::Vector2(22.0f, 36.0f), 2, offset);
		animator->CreateAnimation(L"Jump_R", ResourceManager::Find<Texture>(L"Jump_R"), math::Vector2::Zero, math::Vector2(22.0f, 36.0f), 2, offset);
		animator->CreateAnimation(L"Jump_L", ResourceManager::Find<Texture>(L"Jump_L"), math::Vector2::Zero, math::Vector2(61.0f, 57.0f), 4, offset);
		animator->CreateAnimation(L"Jump_R", ResourceManager::Find<Texture>(L"Jump_R"), math::Vector2::Zero, math::Vector2(61.0f, 57.0f), 4, offset);
		animator->CreateAnimation(L"Dash_L", ResourceManager::Find<Texture>(L"Dash_L"), math::Vector2::Zero, math::Vector2(42.0f, 28.0f), 1, offset);
		animator->CreateAnimation(L"Dash_R", ResourceManager::Find<Texture>(L"Dash_R"), math::Vector2::Zero, math::Vector2(42.0f, 28.0f), 1, offset);
		animator->CreateAnimation(L"Fall_L", ResourceManager::Find<Texture>(L"Fall_L"), math::Vector2::Zero, math::Vector2(34.0f, 36.0f), 2, offset);
		animator->CreateAnimation(L"Fall_R", ResourceManager::Find<Texture>(L"Fall_R"), math::Vector2::Zero, math::Vector2(34.0f, 36.0f), 2, offset);
	}

	/*
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
		{
			break;
		}
		case van::Player::PlayerState::Idle:
		{
			break;
		}
		default:
			break;
		}

		mState = _state;

		// Ư�� ���¿� �� �� �������� �Ѵٸ� ���⼭ Ư���Լ� ȣ��
		switch (_state)
		{
		case van::Player::PlayerState::Walk:
		{
			break;
		}
		case van::Player::PlayerState::Idle:
		{
			break;
		}
		default:
			break;
		}
	}
	*/

	/*
	void Player::StillSameState()
	{
		// �ش� ������ �� �� �� ����� �ϸ� ���⼭ Ư���Լ� ȣ��
		switch (mState)
		{
		case van::Player::PlayerState::Walk:
		{

			break;
		}
		case van::Player::PlayerState::Idle:
		{

			break;
		}
		case van::Player::PlayerState::Jump:
		{

			break;
		}
		case van::Player::PlayerState::Attack:
		{

			break;
		}
		default:
			break;
		}
	}
	*/

	void Player::ShowStatus(HDC _hdc)
	{
		const int SIZE = 50;
		wchar_t szFloat[SIZE] = {};
		swprintf_s(szFloat, SIZE, L"state : %d \n JumpCnt : %d", (UINT)mState, mJumpCnt);
		int strLen = (int)wcsnlen_s(szFloat, SIZE);
		TextOut(_hdc, 10, 50, szFloat, strLen);
	}

	void Player::Idle()
	{
		mJumpCnt = 0;	// Jump || DoubleJump -> Idle
		Animator* animator = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();

		if (Input::GetKey(eKeyCode::Down))
		{
			// nothing
		}

		// Walk_L
		if (Input::GetKey(eKeyCode::Left) && !Input::GetKey(eKeyCode::Right))
		{
			if (!mbDoubleKey)
			{
				animator->PlayAnimation(L"Walk_Weapon_L", true);
				mState = PlayerState::Walk;
			}
		}

		// Walk_R
		if (Input::GetKey(eKeyCode::Right) && !Input::GetKey(eKeyCode::Left))
		{
			if (!mbDoubleKey)
			{
				animator->PlayAnimation(L"Walk_Weapon_R", true);
				mState = PlayerState::Walk;
			}
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::C))
		{
			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				animator->PlayAnimation(L"Jump_L");
			}
			else if (mDirection == PlayerDirection::Right)
			{
				animator->PlayAnimation(L"Jump_R");
			}

			// Logic
			RigidBody* rb = GetComponent<RigidBody>();
			math::Vector2 velocity = rb->GetVelocity();
			velocity.y = -850.0f;		// ������ �ʱ� �ӵ�(v0)
			rb->SetVelocity(velocity);	// �ӵ� setter
			rb->SetGround(false);		// �����߱⿡ ���߿� ������ ǥ�� (mGround = false -> ����)

			// State
			++mJumpCnt;					// ����Ƚ�� + 1 (�ִ� 2 ȸ)
			mState = PlayerState::Jump;
		}

		// Attack
		if (Input::GetKeyDown(eKeyCode::X))
		{
			if (mDirection == PlayerDirection::Left)
			{
				animator->PlayAnimation(L"Attack_A_L", false);
			}
			if (mDirection == PlayerDirection::Right)
			{
				animator->PlayAnimation(L"Attack_A_R", false);
			}

			mState = PlayerState::AttackA;
		}

		// Dash
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			math::Vector2 velocity = rb->GetVelocity();
			math::Vector2 gravity = rb->GetGravity();

			if (mDirection == PlayerDirection::Left)
			{
				// Animmator
				animator->PlayAnimation(L"Dash_L");

				// Logic
				velocity.x -= 500.0f;
				rb->SetVelocity(velocity);
			}
			if (mDirection == PlayerDirection::Right)
			{
				// Animator
				animator->PlayAnimation(L"Dash_R");

				// Logic
				velocity.x += 500.0f;
				rb->SetVelocity(velocity);
			}

			// State
			mState = PlayerState::Dash;
		}

		// ����Ű �Է� ����
		if (mbDoubleKey)
		{
			if (Input::GetKeyUp(eKeyCode::Right))
			{
				animator->PlayAnimation(L"Walk_Weapon_L", true);
				mState = PlayerState::Walk;
				mbDoubleKey = false;
			}
			if (Input::GetKeyUp(eKeyCode::Left))
			{
				animator->PlayAnimation(L"Walk_Weapon_R", true);
				mState = PlayerState::Walk;
				mbDoubleKey = false;
			}
		}
	}

	void Player::Walk()
	{
		Animator* animator = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		// Jump_Down
		if (Input::GetKey(eKeyCode::Down) && Input::GetKey(eKeyCode::C))
		{
			// �Ʒ����� ����
		}
		
		// Walk_Right
		if (Input::GetKey(eKeyCode::Left) && !Input::GetKey(eKeyCode::Right))
		{
			pos.x -= SPEED * Time::GetDeltaTime();
			mDirection = PlayerDirection::Left;
		}

		// Walk_Left
		if (Input::GetKey(eKeyCode::Right) && !Input::GetKey(eKeyCode::Left))
		{
			pos.x += SPEED * Time::GetDeltaTime();
			mDirection = PlayerDirection::Right;
		}

		// ???
		if (Input::GetKey(eKeyCode::Down))
		{
			// nothing
		}

		// Walk_Right
		if (Input::GetKeyUp(eKeyCode::Right))
		{
			animator->PlayAnimation(L"Idle_Weapon_R", true);
			mState = PlayerState::Idle;
		}

		// Walk_Right
		if (Input::GetKeyUp(eKeyCode::Left))
		{
			animator->PlayAnimation(L"Idle_Weapon_L", true);
			mState = PlayerState::Idle;
		}

		// ����Ű �Է�(����Ű)
		if (Input::GetKey(eKeyCode::Right) && Input::GetKey(eKeyCode::Left))
		{
			if (!mbDoubleKey)
			{
				if (mDirection == PlayerDirection::Right)
				{
					animator->PlayAnimation(L"Idle_Weapon_R", true);
					mState = PlayerState::Idle;
				}

				if (mDirection == PlayerDirection::Left)
				{
					animator->PlayAnimation(L"Idle_Weapon_L", true);
					mState = PlayerState::Idle;
				}
				mbDoubleKey = true;
			}
		}

		tr->SetPosition(pos);
	}

	void Player::Jump()
	{
		Animator* animator = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();

		// DoubleJump
		if (Input::GetKeyDown(eKeyCode::C) && mJumpCnt < 2)	
		{
			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				animator->PlayAnimation(L"Jump_L");
			}
			else if (mDirection == PlayerDirection::Right)
			{
				animator->PlayAnimation(L"Jump_R");
			}
			else
			{
				__noop;
			}

			// Logic
			RigidBody* rb = GetComponent<RigidBody>();
			math::Vector2 velocity = rb->GetVelocity();
			velocity.y = -850.0f;		// up Velocity
			rb->SetVelocity(velocity);	// Velocity Setter
			rb->SetGround(false);

			// State
			++mJumpCnt;
			mState = PlayerState::DoubleJump;
		}

		// Fall
		if (velocity.y >= 0.0f && rb->GetGround() == false)	
		{
			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				animator->PlayAnimation(L"Fall_L");
			}
			
			if (mDirection == PlayerDirection::Right)
			{
				animator->PlayAnimation(L"Fall_R");
			}

			// Logic

			// State
			mState = PlayerState::Fall;
		}
	}

	void Player::Dash()
	{
		Animator* animator = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		
	}

	void Player::AttackA()
	{
		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			if (mDirection == PlayerDirection::Left)
			{
				animator->PlayAnimation(L"Idle_Weapon_L", true);
			}
			else if (mDirection == PlayerDirection::Right)
			{
				animator->PlayAnimation(L"Idle_Weapon_R", true);
			}

			mState = PlayerState::Idle;
		}
	}

	void Player::AttackB()
	{

	}

	void Player::JumpAttack()
	{

	}

	void Player::DoubleJump()
	{
		Animator* animator = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();

		// Fall
		if (velocity.y >= 0.0f && rb->GetGround() == false)	// Fall
		{
			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				animator->PlayAnimation(L"Fall_L");
			}
			if (mDirection == PlayerDirection::Right)
			{
				animator->PlayAnimation(L"Fall_R");
			}
			// Logic

			// State
			mState = PlayerState::Fall;
		}
	}

	void Player::DoubleDash()
	{

	}

	void Player::Fall()
	{
		Animator* animator = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();
		
		// DoubleJump
		if (Input::GetKeyDown(eKeyCode::C))
		{
			if (rb->GetGround() == false && velocity.y >= 0.0f && mJumpCnt < 2)
			{
				// Animation
				if (mDirection == PlayerDirection::Left)
				{
					animator->PlayAnimation(L"Jump_L");
				}
				else if (mDirection == PlayerDirection::Right)
				{
					animator->PlayAnimation(L"Jump_R");
				}

				// Logic
				velocity.y = -850.0f;
				rb->SetVelocity(velocity);
				rb->SetGround(false);

				// State
				++mJumpCnt;
				mState = PlayerState::DoubleJump;
			}
			else
			{
				__noop;
			}
		}

		// Idle
		if (velocity.y == 0.0f && rb->GetGround() == true)
		{
			// Animation
			if (mDirection == PlayerDirection::Right)
			{
				animator->PlayAnimation(L"Idle_Weapon_R", true);
				mState = PlayerState::Idle;
			}
			if (mDirection == PlayerDirection::Left)
			{
				animator->PlayAnimation(L"Idle_Weapon_L", true);
				mState = PlayerState::Idle;
			}
			
			// Logic

			// State
			mState = PlayerState::Idle;
		}
		
	}
}