#pragma once
#include "vanGameObject.h"

namespace van
{
	class Animator;

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

		void Walk();
		void Idle();
		void Jump();
		void Dash();
		void AttackA();
		void AttackB();
		void JumpAttack();
		void DoubleJump();
		void DoubleDash();
		void Fall();


	private:
		PlayerState mState;
		PlayerDirection mDirection;
		bool mbDoubleKey;
	};
}

