#pragma once
#include "vanGameObject.h"



namespace van
{
	class Animator;
	class PlayerAttack;
	class Skull;

	class Player : public GameObject
	{
	public:
		enum class PlayerState
		{
			Idle,
			Walk,
			Jump,
			Dash,
			AttackA,
			AttackB,
			JumpAttack,
			DoubleJump,
			DoubleDash,
			Fall,
			DownFall,
			None,
		};
		
		enum class PlayerDirection
		{
			Left,
			Right,
			None,
		};

		Player();
		virtual ~Player();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		//void ChangeState(PlayerState _state);
		//void StillSameState();

		void ShowStatus(HDC _hdc);	// Player ���� ���� ������ ȭ�� ���� ��ܿ� ���
		void Idle();
		void Walk();
		void Jump();
		void Dash();
		void AttackA();
		void AttackB();
		void JumpAttack();
		void DoubleJump();
		void DoubleDash();
		void Fall();

		void Skill();

		__forceinline PlayerDirection GetPlayerDirection() { return mDirection; }
		__forceinline PlayerState GetPlayerState() { return mState; }
		__forceinline bool GetCombo() { return mbCombo; }

		__forceinline float GetHp() { return mHp; }
		__forceinline void SetHp(float _hp) { mHp = _hp; }
		__forceinline float GetMaxHp() { return mMaxHp; }
		__forceinline float SetMaxHp(float _hp) { mMaxHp = _hp; }
		__forceinline void AddHp(float _hp) 
		{ 
			mHp += _hp; 
			if (mHp > mMaxHp)
			{
				mHp = mMaxHp;
			}
		}
		__forceinline void LoseHp(float _hp) 
		{
			mHp -= _hp;
			if (mHp < 0)
			{
				mHp = 0;
			}
		}

		__forceinline float GetCoin() { return mCoin; }
		__forceinline void SetCoin(float _coin) { mCoin = _coin; }
		__forceinline void AddCoin(float _coin) { mCoin += _coin; }
		__forceinline void LoseCoin(float _coin) { mCoin -= _coin; }

		__forceinline float GetBone() { return mBone; }
		__forceinline void SetBone(float _bone) { mBone = _bone; }
		__forceinline float GetJewelry() { return mJewelry; }
		__forceinline void SetJewelry(float _jewelry) { mJewelry = _jewelry; }

	private:
		PlayerState mState;				// ���� Player�� ����
		PlayerDirection mDirection;		// ���� Player�� �ٶ󺸰� �ִ� ���� (Left, Right)
		bool mbDoubleKey;				// ����Ű �Է� ���� (����Ű���� ���)
		UINT mJumpCnt;					// Jump Ƚ�� (�ִ� 2��)
		UINT mDashCnt;					// Dash Ƚ�� (�ִ� 2��)
		bool mbCombo;					// AttackA ���� AttackB ���࿩��
		bool mbAttackMove;				// AttackA�� ��ġ �̵� ����
		bool mbAttackMove2;				// AttackB�� ��ġ �̵� ����
		float mDashX1 = 0.0f;			// Dash ��������
		float mDashX2 = 0.0f;			// Dash ��������
		float mAttackDashX1 = 0.0f;		// AttackDash ��������
		float mAttackDashX2 = 0.0f;		// AttackDash ��������
		PlayerAttack* attackBox;		// Player�� �⺻���� �浹 ���� ����
		bool mbFallAniFlag = true;
		bool mbFallRepeatAniFlag = true;

		float mHp;
		float mMaxHp = 100.0f;
		float mCoin;
		float mBone;
		float mJewelry;

		bool mbSkullLess;	// �Ӹ� ����
		bool mbSkillFlag;	//	��ų �ߵ�����
		float mHeadTime;
		float mCoolTime;

		Skull* head;
	};
}