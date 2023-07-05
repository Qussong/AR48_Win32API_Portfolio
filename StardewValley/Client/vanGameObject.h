#pragma once
#include "vanEntity.h"
#include "vanComponent.h"	// mComponents���� Component ��ü���� �����Ѵ�.

namespace van
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);

		template <typename T>
		__inline T* GetComponent()
		{
			T* comp = nullptr;
			for (Component* c : mComponents)
			{
				comp = dynamic_cast<T*>(c);
				if (comp != nullptr)	// ��������� �ٿ��ش�.
					return comp;
			}
			return comp;
		}

	private:
		std::vector<Component*> mComponents;	// Componenet ��ü���� ���� �����ؾ��ϱ⿡ �ּҸ� �����Ѵ�.
	};
}

