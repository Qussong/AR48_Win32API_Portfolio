#include "vanPlayerAttack.h"
#include "vanTransform.h"
#include "vanPlayer.h"
#include "vanCollider.h"

#include "vanCollisionManager.h"
#include "vanPlayer.h"

#define PLAYER_DAMAGE	10.0f

namespace van
{
	PlayerAttack::PlayerAttack()
		: mbCombo(false)
		, mAttackDamage(PLAYER_DAMAGE)
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
			// PlayerAttack �� Collider ��ġ ����
			Player::PlayerDirection direction =  player->GetPlayerDirection();		// Player�� ������ �о��
			math::Vector2 size = GetOwner()->GetComponent<Collider>()->GetSize();	// Player�� Collider ���� ũ�⸦ �о��

			if (direction == Player::PlayerDirection::Left)							// Player�� ������ ������ ��
			{
				SetOffset(math::Vector2(-(size.x / 2), 0.0f));
			}
			if (direction == Player::PlayerDirection::Right)						// Player�� ������ �������� ��
			{
				SetOffset(math::Vector2(size.x / 2, 0.0f));
			}

			// Ȱ��ȭ ���� ����
			SetOwnerState((UINT)(player->GetPlayerState()));						// Player�� ���¸� �о��

			if(GetOwnerState() == (UINT)Player::PlayerState::AttackA
				|| GetOwnerState() == (UINT)Player::PlayerState::JumpAttack)		// Player�� ���ݻ����� ��(AttackA,JumpAttack)
			{
				mActiveFlag = true;
				GetComponent<Collider>()->SetActive(true);
				SetOwnerDirection((UINT)(player->GetPlayerDirection()));

				mbCombo = player->GetCombo();
			}
			else if (GetOwnerState() == (UINT)Player::PlayerState::AttackB)			// Player�� ���ݻ����� ��(AttackB)
			{
				if (mbCombo)
				{
					attackList.clear();
					mbCombo = false;
				}
				mActiveFlag = true;
				SetOwnerDirection((UINT)(player->GetPlayerDirection()));
			}
			else
			{
				mActiveFlag = false;
				GetComponent<Collider>()->SetActive(false);

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