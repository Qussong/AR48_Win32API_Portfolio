#include "vanYggdrasill.h"
#include "vanCollider.h"
#include "vanPlayerAttack.h"
#include "vanPlayer.h"
#include "vanObject.h"
#include "vanEnergyBomb.h"
#include "vanEnergyBombCharge.h"

#define MAX_HP			800.0f
#define INIT_POS_X		Window_X / 2
#define INIT_POS_Y		Window_Y / 2
#define FIST_SLAM_CNT	2
#define SWIPE_CNT		2
#define MAGIC_ORB_CNT	2
#define MAGIC_ORB_DELAY	1.5f
#define DAMAGE_PERCENT	0.5f

namespace van
{
	Yggdrasill::Yggdrasill()
	{
		// nothing
	}

	Yggdrasill::~Yggdrasill()
	{
		// nothing
	}

	void Yggdrasill::Init()
	{
		Boss::Init();		// �ƹ��͵� ����

		MakeAnimation();	// �ƹ��͵� ����

		//SetBossState(BossState::Gen);
		mState = BossState::Idle;
		SetBossDirection(BossDirection::Center);
		mInitPos = math::Vector2(INIT_POS_X, INIT_POS_Y);
		SetMaxHp(MAX_HP);
		SetHp(MAX_HP);

		mBody = Object::Instantiate<YggdrasillBody>(enums::eLayerType::Yggdrasill_Body);
		mHead = Object::Instantiate<YggdrasillHead>(enums::eLayerType::Yggdrasill_Head);
		mChin = Object::Instantiate<YggdrasillChin>(enums::eLayerType::Yggdrasill_Chin);
		mHandLeft = Object::Instantiate<YggdrasillHand>(enums::eLayerType::Yggdrasill_Hand);
		mHandRight = Object::Instantiate<YggdrasillHand>(enums::eLayerType::Yggdrasill_Hand);

		mBody->SetOwner(this);
		mHead->SetOwner(this);
		mChin->SetOwner(this);
		mHandLeft->SetOwner(this);
		mHandRight->SetOwner(this);
		
		mHandLeft->SetHandPos(YggdrasillHand::HandPos::Left);
		mHandRight->SetHandPos(YggdrasillHand::HandPos::Right);

		mBody->SetPos(mInitPos);
	}

