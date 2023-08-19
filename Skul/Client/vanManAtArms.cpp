#include "vanManAtArms.h"
#include "vanRigidBody.h"
#include "vanCollider.h"
#include "vanAnimator.h"
#include "vanMonsterTrace.h"
#include "vanMonsterAttack.h"
#include "vanTransform.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanPlayerAttack.h"
#include "vanPlayer.h"
#include "vanGold.h"
#include "vanObject.h"

#define HIT_BUMP_X			50.0f
#define HIT_BUMP_Y			-300.0f

namespace van
{
	ManAtArms::ManAtArms()
	{
		// nothing
	}

	ManAtArms::~ManAtArms()
	{
		// nothing
	}

	void ManAtArms::Init()
	{
		Monster::Init();

		MakeAnimation();	// �ִϸ��̼� ����

		// Monster �ʱ⼳��
		SetMonsterState(MonsterState::Gen);									// ����
		GetComponent<Collider>()->SetSize(math::Vector2(160.0f, 190.0f));
		GetComponent<RigidBody>()->SetMass(10.0f);							// ���� ����
		GetComponent<Animator>()->SetScale(math::Vector2(2.0f, 2.0f));		// �̹��� ������ ����

		// traceBox�� �ʱⰪ ����
		MonsterTrace* traceBox = GetMonsterTraceBox();
		traceBox->SetOwner(this);
		traceBox->GetComponent<Collider>()->SetSize(math::Vector2(400.0f, 190.0f));		// ����
		traceBox->SetOffset(math::Vector2::Zero);

		// attackBox�� �ʱⰪ ����
		MonsterAttack* attackBox = GetMonsterAttackBox();
		attackBox->SetOwner(this);
		attackBox->GetComponent<Collider>()->SetSize(math::Vector2(190.0f, 190.0f));	// �����Ÿ� 30
		attackBox->SetOffset(math::Vector2(15.0f, 0.0f));
	}

	void ManAtArms::Update()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		// traceBox ������
		MonsterTrace* traceBox = GetMonsterTraceBox();
		traceBox->SetOwnerPos(pos);
		traceBox->SetOwnerState((UINT)GetMonsterState());
		traceBox->SetOwnerDirection((UINT)GetMonsterDirection());
		// attackBox ������
		MonsterAttack* attackBox = GetMonsterAttackBox();
		attackBox->SetOwnerPos(pos);
		attackBox->SetOwnerState((UINT)GetMonsterState());
		attackBox->SetOwnerDirection((UINT)GetMonsterDirection());

