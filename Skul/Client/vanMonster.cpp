#include "vanMonster.h"
#include "vanInput.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanCollisionManager.h"
#include "vanObject.h"
#include "vanMonsterTrace.h"
#include "vanMonsterAttack.h"
#include "vanPlayerAttack.h"
#include "vanPlayer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanRigidBody.h"
#include "vanGold.h"
#include "vanSkull.h"

#define WALK_SPEED			150.0f
#define HIT_BUMP_X			50.0f
#define HIT_BUMP_Y			-300.0f
#define WALL_BUMP_X			20.0f
#define WALL_BUMP_Y			-100.0f
#define ATTACK_READY_DELAY	1.0f
namespace van
{
	Monster::Monster()
		: mTarget(nullptr)
		, mState(MonsterState::None)
		, mPastState(MonsterState::None)
		, mDirection(MonsterDirection::None)
		, mPastDirection(MonsterDirection::None)
		, mHitDirection(MonsterDirection::None)
		, mTimer(0.0f)
		, mbPatrol(false)
		, mbTrace(false)
		, mbAttack(false)
		, mbPlayAnimation(true)
		, mbWallFlag(false)
		, mTraceBox(nullptr)
		, mAttackBox(nullptr)
		, mAttackCnt(0)
	{
		AddComponent<RigidBody>();
		mTraceBox = Object::Instantiate<MonsterTrace>(enums::eLayerType::Range_Monster_Trace);
		mAttackBox = Object::Instantiate<MonsterAttack>(enums::eLayerType::Range_Monster_Attack);
	}

	Monster::~Monster()
	{
		Destroy(mTraceBox);
		Destroy(mAttackBox);
	}

	void Monster::Init()
	{
		SceneManager::GetActiveScene()->AddMonsterCnt();
	}

	void Monster::Update()
	{
		GameObject::Update();

		// Animation ������� ����_1
		SetMonsterPastState(GetMonsterState());			// ���� ������ ���¸� ����
		SetMonsterPastDirection(GetMonsterDirection());	// ���� ������ ������ ����

		switch (GetMonsterState())
		{
		case MonsterState::Gen:
			Gen();
			break;
		case MonsterState::Idle:
			Idle();
			break;
		case MonsterState::Walk:
			Walk();
			break;
		case MonsterState::Patrol:
			Patrol();
			break;
		case MonsterState::Trace:
			Trace();
			break;
		case MonsterState::AttackReady:
			AttackReady();
			break;
		case MonsterState::Attack:
			Attack();
			break;
		case MonsterState::AttackEnd:
			AttackEnd();
			break;
		case MonsterState::Hit:
			Hit();
			break;
		case MonsterState::Dead:
			Dead();
			break;
		case MonsterState::Wall:
			Wall();
			break;
		default:
			__noop;
		}

		// �ǰ�Ƚ�� 2ȸ�� ����
		if (mAttackCnt > 2)
		{
			SetMonsterState(MonsterState::Dead);
		}

		// Animation ������� ����_2
		// ���� ������ ����,������ �ٲ��ٸ�
		if (GetMonsterState() != GetMonsterPastState()
			|| GetMonsterDirection() != GetMonsterPastDirection())
		{
			SetPlayAnimation(true);
		}
	}

	void Monster::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Monster::MakeAnimation()
	{
		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(L"Monster_Generate", ResourceManager::Find<Texture>(L"Monster_Generate"), math::Vector2(0.0f, 0.0f), math::Vector2(104.0f, 105.0f), 5);
		animator->CreateAnimation(L"Monster_Destroy", ResourceManager::Find<Texture>(L"Monster_Destroy"), math::Vector2(0.0f, 0.0f), math::Vector2(104.0f, 105.0f), 5);
	}

	void Monster::OnCollisionEnter(Collider* _other)
	{
		// �⺻ ���� �Ӹ� ��ų�� ���ݹ޾��� ���
		GameObject* obj = _other->GetOwner();
		Skull* head = dynamic_cast<Skull*>(obj);
		
		if (head != nullptr)
		{
			Skull::HeadDirection headDirection = head->GetDirection();
			// ���ݹ��� ���� ����
			if (headDirection == Skull::HeadDirection::Left)
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

			AddAttackCnt();
			SetMonsterState(MonsterState::Hit);
		}
	}

