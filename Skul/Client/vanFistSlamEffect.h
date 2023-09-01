#pragma once
#include "vanSkill.h"

namespace van
{
	class FistSlamEffect : public Skill
	{
	public:
		enum class FistSlamEffectState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		FistSlamEffect();
		virtual ~FistSlamEffect();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		__forceinline void SetState(FistSlamEffectState _state) { mState = _state; }
		__forceinline FistSlamEffectState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();

	private:
		FistSlamEffectState mState = FistSlamEffectState::None;
		bool mbSetFlag = false;		// �ִϸ��̼� ����� ���� ���� �Ϸ� ����
	};
}