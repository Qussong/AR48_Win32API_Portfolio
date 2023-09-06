#pragma once
#include "vanSkill.h"

namespace van
{
	class EnergyBallObject : public Skill
	{
	public:
		enum class EnergyBallObjectState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		EnergyBallObject();
		virtual ~EnergyBallObject();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		__forceinline void SetState(EnergyBallObjectState _state) { mState = _state; }
		__forceinline EnergyBallObjectState GetState() { return mState; }

		//__forceinline math::Vector2 GetDirect() { return mDirect; }
		//__forceinline void SetDirect(math::Vector2 _dir) { mDirect = _dir; }

		__forceinline float GetRadian() { return mRadian; }
		__forceinline void SetRadian(float _radian) { mRadian = _radian; }

		void Gen();
		void Active();
		void Dead();

	private:
		EnergyBallObjectState mState = EnergyBallObjectState::None;
		bool mbSetFlag = true;									// ��ü �߻縦 ���� ���� ����
		math::Vector2 mDirect = math::Vector2(0.0f, 0.0f);		// ���⺤��
		float mRadian = 0.0f;									// ���⺤���� ����
	};
}

