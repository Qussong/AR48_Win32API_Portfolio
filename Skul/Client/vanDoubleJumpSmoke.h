#pragma once
#include "vanSkill.h"

namespace van
{
	class DoubleJumpSmoke : public Skill
	{
	public:
		enum class DoubleJumpSmokeState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		DoubleJumpSmoke();
		virtual ~DoubleJumpSmoke();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		__forceinline void SetState(DoubleJumpSmokeState _state) { mState = _state; }
		__forceinline DoubleJumpSmokeState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();

	private:
		DoubleJumpSmokeState mState = DoubleJumpSmokeState::None;
		bool mbSetFlag = false;		// �ִϸ��̼� ����� ���� ���� �Ϸ� ����
	};
}