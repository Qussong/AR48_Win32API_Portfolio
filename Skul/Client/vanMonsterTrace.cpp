#include "vanMonsterTrace.h"

#include "vanCollider.h";
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanPlayer.h"

#include "vanCollisionManager.h"
#include "vanMonster.h"

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
		GetComponent<Collider>()->SetLineColor(RGB(255, 255, 0));	// Collider �� ���ڻ� ����(Trace ���� �� : Yellow)
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Trace, eLayerType::Player, true);
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
		Monster* monster = (Monster*)GetOwner();	// MonsterTrace Ŭ������ �����ϰ� �ִ� Monster Ŭ������ �ּ�����
		
		// �浹�� ����� Player�̰� Monster���� Target�� ���� ��
		if (player != nullptr && monster->GetMonsterTarget() == nullptr)	
		{
			// ������ Ÿ�� ����
			monster->SetMonsterTarget(player);
			// ������ ���¸� Trace �� ����
			monster->SetMonsterState(Monster::MonsterState::Trace);
		}
	}

	void MonsterTrace::OnCollisionExit(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Player* player = dynamic_cast<Player*>(obj);
		Monster* monster = (Monster*)GetOwner();

		// �浹���� ��� ��ü�� Player �� ���
		if (player != nullptr)	
		{
			// ������ Ÿ���� ���ش�.
			monster->SetMonsterTarget(nullptr);
			// ������ ���¸� Patrol �� ����
			monster->SetMonsterState(Monster::MonsterState::Patrol);
		}
	}
}