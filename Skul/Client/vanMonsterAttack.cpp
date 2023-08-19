#include "vanMonsterAttack.h"

#include "vanCollider.h"
#include "vanCollisionManager.h"
#include "vanTransform.h"
#include "vanMonster.h"
#include "vanPlayer.h"

namespace van
{
	MonsterAttack::MonsterAttack()
		: mbAttackReadyFlag(false)
	{
		// nothing
	}

	MonsterAttack::~MonsterAttack()
	{
		// nothing
	}

	void MonsterAttack::Init()
	{
		// Collider �� ���ڻ� ����(MonsterAttack ���� �� : Blue)
		GetComponent<Collider>()->SetLineColor(RGB(0, 0, 255));	
		// MonsterAttack �� Player�� �浹������ �޵��� ����
		//CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Attack, eLayerType::Player, true);
	}

	void MonsterAttack::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();

		// ��ġ ����
		// MonsterTrace Ŭ������ �����ϰ� �ִ� ��ü�� ��ġ�� ������� ����ٴѴ�.
		Monster::MonsterDirection direction = (Monster::MonsterDirection)GetOwnerDirection();
		// ���Ͱ� �ٶ󺸴� ������ Left �϶�
		if (direction == Monster::MonsterDirection::Left)
		{
			tr->SetPosition(GetOwnerPos() - GetOffset());
		}
		// ���Ͱ� �ٶ󺸴� ������ Right �϶�
		else
		{
			tr->SetPosition(GetOwnerPos() + GetOffset());
		}
	}

	void MonsterAttack::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void MonsterAttack::MakeAnimation()
	{
		// nothing
	}

	void MonsterAttack::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void MonsterAttack::OnCollisionStay(Collider* _other)
	{
		Monster* monster = (Monster*)GetOwner();	// // MonsterAttack Ŭ������ ������ ��ü�� �ּ� ����
		GameObject* obj = _other->GetOwner();		// �浹 ����� �ּ�����
		Player* playr = dynamic_cast<Player*>(obj);	// �浹 ����� Player ���� Ȯ��

		// Attack Ready ���·� ����
		// �浹�� ��ü�� Player�̰� Attack Ready�� ������ȯ������ ���ٸ� Attack Ready�� ������ȯ
		if (playr != nullptr
			&& mbAttackReadyFlag == false)
		{
			// Monster�� Attack�� �����ϵ��� mbAttack �� true�� ����
			monster->SetAttackFlag(true);
		}
		
		// Attack ���� ����
		// Attack �����϶� Ÿ�������� �����.
		// ���Ͱ� Attack �����̰� Attack Ready�� �̹� �������� ���
		if ((Monster::MonsterState)GetOwnerState() == Monster::MonsterState::Attack
			&& mbAttackReadyFlag == true)
		{
			// ���� Ÿ�ݵ� ����� Set�� ������� �ʴٸ� Ÿ������ o
			if (mAttackList.find(obj) == mAttackList.end())
			{
				// Ÿ�ݵ� ����� Set�� �־��ش�.
				// ���ִ°� Monster���� ���ش�.
				mAttackList.insert(obj);

				// �ǰݴ���� �÷��̾� �϶�
				Player* player = dynamic_cast<Player*>(obj);
				if (player != nullptr)
				{
					// hp ����
					// �ǰ������� ���ư���..
				}
				// �ǰݴ���� �÷��̾ �ƴҶ�
				else
				{
					// �ʿ��� ���� ����
					// ex) Monster��� hp ���Ҵ� ������ ���ư��� �Ѵٰų�...
				}
			}
			else
			{
				// �̹� Set�� ����ִٸ� Ÿ������ x
				__noop;
			}
		}
	}

	void MonsterAttack::OnCollisionExit(Collider* _other)
	{
		Monster* monster = (Monster*)GetOwner();		// MonsterAttack Ŭ������ ������ ��ü�� �ּ� ����
		GameObject* obj = _other->GetOwner();			// �浹 ����� �ּ�����
		Player* playr = dynamic_cast<Player*>(obj);		// �浹 ����� Player ���� Ȯ��

		// Player�� Monster Attack �������� ����� Attack Flag �� ���ش�.
		if (playr != nullptr)
		{
			monster->SetAttackFlag(false);

			if (monster->GetMonsterState() != Monster::MonsterState::AttackReady
				&& monster->GetMonsterState() != Monster::MonsterState::Attack
				&& monster->GetMonsterState() != Monster::MonsterState::AttackEnd)
			{
				monster->SetMonsterState(Monster::MonsterState::Patrol);
			}
		}
	}
}