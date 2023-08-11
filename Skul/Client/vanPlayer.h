#pragma once
#include "vanGameObject.h"



namespace van
{
	class Animator;
	class PlayerAttack;

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

		__forceinline PlayerDirection GetPlayerDirection() { return mDirection; }
		__forceinline PlayerState GetPlayerState() { return mState; }
		//__forceinline void SetPlayerState(PlayerState _state) { mState = _state; }
		__forceinline bool GetCombo() { return mbCombo; }

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
	};
}