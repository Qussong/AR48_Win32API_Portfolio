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
		// nothing
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
		GameObject* obj = _other->GetOwner();
		Transform* tr = obj->GetComponent<Transform>();
		RigidBody* rb = obj->GetComponent<RigidBody>();
		Collider* col = obj->GetComponent<Collider>();

		math::Vector2 objPos = tr->GetPosition();									// �浹ü�� ��ġ
		math::Vector2 floorPos = this->GetComponent<Transform>()->GetPosition();	// �ٴ� ��ü�� ��ġ
		math::Vector2 objSize = col->GetSize();										// �浹ü�� ������
		math::Vector2 floorSize = this->GetComponent<Collider>()->GetSize();		// �ٴ� ��ü�� ũ��

		float gap = floorPos.y - objPos.y;							// ���� �����ӿ��� �浹ü�� Floor ��ü�� �������ִ� �Ÿ� ( + : Player�� �� , - : Floor�� ��)
		float mazino = fabs(objSize.y / 2.0f + floorSize.y / 2.0f);	// �� ��ü�� �������ֱ� ���� �ּҰŸ�

		// �浹ü�� Floor ��ü���� ���� ���� ��(�߽���ǥ ����)
		if (gap > 0)
		{
			// �� ��ü�� �����ִ� ���
			if (fabs(gap) < mazino)
			{
				objPos.y -= (mazino - fabs(gap)) - 1.0f;
				tr->SetPosition(objPos);
			}

			rb->SetGround(true);	// Floor ��ü�� �浹�� ��ü�� ���� �پ��ִ� ���·� ������ش�.
		}
	}

	void Floor::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Floor::OnCollisionExit(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		RigidBody* rb = obj->GetComponent<RigidBody>();

		rb->SetGround(false);
	}
}