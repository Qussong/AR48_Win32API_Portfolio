#pragma once
#include "vanRange.h"

namespace van
{
	class MonsterAttack : public Range
	{
	public:
		MonsterAttack();
		virtual ~MonsterAttack();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;
		virtual void OnCollisionStay(class Collider* _other) override;
		virtual void OnCollisionExit(class Collider* _other) override;

		__forceinline std::set<GameObject*>* GetMonsterAttackList() { return &mAttackList; }

		__forceinline bool GetAttackReadyFlag() { return mbAttackReadyFlag; }
		__forceinline void SetAttackReadyFlag(bool _flag) { mbAttackReadyFlag = _flag; }

		__forceinline bool GetNotifyFlag() { return mbForNotify; }
		__forceinline void SetNotifyFlag(bool _flag) { mbForNotify = _flag; }

	private:
		std::set<GameObject*> mAttackList;	// �浹�� GameObject ���� ����
		bool mbAttackReadyFlag;				// Attack Ready�� ���࿩��
		bool mbForNotify;					// ���ݹ����� �������� �˸��� �뵵�θ� ����� �� true
	};
}

