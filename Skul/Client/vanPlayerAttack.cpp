#include "vanPlayerAttack.h"
#include "vanTransform.h"
#include "vanPlayer.h"
#include "vanCollider.h"

#include "vanCollisionManager.h"
#include "vanPlayer.h"

namespace van
{
	PlayerAttack::PlayerAttack()
		//: mOwner(nullptr)
		//, mOwnerPos(math::Vector2::Zero)
		//, mOwnerState((UINT)Player::PlayerState::None)
		//, mOwnerDirection((UINT)Player::PlayerDirection::None)
		//, mOffset(math::Vector2::Zero)
		: mbCombo(false)
	{
		// nothing
	}

	PlayerAttack::~PlayerAttack()
	{
		// nothing
	}

	void PlayerAttack::Init()
	{
		GetComponent<Collider>()->SetLineColor(RGB(0, 0, 255));			// Collider �� ���ڻ� ����(Attack ���� �� : Blue)
	}

	void PlayerAttack::Update()
	{
		GameObject::Update();

		Player* player = dynamic_cast<Player*>(GetOwner());

		// PlayerAttack Ŭ������ �����ڰ� Player �� ���
		if (player != nullptr)
		{
			Player::PlayerDirection direction =  player->GetPlayerDirection();	// Player�� ������ �о��
			math::Vector2 size = GetOwner()->GetComponent<Collider>()->GetSize();	// Player�� Collider ���� ũ�⸦ �о��

			if (direction == Player::PlayerDirection::Left)			// Player�� ������ ������ ��
			{
				SetOffset(math::Vector2(-(size.x / 2), 0.0f));
			}
			if (direction == Player::PlayerDirection::Right)		// Player�� ������ �������� ��
			{
				SetOffset(math::Vector2(size.x / 2, 0.0f));
			}

			SetOwnerState((UINT)(player->GetPlayerState()));		// Player�� ���¸� �о��
			if(GetOwnerState() == (UINT)Player::PlayerState::AttackA
				|| GetOwnerState() == (UINT)Player::PlayerState::JumpAttack)	// Player�� ���ݻ����� ��(AttackA,JumpAttack)
			{
				GetComponent<Collider>()->SetActive(true);
				CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Attack, eLayerType::Monster, true);
				SetOwnerDirection((UINT)(player->GetPlayerDirection()));

				mbCombo = player->GetCombo();
			}
			else if (GetOwnerState() == (UINT)Player::PlayerState::AttackB)		// Player�� ���ݻ����� ��(AttackB)
			{
				if (mbCombo)
				{
					attackList.clear();
					mbCombo = false;
				}
				CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Attack, eLayerType::Monster, true);
				SetOwnerDirection((UINT)(player->GetPlayerDirection()));
			}
			else
			{
				GetComponent<Collider>()->SetActive(false);
				CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Attack, eLayerType::Monster, false);

				attackList.clear();	// ���������� ������ ���ݹ��� �浹 ������ ����ش�.
			}
		}

		SetOwnerPos(GetOwner()->GetComponent<Transform>()->GetPosition());
		GetComponent<Transform>()->SetPosition(GetOwnerPos() + GetOffset());
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