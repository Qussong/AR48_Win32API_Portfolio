#pragma once
#include "vanUI.h"

namespace van
{
	class Mage;
	class Texture;

	class MageHpBar : public UI
	{
	public:
		MageHpBar();
		virtual ~MageHpBar();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other);	// �浹����
		virtual void OnCollisionExit(class Collider* _other);	// �浹���� ���

		void SetMage(Mage* _mage) { mMage = _mage; }

	private:
		Texture* mHpBar;
		Texture* mDamageBar;
		Texture* mHealBar;

		float mReductionHp = 0.0f;
		//Player* mPlayer = nullptr;
		Mage* mMage = nullptr;
	};
}

