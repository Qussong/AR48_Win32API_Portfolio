#pragma once
#include "vanEntity.h"
#include "vanGameObject.h"	// mGameObjects ���� GameObject �� ��ü���� �����Ѵ�.
namespace van
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);

		__forceinline void AddGameObject(GameObject* gameObj) { mGameObjects.push_back(gameObj); }
		__forceinline std::vector<GameObject*>& GetGameObjects() { return mGameObjects; }

	private:
		std::vector<GameObject*> mGameObjects;	// GameObject ��ü���� ������ �����ؾ��ϱ⿡ �ּҰ����� �����Ѵ�.
	};

}

