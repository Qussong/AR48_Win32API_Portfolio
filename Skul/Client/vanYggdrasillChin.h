#pragma once
#include "vanGameObject.h"
#include "vanTransform.h"

namespace van
{
	class YggdrasillChin : public GameObject
	{
	public:
		enum class ChinState
		{
			Gen,
			Idle,
			AttackReady,
			Attack,
			AttackEnd,
			Dead,
			None,
		};

	public:
		YggdrasillChin();
		virtual ~YggdrasillChin();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other);	// �浹����
		virtual void OnCollisionExit(class Collider* _other);	// �浹���� ���

		void Gen();
		void Idle();
		void AttackReady();
		void Attack();
		void AttackEnd();
		void Dead();

		// AttackReady
		void FistSlamReady();
		void SwipeReady();
		void MagicOrbsReady();
		// Attack
		void FistSlamAttack();
		void SwipeAttack();
		void MagicOrbsAttack();
		// AttackEnd
		void FistSlamEnd();
		void SwipeEnd();
		void MagicOrbsEnd();

		void FollowHeadPos();

		__forceinline void SetPos(math::Vector2 _pos) { GetComponent<Transform>()->SetPosition(_pos); }
		__forceinline math::Vector2 GetPos() { return GetComponent<Transform>()->GetPosition(); }

		__forceinline GameObject* GetOwner() { return mOwner; }
		__forceinline void SetOwner(GameObject* _owner) { mOwner = _owner; }

		__forceinline ChinState GetState() { return mState; }
		__forceinline void SetState(ChinState _state) { mState = _state; }

		__forceinline bool GetFinishFlag() { return mbFinish; }
		__forceinline void SetFinishFlag(bool _flag) { mbFinish = _flag; }

	private:
		GameObject* mOwner;
		ChinState mState = ChinState::None;
		ChinState mPastState = ChinState::None;

		bool mbFinish = false;						// ��ü�� ������ �������� �˷��ش�.
		bool mbEnd = false;
		bool mbPlayAnimation = true;

		// Idle
		float mTime = 0.0f;
		bool mUpDownFlag = false;
		math::Vector2 mInitAddPos = math::Vector2::Zero;	// Head ���� �ʱⰪ(= �ʱ�ȭ��)
		math::Vector2 mAddPos = math::Vector2::Zero;

	};
}


