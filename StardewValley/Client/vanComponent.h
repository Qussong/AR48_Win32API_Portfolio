#pragma once
#include "vanEntity.h"

namespace van
{
	class Component : public Entity	// Component Ŭ������ ��ӵǾ� ���ȴ�.
									//		-> SpriteRenderer, Transform ���� ��üȭ�ȴ�.
	{
	public:
		Component(enums::eComponentType type);
		virtual ~Component();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);

		__inline void SetOwner(class GameObject* owner) { mOwner = owner; }		// Setter
		__inline class GameObject* GetOwner() { return mOwner; }				// Getter

	private:
		const enums::eComponentType mType;	// �����ڿ��� �޾��� type�� mType�� ����ȴ�.
											// ������Ʈ ���� : Transform, SpriteRenderer, End, ...
		class GameObject* mOwner;			// �ش� ������Ʈ ������ ������ �ִ� GameObject ����
	};
}
