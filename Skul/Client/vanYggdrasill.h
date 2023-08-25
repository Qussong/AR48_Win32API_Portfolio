#pragma once
#include "vanBoss.h"
#include "vanYggdrasillBody.h"
#include "vanYggdrasillHead.h"
#include "vanYggdrasillChin.h"
#include "vanYggdrasillHand.h"

namespace van
{
	class Yggdrasill : public Boss
	{
	public:
		enum class BossSkill
		{
			FistSlam,
			Swipe,
			MagicOrbs,
			None,
		};

		enum class AttackHandDir
		{
			Left,
			Right,
			None
		};

	public:
		Yggdrasill();
		~Yggdrasill();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		virtual void Gen() override;
		virtual void Idle() override;
		virtual void AttackReady() override;
		virtual void Attack() override;
		virtual void AttackEnd() override;
		virtual void Hit() override;
		virtual void Dead() override;

		void FistSlamReady();
		void SwipeReady();
		void MagicOrbsReady();
		void FistSlamAttack();	// �����ư��鼭 �ָ����
		void SwipeAttack();		// �ٴ� ����
		void MagicOrbsAttack();	// ������ ����������
		void FistSlamEnd();
		void SwipeEnd();
		void MagicOrbsEnd();

		BossState GetState() { return mState; }
		void SetState(BossState _state) { mState = _state; }

		YggdrasillHead* GetHead() { return mHead; }

		math::Vector2 GetInitPos() { return mInitPos; }

		//void AddFistSlamCnt() { mFistSlamCnt += 1; }
		//int GetFistSlamCnt() { return mFistSlamCnt; }

		BossSkill GetAttackCase() { return mAttackCase; }
		void SetAttackCase(BossSkill _case) { mAttackCase = _case; }

	private:
		YggdrasillBody* mBody = nullptr;		// ��ü
		YggdrasillHead* mHead = nullptr;		// �Ӹ�
		YggdrasillChin* mChin = nullptr;		// ��
		YggdrasillHand* mHandLeft = nullptr;	// �޼�
		YggdrasillHand* mHandRight = nullptr;	// ������

		int mHp = 0;
		int mArmor = 0;
		BossState mState = BossState::None;

		float mTime = 0.0f;
		bool mbChooseSkill = false;						// ���ݽ�ų ���� ����
		BossSkill mAttackCase = BossSkill::None;
		math::Vector2 mInitPos = math::Vector2::Zero;	// ���� ��ġ�� ����(�ʱ�ȭ��)
		AttackHandDir mAttackDir = AttackHandDir::None;	// ������ ������ Hand�� ���� ����

		// FistSlam
		int mFistSlamCnt = 0;

		// Swipe
		int mSwipCnt = 0;

		// MagicOrb
		bool mbShakeFlag = false;
		bool mbMagicOrbShootFlag = false;
		int mMagicOrbCnt = 0;
		bool mbShootDelay = false;

	};
}

