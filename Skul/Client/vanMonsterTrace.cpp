#include "vanMonsterTrace.h"
#include "vanCollider.h"
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
		//CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Trace, eLayerType::Player, true);
	}

	void MonsterTrace::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();

		// ��ġ ����
		tr->SetPosition(GetOwnerPos());	
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
		
		// Monster�� ���°� AttackReady, Attack �� �ƴѰ��
		if (monster->GetMonsterState() != Monster::MonsterState::AttackReady
			|| monster->GetMonsterState() != Monster::MonsterState::Attack)
		{
			// �浹�� ����� Player�̰� Monster���� Target�� ���� ��
			if (player != nullptr && monster->GetMonsterTarget() == nullptr)	
			{
				// // Monster�� Trace�� �����ϵ��� mbTrace �� true�� ����
				monster->SetTraceFlag(true);
				// ������ Ÿ�� ����
				monster->SetMonsterTarget(player);
			}
		}
	}

	void MonsterTrace::OnCollisionExit(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Player* player = dynamic_cast<Player*>(obj);
		Monster* monster = (Monster*)GetOwner();

		// �浹���� ��� ��ü�� Player �� ���
		if (player != nullptr
			&& monster->GetMonsterState() != Monster::MonsterState::AttackReady
			&& monster->GetMonsterState() != Monster::MonsterState::Attack
			&& monster->GetMonsterState() != Monster::MonsterState::AttackEnd)
		{
			monster->SetTraceFlag(false);
			// ������ Ÿ���� ���ش�.
			monster->SetMonsterTarget(nullptr);
			// ������ ���¸� Patrol �� ����
			monster->SetMonsterState(Monster::MonsterState::Patrol);
		}
	}

}