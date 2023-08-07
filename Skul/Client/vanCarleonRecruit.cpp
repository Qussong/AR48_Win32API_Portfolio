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

#define WALK_SPEED		150.0f
#define HIT_BUMP_X		50.0f
#define HIT_BUMP_Y		-300.0f
#define DASH_FORCE_X	700.0f
	
namespace van
{
	CarleonRecruit::CarleonRecruit()
		: mTimer(0.0f)
		, mTraceBox(nullptr)
		, mAttackBox(nullptr)
	{
		AddComponent<RigidBody>();
	}

	CarleonRecruit::~CarleonRecruit()
	{
		// nothing
	}

	void CarleonRecruit::Init()
	{
		MakeAnimation();	// �ִϸ��̼� ����

		// Monster �ʱ⼳��
		SetMonsterDirection(MonsterDirection::Left);	// ����
		SetMonsterState(MonsterState::Patrol);			// ����
		GetComponent<Collider>()->SetSize(math::Vector2(60.0f, 110.0f));	// �浹ü ũ�� ����
		GetComponent<RigidBody>()->SetMass(10.0f);							// ���� ����

		// mTraaceBox�� �ʱⰪ ����
		mTraceBox = Object::Instantiate<MonsterTrace>(enums::eLayerType::Range_Monster_Trace);	// ��ü����
		mTraceBox->SetOwner(this);																// ������ ����
		mTraceBox->GetComponent<Collider>()->SetSize(math::Vector2(400.0f, 110.0f));			// traceBox �浹ü�� ũ�� ����
		mTraceBox->SetOffset(math::Vector2::Zero);

		// mAttackBox�� �ʱⰪ ����
		mAttackBox = Object::Instantiate<MonsterAttack>(enums::eLayerType::Range_Monster_Attack);
		mAttackBox->SetOwner(this);
		mAttackBox->GetComponent<Collider>()->SetSize(math::Vector2(50.0f, 110.0f));
		mAttackBox->SetOffset(math::Vector2(55.0f, 0.0f));
	}

	void CarleonRecruit::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		// mTraceBox ������
		mTraceBox->SetOwnerPos(pos);
		mTraceBox->SetOwnerState((UINT)GetMonsterState());
		mTraceBox->SetOwnerDirection((UINT)GetMonsterDirection());

		// mAttackBox ������
		mAttackBox->SetOwnerPos(pos);
		mAttackBox->SetOwnerState((UINT)GetMonsterState());
		mAttackBox->SetOwnerDirection((UINT)GetMonsterDirection());

		SetMonsterPastState(GetMonsterState());	// ���� ������ ���¸� ����
		SetMonsterPastDirection(GetMonsterDirection());	// ���� ������ ������ ����

		switch (GetMonsterState())
		{
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
		case CarleonRecruit::MonsterState::Hit:
			Hit();
			break;
		default:
			__noop;
		}

