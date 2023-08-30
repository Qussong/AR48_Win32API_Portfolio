#pragma once
#include "vanSkill.h"

namespace van
{
	class WorldOnFireShootEffect : public Skill
	{
	public:
		enum class WorldOnFireShootEffectState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		WorldOnFireShootEffect();
		virtual ~WorldOnFireShootEffect();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		__forceinline void SetState(WorldOnFireShootEffectState _state) { mState = _state; }
		__forceinline WorldOnFireShootEffectState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();

	private:
		WorldOnFireShootEffectState mState = WorldOnFireShootEffectState::None;
		bool mbSetFlag = false;		// �ִϸ��̼� ����� ���� ���� �Ϸ� ����
	};
}

