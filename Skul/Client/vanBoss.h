#pragma once
#include "vanGameObject.h"

namespace van
{
	class Boss : public GameObject
	{
	public:
		enum class BossState
		{
			Gen,
			Idle,
			Walk,
			AttackReady,
			Attack,
			AttackEnd,
			Hit,
			Dead,
			TakeOff,	// Mage ����
			None,
		};

		enum class BossDirection
		{
			Left,
			Right,
			Center,
			None
		};

	public:
		Boss();
		~Boss();
		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		float GetHp() { return mHp; }
		void SetHp(float _hp) { mHp = _hp; }
		float GetMaxHp() { return mMaxHp; }
		void SetMaxHp(float _hp) { mMaxHp = _hp; }
		void AddHp(float _heal) { mHp += _heal; }
		void LoseHp(float _damage) { mHp -= _damage; }

		BossState GetBossState() { return mBossState; }
		void SetBossState(BossState _state) { mBossState = _state; }

		BossDirection GetBossDirection() { return mBossDirection; }
		void SetBossDirection(BossDirection _direction) { mBossDirection = _direction; }

		GameObject* GetTarget() { return mTarget; }
		void SetTartget(GameObject* _obj) { mTarget = _obj; }

		__forceinline float GetTimer() { return mTimer; }
		__forceinline void SetTimer(float _timer) { mTimer = _timer; }
		__forceinline void AddTimer(float _time) { mTimer += _time; }

		virtual void Gen();
		virtual void Idle();
		virtual void Walk();
		virtual void AttackReady();
		virtual void Attack();
		virtual void AttackEnd();
		virtual void Hit();
		virtual void Dead();
		virtual void Special();

	private:
		float mHp;
		float mMaxHp;

		BossState mBossState = BossState::None;
		BossDirection mBossDirection = BossDirection::None;
		float mTimer;
		GameObject* mTarget;	// Init()���� �ڵ����� �ش� Scene�� Ÿ������ �����Ѵ�.
	};
}

