#include "vanCollider.h"
#include "vanTransform.h"
#include "vanObject.h"
#include "vanCamera.h"

namespace van
{
	UINT Collider::mCollisionCount = 0;

	// ������
	Collider::Collider()	
		: Component(enums::eComponentType::Collider)
		, mSize(math::Vector2::Zero)	// �浹ü �⺻ũ�� 0
		, mOffset(math::Vector2::Zero)	// ��ü�� �������κ��� �浹ü�� ��ġ������
		, mPos(math::Vector2::Zero)		// �浹ü�� �߽���ǥ : (0,0)
		, mCollisionNum(-1)				// �̸� �⺻�� : -1
		, mbIsCollision(false)			// �浹���� �⺻�� : ���浹����
	{
		// �浹ü Numbering : 0 ~ ...
		mCollisionNum = mCollisionCount;	// �浹ü�� �����Ǹ� ���° �浹ü���� �̸��� �ް�
		++mCollisionCount;					// ��ü �浹ü�� ������ �ϳ� �÷��ش�.
	}

	// �Ҹ���
	Collider::~Collider()
	{
		// nothing
	}

	// �ʱ�ȭ
	void Collider::Init()
	{
		// nothing
	}
	
	// �� ����
	void Collider::Update()
	{
		// nothing
	}

	// ���
	void Collider::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();	// pos�� GameObject ��ü�� ��ġ�� ����
		mPos = pos + mOffset;		// �浹ü�� ������ġ = ���� ��ġ + �ɼ� �� 
									// �浹ü�� ��ġ�� ȭ��󿡼� ��ü�� �������κ��� ��ġ ������ �ʿ��Ҽ��� �ִ�.
		
		pos.x -= mSize.x / 2.0f;	// �׷��� ����(�簢��)�� �ʺ� �߽��� pos.x
		pos.y -= mSize.y / 2.0f;	// �׷��� ����(�簢��)�� ���̰� �߽��� pos.y
		pos.x += mOffset.x;			// �׷��� ����(�簢��)�� �ʺ� ��ġ ���� ��
		pos.y += mOffset.y;			// �׷��� ����(�簢��)�� ���� ��ġ ���� ��

		pos = Camera::CalculatePosition(pos);	// ī�޶� ���� ����

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	// ����귯�� �ڵ� ���� ���´�.
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);	// Brush ��ü

		HPEN newPen = NULL;

		if (mbIsCollision)
		{
			newPen = CreatePen(PS_SOLID, 2, RGB(255, 50, 50));	// ������
		}
		else
		{
			newPen = CreatePen(PS_SOLID, 2, RGB(50, 255, 50));	// ���� �ʷϻ�
		}

		HPEN oldPen = (HPEN)SelectObject(hdc, newPen);	// �浹���ο� ���� ������ ������ �ִ� PEN���� ����

		Rectangle(hdc
			, pos.x, pos.y
			, pos.x + mSize.x, pos.y + mSize.y);	// �簢�� �׸���

		SelectObject(hdc, oldBrush);	// ����
		DeleteObject(transparentBrush);	// �޸� ����

		SelectObject(hdc, oldPen);		// ����
		DeleteObject(newPen);			// �޸� ����
	}

	void Collider::OnCollisionEnter(Collider* _other)
	{
		mbIsCollision = true;
		GetOwner()->OnCollisionEnter(_other);
	}

	void Collider::OnCollisionStay(Collider* _other)
	{
		GetOwner()->OnCollisionStay(_other);
	}

	void Collider::OnCollisionExit(Collider* _other)
	{
		mbIsCollision = false;
		GetOwner()->OnCollisionExit(_other);
	}
}