#include "vanPlayerAttack.h"
#include "vanTransform.h"
#include "vanPlayer.h"
#include "vanCollider.h"

#include "vanCollisionManager.h"
#include "vanPlayer.h"

namespace van
{
	PlayerAttack::PlayerAttack()
		: mOwner(nullptr)
		, mOwnerPos(math::Vector2::Zero)
		, mOwnerState((UINT)Player::PlayerState::None)
		, mOwnerDirection((UINT)Player::PlayerDirection::None)
		, mOffset(math::Vector2::Zero)
		, mbCombo(false)
	{
		// nothing
	}

	PlayerAttack::~PlayerAttack()
	{
		// nothing
	}

	void PlayerAttack::Init()
	{
		GetComponent<Collider>()->SetLineColor(RGB(0, 0, 255));	// Collider �� ���� ���� �Ķ������� ����
	}

	void PlayerAttack::Update()
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
			if(mOwnerState == (UINT)Player::PlayerState::AttackA
				|| mOwnerState == (UINT)Player::PlayerState::JumpAttack)	// Player�� ���ݻ����� ��(AttackA,JumpAttack)
			{
				GetComponent<Collider>()->SetActive(true);
				CollisionManager::SetCollisionLayerCheck(eLayerType::Effect, eLayerType::Monster, true);
				mOwnerDirection = (UINT)(player->GetPlayerDirection());

				mbCombo = player->GetCombo();
			}
			else if (mOwnerState == (UINT)Player::PlayerState::AttackB)		// Player�� ���ݻ����� ��(AttackB)
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

	void PlayerAttack::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void PlayerAttack::MakeAnimation()
	{
		// nothing
	}

	void PlayerAttack::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void PlayerAttack::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void PlayerAttack::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}