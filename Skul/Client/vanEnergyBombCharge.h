#pragma once
#include "vanSkill.h"

namespace van
{
	class EnergyBombCharge : public Skill
	{
	public:
		enum class EnergyBombChargeState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		EnergyBombCharge();
		virtual ~EnergyBombCharge();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		__forceinline void SetState(EnergyBombChargeState _state) { mState = _state; }
		__forceinline EnergyBombChargeState GetState() { return mState; }

		__forceinline bool GetChargeFinishFlag() { return mbChargeFinish; }

		void Gen();
		void Active();
		void Dead();

	private:
		EnergyBombChargeState mState = EnergyBombChargeState::None;
		bool mbSetFlag = false;		// �ִϸ��̼� ����� ���� ���� �Ϸ� ����
		bool mbChargeFinish = false;
	};
}

