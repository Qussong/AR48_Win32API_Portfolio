#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanSpriteRenderer.h"
#include "vanSceneManager.h"
#include "vanCollider.h"
#include "vanMonster.h"

namespace van
{
	GameObject::GameObject()
		: offset(math::Vector2::Zero)
		, mState(eState::Active)
	{
		AddComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));	// �⺻ ��ġ ȭ�� �߾�
		AddComponent<Animator>();
		AddComponent<Collider>();	
	}

	GameObject::~GameObject()
	{
		// nothingz
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

	void GameObject::MakeAnimation()
	{
		// nothing
	}
}