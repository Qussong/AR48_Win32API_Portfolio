#include "vanAttack.h"
#include "vanTransform.h"
#include "vanPlayer.h"
#include "vanCollider.h"

#include "vanCollisionManager.h"
#include "vanPlayer.h"

namespace van
{
	Attack::Attack()
		: mOwner(nullptr)
		, mOwnerPos(math::Vector2::Zero)
		, mOwnerState((UINT)Player::PlayerState::None)
		, mOwnerDirection((UINT)Player::PlayerDirection::None)
		, mOffset(math::Vector2::Zero)
		, mbCombo(false)
	{
		// nothing
	}

	Attack::~Attack()
	{
		// nothing
	}

	void Attack::Init()
	{
		GetComponent<Collider>()->SetLineColor(RGB(0, 0, 255));	// Collider �� ���� ���� �Ķ������� ����
	}

	void Attack::Update()
	{
		GameObject::Update();

		Player* player = dynamic_cast<Player*>(mOwner);

		// Attack Ŭ������ �����ڰ� Player �� ���
		if (player != nullptr)
		{
			Player::PlayerDirection direction =  player->GetPlayerDirection();	// Player�� ������ �о��
			math::Vector2 size = mOwner->GetComponent<Collider>()->GetSize();	// Player�� Collider ���� ũ�⸦ �о��

			if (direction == Player::PlayerDirection::Left)						// Player�� ������ ������ ��
			{
				mOffset = math::Vector2(-(size.x / 2 ), 0.0f);
			}
			if (direction == Player::PlayerDirection::Right)			// Player�� ������ �������� ��
			{
				mOffset = math::Vector2(size.x / 2, 0.0f);
			}

			mOwnerState = (UINT)(player->GetPlayerState());				// Player�� ���¸� �о��
			if(mOwnerState == (UINT)Player::PlayerState::AttackA)		// Player�� ���ݻ����� ��(AttackA)
			{
				GetComponent<Collider>()->SetActive(true);
				CollisionManager::SetCollisionLayerCheck(eLayerType::Effect, eLayerType::Monster, true);
				mOwnerDirection = (UINT)(player->GetPlayerDirection());

				mbCombo = player->GetCombo();
			}
			else if (mOwnerState == (UINT)Player::PlayerState::AttackB)	// Player�� ���ݻ����� ��(AttackB)
			{
				if (mbCombo)
				{
					attackList.clear();
					mbCombo = false;
				}
				CollisionManager::SetCollisionLayerCheck(eLayerType::Effect, eLayerType::Monster, true);
				mOwnerDirection = (UINT)(player->GetPlayerDirection());
			}
			else
			{
				GetComponent<Collider>()->SetActive(false);
				CollisionManager::SetCollisionLayerCheck(eLayerType::Effect, eLayerType::Monster, false);

				attackList.clear();	// ���������� ������ ���ݹ��� �浹 ������ ����ش�.
			}
		}

		mOwnerPos = mOwner->GetComponent<Transform>()->GetPosition();
		/*this->*/GetComponent<Transform>()->SetPosition(mOwnerPos + mOffset);
	}

	void Attack::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Attack::MakeAnimation()
	{

	}

	void Attack::OnCollisionEnter(Collider* _other)
	{

	}

	void Attack::OnCollisionStay(Collider* _other)
	{
		
	}

	void Attack::OnCollisionExit(Collider* _other)
	{
		
	}
}