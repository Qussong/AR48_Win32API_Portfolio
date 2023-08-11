#include "vanFloor.h"
#include "vanPlayer.h"
#include "vanCollider.h"
#include "vanTransform.h"
#include "vanRigidBody.h"
#include "vanNPC.h"
#include "vanMonster.h"
#include "vanObject.h"

namespace van
{
	Floor::Floor()
	{
		// nothing
	}

	Floor::~Floor()
	{
		// nothing
	}

	void Floor::Init()
	{

	}

	void Floor::Update()
	{
		GameObject::Update();
	}

	void Floor::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Floor::OnCollisionEnter(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());	// Collider �Ӽ��� ���� �ش� GameObject ��ü�� ������ �����´�
		NPC* npc = dynamic_cast<NPC*>(_other->GetOwner());
		Monster* monster = dynamic_cast<Monster*>(_other->GetOwner());

		Transform* tr = nullptr;
		RigidBody* rb = nullptr;
		math::Vector2 objPos;

		if (player != nullptr)
		{
			Player::PlayerState state = player->GetPlayerState();
			tr = player->GetComponent<Transform>();		// Transform
			rb = player->GetComponent<RigidBody>();		// RigidBody
			objPos = tr->GetPosition();					// Floor ��ü�� �浹�� ��ü�� ��ġ�� ����

			// ���� �����ӿ��� �浹ü���� �������ִ� �Ÿ� (�߽���ǥ ����)
			float gap = fabs(_other->GetPos().y - this->GetComponent<Collider>()->GetPos().y);
			// �ι�ü�� �������ֱ� ���� �ּҰŸ�
			float mazino = fabs(_other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

			// �� ��ü�� ���� �ִ� ���
			if (gap < mazino)
			{
				objPos.y -= (mazino - gap) - 1.0f;
				tr->SetPosition(objPos);
			}

			rb->SetGround(true);	// Floor ��ü�� �浹�� ��ü�� ���� �پ��ִ� ���·� ������ش�.
		}

		if (npc != nullptr)
		{
			tr = npc->GetComponent<Transform>();		// Transform
			rb = npc->GetComponent<RigidBody>();		// RigidBody
			objPos = tr->GetPosition();					// Floor ��ü�� �浹�� ��ü�� ��ġ�� ����

			float gap = fabs(_other->GetPos().y - this->GetComponent<Collider>()->GetPos().y);	// ���� �����ӿ��� �浹ü���� �������ִ� �Ÿ� (�߽���ǥ ����)
			float mazino = fabs(_other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);	// �ι�ü�� �������� �������ֱ� ���� �ּҰŸ�

			if (gap < mazino)	// �� ��ü�� ���� �ִ� ���
			{
				objPos.y -= (mazino - gap) - 1.0f;
				tr->SetPosition(objPos);
			}
			else  // �� ��ü�� ��ġ�� ���� ���
			{
				__noop;
			}

			rb->SetGround(true);	// Floor ��ü�� �浹�� ��ü�� ���� �پ��ִ� ���·� ������ش�.
		}

		if (monster != nullptr)
		{
			tr = monster->GetComponent<Transform>();	// Transform
			rb = monster->GetComponent<RigidBody>();	// RigidBody
			objPos = tr->GetPosition();					// Floor ��ü�� �浹�� ��ü�� ��ġ�� ����

			float gap = fabs(_other->GetPos().y - this->GetComponent<Collider>()->GetPos().y);						// ���� �����ӿ��� �浹ü���� �������ִ� �Ÿ� (�߽���ǥ ����)
			float mazino = fabs(_other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);	// �ι�ü�� �������� �������ֱ� ���� �ּҰŸ�

			if (gap < mazino)	// �� ��ü�� ���� �ִ� ���
			{
				objPos.y -= (mazino - gap) - 1.0f;
				tr->SetPosition(objPos);
			}
			else  // �� ��ü�� ��ġ�� ���� ���
			{
				__noop;
			}

			rb->SetGround(true);	// Floor ��ü�� �浹�� ��ü�� ���� �پ��ִ� ���·� ������ش�.
		}
	}

	void Floor::OnCollisionStay(Collider* _other)
	{

	}

	void Floor::OnCollisionExit(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		RigidBody* rb = obj->GetComponent<RigidBody>();

		rb->SetGround(false);
	}
}