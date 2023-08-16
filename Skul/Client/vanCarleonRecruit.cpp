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

#define WALK_SPEED			150.0f
#define HIT_BUMP_X			50.0f
#define HIT_BUMP_Y			-300.0f
#define DASH_FORCE_X		700.0f
#define ATTACK_READY_DELAY	1.0f
	
namespace van
{
	CarleonRecruit::CarleonRecruit()
		: mAttackCnt(0)
	{
		AddComponent<RigidBody>();
	}

	CarleonRecruit::~CarleonRecruit()
	{
		// nothing
	}

	void CarleonRecruit::Init()
	{
		Monster::Init();

		MakeAnimation();	// �ִϸ��̼� ����

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
		attackBox->GetComponent<Collider>()->SetSize(math::Vector2(110.0f, 110.0f));
		attackBox->SetOffset(math::Vector2(25.0f, 0.0f));
	}

	void CarleonRecruit::Update()
	{
		Monster::Update();

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

		// �ǰ�Ƚ�� 2ȸ�� ����
		if (mAttackCnt > 2)
		{
			SetMonsterState(MonsterState::Dead);
		}

		// Animation ������� ����_1
		SetMonsterPastState(GetMonsterState());			// ���� ������ ���¸� ����
		SetMonsterPastDirection(GetMonsterDirection());	// ���� ������ ������ ����

		switch (GetMonsterState())
		{
		case CarleonRecruit::MonsterState::Gen:
			Gen();
			break;
		case CarleonRecruit::MonsterState::Idle:
			Idle();
			break;
		case CarleonRecruit::MonsterState::Walk:
			Walk();
			break;
		case CarleonRecruit::MonsterState::Patrol:
			Patrol();
			break;
		case CarleonRecruit::MonsterState::Trace:
			Trace();
			break;
		case CarleonRecruit::MonsterState::AttackReady:
			AttackReady();
			break;
		case CarleonRecruit::MonsterState::Attack:
			Attack();
			break;
		case CarleonRecruit::MonsterState::AttackEnd:
			AttackEnd();
			break;
		case CarleonRecruit::MonsterState::Hit:
			Hit();
			break;
		case CarleonRecruit::MonsterState::Dead:
			Dead();
			break;
		default:
			__noop;
		}

		if (GetWallFlag() == true)
		{
			if (GetMonsterDirection() == MonsterDirection::Left)
			{
				SetMonsterDirection(MonsterDirection::Right);
			}
			if (GetMonsterDirection() == MonsterDirection::Right)
			{
				SetMonsterDirection(MonsterDirection::Left);
			}

			SetWallFlag(false);
		}

		// Animation ������� ����_2
		// ���� ������ ����,������ �ٲ��ٸ�
		if (GetMonsterState() != GetMonsterPastState()
			|| GetMonsterDirection() != GetMonsterPastDirection())
		{
			SetPlayAnimation(true);
		}

	}

	void CarleonRecruit::Render(HDC _hdc)
	{
		Monster::Render(_hdc);
		//GameObject::Render(_hdc);
	}

