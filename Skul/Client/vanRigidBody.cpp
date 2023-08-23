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
		, mLimitedVelocity(math::Vector2(1000.0f, 3000.0f))
		, mbGround(false)
		, mbSkyDash(false)
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

		if (mbProjectiveBody == true)					// y�� �� �ۿ� o, �߷� �ۿ� x
		{
			math::Vector2 dir = mProjectiveDirection;	// ����ü�� ���Ͱ�

			if (dir != math::Vector2::Zero)
			{
				dir.Normalize();							// ���Ⱚ�� �����.
				float dot = math::Dot(mVelocity, dir);		// ����ü�� ���⺤�Ϳ� �ӵ��� ���Ѵ�.
															// ������ �ǹ� : �º��� ���͸� �캯�� ���Ϳ� �������� ���ϴ� ��
				math::Vector2 velocity = dir * dot;			// �����ӵ�
				mVelocity = velocity;
			}
		}
		else if (mbGround || mbSkyDash)					// y�� �� �ۿ� x
		{
			math::Vector2 gravity = mGravity;			// �߷� �ʱⰪ -> x = 0, y = 980
			gravity.Normalize();						// �߷� -> x = 0, y = 1
			float dot = math::Dot(mVelocity, gravity);	// dot = mVelocity.y
														// ������ �ǹ� : �º��� ���͸� �캯�� ���Ϳ� �������� ���ϴ� ��
			math::Vector2 vel = gravity * dot;
			mVelocity -= vel;							// mVelocity -= Vector2(0, mVelocity.y)
														// mVelocity �� x���и� ���´�.
		}
		else                                            // y�� �� �ۿ� o, �߷� �ۿ� o
		{
			mVelocity += mGravity * Time::GetDeltaTime();
		}

		// �ִ� �ӵ� ����
		math::Vector2 gravity = mGravity;					
		gravity.Normalize();								
		float dot = math::Dot(mVelocity, gravity);			
		gravity = gravity * dot;							
		math::Vector2 sideVelocity = mVelocity - gravity;	

		if (mLimitedVelocity.y < gravity.Length())			// y���� �ӵ��� y���� ���Ѽӵ����� Ŭ��
		{
			gravity.Normalize();
			gravity *= mLimitedVelocity.y;
		}
		if (mLimitedVelocity.x < sideVelocity.Length())		// x���� �ӵ��� x���� ���Ѽӵ����� Ŭ��
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocity.x;
		}
		mVelocity = gravity + sideVelocity;

		// ������
		bool noSpeed = (mVelocity == math::Vector2::Zero);
		if (!noSpeed
			&& mbProjectiveBody == false)	// �ӵ� 0�� �ƴ� ���
		{
			math::Vector2 friction = -mVelocity;	// �ӵ��� �ݴ� �������� ������ �ۿ�
			friction = 
				friction.Normalize() * mFriction * mMass * Time::GetDeltaTime();	// ������ = ������ ��� * ����

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
			if (mVelocity.Length() < friction.Length())
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
		mForce.Clear();
	}

	void RigidBody::Render(HDC _hdc)
	{
		// nothing
	}
}