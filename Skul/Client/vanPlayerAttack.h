#pragma once
#include "vanRange.h"

namespace van
{
	class PlayerAttack : public Range
	{
	public:
		PlayerAttack();
		virtual ~PlayerAttack();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;
		virtual void OnCollisionStay(class Collider* _other) override;
		virtual void OnCollisionExit(class Collider* _other) override;

		__forceinline std::set<GameObject*>* GetAttackList() { return &attackList; }

		float GetPlayerAttackDamage() { return mAttackDamage; }

		bool GetActiveFlag() { return mActiveFlag; }

	private:
		std::set <GameObject*> attackList;	// �浹�� GameObject ���� ����
		bool mbCombo;						// Attack�� �޺��� �̾����������� ����(true = �޺�o, false = �޺�x)
		float mAttackDamage;
		bool mActiveFlag = false;
	};
}

