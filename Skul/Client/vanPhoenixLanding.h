#pragma once
#include "vanSkill.h"

namespace van
{
	class PhoenixLanding : public Skill
	{
	public:
		enum class PhoenixLandingState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		PhoenixLanding();
		virtual ~PhoenixLanding();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		void Gen();
		void Active();
		void Dead();

		__forceinline void SetState(PhoenixLandingState _state) { mState = _state; }
		__forceinline PhoenixLandingState GetState() { return mState; }

		__forceinline bool GetEffectFinishFlag() { return mbEffectFinish; }

	private:
		PhoenixLandingState mState = PhoenixLandingState::None;
		bool mbSetFlag = false;		// �ִϸ��̼� ����� ���� ���� �Ϸ� ����
		bool mbEffectFinish = false;
		//std::set<GameObject*> mAttackList;
	};
}

