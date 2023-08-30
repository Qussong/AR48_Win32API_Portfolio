#pragma once
#include "vanSkill.h"

namespace van
{
	class FinishMoveReady : public Skill
	{
	public:
		enum class FinishMoveReadyState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		FinishMoveReady();
		virtual ~FinishMoveReady();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		__forceinline void SetState(FinishMoveReadyState _state) { mState = _state; }
		__forceinline FinishMoveReadyState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();

	private:
		FinishMoveReadyState mState = FinishMoveReadyState::None;
		//bool mbSetFlag = false;		// �ִϸ��̼� ����� ���� ���� �Ϸ� ����
		bool mbPlayAnimation = true;
	};
}

