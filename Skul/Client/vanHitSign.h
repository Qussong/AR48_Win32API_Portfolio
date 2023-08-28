#pragma once
#include "vanUI.h"

namespace van
{
	class HitSign : public UI
	{
	public:
		HitSign();
		virtual ~HitSign();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other);	// �浹����
		virtual void OnCollisionExit(class Collider* _other);	// �浹���� ���
	};
}

