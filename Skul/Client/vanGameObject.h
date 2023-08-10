#pragma once
#include "vanEntity.h"
#include "vanComponent.h"	// mComponents �������� Component ��ü���� ������ �ִ�.

namespace van
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			// Ȱ��ȭ ����, Update(OK), Render(OK)
			Active,
			// �����ִ� ����, Update(X), Render(X)
			Pause,
			// �̹� Render�� �������ǰ� �� ��ü�� �����Ǿ�� �ϴ� ���. 
			// Render�� ������ �� ��ü�� �����ϵ���. ex) Bullet.
			Dead,
			End,
		};

		friend static __forceinline void Destroy(GameObject* _obj);

		GameObject();
		virtual ~GameObject();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	// �浹�� ������ ����
		virtual void OnCollisionStay(class Collider* _other);	// �浹����
		virtual void OnCollisionExit(class Collider* _other);	// �浹���� ���

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
			comp->SetOwner(this);	// this = AddComponent()�� ����ϴ� Ŭ������ �ּҰ�
			mComponents.push_back(comp);
			
			return comp;
		}

		__forceinline void SetOffset(math::Vector2 _offset) { offset = _offset; }
		__forceinline math::Vector2 GetOffset() { return offset; }

		__forceinline eState GetState() { return mState; }
		__forceinline void Pause() { mState = eState::Pause; }

	private:
		void Death() { mState = eState::Dead; }

	private:
		std::vector<Component*> mComponents;	// Componenet ��ü���� ���� �����ؾ��ϱ⿡ �ּҸ� �����Ѵ�.
		math::Vector2 offset;
		eState mState;
	};

	static __forceinline void Destroy(GameObject* _obj)
	{
		_obj->Death();
	}
}