	void Yggdrasill::Update()
	{
		Boss::Update();	// �ش� ��ü�� ������ �ִ� Component �Ӽ����� ���� ������Ʈ���ش�.

		// ������ ������ �ֱ�
		CmdDamage();

		switch (mState)
		{
		case BossState::Gen:
			Gen();
			break;
		case BossState::Idle:
		{
			Idle();
			break;
		}
		case BossState::AttackReady:
			AttackReady();
			break;
		case BossState::Attack:
			Attack();
			break;
		case BossState::AttackEnd:
			AttackEnd();
			break;
		case BossState::Hit:
			Hit();
			break;
		case BossState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void Yggdrasill::Render(HDC _hdc)
	{
		Boss::Render(_hdc);	// GameObject�� ������ �ִ� Component Ŭ������ ����ϰ� �ִ� Ŭ�������� Render()ȣ��
	}

	void Yggdrasill::MakeAnimation()
	{
		// nothing
	}

	void Yggdrasill::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void Yggdrasill::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Yggdrasill::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void Yggdrasill::Gen()
	{

	}

	void Yggdrasill::Idle()
	{
		mBody->SetState(YggdrasillBody::BodyState::Idle);
		mHead->SetState(YggdrasillHead::HeadState::Idle);
		mChin->SetState(YggdrasillChin::ChinState::Idle);
		mHandLeft->SetState(YggdrasillHand::HandState::Idle);
		mHandRight->SetState(YggdrasillHand::HandState::Idle);

		mTime += Time::GetDeltaTime();
		// Idle --(3��)--> Attack Ready
		if (mTime >= 3.0f)
		{
			mTime = 0.0f;
			mState = BossState::AttackReady;
		}

		CmdSkill();	// ���� Ŀ�ǵ� ��ų
	}

	void Yggdrasill::AttackReady()
	{
		if (mbChooseSkill == false)
		{
			if (mbCmd == true)
			{
				mAttackCase = (BossSkill)mCmdSkill;
			}
			else
			{
				/*
					FistSlam,	// 0
					Swipe,		// 1
					MagicOrbs,	// 2
				*/
				((UINT)time(NULL));
				mAttackCase = (BossSkill)(rand() % 3);
				//mAttackCase = (BossSkill)(1);
			}
			mbChooseSkill = true;
		}

		if (mbChooseSkill == true)
		{
			switch (mAttackCase)
			{
			case BossSkill::FistSlam:
				FistSlamReady();
				break;
			case BossSkill::Swipe:
				SwipeReady();
				break;
			case BossSkill::MagicOrbs:
				MagicOrbsReady();
				break;
			default:
				__noop;
			}
		}
	}

	void Yggdrasill::Attack()
	{
		switch (mAttackCase)
		{
		case BossSkill::FistSlam:
			FistSlamAttack();
			break;
		case BossSkill::Swipe:
			SwipeAttack();
			break;
		case BossSkill::MagicOrbs:
			MagicOrbsAttack();
			break;
		default:
			__noop;
		}
	}

	void Yggdrasill::AttackEnd()
	{
		switch (mAttackCase)
		{
		case BossSkill::FistSlam:
			FistSlamEnd();
			break;
		case BossSkill::Swipe:
			SwipeEnd();
			break;
		case BossSkill::MagicOrbs:
			MagicOrbsEnd();
			break;
		default:
			__noop;
		}
		// �ʱ�ȭ
		mbCmd = false;
		mCmdSkill = 0;
	}

	void Yggdrasill::Hit()
	{

	}

	void Yggdrasill::Dead()
	{

	}

	void Yggdrasill::FistSlamReady()
	{
		mHandLeft->SetState(YggdrasillHand::HandState::AttackReady);
		mHandRight->SetState(YggdrasillHand::HandState::AttackReady);

		if (mHandLeft->GetFinishFlag() == true
			&& mHandRight->GetFinishFlag() == true)
		{
			mHandLeft->SetFinishFlag(false);
			mHandRight->SetFinishFlag(false);

			mState = BossState::Attack;
		}
	}
	
	void Yggdrasill::SwipeReady()
	{
		mHandLeft->SetState(YggdrasillHand::HandState::AttackReady);
		mHandRight->SetState(YggdrasillHand::HandState::AttackReady);

		if (mHandLeft->GetFinishFlag() == true
			&& mHandRight->GetFinishFlag() == true)
		{
			mHandLeft->SetFinishFlag(false);
			mHandRight->SetFinishFlag(false);

			mState = BossState::Attack;
		}
	}

	void Yggdrasill::MagicOrbsReady()
	{
		mBody->SetState(YggdrasillBody::BodyState::AttackReady);
		mHead->SetState(YggdrasillHead::HeadState::AttackReady);
		mChin->SetState(YggdrasillChin::ChinState::AttackReady);
		mHandLeft->SetState(YggdrasillHand::HandState::AttackReady);
		mHandRight->SetState(YggdrasillHand::HandState::AttackReady);

		if (mBody->GetFinishFlag() == true
			&& mHead->GetFinishFlag() == true
			&& mChin->GetFinishFlag() == true
			&& mbShakeFlag == false)
		{
			mBody->SetFinishFlag(false);
			mHead->SetFinishFlag(false);
			mChin->SetFinishFlag(false);

			mbShakeFlag = true;
			mCharge = Object::Instantiate<EnergyBombCharge>(enums::eLayerType::Yggdrasill_Effect);
			mCharge->SetOwner(mHead);
		}

		if (mbShakeFlag == true)
		{
			mHead->ShakeHead();

			if (mCharge->GetChargeFinishFlag() == true)
			{
				mCharge = nullptr;
				mbShakeFlag = false;
				mState = BossState::Attack;
			}
		}
	}

	void Yggdrasill::FistSlamAttack()
	{
		// �� ������ ���°� ����
		mHandLeft->SetState(YggdrasillHand::HandState::Attack);
		mHandRight->SetState(YggdrasillHand::HandState::Attack);

		GameObject* target = GetTarget();
		math::Vector2 targetPos = target->GetComponent<Transform>()->GetPosition();
		math::Vector2 ownPos = GetComponent<Transform>()->GetPosition();

		// ������ Hand ���� ����
		if(mAttackDir == AttackHandDir::None)
		{
			// target �� own ���� ���ʿ� ���� �� (target.x < own.x)
			if (targetPos.x <= ownPos.x)
			{
				mAttackDir = AttackHandDir::Left;
			}
			// target �� own ���� �����ʿ� ���� �� (target.x > own.x)
			if (targetPos.x > ownPos.x)
			{
				mAttackDir = AttackHandDir::Right;
			}
		}

		// ������ Ƚ����ŭ ���ݼ���
		if (mFistSlamCnt < FIST_SLAM_CNT
			&& mAttackDir != AttackHandDir::None)
		{
			if (mAttackDir == AttackHandDir::Left)
			{
				mHandLeft->FistSlam();
				// ���� �Ϸ�� ����Ƚ�� ī��Ʈ
				if (mHandLeft->GetFistSlamFlag() == true)
				{
					mHandLeft->SetFistSlamFlag(false);
					mAttackDir = AttackHandDir::None;
					++mFistSlamCnt;
				}
			}
			if (mAttackDir == AttackHandDir::Right)
			{
				mHandRight->FistSlam();
				// ���� �Ϸ�� ����Ƚ�� ī��Ʈ
				if (mHandRight->GetFistSlamFlag() == true)
				{
					mHandRight->SetFistSlamFlag(false);
					mAttackDir = AttackHandDir::None;
					++mFistSlamCnt;
				}
			}
		}
		// ������ �Ϸ����� ��
		else
		{
			mHandLeft->FistSlamAfter();
			mHandRight->FistSlamAfter();

			if (mHandLeft->GetFinishFlag() == true
				&& mHandRight->GetFinishFlag() == true)
			{
				// �ʱ�ȭ
				mFistSlamCnt = 0;
				mHandLeft->SetFinishFlag(false);
				mHandRight->SetFinishFlag(false);
				// ���º��� (Attack --> Attack End)
				mState = BossState::AttackEnd;
			}
		}
	}

	void Yggdrasill::SwipeAttack()
	{
		GameObject* target = GetTarget();
		math::Vector2 targetPos = target->GetComponent<Transform>()->GetPosition();
		math::Vector2 ownPos = GetComponent<Transform>()->GetPosition();

		// �� ������ ���°� ����
		mHandLeft->SetState(YggdrasillHand::HandState::Attack);
		mHandRight->SetState(YggdrasillHand::HandState::Attack);

		// ������ Hand ���� ����
		if (mAttackDir == AttackHandDir::None)
		{
			// target �� own ���� ���ʿ� ���� �� (target.x < own.x)
			if (targetPos.x <= ownPos.x)
			{
				mAttackDir = AttackHandDir::Right;
			}
			// target �� own ���� �����ʿ� ���� �� (target.x > own.x)
			if (targetPos.x > ownPos.x)
			{
				mAttackDir = AttackHandDir::Left;
			}
		}

		// ������ Ƚ����ŭ ���ݼ���
		if (mSwipCnt < FIST_SLAM_CNT
			&& mAttackDir != AttackHandDir::None)
		{
			if (mAttackDir == AttackHandDir::Left)
			{
				mHandLeft->Swip();
				// ���� �Ϸ�� ����Ƚ�� ī��Ʈ
				if (mHandLeft->GetSwipeFlag() == true)
				{
					mHandLeft->SetSwipeFlag(false);
					mAttackDir = AttackHandDir::None;
					++mSwipCnt;
				}
			}
			if (mAttackDir == AttackHandDir::Right)
			{
				mHandRight->Swip();
				// ���� �Ϸ�� ����Ƚ�� ī��Ʈ
				if (mHandRight->GetSwipeFlag() == true)
				{
					mHandRight->SetSwipeFlag(false);
					mAttackDir = AttackHandDir::None;
					++mSwipCnt;
				}
			}
		}
		// ������ �Ϸ����� ��
		else
		{
			mSwipCnt = 0;
			// ���º��� (Attack --> Attack End)
			mState = BossState::AttackEnd;
		}

	}

	void Yggdrasill::MagicOrbsAttack()
	{
		mBody->SetState(YggdrasillBody::BodyState::Attack);
		mHead->SetState(YggdrasillHead::HeadState::Attack);
		mChin->SetState(YggdrasillChin::ChinState::Attack);

		if (mBody->GetFinishFlag() == true
			&& mHead->GetFinishFlag() == true
			&& mChin->GetFinishFlag() == true
			&& mbMagicOrbShootFlag == false)
		{
			mBody->SetFinishFlag(false);
			mHead->SetFinishFlag(false);
			mChin->SetFinishFlag(false);

			mbMagicOrbShootFlag = true;
		}

		if (mbMagicOrbShootFlag == true
			&& mMagicOrbCnt <= MAGIC_ORB_CNT)
		{
			if (mHead->GetMagicOrbShootFlag() == false)
			{
				mTime += Time::GetDeltaTime();
				if (mTime >= MAGIC_ORB_DELAY)
				{
					mTime = 0.0f;
					mbShootDelay = true;
				}

				if (mbShootDelay == true)
				{
					mHead->ShootEnerge();
				}
			}
			else
			{
				// EnergyBomb ���� & �߻�
				ShootEnergyBomb();

				mbShootDelay = false;
				++mMagicOrbCnt;
				mHead->SetMagicOrbShootFlag(false);
				mHead->ResetMagicOrbShootMotionValue();
			}
		}

		if (mMagicOrbCnt > MAGIC_ORB_CNT)
		{
			mMagicOrbCnt = 0;
			mBody->SetFinishFlag(false);
			mState = BossState::AttackEnd;
		}
	}

	void Yggdrasill::FistSlamEnd()
	{
		mHandLeft->SetState(YggdrasillHand::HandState::AttackEnd);
		mHandRight->SetState(YggdrasillHand::HandState::AttackEnd);

		if (mHandLeft->GetFinishFlag() == true
			&& mHandRight->GetFinishFlag() == true)
		{
			// �ʱ�ȭ
			mHandLeft->SetFinishFlag(false);
			mHandRight->SetFinishFlag(false);
			mbChooseSkill = false;
			// ���º��� (Attack End --> Idle)
			mState = BossState::Idle;
		}
	}

	void Yggdrasill::SwipeEnd()
	{
		mHandLeft->SetState(YggdrasillHand::HandState::AttackEnd);
		mHandRight->SetState(YggdrasillHand::HandState::AttackEnd);

		if (mHandLeft->GetFinishFlag() == true
			&& mHandRight->GetFinishFlag() == true)
		{
			// �ʱ�ȭ
			mHandLeft->SetFinishFlag(false);
			mHandRight->SetFinishFlag(false);
			mbChooseSkill = false;

			// ���º��� (Attack End --> Idle)
			mState = BossState::Idle;
		}
	}

	void Yggdrasill::MagicOrbsEnd()
	{
		mBody->SetState(YggdrasillBody::BodyState::AttackEnd);
		mHead->SetState(YggdrasillHead::HeadState::AttackEnd);
		mChin->SetState(YggdrasillChin::ChinState::AttackEnd);

		if (mHead->GetFinishFlag() == true)
		{
			int a = 0;
		}

		if (mBody->GetFinishFlag() == true
			&& mHead->GetFinishFlag() == true
			&& mChin->GetFinishFlag() == true)
		{
			// �ʱ�ȭ
			mBody->SetFinishFlag(false);
			mHead->SetFinishFlag(false);
			mChin->SetFinishFlag(false);
			mbChooseSkill = false;

			// ���º��� (Attack End --> Idle)
			mState = BossState::Idle;
		}
	}

	void Yggdrasill::ShootEnergyBomb()
	{
		Transform* tr_head = mHead->GetComponent<Transform>();

		EnergyBomb* energyBomb = Object::Instantiate<EnergyBomb>(enums::eLayerType::Yggdrasill_Skill_EnergyBomb);
		energyBomb->SetOwner(mHead);
		energyBomb->GetComponent<Transform>()->SetPosition(tr_head->GetPosition());
	}

	void Yggdrasill::CmdDamage()
	{
		// FistSlam
		if (Input::GetKey(eKeyCode::M)
			&& Input::GetKeyDown(eKeyCode::D))
		{
			LoseHp(MAX_HP * DAMAGE_PERCENT);
		}
	}

	void Yggdrasill::CmdSkill()
	{
		if (Input::GetKey(eKeyCode::Q)
			&& Input::GetKeyDown(eKeyCode::W))
		{
			mbCmd = true;
			mCmdSkill = 0;
		}
		// Swipe
		if (Input::GetKey(eKeyCode::Q)
			&& Input::GetKeyDown(eKeyCode::E))
		{
			mbCmd = true;
			mCmdSkill = 1;
		}
		// MagicOrb
		if (Input::GetKey(eKeyCode::Q)
			&& Input::GetKeyDown(eKeyCode::R))
		{
			mbCmd = true;
			mCmdSkill = 2;
		}
	}
}