		// ���� ������ ����,������ �ٲ��ٸ�
		if (GetMonsterState() != GetMonsterPastState()
			|| GetMonsterDirection() != GetMonsterPastDirection())
		{
			SetPlayAnimation(true);
		}
		
	}

	void CarleonRecruit::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
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

	void CarleonRecruit::Idle()
	{
		Animator* at = GetComponent<Animator>();

		// Patrol ������ �� 
		if (GetPatrolFlag() == true)
		{
			// �ð� ����
			mTimer += Time::GetDeltaTime();

			// ������ �ð��� 3�� �̻��̵Ǹ�
			if (mTimer >= 3.0f)				
			{
				mTimer = 0.0f;							// �����ð� 0�ʷ� �ʱ�ȭ
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
			// �ð� ����
			mTimer += Time::GetDeltaTime();

			// ������ �ð��� 2�� �̻��̵Ǹ�
			if (mTimer >= 2.0f)
			{
				mTimer = 0.0f;
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
		else if(GetTraceFlag() == true)
		{
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
		// Attack ������ ��
		else if (GetAttackFlag() == true)
		{
			SetMonsterState(MonsterState::AttackReady);
		}
		// Patrol, Trace, Attack ���°� �ƴҶ�
		else
		{
			__noop;
		}
	}

	void CarleonRecruit::Patrol()
	{
		// ���Ͱ� ��� ���¿��� Patrol �ൿ�� ���̵��� ����
		SetPatrolFlag(true);
		// Patrol ���·� ��ȯ�Ʊ⿡ Trace Flag�� ���ش�.
		SetTraceFlag(false);
		// Patrol�� Idle ���� �����ϵ��� �Ѵ�.
		SetMonsterState(MonsterState::Idle);
	}

	void CarleonRecruit::Trace()
	{
		// ���Ͱ� ��� ���¿��� Trace �ൿ�� ���̵��� ����
		SetTraceFlag(true);
		// Trace ���·� ��ȯ�Ʊ⿡ Patrol Flag�� ���ش�.
		SetPatrolFlag(false);
		// Patrol �ൿ ���Ͽ� ����ߴ� Timer�� �ʱ�ȭ���ش�.
		mTimer = 0.0f;	

		// Trace�� Target�� �Ѿư��⿡ Walk ���� ����
		SetMonsterState(MonsterState::Walk);

		// Monster�� Attack ������ Player�� ������ �ʾ��� ���
		//if (GetAttackFlag() == false)
		//{
		//	// Trace�� Target�� �Ѿư��⿡ Walk ���� ����
		//	SetMonsterState(MonsterState::Walk);
		//}
		//// Monster�� Attack ������ Player�� ������ ���
		//else
		//{
		//	// Attack �����ϱ⿡ Trace Flag ���ش�.
		//	SetTraceFlag(false);
		//	// Attack Ready�� ���º���
		//	SetMonsterState(MonsterState::AttackReady);
		//}
	}

	void CarleonRecruit::AttackReady()
	{
		Animator* ani = GetComponent<Animator>();
		Monster::MonsterDirection direction = GetMonsterDirection();
		math::Vector2 pos = GetComponent<Transform>()->GetPosition();

		// Attack Ready ���
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

		// Timer�� 1~2�� ī��Ʈ
		// ī��Ʈ�߿� �ǰݵǸ� Timer ����, AttackReadyFlag = false ( Hit()���� ���� )
		mTimer += Time::GetDeltaTime();
		
		// ī��Ʈ �Ϸ�� Attack ���·� �Ѿ��, Timer ����
		if (mTimer >= 2.0f)
		{
			mTimer = 0.0f;
			SetMonsterState(Monster::MonsterState::Attack);
			mAttackDashX1 = pos.x;	// Attack Dash �� ������ġ
		}
	}

	void CarleonRecruit::Attack()
	{
		Animator* ani = GetComponent<Animator>();
		Monster::MonsterDirection direction = GetMonsterDirection();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();
		math::Vector2 pos = GetComponent<Transform>()->GetPosition();
		std::set<GameObject*>* list = mAttackBox->GetMonsterAttackList();
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


		// Animation ����� �Ϸ� && �����Ÿ� �̵� �Ϸ�� 
		// 1) AttackReadyFlag = false
		// 2) AttacList �ʱ�ȭ
		// 3) Attack Flag false ��ȯ
		// 4) Trace Flag true ��ȯ, Trace ���·� ��ȯ
		if (ani->IsActiveAnimationComplete() == true
			&& moveComplete == true)
		{

			mAttackBox->SetAttackReadyFlag(false);

			list->clear();

			SetAttackFlag(false);

			//SetTraceFlag(true);
			//SetMonsterState(MonsterState::Trace);

			SetPatrolFlag(true);
			SetMonsterState(MonsterState::Patrol);
		}
	}

	void CarleonRecruit::Hit()
	{
		Animator* at = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();

		// AttackReady�߿� �ǰݴ��ϸ� 
		// 1) mTimer�� 0.0f�� �ʱ�ȭ 
		// 2) AttackReady���࿩�θ� false�� ����
		// 3) mbAttack�� false�� ����
		mTimer = 0.0f;
		mAttackBox->SetAttackReadyFlag(false);
		SetAttackFlag(false);
			
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
		// ������ ���ݹ��� ������ �ʱ�ȭ���ش�.
		SetMonsterHitDirection(MonsterDirection::None);

		// ���ݹ��� �� ���� ������ Trace ���·� ��ȯ
		if (rb->GetGround() == true)
		{
			//SetMonsterState(MonsterState::Idle);
			//if (GetMonsterDirection() == MonsterDirection::Left)
			//{
			//	at->PlayAnimation(L"Idle_L", true);
			//}
			//if (GetMonsterDirection() == MonsterDirection::Right)
			//{
			//	at->PlayAnimation(L"Idle_R", true);
			//}
			SetMonsterState(MonsterState::Trace);
		}
	}
}