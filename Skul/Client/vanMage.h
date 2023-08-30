#pragma once
#include "vanBoss.h"

namespace van
{
	class FireBall;
	class RangeFire;
	class PhoenixRandingReady;
	class PhoenixLanding;
	class FinishMoveReady;

	class Mage : public Boss
	{
	public:
		enum class BossSkill
		{
			FireBall,
			RangeFire,
			PhoenixLanding,
			FinishMove,
			None,
		};

	public:
		Mage();
		~Mage();
		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		virtual void Gen() override;
		virtual void Idle() override;
		virtual void Walk() override;
		virtual void AttackReady() override;
		virtual void Attack() override;
		virtual void AttackEnd() override;
		virtual void Hit() override;
		virtual void Dead() override;

		// AttackReady
		void AttackFireBallReady();
		void AttackRangeFireReady();
		void AttackPhoenixLandingReady();
		void AttackFinishMoveReady();

		// Attack
		void AttackFireBall();
		void AttackRangeFire();
		void AttackPhoenixLanding();
		void AttackFinishMove();

		void ComparePosWithBossAndTarget();
		void LandingTimerCnt();
		void TakeOff();
		void ChekDead();
		BossDirection GetBossAttackDirection() { return mBossAttackDirection; }
		void CmdDamage();
		void CmdSkill();

		__forceinline void SetPhoenixLandingEffectFlag(bool _flag) { mbPhoenixLandingEffect = _flag; }

		__forceinline bool GetFinishMoveChargeFlag() { return mbFinishMoveCharge; }
		__forceinline void SetFinishMoveEffectFinishFlag(bool _flag) { mbFinishMoveEffectFinish = _flag; }

	private:
		bool mbPlayAnimation = true;
		bool mbIntroFlag = false;
		bool mbIntroEndFlag = false;
		BossSkill mAttackCase = BossSkill::None;
		bool mbChooseSkill = false;

		BossState mBossPastState = BossState::None;
		BossDirection mBossPastDirection = BossDirection::None;
		BossDirection mBossAttackDirection = BossDirection::None;
		BossDirection mBossPastAttackDirection = BossDirection::None;

		bool mbAnimationReDirectionFlag = false;	

		// FireBall
		int mFireBallCnt = 0;
		bool mbShoot = true;
		std::vector<FireBall*> mListFireBall;

		// RangeFire
		int mRangeFire = 0;
		std::vector<RangeFire*> mListRangeFire;

		// PhoenixLanding
		bool mbPhoenixLandingEffect = false;	// Phoenix Landing Attack �ִϸ��̼� ����Ϸ� ����
		bool PhoenixLandingAnimation = true;	// Phoenix Landing Attack �ִϸ��̼� �������
		bool mbTakeOff = false;			// ��ġ �ʱ�ȭ ����
		PhoenixRandingReady* mReadyEffect = nullptr;
		PhoenixLanding* mAttackEffect = nullptr;
		// mbTakeOff (false -> true) �� �� �� �ʱ�ȭ ��
		float mLandingTimer = 0.0f;						// Delay 10�� ����
		bool mbLandingTimer = false;					// Landing �� �ٽ� �ö󰡱������ Delay �ð� ī��Ʈ ����
		math::Vector2 mInitPos = math::Vector2::Zero;	// ���ƿ������� �ʱ���ġ�� ����
		bool mbSky = false;								// �ʱⰪ true = �ϴÿ� �ִ� -> ��ų ����� �ٽ� ���ƿ����������� false
		// ����ݼ����� �ʱ�ȭ ��
		bool mbRecordPosY = false;	// �ʱ� pos.y �� ���
		bool mbFly = true;			// Ư����ġ�� �����ߴ��� Ȯ�� ���������� false �� �ö󰡾��ϸ� true
		bool mbLand = false;		// ���ϼ��� ���� Ȯ��, �����غ� �Ϸ�Ǹ� true �� ������ false
		
		// FinishMove
		FinishMoveReady* readyEffect = nullptr;	// ����Ʈ ��ü
		bool mbFinishMoveReadyRe = false;		// �غ��ڼ� �ݺ� �������
		float mFinishMoveChargeTime = 0.0f;		// �غ��ڼ� ���� �ð�
		bool mbFinishMoveCharge = false;		// FinishMove �غ�ϷῩ��
		bool mbFinishMoveEffectFinish = false;	// ����Ʈ �ϷῩ��

		float mOrbGenDelay = 0.0f;
		bool mbOrbGenFlag = true;
		int mOrbCnt = 0;

		bool mbCmd = false;
		int mCmdSkill = 3;
		bool mbDead = false;
	};
}

