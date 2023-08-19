#include "vanWall.h"
#include "vanCollider.h"
#include "vanTransform.h"
#include "vanRigidBody.h"
#include "vanObject.h"
#include "vanMonster.h"
#include "vanPlayer.h"
#include "vanCollider.h"

namespace van
{
	Wall::Wall()
		: mbFloorLimit(false)
	{
		// nothing
	}

	Wall::~Wall()
	{
		// nothing
	}

	void Wall::Init()
	{
		if (mbFloorLimit == false)
		{
			GetComponent<Collider>()->SetLineColor(RGB(255, 128, 0));
		}
	}

	void Wall::Update()
	{
		GameObject::Update();

		if (mbFloorLimit == true)
		{
			GetComponent<Collider>()->SetLineColor(RGB(0, 255, 255));
		}
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
		Collider* col_this = GetComponent<Collider>();

		math::Vector2 objPos = tr->GetPosition();									// �浹ü�� ��ġ
		math::Vector2 floorPos = this->GetComponent<Transform>()->GetPosition();	// �ٴ� ��ü�� ��ġ
		math::Vector2 objSize = col->GetSize();										// �浹ü�� ������
		math::Vector2 thisSize = col_this->GetSize();								// Wall��ü�� ������
		math::Vector2 floorSize = this->GetComponent<Collider>()->GetSize();		// �ٴ� ��ü�� ũ��

		// x��
		float gapX = floorPos.x - objPos.x;							// ���� �����ӿ��� �浹ü�� Floor ��ü�� �������ִ� �Ÿ� (+ : ��ü�� ����, - : ��ü�� ������)
		float mazinoX =objSize.x / 2.0f + floorSize.x / 2.0f;		// �� ���� �������ֱ� ���� �ּҰŸ�
		// y��
		float gapY = floorPos.y - objPos.y;							// ���� �����ӿ��� �浹ü�� Floor ��ü�� �������ִ� �Ÿ� (+ : ��ü�� ����, - : ��ü�� ������)
		float mazinoY = objSize.y / 2.0f + floorSize.y / 2.0f;		// �� ���� �������ֱ� ���� �ּҰŸ�

		Player* player = dynamic_cast<Player*>(obj);
		Monster* monster = dynamic_cast<Monster*>(obj);

		// �÷��̾�� �浹���� ���
		if (player != nullptr
			&& mbFloorLimit == false)
		{
			// Wall ��ü�� y�� ���̰� �� �� ��� (�Ϲ����� ���)
			if (thisSize.x < thisSize.y)
			{
				if (fabs(gapX) < mazinoX)
				{
					// ������ ��(+)
					if (gapX > 0)
					{
						objPos.x -= ((mazinoX - fabs(gapX)) - 1.0f);
						tr->SetPosition(objPos);
					}

					// �������� ��(-)
					if(gapX < 0)
					{
						objPos.x += ((mazinoX - fabs(gapX)) + 1.0f);
						tr->SetPosition(objPos);
					}
				}
			}
			// Wall ��ü�� x�� ���̰� �� �� ���
			else if(thisSize.x > thisSize.y)
			{
				if (fabs(gapY) < mazinoY)
				{
					// Wall �� �Ʒ��� ���� ��(+)
					if (gapY > 0)
					{
						objPos.y -= ((mazinoY - fabs(gapY)) - 1.0f);
						tr->SetPosition(objPos);
					}

					// Wall �� ���� ���� ��(-)
					if (gapY < 0)
					{
						objPos.y += ((mazinoY - fabs(gapY)) + 1.0f);
						tr->SetPosition(objPos);
					}
				}
			}
		}

		// ���Ϳ� �浹���� ���
		if (monster != nullptr)
		{
			monster->SetWallFlag(true);
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