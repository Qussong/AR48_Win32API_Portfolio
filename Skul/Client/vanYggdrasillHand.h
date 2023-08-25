#pragma once
#include "vanGameObject.h"
#include "vanTransform.h"

namespace van
{
	class YggdrasillHand : public GameObject
	{
	public:
		enum class HandPos
		{
			Left,
			Right,
			None,
		};

		enum class HandState
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
		YggdrasillHand();
		virtual ~YggdrasillHand();

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

		void InitAddPos();		// �ʱ���ġ�� ���� -> Left, Right ������ Init���� �� �� ���⿡ Update�� �־��ش�.
		void FollowBodyPos();	// Idle ������ �� Body��ü�� ��ġ�� �������� Hand�� ��ġ���� �����Ѵ�.
		void FistSlam();		// FistSlam ������ �����ϴ� ����
		void FistSlamAfter();	// FistSlam ���ݼ����� Hand ��ġ ������

		__forceinline HandPos GetHandPos() { return mHandPos; }
		__forceinline void SetHandPos(HandPos _pos) { mHandPos = _pos; }

		__forceinline GameObject* GetOwner() { return mOwner; }
		__forceinline void SetOwner(GameObject* _owner) { mOwner = _owner; }

		__forceinline void SetPos(math::Vector2 _pos) { GetComponent<Transform>()->SetPosition(_pos); }
		__forceinline math::Vector2 GetPos() { return GetComponent<Transform>()->GetPosition(); }

		__forceinline HandState GetState() { return mState; }
		__forceinline void SetState(HandState _state) { mState = _state; }

		__forceinline void SetAddPos(math::Vector2 _pos) { mAddPos = _pos; }

		__forceinline bool GetFinishFlag() { return mbFinish; }
		__forceinline void SetFinishFlag(bool _flag) { mbFinish = _flag; }

		__forceinline void SetPlayAnimationFlag(bool _flag) { mbPlayAnimation = _flag; }

		__forceinline bool GetFistSlamFlag() { return mbFistSlam; }
		__forceinline void SetFistSlamFlag(bool _flag) { mbFistSlam = _flag; }
		
		__forceinline bool GetEndFlag() { return mbEnd; }
		__forceinline void SetEndFlag(bool _flag) { mbEnd = _flag; }

	private:
		bool mbInitFlag = true;								// mInitAddPos ������ �ʱ� ���� �÷���(Init�� �ƴ϶� Update���� �����ϱ⿡ �ʿ���, �� �ѹ��������)
		math::Vector2 mInitAddPos = math::Vector2::Zero;	// ���ذ�(Body Pos ����)�� �����ִ� ��(= �ʱ���ġ ���ϴ� �뵵)

		bool mbFinish = false;						// ��ü�� ������ �������� �˷��ش�.
		GameObject* mOwner = nullptr;				// �����ϰ� �ִ� ��ü ����
		HandPos mHandPos = HandPos::None;			// ��, �� ����
		bool mbPlayAnimation = true;				// �ִϸ��̼� ��� ����
		HandState mState = HandState::None;			// ���� ����
		HandState mPastState = HandState::None;		// ���� ���� (�ִϸ��̼� ������� �Ǻ��� ���)
		math::Vector2 mAddPos = math::Vector2::Zero;// Hand ��ġ ������ ���������� ����ϴ� ����

		// Idle
		float mTime = 0.0f;					// ��������, �����̵� �÷��׿� ���
		bool mUpDownFlag = false;			// Idle ���¿��� ��, �Ʒ� ������ ���� �ٲ��ִ� �÷��� ��

		// FistSlam Ready
		float mDepartHeight = 0.0f;			// �غ��ڼ� ���� ����
		bool mbCollisionFloor = false;		// �� �浹����

		// FistSlam Attack
		math::Vector2 mResetPos = math::Vector2::Zero;	// �����ؾ��ϴ� ��ġ(�غ��ڼ� ������ġ)
		math::Vector2 dir = math::Vector2::Zero;		//
		bool mbFistSlam = false;						// ����ġ�� �ϷῩ��

		// FistSlamAttack() �Լ� ���ڰ���
		bool mbDirectionSet = false;				// ����ĥ ��ġ�� ���� ���⺤�� ���� ����

		// FistSlam End
		bool mbEnd = false;
	};
}

