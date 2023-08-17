#pragma once
#include "vanGameObject.h"


namespace van
{
	class Animator;
	class MonsterTrace;
	class MonsterAttack;

	class Monster : public GameObject
	{
	public:
		enum class MonsterState
		{
			Gen,
			Idle,
			Walk,
			Patrol,
			Trace,
			AttackReady,
			Attack,
			AttackEnd,
			Hit,
			Dead,
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

		virtual void Gen();
		virtual void Idle();
		virtual void Walk();
		virtual void Patrol();
		virtual void Trace();
		virtual void AttackReady();
		virtual void Attack();
		virtual void AttackEnd();
		virtual void Hit();
		virtual void Dead();

		__forceinline GameObject* GetMonsterTarget() { return mTarget; }
		__forceinline void SetMonsterTarget(GameObject* _target) { mTarget = _target; }

		__forceinline MonsterState GetMonsterState() { return mState; }
		__forceinline void SetMonsterState(MonsterState _state) { mState = _state; }
		
		__forceinline MonsterState GetMonsterPastState() { return mPastState; }
		__forceinline void SetMonsterPastState(MonsterState _state) { mPastState = _state; }

		__forceinline MonsterDirection GetMonsterDirection() { return mDirection; }
		__forceinline void SetMonsterDirection(MonsterDirection _direction) { mDirection = _direction; }

		__forceinline MonsterDirection GetMonsterPastDirection() { return mPastDirection; }
		__forceinline void SetMonsterPastDirection(MonsterDirection _direction) { mPastDirection = _direction; }

		__forceinline MonsterDirection GetMonsterHitDirection() { return mHitDirection; }
		__forceinline void SetMonsterHitDirection(MonsterDirection _direction) { mHitDirection = _direction; }

		__forceinline float GetTimer() { return mTimer; }
		__forceinline void SetTimer(float _timer) { mTimer = _timer; }
		__forceinline void AddTimer(float _time) { mTimer += _time; }

		__forceinline bool GetPatrolFlag() { return mbPatrol; }
		__forceinline void SetPatrolFlag(bool _flag) { mbPatrol = _flag; }

		__forceinline bool GetTraceFlag() { return mbTrace; }
		__forceinline void SetTraceFlag(bool _flag) { mbTrace = _flag; }

		__forceinline bool GetAttackFlag() { return mbAttack; }
		__forceinline void SetAttackFlag(bool _flag) { mbAttack = _flag; }

		__forceinline bool GetPlayAnimation() { return mbPlayAnimation; }
		__forceinline void SetPlayAnimation(bool _flag) { mbPlayAnimation = _flag; }

		__forceinline bool GetWallFlag() { return mbWallFlag; }
		__forceinline void SetWallFlag(bool _flag) { mbWallFlag = _flag; }

		__forceinline MonsterTrace* GetMonsterTraceBox() { return mTraceBox; }

		__forceinline MonsterAttack* GetMonsterAttackBox() { return mAttackBox; }

		__forceinline int GetAttackCnt() { return mAttackCnt; }
		__forceinline void SetAttackCnt(int _cnt) { mAttackCnt = _cnt; }
		__forceinline void AddAttackCnt() { mAttackCnt += 1; }

	private:
		GameObject* mTarget;			// Monster�� ��ǥ���(Trace)

		MonsterState mState;
		MonsterState mPastState;
		MonsterDirection mDirection;
		MonsterDirection mPastDirection;
		MonsterDirection mHitDirection;

		float mTimer;
		bool mbPatrol;			// Monster�� �� ���¿��� Patrol �ൿ�� ���̵��� ����
		bool mbTrace;			// Monster�� �� ���¿��� Trace �ൿ�� ���̵��� ����
		bool mbAttack;			// Monster�� �� ���¿��� Attack �ൿ�� ���̵��� ����
		bool mbPlayAnimation;	// Animation ��� ����
		bool mbWallFlag;		// ���� �ε����� ��

		MonsterTrace* mTraceBox;	// Monster�� Trace���� ����
		MonsterAttack* mAttackBox;	// Monster�� Attack���� ����

		float mDeathTime;
		int mAttackCnt;
	};
}

