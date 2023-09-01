#pragma once
#include "vanSkill.h"

namespace van
{
	class DashSmoke : public Skill
	{
	public:
		enum class DashSmokeState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		DashSmoke();
		virtual ~DashSmoke();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		__forceinline void SetState(DashSmokeState _state) { mState = _state; }
		__forceinline DashSmokeState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();

	private:
		DashSmokeState mState = DashSmokeState::None;
		bool mbSetFlag = false;		// �ִϸ��̼� ����� ���� ���� �Ϸ� ����

	};
}