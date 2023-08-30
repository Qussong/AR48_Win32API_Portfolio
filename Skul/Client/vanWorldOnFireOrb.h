#pragma once
#include "vanSkill.h"

namespace van
{
	class WorldOnFireOrb : public Skill
	{
	public:
		enum class OrbState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		WorldOnFireOrb();
		virtual ~WorldOnFireOrb();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		void SetState(OrbState _state) { mState = _state; }
		OrbState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();

	private:
		OrbState mState = OrbState::None;
	};
}

