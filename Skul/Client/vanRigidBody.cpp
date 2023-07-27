#include "vanRigidBody.h"
#include "vanTransform.h"
#include "vanObject.h"

namespace van
{
	RigidBody::RigidBody()
		: Component(enums::eComponentType::RigidBody)
		, mMass(1.0f)
		, mFriction(10.0f)
		, mForce(math::Vector2::Zero)
		, mAccelation(math::Vector2::Zero)
		, mVelocity(math::Vector2::Zero)
		, mGravity(math::Vector2(0.0f, 2000.0f))
		, mLimitedVelocity(math::Vector2(2000.0f, 2000.0f))
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
			mVelocity -= val;					// mVelocity -= Vector2(0, mVelocity.y)
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

		math::Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocity.y < gravity.length())
		{
			gravity.normalize();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < sideVelocity.length())
		{
			sideVelocity.normalize();
			sideVelocity *= mLimitedVelocity.x;
		}
		mVelocity = gravity + sideVelocity;

		// ������ ���� (����� ���� ���� �ӵ� 0�� �ƴ� ���)
		if (!(mVelocity == math::Vector2::Zero))
		{
			// �ӵ��� �ݴ� �������� �������� ����
			math::Vector2 friction = -mVelocity;
			friction = friction.normalize() * mFriction * mMass * Time::GetDeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
			if (mVelocity.length() < friction.length())
			{
				// �ӵ��� 0 �� �����.
				mVelocity = math::Vector2(0.0f, 0.0f);
			}
			else
			{
				// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
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