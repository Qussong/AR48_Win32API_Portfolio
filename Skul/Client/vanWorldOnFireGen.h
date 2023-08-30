#pragma once
#include "vanSkill.h"

namespace van
{
	class WorldOnFireGen : public Skill
	{
	public:
		enum class WorldOnFireGenEffectState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		WorldOnFireGen();
		virtual ~WorldOnFireGen();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		__forceinline void SetState(WorldOnFireGenEffectState _state) { mState = _state; }
		__forceinline WorldOnFireGenEffectState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();

	private:
		WorldOnFireGenEffectState mState = WorldOnFireGenEffectState::None;
		bool mbSetFlag = false;		// �ִϸ��̼� ����� ���� ���� �Ϸ� ����
	};
}

