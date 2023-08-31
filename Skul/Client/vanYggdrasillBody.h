#pragma once
#include "vanGameObject.h"
#include "vanTransform.h"

namespace van
{
	class YggdrasillBody : public GameObject
	{
	public:
		enum class BodyState
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
		YggdrasillBody();
		virtual ~YggdrasillBody();

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

		void SetOwnerPos();
		void ChkNextPhase();

		__forceinline void SetPos(math::Vector2 _pos) { GetComponent<Transform>()->SetPosition(_pos); }
		__forceinline math::Vector2 GetPos() { return GetComponent<Transform>()->GetPosition(); }

		__forceinline GameObject* GetOwner() { return mOwner; }
		__forceinline void SetOwner(GameObject* _owner) { mOwner = _owner; }

		__forceinline BodyState GetState() { return mState; }
		__forceinline void SetState(BodyState _state) { mState = _state; }

		__forceinline bool GetFinishFlag() { return mbFinish; }
		__forceinline void SetFinishFlag(bool _flag) { mbFinish = _flag; }

	private:
		GameObject* mOwner;
		BodyState mState = BodyState::None;
		BodyState mPastState = BodyState::None;
		bool mbCPhaseonfirm = true;		// Phase Ȯ�� ���� (true = �ؾ���, false = ����)

		bool mbFinish = false;			// ��ü�� ������ �������� �˷��ش�.
		bool mbEnd = false;
		bool mbPlayAnimation = true;

		// Idle
		float mTime = 0.0f;
		bool mUpDownFlag = false;

		// MagicOrb Ready

		// MagicOrb Attack

		// MagicOrb End

	};
}

