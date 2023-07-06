#include "vanGameObject.h"
#include "vanTransform.h"		
#include "vanSpriteRenderer.h"

namespace van
{
	GameObject::GameObject()
	{
		/*
		// Transform ��ü�� �ش� Transform�� �����ϰ� �ִ� GameObject ��ü�� �˷��ش�.
		mComponents.push_back(new Transform());
		mComponents[0]->SetOwner(this);

		// SpriteRenderer ��ü�� �ش� Transform�� �����ϰ� �ִ� GameObject ��ü�� �˷��ش�.
		mComponents.push_back(new SpriteRenderer());
		mComponents[1]->SetOwner(this);
		*/
		AddComponent<Transform>();	// GameObject ��ü�� Transform �Ӽ��� ����� �־��ش�.
	}

	GameObject::~GameObject()
	{
		// nothing
	}

	void GameObject::Init()
	{
		// nothing
	}

	void GameObject::Update()
	{
		// �ش� ��ü�� ������ �ִ� Component �Ӽ����� ���� ������Ʈ���ش�.
		for (Component* comp : mComponents)
			comp->Update();
	}

	void GameObject::Render(HDC _hdc)
	{
		// �ش� ��ü�� ȭ�鿡 ������ش�.
		for (Component* comp : mComponents)
			comp->Render(_hdc);
	}
}