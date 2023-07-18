#pragma once
#include "vanEntity.h"
#include "vanComponent.h"	// mComponents �������� Component ��ü���� ������ �ִ�.

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
		__inline T* GetComponent()	// Ư�� Ÿ���� Component ��ü�� �����Ѵٸ� �ش� ��ü�� �ּҰ��� ��ȯ�Ѵ�.
		{
			T* comp = nullptr;
			for (Component* c : mComponents)
			{
				/* 
					[ dynamic_cast<T> ]
					�ڽ� Ÿ�԰� TŸ���� ��ġ�ϴٸ� �ּҸ� ��ȯ,
					�׷��� �ʴٸ� nullptr ��ȯ

					��, �θ� Ÿ������ ĳ���� �� c�� ���� Ÿ�԰�
					T�� Ÿ���� �����ϸ� �ش� ��ü�� �ּҸ� ��ȯ�ϰ�
					Ÿ���� �ٸ��ٸ� nullptr�� ��ȯ�Ѵ�.
				*/
				comp = dynamic_cast<T*>(c);
				if (comp != nullptr)
					return comp;
			}
			return comp;
		}

		template <typename T>
		__inline T* AddComponent()	// Ư�� Ÿ���� Component ��ü�� �����ϰ� �ش� ��ü�� �ּҸ� ��ȯ�Ѵ�.
		{
			T* comp = new T();
			/* 
				[ SetOwner() ]
				Componenet�� ������ �ִ� GameObject ��ü���� �����״� 
				� GameObject�� Component���� �˱����� �������ش�.
			*/
			comp->SetOwner(this);	
			mComponents.push_back(comp);
			
			return comp;
		}

	private:
		std::vector<Component*> mComponents;	// Componenet ��ü���� ���� �����ؾ��ϱ⿡ �ּҸ� �����Ѵ�.
	};
}

