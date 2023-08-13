#include "vanWall.h"
#include "vanCollider.h"
#include "vanTransform.h"
#include "vanRigidBody.h"
#include "vanObject.h"
#include "vanMonster.h"

namespace van
{
	Wall::Wall()
	{
		// nothing
	}

	Wall::~Wall()
	{
		// nothing
	}

	void Wall::Init()
	{
		// nothing
	}

	void Wall::Update()
	{
		GameObject::Update();
	}

	void Wall::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Wall::OnCollisionEnter(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Transform* tr = obj->GetComponent<Transform>();
		RigidBody* rb = obj->GetComponent<RigidBody>();
		Collider* col = obj->GetComponent<Collider>();

		math::Vector2 objPos = tr->GetPosition();									// �浹ü�� ��ġ
		math::Vector2 floorPos = this->GetComponent<Transform>()->GetPosition();	// �ٴ� ��ü�� ��ġ
		math::Vector2 objSize = col->GetSize();										// �浹ü�� ������
		math::Vector2 floorSize = this->GetComponent<Collider>()->GetSize();		// �ٴ� ��ü�� ũ��

		float gap = floorPos.x - objPos.x;							// ���� �����ӿ��� �浹ü�� Floor ��ü�� �������ִ� �Ÿ� (+ : ��ü�� ����, - : ��ü�� ������)
		float mazino = fabs(objSize.x / 2.0f + floorSize.x / 2.0f);	// �� ��ü�� �������ֱ� ���� �ּҰŸ�

		// �浹ü�� Floor ��ü���� ���� ���� ��(�߽���ǥ ����)
		// �� ��ü�� �����ִ� ���
		if (fabs(gap) < mazino)
		{
			// ������ ��(+)
			if (gap > 0)
			{
				objPos.x -= ((mazino - fabs(gap)) - 1.0f);
				tr->SetPosition(objPos);
			}
			// �������� ��(-)
			else
			{
				objPos.x += ((mazino - fabs(gap)) + 1.0f);
				tr->SetPosition(objPos);
			}
		}
	}

	void Wall::OnCollisionStay(Collider* _other)
	{
		OnCollisionEnter(_other);
	}

	void Wall::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}