		Monster::Update();
	}

	void ManAtArms::Render(HDC _hdc)
	{
		Monster::Render(_hdc);
	}

	void ManAtArms::MakeAnimation()
	{
		Monster::MakeAnimation();

		Animator* animator = GetComponent<Animator>();
		animator->CreateAnimation(L"Attack_L", ResourceManager::Find<Texture>(L"ManAtArms_Attack_L"), math::Vector2(0.0f, 0.0f), math::Vector2(108.0f, 109.0f), 5, math::Vector2(0.0f, 0.0f));
		animator->CreateAnimation(L"Attack_R", ResourceManager::Find<Texture>(L"ManAtArms_Attack_R"), math::Vector2(0.0f, 0.0f), math::Vector2(108.0f, 109.0f), 5, math::Vector2(0.0f, 0.0f));
		animator->CreateAnimation(L"Attack_Ready_L", ResourceManager::Find<Texture>(L"ManAtArms_Attack_Ready_L"), math::Vector2(0.0f, 0.0f), math::Vector2(108.0f, 109.0f), 3, math::Vector2(0.0f, 0.0f));
		animator->CreateAnimation(L"Attack_Ready_R", ResourceManager::Find<Texture>(L"ManAtArms_Attack_Ready_R"), math::Vector2(0.0f, 0.0f), math::Vector2(108.0f, 109.0f), 3, math::Vector2(0.0f, 0.0f));
		//animator->CreateAnimation(L"Dead_L", ResourceManager::Find<Texture>(L"ManAtArms_Dead_L"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 64.0f), 1);
		//animator->CreateAnimation(L"Dead_R", ResourceManager::Find<Texture>(L"ManAtArms_Dead_R"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 64.0f), 1);
		//animator->CreateAnimation(L"Hit_L", ResourceManager::Find<Texture>(L"ManAtArms_Hit_L"), math::Vector2(0.0f, 0.0f), math::Vector2(56.0f, 67.0f), 1);
		//animator->CreateAnimation(L"Hit_R", ResourceManager::Find<Texture>(L"ManAtArms_Hit_R"), math::Vector2(0.0f, 0.0f), math::Vector2(56.0f, 67.0f), 1);
		animator->CreateAnimation(L"Idle_L", ResourceManager::Find<Texture>(L"ManAtArms_Idle_L"), math::Vector2(0.0f, 0.0f), math::Vector2(109.0f, 100.0f), 4);
		animator->CreateAnimation(L"Idle_R", ResourceManager::Find<Texture>(L"ManAtArms_Idle_R"), math::Vector2(0.0f, 0.0f), math::Vector2(109.0f, 100.0f), 4);
		animator->CreateAnimation(L"Walk_L", ResourceManager::Find<Texture>(L"ManAtArms_Walk_L"), math::Vector2(0.0f, 0.0f), math::Vector2(112.0f, 100.0f), 8, math::Vector2(0.0f, 0.0f));
		animator->CreateAnimation(L"Walk_R", ResourceManager::Find<Texture>(L"ManAtArms_Walk_R"), math::Vector2(0.0f, 0.0f), math::Vector2(112.0f, 100.0f), 8, math::Vector2(0.0f, 0.0f));
	}

	void ManAtArms::OnCollisionEnter(Collider* _other)
	{
		Monster::OnCollisionEnter(_other);
	}

	void ManAtArms::OnCollisionStay(Collider* _other)
	{
		Monster::OnCollisionStay(_other);
	}

	void ManAtArms::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void ManAtArms::Gen()
	{
		Monster::Gen();
	}

	void ManAtArms::Idle()
	{
		Monster::Idle();
	}

	void ManAtArms::Walk()
	{
		Monster::Walk();
	}

	void ManAtArms::Patrol()
	{
		Monster::Patrol();
	}

	void ManAtArms::Trace()
	{
		Monster::Trace();
	}

	void ManAtArms::AttackReady()
	{
		Monster::AttackReady();
	}

	void ManAtArms::Attack()
	{
		Monster::Attack();
	}

	void ManAtArms::AttackEnd()
	{
		Monster::AttackEnd();
	}

	void ManAtArms::Hit()
	{
		//Monster::Hit();

		Animator* at = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();

		// AttackReady�߿� �ǰݴ��ϸ� mTimer�� 0.0f�� �ʱ�ȭ 
		SetTimer(0.0f);

		// �ǰ� �ִϸ��̼�
		// Monster�� ���ʿ��� ���ݹ޾��� ���
		if (GetMonsterHitDirection() == MonsterDirection::Left)
		{
			rb->SetHit(true);
			rb->SetGround(false);
			// ���ʿ��� �¾ұ⿡ ���������� ���ư����Ѵ�.
			velocity.x = HIT_BUMP_X;
			velocity.y = HIT_BUMP_Y;
			rb->SetVelocity(velocity);

			SetMonsterDirection(MonsterDirection::Left);
		}
		// ���Ͱ� �����ʿ��� ���ݹ޾��� ���
		if (GetMonsterHitDirection() == MonsterDirection::Right)
		{
			rb->SetHit(true);
			rb->SetGround(false);
			// �����ʿ��� �¾ұ⿡ �������� ���ư����Ѵ�.
			velocity.x = -HIT_BUMP_X;
			velocity.y = HIT_BUMP_Y;
			rb->SetVelocity(velocity);

			SetMonsterDirection(MonsterDirection::Right);
		}
		// ���Ͱ� ���ݹ��� ������ �ʱ�ȭ���ش�.
		SetMonsterHitDirection(MonsterDirection::None);

		// ���ݹ��� �� ���� ������ Trace ���·� ��ȯ
		if (rb->GetGround() == true)
		{
			//�ǰ�Ƚ�� ����
			SetMonsterState(MonsterState::AttackReady);
		}
	}

	void ManAtArms::Dead()
	{
		Monster::Dead();
	}

	void ManAtArms::Wall()
	{
		Monster::Wall();
	}
}