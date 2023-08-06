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

		
		if (player != nullptr)	// �浹�� ��ü�� Player �� ���
		{
			// ������ ���¸� Trace �� ����
			Monster* monster = (Monster*)GetOwner();
			monster->SetMonsterState(Monster::MonsterState::Trace);

			// ��ġ�� ���Ͽ� Monster �������� �������� ���������� ����
			math::Vector2 playerPos = player->GetComponent<Transform>()->GetPosition();
			math::Vector2 monsterPos = monster->GetComponent<Transform>()->GetPosition();
			if (playerPos.x < monsterPos.x)
			{
				// Player�� Monster�� Left�� �ִ�.
				// Monster�� �̵� ������ Left�� ����
				monster->SetMonsterDirection(Monster::MonsterDirection::Left);
			}
			else
			{
				// Player�� Monster�� Right�� �ִ�.
				// Monster�� �̵� ������ Right�� ����
				monster->SetMonsterDirection(Monster::MonsterDirection::Right);
			}
		}
	}

	void MonsterTrace::OnCollisionExit(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Player* player = dynamic_cast<Player*>(obj);

		if (player != nullptr)	// �浹���� ��� ��ü�� Player �� ���
		{
			// ������ ���¸� Idle �� ����
			Monster* monster = (Monster*)GetOwner();
			monster->SetMonsterState(Monster::MonsterState::Idle);
		}
	}
}