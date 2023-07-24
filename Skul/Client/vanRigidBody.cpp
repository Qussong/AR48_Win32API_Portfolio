#include "vanRigidBody.h"
#include "vanTransform.h"
#include "vanObject.h"

namespace van
{
	RigidBody::RigidBody()
		: Component(enums::eComponentType::RigidBody)
		, mMass(1.0f)
		, mFriction(10.0f)
		, mbGround(false)
	{
		mLimitedVelocity.x = 200.0f;
		mLimitedVelocity.y = 1000.0f;
		mGravity = math::Vector2(0.0f, 800.0f);
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
		// F = m * a -> a = F / m
		mAccelation = mForce / mMass;
		// v1 = v0 + at
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround)	// GameObject�� ������ ���� ��
		{
			math::Vector2 gravity = mGravity;
			gravity.normalize();
			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else  // GameObject�� ���߿� ���� ��
		{
			mVelocity += mGravity * Time::DeltaTime();
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
			friction = friction.normalize() * mFriction * mMass * Time::DeltaTime();

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
		pos = pos + mVelocity * Time::DeltaTime();
		tr->SetPosition(pos);
		mForce.clear();
	}

	void RigidBody::Render(HDC _hdc)
	{
		// nothing
	}
}