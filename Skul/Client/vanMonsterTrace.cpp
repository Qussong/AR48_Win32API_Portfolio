#include "vanMonsterTrace.h"

#include "vanCollider.h";
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanPlayer.h"

namespace van
{
	MonsterTrace::MonsterTrace()
	{
		// nothing
	}

	MonsterTrace::~MonsterTrace()
	{
		// nothing
	}

	void MonsterTrace::Init()
	{
		GetComponent<Collider>()->SetLineColor(RGB(255, 255, 0));		// Collider �� ���ڻ� ����(Trace ���� �� : Yellow)
	}

	void MonsterTrace::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();

		// ��ġ ����
		tr->SetPosition(GetOwnerPos());	// �������� ��ġ�� ����ٴѴ�.

	}

	void MonsterTrace::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void MonsterTrace::MakeAnimation()
	{
		// nothing
	}

	void MonsterTrace::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void MonsterTrace::OnCollisionStay(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Player* player = dynamic_cast<Player*>(obj);

		if (player != nullptr)
		{
			// trace ���� ����
		}
	}

	void MonsterTrace::OnCollisionExit(Collider* _other)
	{
		
	}
}