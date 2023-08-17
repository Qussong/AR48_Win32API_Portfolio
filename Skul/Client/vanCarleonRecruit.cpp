#include "vanCarleonRecruit.h"
#include "vanTexture.h"
#include "vanResourceManager.h"
#include "vanAnimator.h"
#include "vanRigidBody.h"
#include "vanCollider.h"
#include "vanTime.h"
#include "vanTransform.h"
#include "vanPlayerAttack.h"
#include "vanPlayer.h"
#include "vanMonsterTrace.h"
#include "vanObject.h"
#include "vanMonsterAttack.h"
#include "vanGold.h"

#define DASH_FORCE_X		900.0f
#define DASH_DISTANCE_X		50.0f
#define ATTACK_READY_DELAY	0.6f
	
namespace van
{
	CarleonRecruit::CarleonRecruit()
	{
		// nothing
	}

	CarleonRecruit::~CarleonRecruit()
	{
		// nothing
	}

	void CarleonRecruit::Init()
	{
		Monster::Init();

		// �ִϸ��̼� ����
		MakeAnimation();

		// Monster �ʱ⼳��
		SetMonsterState(MonsterState::Gen);									// ����
		GetComponent<Collider>()->SetSize(math::Vector2(60.0f, 110.0f));	// �浹ü ũ�� ����
		GetComponent<RigidBody>()->SetMass(10.0f);							// ���� ����
		GetComponent<Animator>()->SetScale(math::Vector2(2.0f, 2.0f));		// �̹��� ������ ����

		// traceBox�� �ʱⰪ ����
		MonsterTrace* traceBox = GetMonsterTraceBox();
		traceBox->SetOwner(this);
		traceBox->GetComponent<Collider>()->SetSize(math::Vector2(400.0f, 110.0f));
		traceBox->SetOffset(math::Vector2::Zero);

		// attackBox�� �ʱⰪ ����
		MonsterAttack* attackBox = GetMonsterAttackBox();
		attackBox->SetOwner(this);
		attackBox->GetComponent<Collider>()->SetSize(math::Vector2(100.0f, 110.0f));	// �����Ÿ� 40
		attackBox->SetOffset(math::Vector2(20.0f, 0.0f));
	}

	void CarleonRecruit::Update()
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

	void CarleonRecruit::Render(HDC _hdc)
	{
		Monster::Render(_hdc);
	}

