#pragma once
#include "vanGameObject.h"

namespace van
{
	class Skill	: public GameObject
	{
	public:
		Skill();
		virtual ~Skill();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

		void SetOwner(GameObject* _owner) { mOwner = _owner; }
		GameObject* GetOwner() { return mOwner; }

	private:
		GameObject* mOwner;
	};
}

