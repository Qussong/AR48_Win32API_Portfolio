#pragma once
#include "vanSkill.h"

namespace van
{
	class WorldOnFireFireBall;

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

		void Gen();
		void Active();
		void Dead();

		__forceinline void SetState(OrbState _state) { mState = _state; }
		__forceinline OrbState GetState() { return mState; }

		__forceinline GameObject* GetTarget() { return mTarget; }

		__forceinline void AddFireBallDeadCnt() { mFireBallDeadCnt += 1; }
	private:
		OrbState mState = OrbState::None;
		GameObject* mTarget = nullptr;
		bool mbShoot = true;	// FireBall �߻� ����
		float mShootDelay = 0.0f;	// FireBall �߻� Delay
		int mFireBallCnt = 0;
		int mFireBallDeadCnt = 0;
	};
}