	void Monster::OnCollisionStay(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		van::PlayerAttack* attack = dynamic_cast<van::PlayerAttack*>(obj);	// �浹�� ��ü�� Attack Ŭ�������� Ȯ��

		// �浹�� ��ü�� PlayerAttack Ŭ������ ��� == �ǰ�(Hit)����
		if (attack != nullptr
			&& GetMonsterState() != MonsterState::Dead)
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
					AddAttackCnt();
					SetMonsterState(MonsterState::Hit);
					// Hit ������ ������ Patrol ���°� �ƴϱ⿡ Patrol Flag�� ���ش�.
					SetPatrolFlag(false);
				}

				// �������� ������ �浹�� �浹ü ����
				list->insert(this);
			}
		}
	}

	void Monster::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void Monster::Gen()
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

	void Monster::Idle()
	{
		Animator* at = GetComponent<Animator>();

		if (GetWallFlag() == false)
		{
			// Patrol ������ �� 
			if (GetPatrolFlag() == true
				&& GetWallFlag() == false)
			{
				// Trace ������ Player�� ������ ��� Trace ���·� ��ȯ
				if (GetTraceFlag() == true)
				{
					// Patrol �ൿ ���Ͽ� ����ߴ� Timer�� �ʱ�ȭ���ش�.
					SetTimer(0.0f);
					SetMonsterState(MonsterState::Trace);
					return;
				}
				// �ð� ����
				AddTimer(Time::GetDeltaTime());
				// Patrol���½� Idle�� 2�ʰ� ����
				// Idle ���°� 2�� �̻� �����Ǿ��� ��
				if (GetTimer() >= 2.0f)
				{
					SetTimer(0.0f);							// �����ð� 0�ʷ� �ʱ�ȭ
					SetMonsterState(MonsterState::Walk);	// Walk �� ���� ����
					// ������ȯ
					if (GetMonsterDirection() == MonsterDirection::Left)
					{
						SetMonsterDirection(MonsterDirection::Right);
					}
					else
					{
						SetMonsterDirection(MonsterDirection::Left);
					}
					return;
				}
				// ������ �ð��� 3�� �̻��� �ƴ϶��
				else
				{
					// Idle_L
					if (GetMonsterDirection() == MonsterDirection::Left)
					{
						if (GetPlayAnimation() == true)
						{
							at->PlayAnimation(L"Idle_L", true);
							SetPlayAnimation(false);
						}
					}
					// Idle_R
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
			// Attack ������ ��
			else if (GetAttackFlag() == true)
			{
				// �ð� ����
				AddTimer(Time::GetDeltaTime());
				// Attack���½� Idle�� 0.5�ʰ� ����
				if (GetTimer() >= 0.5f)
				{
					SetTimer(0.0f);								// �����ð� 0�ʷ� �ʱ�ȭ
					SetMonsterState(MonsterState::AttackReady);	//	AttackReady�� ���� ����
				}
				// ������ �ð��� 0.5�� �̻��� �ƴ϶��
				else
				{
					// Idle_L
					if (GetMonsterDirection() == MonsterDirection::Left)
					{
						if (GetPlayAnimation() == true)
						{
							at->PlayAnimation(L"Idle_L", true);
							SetPlayAnimation(false);
						}
					}
					// Idle_R
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
		else
		{
			SetMonsterState(MonsterState::Wall);
		}
	}

	void Monster::Walk()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		Animator* at = GetComponent<Animator>();

		if (GetWallFlag() == false)
		{
			// Patrol ������ �� 
			if (GetPatrolFlag() == true)
			{
				// Trace ������ Player�� ������ ���
				if (GetTraceFlag() == true)
				{
					// Patrol �ൿ ���Ͽ� ����ߴ� Timer�� �ʱ�ȭ���ش�.
					SetTimer(0.0f);
					// Trace ���·� �ٷ� ��ȯ
					SetMonsterState(MonsterState::Trace);
					return;
				}
				// �ð� ����
				AddTimer(Time::GetDeltaTime());
				// Patrol���½� Walk�� 2�ʰ� ����
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
					// AttackReady ���·� �ٷ� ��ȯ
					SetMonsterState(MonsterState::AttackReady);
					return;
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
		else
		{
			SetMonsterState(MonsterState::Wall);
		}
	}

	void Monster::Patrol()
	{
		// ���Ͱ� ��� ���¿��� Patrol �ൿ�� ���̵��� ����
		SetPatrolFlag(true);
		// Patrol�� Idle ���� �����ϵ��� �Ѵ�.
		SetMonsterState(MonsterState::Idle);
	}

	void Monster::Trace()
	{
		// Trace ���·� ��ȯ�Ʊ⿡ Patrol, Attack Flag�� ���ش�.
		SetPatrolFlag(false);
		// Trace�� Target�� �Ѿư��⿡ Walk ���� ����
		SetMonsterState(MonsterState::Walk);
	}

	void Monster::AttackReady()
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
		// ī��Ʈ�߿� �ǰݵǸ� Timer ���� (AttackReadyFlag == false)
		AddTimer(Time::GetDeltaTime());

		// ī��Ʈ �Ϸ� (Attack Ready�� �Ϸ�)
		if (GetTimer() >= ATTACK_READY_DELAY)
		{
			// 1) AttackReadyFlag = true
			attackBox->SetAttackReadyFlag(true);
			// 2) Timer ����
			SetTimer(0.0f);
			// 3) Attack ���·� �Ѿ��
			SetMonsterState(Monster::MonsterState::Attack);
		}
	}

	void Monster::Attack()
	{
		Animator* ani = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		Monster::MonsterDirection direction = GetMonsterDirection();
		math::Vector2 velocity = rb->GetVelocity();
		math::Vector2 pos = GetComponent<Transform>()->GetPosition();
		MonsterAttack* attackBox = GetMonsterAttackBox();
		std::set<GameObject*>* list = attackBox->GetMonsterAttackList();

		// Attack Animation���
		if (GetPlayAnimation() == true)
		{
			// Monster Direction == Left �� ���
			if (direction == Monster::MonsterDirection::Left)
			{
				ani->PlayAnimation(L"Attack_L", false);
			}
			// Monster Direction == Right �� ���
			else
			{
				ani->PlayAnimation(L"Attack_R", false);
			}

			SetPlayAnimation(false);
		}

		// ���� �Ϸ�
		// ���� : Attack Animation ��� �Ϸ�
		if (ani->IsActiveAnimationComplete() == true)
		{
			// ������ �����߱⿡ Attack Ready Flag = false �� ��ȯ
			attackBox->SetAttackReadyFlag(false);
			// ���� ��󿡴��� ������ �����ϵ��� AttacList �ʱ�ȭ
			list->clear();
			// ����� �缳�� �� �� �ֵ��� ���ݴ���� Ǯ���ش�.
			SetMonsterTarget(nullptr);
			// Attack End ���� �����
			SetMonsterState(MonsterState::AttackEnd);
		}
	}

	void Monster::AttackEnd()
	{
		if (GetAttackFlag() == true)
		{
			// Idel ���� ���ٰ� 0.5�� �Ŀ� ���� ���غ�
			SetMonsterState(MonsterState::Idle);
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

	void Monster::Hit()
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
			at->PlayAnimation(L"Hit_L", false);
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
			at->PlayAnimation(L"Hit_R", false);
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

		if (rb->GetGround() == true)
		{
			rb->SetHit(false);
			SetMonsterState(MonsterState::AttackReady);
		}
	}

	void Monster::Dead()
	{
		Animator* at = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		if (GetPlayAnimation() == true)
		{
			// �Ҹ� �ִϸ��̼� ���
			at->PlayAnimation(L"Monster_Destroy");
			SetPlayAnimation(false);
		}

		if (at->IsActiveAnimationComplete())
		{
			// ���� ������ ����
			Gold* gold = Object::Instantiate<Gold>(enums::eLayerType::Drop);
			gold->GetComponent<Transform>()->SetPosition(tr->GetPosition());
			// �ش� Scene�� ���� ���� ���ҽ����ֱ�
			SceneManager::GetActiveScene()->LoseMonsterCnt();
			// ��ü �Ҹ�
			Destroy(this);
		}
	}

	void Monster::Wall()
	{
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();
		SetWallFlag(false);
		rb->SetHit(true);
		velocity.x = -WALL_BUMP_X;
		velocity.y = WALL_BUMP_Y;
		rb->SetVelocity(velocity);

		if (rb->GetGround() == true)
		{
			rb->SetHit(false);
			SetMonsterState(MonsterState::Patrol);
		}
	}
}
