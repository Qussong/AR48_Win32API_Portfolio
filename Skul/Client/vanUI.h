#pragma once
#include "vanGameObject.h"

namespace van
{
	class UI : public GameObject
	{
	public:
		UI();
		virtual ~UI();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other);	// �浹����
		virtual void OnCollisionExit(class Collider* _other);	// �浹���� ���

	private:

	};
}

