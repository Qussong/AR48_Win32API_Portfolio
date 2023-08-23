#pragma once
#include "vanBoss.h"

namespace van
{
	class FireBall;

	class Mage : public Boss
	{
	public:
		enum class BossSkill
		{
			FireBall,
			RangeFire1,
			RangeFire2,
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

		bool mbAnimationFlag = false;	// �ִϸ��̼� ������ ��� (RangeFire_Ready)

		// FireBall
		int mFireBallCnt = 0;
		bool mbShoot = true;
		std::vector<FireBall*> mListFireBall;
	};
}

