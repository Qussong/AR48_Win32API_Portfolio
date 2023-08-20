#pragma once
#include "vanGameObject.h"
#include "vanTransform.h"

namespace van
{
	class YggdrasillChin : public GameObject
	{
	public:
		YggdrasillChin();
		virtual ~YggdrasillChin();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other);	// �浹����
		virtual void OnCollisionExit(class Collider* _other);	// �浹���� ���

		__forceinline void SetPos(math::Vector2 _pos) { GetComponent<Transform>()->SetPosition(_pos); }
		__forceinline math::Vector2 GetPos() { return GetComponent<Transform>()->GetPosition(); }

	private:

	};
}


