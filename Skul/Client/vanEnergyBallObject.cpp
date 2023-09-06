#include "vanEnergyBallObject.h"
#include "vanCollider.h"
#include "vanCollisionManager.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanPlayer.h"
#include "vanFloor.h"
#include "vanWall.h"
#include "vanTransform.h"
#include "vanEnergyBall.h"
#include "vanYggdrasill.h"
#include "vanMagicOrbEffect.h"
#include "vanObject.h"

#define OBJECT_SPEED	500.0f
#define DAMAGE			10.0f
#define RADIUS			100.0f

namespace van
{
	EnergyBallObject::EnergyBallObject()
	{
		// nothing
	}

	EnergyBallObject::~EnergyBallObject()
	{
		// nothing
	}

	void EnergyBallObject::Init()
	{
		Skill::Init();
		MakeAnimation();

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(50.0f, 50.0f));

		mState = EnergyBallObjectState::Gen;

		CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Skill_EnergyBall, eLayerType::Player, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Skill_EnergyBall, eLayerType::FrontFloor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Skill_EnergyBall, eLayerType::Wall, true);
	}

	void EnergyBallObject::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case EnergyBallObjectState::Gen:
			Gen();
			break;
		case EnergyBallObjectState::Active:
			Active();
			break;
		case EnergyBallObjectState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void EnergyBallObject::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void EnergyBallObject::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"Yggdrasill_EnergyBomb_Object", ResourceManager::Find<Texture>(L"Yggdrasill_EnergyBomb_Object"), math::Vector2(0.0f, 0.0f), math::Vector2(107.0f, 108.0f), 14);
		at->SetScale(math::Vector2(0.5f, 0.5f));
	}

	void EnergyBallObject::OnCollisionEnter(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();

		Player* player = dynamic_cast<Player*>(obj);
		Floor* floor = dynamic_cast<Floor*>(obj);
		Wall* wall = dynamic_cast<Wall*>(obj);

		if (player != nullptr
			|| floor != nullptr 
			|| wall != nullptr)
		{
			// �浹����� Player�� ���
			if (player != nullptr)
			{
				if (player->GetPlayerState() != Player::PlayerState::Dash
					&& player->GetPlayerState() != Player::PlayerState::DoubleDash)
				{
					// �÷��̾�� �������� �ش� or �÷��̾�� �¾����� �˷��ش�.
					player->LoseHp(DAMAGE);
					player->SetPlayerState(Player::PlayerState::Hit);
				}
			}

			// �浹����� Floor�� ���
			if (floor != nullptr)
			{
				// �Ҹ� ����Ʈ 
				MagicOrbEffect* effect = Object::Instantiate<MagicOrbEffect>(enums::eLayerType::Yggdrasill_Effect);
				effect->SetOwner(this);
				effect->GetComponent<Animator>()->SetScale(math::Vector2(0.5f, 0.5f));
				effect->SetOffset(math::Vector2(0.0f, 40.0f));
			}

			// Dead ���·� ��ȯ
			mState = EnergyBallObjectState::Dead;
		}
	}

	void EnergyBallObject::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void EnergyBallObject::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void EnergyBallObject::Gen()
	{
		Animator* at = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		GameObject* owner = GetOwner();

		if (owner != nullptr)
		{
			math::Vector2 center = owner->GetComponent<Transform>()->GetPosition();
			tr->SetPosition(center);	// ��������
			mDirect = math::Vector2(cosf(mRadian), sinf(mRadian)).Normalize();

			at->PlayAnimation(L"Yggdrasill_EnergyBomb_Object", true);

			mState = EnergyBallObjectState::Active;
		}
	}

	void EnergyBallObject::Active()
	{
		EnergyBall* owner = dynamic_cast<EnergyBall*>(GetOwner());

		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		pos += mDirect * OBJECT_SPEED * Time::GetDeltaTime();
		tr->SetPosition(pos);
	}

	void EnergyBallObject::Dead()
	{
		// ��ü�Ҹ�� EnergyBall ��ü�� �ش� ��ü�� �Ҹ��� �˷��ش�.
		GameObject* owner = GetOwner();
		dynamic_cast<EnergyBall*>(owner)->AddBallDestroyCnt();

		// EnergyBallObject ��ü �Ҹ�
		Destroy(this);
	}
}