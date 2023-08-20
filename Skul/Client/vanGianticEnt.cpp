#include "vanGianticEnt.h"
#include "vanCollider.h"
#include "vanRigidBody.h"
#include "vanAnimator.h"
#include "vanMonsterAttack.h"
#include "vanTransform.h"
#include "vanResourceManager.h"
#include "vanTexture.h"



namespace van
{
	GianticEnt::GianticEnt()
	{
		// nothing
	}

	GianticEnt::~GianticEnt()
	{
		// nothing
	}

	void GianticEnt::Init()
	{
		Monster::Init();

		MakeAnimation();

		// Monster �ʱ⼳��
		SetMonsterState(MonsterState::Gen);									// ����
		GetComponent<Collider>()->SetSize(math::Vector2(100.0f, 200.0f));	// �浹ü ũ�� ����
		GetComponent<RigidBody>()->SetMass(10.0f);							// ���� ����
		GetComponent<Animator>()->SetScale(math::Vector2(2.0f, 2.0f));		// �̹��� ������ ����

		// attackBox�� �ʱⰪ ����
		MonsterAttack* attackBox = GetMonsterAttackBox();
		attackBox->SetOwner(this);
		attackBox->SetNotifyFlag(true);
		attackBox->GetComponent<Collider>()->SetSize(math::Vector2(600.0f, 250.0f));
		attackBox->SetOffset(math::Vector2(0.0f, -25.0f));
	}

	void GianticEnt::Update()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		// attackBox ������
		MonsterAttack* attackBox = GetMonsterAttackBox();
		attackBox->SetOwnerPos(pos);
		attackBox->SetOwnerState((UINT)GetMonsterState());
		attackBox->SetOwnerDirection((UINT)GetMonsterDirection());

		GameObject::Update();

		switch (GetMonsterState())
		{
		case MonsterState::Gen:
			Gen();
			break;
		case MonsterState::Idle:
			Idle();
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
		default:
			__noop;
		}

