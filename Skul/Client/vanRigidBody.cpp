#include "vanRigidBody.h"
#include "vanTransform.h"
#include "vanObject.h"

namespace van
{
	RigidBody::RigidBody()
		: Component(enums::eComponentType::RigidBody)
		, mMass(1.0f)
		, mFriction(15.0f)
		, mForce(math::Vector2::Zero)
		, mAccelation(math::Vector2::Zero)
		, mVelocity(math::Vector2::Zero)
		, mGravity(math::Vector2(0.0f, 2000.0f))
		, mLimitedVelocity(math::Vector2(500.0f, 2000.0f))
		, mbGround(false)
	{
	}

	RigidBody::~RigidBody()
	{
		// nothing
	}

	void RigidBody::Init()
	{
		// nothing
	}

	void RigidBody::Update()
	{
		
		mAccelation = mForce / mMass;	// F = m * a -> a = F / m
		mVelocity += mAccelation * Time::GetDeltaTime();	// v1 = v0 + at


		if (mbGround)	// GameObject�� ������ ���� ��
		{
			math::Vector2 gravity = mGravity;			// �߷� �ʱⰪ -> x = 0, y = 980
			gravity.normalize();						// �߷� -> x = 0, y = 1
			float dot = math::Dot(mVelocity, gravity);	// dot = mVelocity.y
			math::Vector2 val = gravity * dot;
			mVelocity -= val;							// mVelocity -= Vector2(0, mVelocity.y)
														// mVelocity �� x���и� ���´�.
		}
		else  // GameObject�� ���߿� ���� ��
		{
			mVelocity += mGravity * Time::GetDeltaTime();
		}

		// �ִ� �ӵ� ����
		math::Vector2 gravity = mGravity;					
		gravity.normalize();								
		float dot = math::Dot(mVelocity, gravity);			
		gravity = gravity * dot;							
		math::Vector2 sideVelocity = mVelocity - gravity;	// �ӵ��� �߷��� ���� �ݿ�?
		if (mLimitedVelocity.y < gravity.length())	// y���� �ӵ��� y���� ���Ѽӵ����� Ŭ��
		{
			gravity.normalize();
			gravity *= mLimitedVelocity.y;
		}
		if (mLimitedVelocity.x < sideVelocity.length())	// x���� �ӵ��� x���� ���Ѽӵ����� Ŭ��
		{
			sideVelocity.normalize();
			sideVelocity *= mLimitedVelocity.x;
		}
		mVelocity = gravity + sideVelocity;

		// ������
		bool noSpeed = (mVelocity == math::Vector2::Zero);
		if (!noSpeed)	// �ӵ� 0�� �ƴ� ���
		{
			math::Vector2 friction = -mVelocity;	// �ӵ��� �ݴ� �������� ������ �ۿ�
			friction = friction.normalize() * mFriction * mMass * Time::GetDeltaTime();	// ������ = ������ ��� * ����

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
			if (mVelocity.length() < friction.length())
			{
				// �ӵ��� 0 �� �����.
				mVelocity = math::Vector2(0.0f, 0.0f);
			}
			else
			{
				// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
				// �������� �ӵ��� �ݴ�����̱⿡ '+' �Ѵ�.
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::GetDeltaTime();
		tr->SetPosition(pos);
		mForce.clear();
	}

	void RigidBody::Render(HDC _hdc)
	{
		// nothing
	}
}