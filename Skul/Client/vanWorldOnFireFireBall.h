#pragma once
#include "vanSkill.h"

namespace van
{
	class WorldOnFireFireBall : public Skill
	{
	public:
		enum class WorldOnFireFireBallState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		WorldOnFireFireBall();
		virtual ~WorldOnFireFireBall();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		void SetState(WorldOnFireFireBallState _state) { mState = _state; }
		WorldOnFireFireBallState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();
		void SetFireBallMove();

	private:
		WorldOnFireFireBallState mState = WorldOnFireFireBallState::None;

		bool mbSetFlag = true;									// ��ü �߻縦 ���� ���� ����
		math::Vector2 mDepartPos = math::Vector2(0.0f, 0.0f);	// �߻�����
		math::Vector2 mTargetPos = math::Vector2(0.0f, 0.0f);	// ��������
		math::Vector2 mDirect = math::Vector2(0.0f, 0.0f);		// ���⺤��
	};
}