	void CarleonRecruit::MakeAnimation()
	{
		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(L"Idle_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Idle_L"), math::Vector2(0.0f, 0.0f), math::Vector2(34.0f, 57.0f), 6);
		animator->CreateAnimation(L"Idle_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Idle_R"), math::Vector2(0.0f, 0.0f), math::Vector2(34.0f, 57.0f), 6);
		animator->CreateAnimation(L"Walk_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Walk_L"), math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 50.0f), 8, math::Vector2(0.0f, 5.0f));
		animator->CreateAnimation(L"Walk_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Walk_R"), math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 50.0f), 8, math::Vector2(0.0f, 5.0f));
		animator->CreateAnimation(L"Attack_Ready_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_Ready_L"), math::Vector2(0.0f, 0.0f), math::Vector2(38.0f, 67.0f), 1, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Attack_Ready_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_Ready_R"), math::Vector2(0.0f, 0.0f), math::Vector2(38.0f, 67.0f), 1, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Attack_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_L"), math::Vector2(0.0f, 0.0f), math::Vector2(58.0f, 67.0f), 5, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Attack_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_R"), math::Vector2(0.0f, 0.0f), math::Vector2(58.0f, 67.0f), 5, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"CarleonRecruit_Hit_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Hit_L"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 51.0f), 1);
		animator->CreateAnimation(L"CarleonRecruit_Hit_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Hit_R"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 51.0f), 1);
		animator->CreateAnimation(L"CarleonRecruit_Dead_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Dead_L"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 47.0f), 1);
		animator->CreateAnimation(L"CarleonRecruit_Dead_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Dead_R"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 47.0f), 1);
		animator->CreateAnimation(L"Monster_Generate", ResourceManager::Find<Texture>(L"Monster_Generate"), math::Vector2(0.0f, 0.0f), math::Vector2(104.0f, 105.0f), 5);
		animator->CreateAnimation(L"Monster_Destroy", ResourceManager::Find<Texture>(L"Monster_Destroy"), math::Vector2(0.0f, 0.0f), math::Vector2(104.0f, 105.0f), 5);
	}

	void CarleonRecruit::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void CarleonRecruit::OnCollisionStay(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		van::PlayerAttack* attack = dynamic_cast<van::PlayerAttack*>(obj);	// �浹�� ��ü�� Attack Ŭ�������� Ȯ��

		// �浹�� ��ü�� PlayerAttack Ŭ������ ��� == �ǰ�(Hit)����
		if (attack != nullptr)
		{
			// PlayerAttack Ŭ������ �浹ü ���� ������ �����´�
			std::set<GameObject*>* list = attack->GetAttackList();

			// �ش� Ŭ������ ������ �浹ü ���� list�� �������� �ʰ� Attack���°� �ƴϸ� Hit ����
			if (list->find(this) == list->end()
				&& GetMonsterState() != Monster::MonsterState::Attack)
			{
				//SetHitFlag(true);
				UINT state = attack->GetOwnerState();
				Player::PlayerDirection playerDirection = (Player::PlayerDirection)(attack->GetOwnerDirection());

				// ���ݹ��� ���� ����
				if (playerDirection == Player::PlayerDirection::Left)
				{
					// Player�� ���ݽ� ������ Left ���
					// Monster ���忡�� Right���� ���ݹ�������
					SetMonsterHitDirection(MonsterDirection::Right);
					SetMonsterDirection(MonsterDirection::Right);
				}
				else
				{
					SetMonsterHitDirection(MonsterDirection::Left);
					SetMonsterDirection(MonsterDirection::Left);
				}

				// Hit ����
				if (state == (UINT)Player::PlayerState::AttackA
					|| state == (UINT)Player::PlayerState::AttackB
					|| state == (UINT)Player::PlayerState::JumpAttack)
				{
					SetMonsterState(MonsterState::Hit);
					// Hit ������ ������ Patrol ���°� �ƴϱ⿡ Patrol Flag�� ���ش�.
					SetPatrolFlag(false);
				}

				// �������� ������ �浹�� �浹ü ����
				list->insert(this);
			}
		}
	}

	void CarleonRecruit::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void CarleonRecruit::Gen()
	{
		Animator* at = GetComponent<Animator>();
		if (GetPlayAnimation() == true)
		{
			at->PlayAnimation(L"Monster_Generate");
			SetPlayAnimation(false);
		}

		if (at->IsActiveAnimationComplete())
		{
			SetMonsterDirection(MonsterDirection::Left);	// ����
			SetMonsterState(MonsterState::Patrol);			// ����
		}
	}

	void CarleonRecruit::Idle()
	{
		Animator* at = GetComponent<Animator>();

		// Patrol ������ �� 
		if (GetPatrolFlag() == true)
		{
			// Trace ������ Player�� ������ ��� Trace ���·� ��ȯ
			if (GetTraceFlag() == true)
			{
				SetMonsterState(MonsterState::Trace);
				return;
			}

			// �ð� ����
			AddTimer(Time::GetDeltaTime());

			// ������ �ð��� 3�� �̻��̵Ǹ�
			if (GetTimer() >= 3.0f)
			{
				SetTimer(0.0f);							// �����ð� 0�ʷ� �ʱ�ȭ
				SetMonsterState(MonsterState::Walk);	// Monster�� ���¸� Walk �� ����

				// ������ȯ
				if (GetMonsterDirection() == MonsterDirection::Left)
				{
					SetMonsterDirection(MonsterDirection::Right);
				}
				else
				{
					SetMonsterDirection(MonsterDirection::Left);
				}
			}
			// ������ �ð��� 3�� �̻��� �ƴ϶��
			else
			{
				if (GetMonsterDirection() == MonsterDirection::Left)
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Idle_L", true);
						SetPlayAnimation(false);
					}
				}
				else
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Idle_R", true);
						SetPlayAnimation(false);
					}
				}
			}
		}
		// Patrol ���°� �ƴҶ�
		else
		{
			__noop;
		}
	}

	void CarleonRecruit::Walk()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		Animator* at = GetComponent<Animator>();

		// Patrol ������ �� 
		if (GetPatrolFlag() == true)
		{
			// Trace ������ Player�� ������ ���
			if (GetTraceFlag() == true)
			{
				SetMonsterState(MonsterState::Trace);
			}

			// �ð� ����
			AddTimer(Time::GetDeltaTime());

			// ������ �ð��� 2�� �̻��̵Ǹ�
			if (GetTimer() >= 2.0f)
			{
				SetTimer(0.0f);
				SetMonsterState(MonsterState::Idle);
			}
			// ������ �ð��� 2�� �̻��� �ƴ϶��
			else
			{
				// Walk_L
				if (GetMonsterDirection() == MonsterDirection::Left)
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Walk_L", true);
						SetPlayAnimation(false);
					}
					pos.x -= (WALK_SPEED * Time::GetDeltaTime());
					tr->SetPosition(pos);
				}
				// Walk_R
				if (GetMonsterDirection() == MonsterDirection::Right)
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Walk_R", true);
						SetPlayAnimation(false);
					}
					pos.x += (WALK_SPEED * Time::GetDeltaTime());
					tr->SetPosition(pos);
				}
			}
		}
		// Trace ������ ��
		else if (GetTraceFlag() == true)
		{
			// Trace ������ Player�� ������ ���
			if (GetAttackFlag() == true)
			{
				SetMonsterState(MonsterState::AttackReady);
			}

			// Monster �������� Target�� ��ġŽ��
			math::Vector2 targetPos = GetMonsterTarget()->GetComponent<Transform>()->GetPosition();	// Target�� ��ġ
			math::Vector2 monsterPos = GetComponent<Transform>()->GetPosition();					// Monster�� ��ġ

			// Target�� Monster�� Left�� ���� ��
			if (targetPos.x < monsterPos.x)
			{
				// Monster�� �̵� ������ Left�� ����
				SetMonsterDirection(Monster::MonsterDirection::Left);
			}
			// Target�� Monster�� Right�� ���� ��
			else
			{
				// Monster�� �̵� ������ Right�� ����
				SetMonsterDirection(Monster::MonsterDirection::Right);
			}

			// Walk_L
			if (GetMonsterDirection() == MonsterDirection::Left)
			{
				if (GetPlayAnimation() == true)
				{
					at->PlayAnimation(L"Walk_L", true);
					SetPlayAnimation(false);
				}
				pos.x -= (WALK_SPEED * Time::GetDeltaTime());
				tr->SetPosition(pos);
			}
			// Walk_R
			if (GetMonsterDirection() == MonsterDirection::Right)
			{
				if (GetPlayAnimation() == true)
				{
					at->PlayAnimation(L"Walk_R", true);
					SetPlayAnimation(false);
				}
				pos.x += (WALK_SPEED * Time::GetDeltaTime());
				tr->SetPosition(pos);
			}
		}
		// Patrol, Trace ���°� �ƴҶ�
		else
		{
			__noop;
		}
	}

	void CarleonRecruit::Patrol()
	{
		// ���Ͱ� ��� ���¿��� Patrol �ൿ�� ���̵��� ����
		SetPatrolFlag(true);
		// Patrol ���·� ��ȯ�Ʊ⿡ Trace, Attack Flag�� ���ش�.
		SetAttackFlag(false);
		SetTraceFlag(false);
		// Patrol�� Idle ���� �����ϵ��� �Ѵ�.
		SetMonsterState(MonsterState::Idle);
	}

	void CarleonRecruit::Trace()
	{
		// Trace ���·� ��ȯ�Ʊ⿡ Patrol, Attack Flag�� ���ش�.
		SetPatrolFlag(false);
		SetAttackFlag(false);
		// Patrol �ൿ ���Ͽ� ����ߴ� Timer�� �ʱ�ȭ���ش�.
		SetTimer(0.0f);

		// Trace�� Target�� �Ѿư��⿡ Walk ���� ����
		SetMonsterState(MonsterState::Walk);
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
		if (distance >= 30.0f)
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
		if (GetAttackFlag() == true)
		{
			SetMonsterState(MonsterState::AttackReady);
		}
		else if (GetTraceFlag() == true)
		{
			SetMonsterState(MonsterState::Trace);
		}
		else
		{
			SetMonsterState(MonsterState::Patrol);
		}

	}

	void CarleonRecruit::Hit()
	{
		Animator* at = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();

		// AttackReady�߿� �ǰݴ��ϸ� mTimer�� 0.0f�� �ʱ�ȭ 
		SetTimer(0.0f);

		// �ǰ� �ִϸ��̼�
		// Monster�� ���ʿ��� ���ݹ޾��� ���
		if (GetMonsterHitDirection() == MonsterDirection::Left)
		{
			at->PlayAnimation(L"CarleonRecruit_Hit_L", false);
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
			at->PlayAnimation(L"CarleonRecruit_Hit_R", false);
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
			// �ǰ�Ƚ�� ����
			++mAttackCnt;
			SetMonsterState(MonsterState::AttackReady);
		}
	} 

	void CarleonRecruit::Dead()
	{
		Animator* at = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		if (GetPlayAnimation() == true)
		{
			at->PlayAnimation(L"Monster_Destroy");
			SetPlayAnimation(false);

			// ���� ������ ����
			Gold* gold = Object::Instantiate<Gold>(enums::eLayerType::Drop);
			gold->GetComponent<Transform>()->SetPosition(tr->GetPosition());
		}


		if (at->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}
}