	void CarleonRecruit::MakeAnimation()
	{
		Monster::MakeAnimation();

		Animator* animator = GetComponent<Animator>();
		animator->CreateAnimation(L"Idle_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Idle_L"), math::Vector2(0.0f, 0.0f), math::Vector2(34.0f, 57.0f), 6);
		animator->CreateAnimation(L"Idle_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Idle_R"), math::Vector2(0.0f, 0.0f), math::Vector2(34.0f, 57.0f), 6);
		animator->CreateAnimation(L"Walk_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Walk_L"), math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 50.0f), 8, math::Vector2(0.0f, 5.0f));
		animator->CreateAnimation(L"Walk_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Walk_R"), math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 50.0f), 8, math::Vector2(0.0f, 5.0f));
		animator->CreateAnimation(L"Attack_Ready_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_Ready_L"), math::Vector2(0.0f, 0.0f), math::Vector2(38.0f, 67.0f), 1, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Attack_Ready_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_Ready_R"), math::Vector2(0.0f, 0.0f), math::Vector2(38.0f, 67.0f), 1, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Attack_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_L"), math::Vector2(0.0f, 0.0f), math::Vector2(58.0f, 67.0f), 5, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Attack_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_R"), math::Vector2(0.0f, 0.0f), math::Vector2(58.0f, 67.0f), 5, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Hit_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Hit_L"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 51.0f), 1);
		animator->CreateAnimation(L"Hit_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Hit_R"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 51.0f), 1);
		animator->CreateAnimation(L"Dead_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Dead_L"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 47.0f), 1);
		animator->CreateAnimation(L"Dead_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Dead_R"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 47.0f), 1);
		
	}

	void CarleonRecruit::OnCollisionEnter(Collider* _other)
	{
		Monster::OnCollisionEnter(_other);
	}

	void CarleonRecruit::OnCollisionStay(Collider* _other)
	{
		Monster::OnCollisionStay(_other);
	}

	void CarleonRecruit::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void CarleonRecruit::Gen()
	{
		Monster::Gen();
	}

	void CarleonRecruit::Idle()
	{
		Monster::Idle();
	}

	void CarleonRecruit::Walk()
	{
		Monster::Walk();
	}

	void CarleonRecruit::Patrol()
	{
		Monster::Patrol();
	}

	void CarleonRecruit::Trace()
	{
		Monster::Trace();
	}

	void CarleonRecruit::AttackReady()
	{
		// Attack ���·� ��ȯ�Ʊ⿡ Patrol, Trace Flag�� ���ش�.
		SetPatrolFlag(false);
		SetTraceFlag(false);

		Animator* ani = GetComponent<Animator>();
		Monster::MonsterDirection direction = GetMonsterDirection();
		math::Vector2 pos = GetComponent<Transform>()->GetPosition();
		MonsterAttack* attackBox = GetMonsterAttackBox();

		// Attack Ready �ִϸ��̼� ���
		if (GetPlayAnimation() == true)
		{
			// Monster�� ������ Left�� ���
			if (direction == Monster::MonsterDirection::Left)
			{
				ani->PlayAnimation(L"Attack_Ready_L", false);
			}
			// Monster�� ������ Right�� ���
			else
			{
				ani->PlayAnimation(L"Attack_Ready_R", false);
			}
			SetPlayAnimation(false);
		}

		// ī��Ʈ ����
		// 1) ī��Ʈ�߿� �ǰݵǸ� Timer ����
		// 2) AttackReadyFlag = false ( Hit()���� ���� )
		AddTimer(Time::GetDeltaTime());

		// ī��Ʈ �Ϸ�� 
		// 1) Attack Ready�� �Ϸ�����
		// 2) Attack ���·� �Ѿ��
		// 3) Timer ����
		// 4) Attack Dash �������� ����
		if (GetTimer() >= ATTACK_READY_DELAY)
		{
			attackBox->SetAttackReadyFlag(true);
			SetTimer(0.0f);
			mAttackDashX1 = pos.x;	// Attack Dash �� ������ġ
			SetMonsterState(Monster::MonsterState::Attack);
		}
	}

	void CarleonRecruit::Attack()
	{
		Animator* ani = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		Monster::MonsterDirection direction = GetMonsterDirection();
		math::Vector2 velocity = rb->GetVelocity();
		math::Vector2 pos = GetComponent<Transform>()->GetPosition();
		MonsterAttack* attackBox = GetMonsterAttackBox();
		std::set<GameObject*>* list = attackBox->GetMonsterAttackList();
		bool moveComplete = false;

		// Attack�� �̵�
		if (direction == MonsterDirection::Left)
		{
			velocity.x -= DASH_FORCE_X;
		}
		if (direction == MonsterDirection::Right)
		{
			velocity.x += DASH_FORCE_X;
		}
		rb->SetVelocity(velocity);

		// Attack Animation���
		if (GetPlayAnimation() == true)
		{
			// Monster�� ������ Left�� ���
			if (direction == Monster::MonsterDirection::Left)
			{
				ani->PlayAnimation(L"Attack_L", false);
			}
			// Monster�� ������ Right�� ���
			else
			{
				ani->PlayAnimation(L"Attack_R", false);
			}
			SetPlayAnimation(false);
		}

		// �����Ÿ� �̵��� ����
		mAttackDashX2 = pos.x;									// Attack Dash ������ġ
		float distance = abs(mAttackDashX2 - mAttackDashX1);	// ���ݼ������� ���� �̵��Ÿ�
		if (distance >= DASH_DISTANCE_X)
		{
			rb->SetVelocity(math::Vector2(0.0f, velocity.y));	// x���� �ӵ� 0���� �����
			// �� �ʱ�ȭ
			mAttackDashX1 = 0.0f;
			mAttackDashX2 = 0.0f;
			moveComplete = true;
		}

		// ���� �Ϸ�
		// ���� : Animation ����� �Ϸ� && �����Ÿ� �̵� �Ϸ� || ������ �浹
		// 1) AttackReadyFlag = false
		// 2) AttacList �ʱ�ȭ
		// 3) Attack Flag false ��ȯ
		// 4) Trace Flag true ��ȯ, Trace ���·� ��ȯ
		if (ani->IsActiveAnimationComplete() == true
			&& moveComplete == true)
		{
			// ������ �����߱⿡ �ٽ� Attack Ready�� ������Ѵ�.
			attackBox->SetAttackReadyFlag(false);
			// ���� ��󿡴��� ������ �����ϵ������ش�.
			list->clear();
			// Attack �� �����߱⿡ mbAttack �� false�� ����
			SetAttackFlag(false);
			// Trace ���°� �� �� �ֵ��� ��� Ǯ���ش�.
			SetMonsterTarget(nullptr);
			// Attack End ���� �����
			SetMonsterState(MonsterState::AttackEnd);
		}
	}

	void CarleonRecruit::AttackEnd()
	{
		Monster::AttackEnd();
	}

	void CarleonRecruit::Hit()
	{
		Monster::Hit();
	} 

	void CarleonRecruit::Dead()
	{
		Monster::Dead();
	}
}