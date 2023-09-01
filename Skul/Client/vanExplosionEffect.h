#pragma once
#include "vanSkill.h"

namespace van
{
	class ExplosionEffect : public Skill
	{
	public:
		enum class ExplosionEffectState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		ExplosionEffect();
		virtual ~ExplosionEffect();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		__forceinline void SetState(ExplosionEffectState _state) { mState = _state; }
		__forceinline ExplosionEffectState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();

	private:
		ExplosionEffectState mState = ExplosionEffectState::None;
		bool mbSetFlag = false;		// �ִϸ��̼� ����� ���� ���� �Ϸ� ����
	};
}

