#pragma once
#include "vanSkill.h"


namespace van
{
	class FireBall : public Skill
	{
	public:
		enum class FireBallState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		FireBall();
		virtual ~FireBall();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		void SetState(FireBallState _state) { mState = _state; }
		FireBallState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();
		void SetFireBallMove();

	private:
		FireBallState mState = FireBallState::None;
	};
}

