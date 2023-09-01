#pragma once
#include "vanSkill.h"

namespace van
{
	class SeolEffect : public Skill
	{
	public:
		enum class SeolEffectState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		SeolEffect();
		virtual ~SeolEffect();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		__forceinline void SetState(SeolEffectState _state) { mState = _state; }
		__forceinline SeolEffectState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();

	private:
		SeolEffectState mState = SeolEffectState::None;
		bool mbSetFlag = false;		// �ִϸ��̼� ����� ���� ���� �Ϸ� ����
	};
}

