#pragma once
#include "vanSkill.h"

namespace van
{
	class RangeFire : public Skill
	{
	public:
		RangeFire();
		virtual ~RangeFire();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other) override;	// �浹����
		virtual void OnCollisionExit(class Collider* _other) override;	// �浹���� ���

	private:

	};
}
