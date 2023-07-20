#include "vanGameObject.h"
#include "vanTransform.h"		
#include "vanSpriteRenderer.h"

namespace van
{
	GameObject::GameObject()
	{
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
		// GameObject�� ������ �ִ� Component Ŭ������ ����ϰ� �ִ� Ŭ�������� Render()ȣ��
		// Ŭ���� ���� : Transform, SpriteRenderer
		for (Component* comp : mComponents)
			comp->Render(_hdc);
	}

	void GameObject::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void GameObject::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void GameObject::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}