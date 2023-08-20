#pragma once
#include "vanBoss.h"
#include "vanYggdrasillBody.h"
#include "vanYggdrasillHead.h"
#include "vanYggdrasillChin.h"
#include "vanYggdrasillHand.h"

namespace van
{
	class Yggdrasill : public Boss
	{
	public:
		Yggdrasill();
		~Yggdrasill();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���
		
		void AttackMelee();	// �����ư��鼭 �ָ����
		void AttackSmash(); // ������� �ٴ����
		void AttackRange();	// ������ ����������

	private:
		YggdrasillBody* mBody = nullptr;		// ��ü
		YggdrasillHead* mHead = nullptr;		// �Ӹ�
		YggdrasillChin* mChin = nullptr;		// ��
		YggdrasillHand* mHandLeft = nullptr;	// �޼�
		YggdrasillHand* mHandRight = nullptr;	// ������

		int mHp;
		int mArmor;
	};
}