		// �ǰ�Ƚ�� 2ȸ�� ����
		if (GetAttackCnt() > 2)
		{
			SetMonsterState(MonsterState::Dead);
		}
	}

	void GianticEnt::Render(HDC _hdc)
	{
		Monster::Render(_hdc);
	}

	void GianticEnt::MakeAnimation()
	{
		Monster::MakeAnimation();

		Animator* animator = GetComponent<Animator>();
		animator->CreateAnimation(L"Idle", ResourceManager::Find<Texture>(L"GianticEnt_Idle"), math::Vector2(0.0f, 0.0f), math::Vector2(115.0f, 114.0f), 5);
		animator->CreateAnimation(L"Attack_Melee_Ready", ResourceManager::Find<Texture>(L"GianticEnt_Attack_Melee_Ready"), math::Vector2(0.0f, 0.0f), math::Vector2(140.0f, 112.0f), 4);
		animator->CreateAnimation(L"Attack_Melee", ResourceManager::Find<Texture>(L"GianticEnt_Attack_Melee"), math::Vector2(0.0f, 0.0f), math::Vector2(140.0f, 112.0f), 4);
		animator->CreateAnimation(L"Attack_Range_Ready", ResourceManager::Find<Texture>(L"GianticEnt_Attack_Range_Ready"), math::Vector2(0.0f, 0.0f), math::Vector2(134.0f, 115.0f), 2);
		animator->CreateAnimation(L"Attack_Range", ResourceManager::Find<Texture>(L"GianticEnt_Attack_Range"), math::Vector2(0.0f, 0.0f), math::Vector2(134.0f, 115.0f), 2);
	}

	void GianticEnt::OnCollisionEnter(Collider* _other)
	{
		Monster::OnCollisionEnter(_other);
	}

	void GianticEnt::OnCollisionStay(Collider* _other)
	{
		Monster::OnCollisionStay(_other);
	}

	void GianticEnt::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void GianticEnt::Gen()
	{
		Animator* at = GetComponent<Animator>();
		if (GetPlayAnimation() == true)
		{
			at->PlayAnimation(L"Monster_Generate");
			SetPlayAnimation(false);
		}

		if (at->IsActiveAnimationComplete())
		{
			SetMonsterDirection(MonsterDirection::Center);	// ����
			SetMonsterState(MonsterState::Idle);			// ����
			SetPlayAnimation(true);
		}
	}

	void GianticEnt::Idle()
	{
		Animator* at = GetComponent<Animator>();

		if (GetPlayAnimation())
		{
			at->PlayAnimation(L"Idle", true);
			SetPlayAnimation(false);
		}
		if (mbAttackEnd == true)
		{
			AddTimer(Time::GetDeltaTime());
			if (GetTimer() >= 1.0f)
			{
				SetTimer(0.0f);
				mbAttackEnd = false;
			}
		}
		else
		{
			// Attack ������ �÷��̾ ������ Attack Ready ����
			if (GetAttackFlag() == true)
			{
				SetMonsterState(MonsterState::AttackReady);
				SetPlayAnimation(true);
			}
		}
	}

	void GianticEnt::Walk()
	{
		// notjing
	}

	void GianticEnt::Patrol()
	{
		// notjing
	}

	void GianticEnt::Trace()
	{
		// notjing
	}

	void GianticEnt::AttackReady()
	{
		// Melee || Range �������� ����
		if (mbChooseSkill == false)
		{
			srand((UINT)time(NULL));
			mAttackCase = (MonsterSkill)(rand() % 2);	// 0 = Melee , 1 = Range
			mbChooseSkill = true;
		}

		// �ش��ϴ� ���������� �غ��ڼ��� ����
		// ���� �ð��� ������ Attack ���·� �Ѿ
		switch (mAttackCase)
		{
		case MonsterSkill::Melee:
			AttackMeleeReady();
			break;
		case MonsterSkill::Range:
			AttackRangeReady();
			break;
		default:
			__noop;
		}
	}

	void GianticEnt::Attack()
	{
		// �ش��ϴ� ���������� ������ ����
		switch (mAttackCase)
		{
		case MonsterSkill::Melee:
			AttackMelee();
			break;
		case MonsterSkill::Range:
			AttackRange();
			break;
		default:
			__noop;
		}
	}

	void GianticEnt::AttackEnd()
	{
		// Idle ���·� �ѱ�� 
		// 1�� �����ϴٰ� �ٽ� ���ݹ����ȿ� �ִٸ� ���ݼ���
		mbAttackEnd = true;
		SetMonsterState(MonsterState::Idle);
		SetPlayAnimation(true);
		// ���ݽ�ų�� �ٽ� �����ؾ��ϱ⿡ false�� ����
		mbChooseSkill = false;
	}

	void GianticEnt::Hit()
	{
		SetPlayAnimation(true);
	}

	void GianticEnt::Dead()
	{
		Monster::Dead();
	}

	void GianticEnt::Wall()
	{
		// nothing
	}

	void GianticEnt::AttackMeleeReady()
	{
		Animator* at = GetComponent<Animator>();
		// ���� �غ������ ��
		if (GetMonsterState() == Monster::MonsterState::AttackReady)
		{
			// Attack Ready �ִϸ��̼� ���
			if (GetPlayAnimation() == true)
			{
				at->PlayAnimation(L"Attack_Melee_Ready", false);
				SetPlayAnimation(false);
			}
			// Attack ���·� ��ȯ
			if (at->IsActiveAnimationComplete() == true)
			{
				// �ð� ī��Ʈ
				AddTimer(Time::GetDeltaTime());
				// 2�� �̻��� �Ǹ� ���ݻ��·� ��ȯ
				if (GetTimer() >= 2.0f)
				{
					SetTimer(0.0f);
					SetMonsterState(MonsterState::Attack);
					SetPlayAnimation(true);
				}
			}
		}
	}

	void GianticEnt::AttackMelee()
	{
		Animator* at = GetComponent<Animator>();
		// ���� ������ ��
		if (GetMonsterState() == Monster::MonsterState::Attack)
		{
			// Attack Ready �ִϸ��̼� ���
			if (GetPlayAnimation() == true)
			{
				at->PlayAnimation(L"Attack_Melee", false);
				SetPlayAnimation(false);
			}

			if (at->IsActiveAnimationComplete())
			{
				SetMonsterState(MonsterState::AttackEnd);
			}
		}
	}

	void GianticEnt::AttackRangeReady()
	{
		Animator* at = GetComponent<Animator>();
		// ���� �غ������ ��
		if (GetMonsterState() == Monster::MonsterState::AttackReady)
		{
			// Attack Ready �ִϸ��̼� ���
			if (GetPlayAnimation() == true)
			{
				at->PlayAnimation(L"Attack_Range_Ready", false);
				SetPlayAnimation(false);
			}

			// Attack ���·� ��ȯ
			if (at->IsActiveAnimationComplete() == true)
			{
				// �ð� ī��Ʈ
				AddTimer(Time::GetDeltaTime());
				// 2�� �̻��� �Ǹ� ���ݻ��·� ��ȯ
				if (GetTimer() >= 2.0f)
				{
					SetTimer(0.0f);
					SetMonsterState(MonsterState::Attack);
					SetPlayAnimation(true);
				}
			}
		}
	}

	void GianticEnt::AttackRange()
	{
		Animator* at = GetComponent<Animator>();
		// ���� ������ ��
		if (GetMonsterState() == Monster::MonsterState::Attack)
		{
			// Attack Ready �ִϸ��̼� ���
			if (GetPlayAnimation() == true)
			{
				at->PlayAnimation(L"Attack_Range", false);
				SetPlayAnimation(false);
			}
		
			if (at->IsActiveAnimationComplete())
			{
				SetMonsterState(MonsterState::AttackEnd);
			}
		}
	}

}