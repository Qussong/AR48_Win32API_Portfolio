#pragma once
#include "vanGameObject.h"


namespace van
{
	class Animator;

	class Monster : public GameObject
	{
	public:
		enum class MonsterState
		{
			Idle,
			Walk,
			Patrol,
			Trace,
			AttackReady,
			Attack,
			Hit,
			None,
		};

		enum class MonsterDirection
		{
			Left,
			Right,
			None,
		};

		Monster();
		virtual ~Monster();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		__forceinline MonsterState GetMonsterState() { return mState; }
		__forceinline void SetMonsterState(MonsterState _state) { mState = _state; }
		
		__forceinline MonsterDirection GetMonsterDirection() { return mDirection; }
		__forceinline void SetMonsterDirection(MonsterDirection _direction) { mDirection = _direction; }

		__forceinline MonsterDirection GetMonsterHitDirection() { return mHitDirection; }
		__forceinline void SetMonsterHitDirection(MonsterDirection _direction) { mHitDirection = _direction; }

		__forceinline bool GetPatroFlag() { return mbPatrol; }
		__forceinline void SetPatroFlag(bool _flag) { mbPatrol = _flag; }

		__forceinline bool GetTraceFlag() { return mbTrace; }
		__forceinline void SetTraceFlag(bool _flag) { mbTrace = _flag; }

		__forceinline bool GetAttackFlag() { return mbAttack; }
		__forceinline void SetAttackFlag(bool _flag) { mbAttack = _flag; }
		
		__forceinline bool GetHitFlag() { return mbHit; }
		__forceinline void SetHitFlag(bool _flag) { mbHit = _flag; }



	private:
		MonsterState mState;
		MonsterDirection mDirection;
		MonsterDirection mHitDirection;

		bool mbPatrol;	// Patrol ����
		bool mbTrace;	// Trace ����
		bool mbAttack;	// Attack ����
		bool mbHit;		// Hit ����
	};
}

