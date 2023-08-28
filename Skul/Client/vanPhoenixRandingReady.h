#pragma once
#include "vanSkill.h"

namespace van
{
	class PhoenixRandingReady : public Skill
	{
	public:
		enum class PhoenixRandingReadyState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		PhoenixRandingReady();
		virtual ~PhoenixRandingReady();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		__forceinline void SetState(PhoenixRandingReadyState _state) { mState = _state; }
		__forceinline PhoenixRandingReadyState GetState() { return mState; }

		__forceinline bool GetEffectFinishFlag() { return mbEffectFinish; }

		void Gen();
		void Active();
		void Dead();

	private:
		PhoenixRandingReadyState mState = PhoenixRandingReadyState::None;
		bool mbSetFlag = false;		// �ִϸ��̼� ����� ���� ���� �Ϸ� ����
		bool mbEffectFinish = false;
	};
}

