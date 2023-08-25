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
		void FistSlam();	// �����ư��鼭 �ָ����
		void Swipe();		// �ٴ� ����
		void MagicOrbs();	// ������ ����������
		void FistSlamEnd();
		void SwipeEnd();
		void MagicOrbsEnd();

		BossState GetState() { return mState; }
		void SetState(BossState _state) { mState = _state; }

		YggdrasillHead* GetHead() { return mHead; }

		math::Vector2 GetInitPos() { return mInitPos; }

		void AddFistSlamCnt() { mFistSlamCnt += 1; }
		int GetFistSlamCnt() { return mFistSlamCnt; }

		BossSkill GetAttackCase() { return mAttackCase; }
		void SetAttackCase(BossSkill _case) { mAttackCase = _case; }

	private:
		YggdrasillBody* mBody = nullptr;		// ��ü
		YggdrasillHead* mHead = nullptr;		// �Ӹ�
		YggdrasillChin* mChin = nullptr;		// ��
		YggdrasillHand* mHandLeft = nullptr;	// �޼�
		YggdrasillHand* mHandRight = nullptr;	// ������

		BossState mState = BossState::None;

		float mTime = 0.0f;

		int mHp;
		int mArmor;
		bool mbChooseSkill = false;				// ���ݽ�ų ���� ����
		BossSkill mAttackCase = BossSkill::None;
		math::Vector2 mInitPos = math::Vector2::Zero;

		int mFistSlamCnt = 0;
	};
}

