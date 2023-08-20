#include "vanYggdrasillChin.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"

namespace van
{
	YggdrasillChin::YggdrasillChin()
	{
		AddComponent<SpriteRenderer>();
	}

	YggdrasillChin::~YggdrasillChin()
	{
		// nothing
	}

	void YggdrasillChin::Init()
	{
		GameObject::Init();	// �ƹ��͵� ����

		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		sr->SetTexture(ResourceManager::Find<Texture>(L"Yggdrasill_Chin"));
		sr->SetScale(math::Vector2(2.0f, 2.0f));

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(110.0f * 2, 97.0f * 2));
	}

	void YggdrasillChin::Update()
	{
		GameObject::Update();	// �ش� ��ü�� ������ �ִ� Component �Ӽ����� ���� ������Ʈ���ش�.
	}

	void YggdrasillChin::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);	// GameObject�� ������ �ִ� Component Ŭ������ ����ϰ� �ִ� Ŭ�������� Render()ȣ��
	}

	void YggdrasillChin::MakeAnimation()
	{
		// nothing
	}

	void YggdrasillChin::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void YggdrasillChin::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void YggdrasillChin::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}