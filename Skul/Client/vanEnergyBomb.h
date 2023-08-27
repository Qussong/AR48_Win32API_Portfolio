#pragma once
#include "vanSkill.h"

namespace van
{
	class EnergyBomb : public Skill
	{
	public:
		enum class EnergyBombState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		EnergyBomb();
		virtual ~EnergyBomb();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		void SetState(EnergyBombState _state) { mState = _state; }
		EnergyBombState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();
		void SetEnergyBombPos();

	private:
		EnergyBombState mState = EnergyBombState::None;
		bool mbSetFlag = true;									// ��ü �߻縦 ���� ���� ����
		math::Vector2 mDepartPos = math::Vector2(0.0f, 0.0f);	// �߻�����
		math::Vector2 mTargetPos = math::Vector2(0.0f, 0.0f);	// ��������
		math::Vector2 mDirect = math::Vector2(0.0f, 0.0f);		// ���⺤��
	};
}
