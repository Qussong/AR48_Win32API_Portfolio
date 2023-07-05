#include "vanGameObject.h"
#include "vanTransform.h"		
#include "vanSpriteRenderer.h"

namespace van
{
	GameObject::GameObject()
	{
		// Transform ��ü�� �ش� Transform�� �����ϰ� �ִ� GameObject ��ü�� �˷��ش�.
		mComponents.push_back(new Transform());
		mComponents[0]->SetOwner(this);

		// SpriteRenderer ��ü�� �ش� Transform�� �����ϰ� �ִ� GameObject ��ü�� �˷��ش�.
		mComponents.push_back(new SpriteRenderer());
		mComponents[1]->SetOwner(this);
	}
	GameObject::~GameObject()
	{
	}
	void GameObject::Init()
	{
	}
	void GameObject::Update()
	{
		for (Component* comp : mComponents)
			comp->Update();
	}
	void GameObject::Render(HDC _hdc)
	{
		for (Component* comp : mComponents)
			comp->Render(_hdc);
	}
}