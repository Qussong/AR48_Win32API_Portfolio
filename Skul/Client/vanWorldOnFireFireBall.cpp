#include "vanWorldOnFireFireBall.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanCollisionManager.h"
#include "vanPlayer.h"
#include "vanWall.h"
#include "vanFloor.h"
#include "vanWorldOnFireOrb.h"
#include "vanTransform.h"
#include "vanBoss.h"
#include "vanExplosionEffect.h"
#include "vanObject.h"

#define OBJECT_SPEED	300.0f
#define DAMAGE			20.0f

namespace van
{
	WorldOnFireFireBall::WorldOnFireFireBall()
	{
		// nothing
	}

	WorldOnFireFireBall::~WorldOnFireFireBall()
	{
		// nothing
	}

	void WorldOnFireFireBall::Init()
	{
		Skill::Init();

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(25.0f, 25.0f));

		mState = WorldOnFireFireBallState::Gen;

		CollisionManager::SetCollisionLayerCheck(eLayerType::Boss_Mage_Skill_FireBall, eLayerType::Player, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Boss_Mage_Skill_FireBall, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Boss_Mage_Skill_FireBall, eLayerType::Wall, true);
	}

	void WorldOnFireFireBall::Update()
	{
		Skill::Update();

		MakeAnimation();

		switch (mState)
		{
		case WorldOnFireFireBallState::Gen:
			Gen();
			break;
		case WorldOnFireFireBallState::Active:
			Active();
			break;
		case WorldOnFireFireBallState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void WorldOnFireFireBall::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void WorldOnFireFireBall::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"WorldOnFire_FireBall_Object_L", ResourceManager::Find<Texture>(L"Mage_WorldOnFire_FireBall_Object_L"), math::Vector2(0.0f, 0.0f), math::Vector2(110.0f, 62.0f), 24);
		at->CreateAnimation(L"WorldOnFire_FireBall_Object_R", ResourceManager::Find<Texture>(L"Mage_WorldOnFire_FireBall_Object_R"), math::Vector2(0.0f, 0.0f), math::Vector2(110.0f, 62.0f), 24);
		at->SetScale(math::Vector2(1.5f, 1.5f));
	}

	void WorldOnFireFireBall::OnCollisionEnter(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();

		Player* player = dynamic_cast<Player*>(obj);
		Floor* floor = dynamic_cast<Floor*>(obj);
		Wall* wall = dynamic_cast<Wall*>(obj);

		if (player != nullptr)
		{
			if (player->GetPlayerState() != Player::PlayerState::Dash
				&& player->GetPlayerState() != Player::PlayerState::DoubleDash)
			{
				// �÷��̾�� �������� �ش� or �÷��̾�� �¾����� �˷��ش�.
				player->LoseHp(DAMAGE);
				player->SetPlayerState(Player::PlayerState::Hit);
			}
			// FireBall��ü �Ҹ�
			mState = WorldOnFireFireBallState::Dead;
		}

		if (floor != nullptr || wall != nullptr)
		{
			if (floor != nullptr)
			{
				ExplosionEffect* effect = Object::Instantiate<ExplosionEffect>(enums::eLayerType::Boss_Mage_Effect);
				effect->SetOwner(this);
				effect->GetComponent<Animator>()->SetScale(math::Vector2(3.0f, 3.0f));
			}
			mState = WorldOnFireFireBallState::Dead;
		}
	}

	void WorldOnFireFireBall::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void WorldOnFireFireBall::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void WorldOnFireFireBall::Gen()
	{
		Animator* at = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		Skill* owner = dynamic_cast<Skill*>(GetOwner());
		Boss* boss = dynamic_cast<Boss*>(owner->GetOwner());	// target(= Player�� ������ �޾ƿ´�)
		
		if (owner != nullptr
			&& boss != nullptr)
		{
			GameObject* target = boss->GetTarget();
			math::Vector2 targetPos = target->GetComponent<Transform>()->GetPosition();
			math::Vector2 ownerPos = owner->GetComponent<Transform>()->GetPosition();

			// FireBall�� ������ġ ����
			tr->SetPosition(ownerPos);

			// Target�� Orb�������� Left�� ���� ��
			if (ownerPos.x >= targetPos.x)
			{
				at->PlayAnimation(L"WorldOnFire_FireBall_Object_L", true);
			}
			// Target�� Orb�������� Right�� ���� ��
			if (ownerPos.x < targetPos.x)
			{
				at->PlayAnimation(L"WorldOnFire_FireBall_Object_R", true);
			}

			mState = WorldOnFireFireBallState::Active;
		}
	}

	void WorldOnFireFireBall::Active()
	{
		SetFireBallMove();
	}

	void WorldOnFireFireBall::Dead()
	{
		// �ش� ��ü�� �Ҹ� ������ �˷��ش�.
		WorldOnFireOrb* owner = dynamic_cast<WorldOnFireOrb*>(GetOwner());
		owner->AddFireBallDeadCnt();

		// FireBall��ü �Ҹ�
		Destroy(this);
	}

	void WorldOnFireFireBall::SetFireBallMove()
	{
		WorldOnFireOrb* owner = dynamic_cast<WorldOnFireOrb*>(GetOwner());

		if (owner != nullptr)
		{
			Transform* tr = GetComponent<Transform>();
			Transform* tr_owner = owner->GetComponent<Transform>();
			Transform* tr_target = owner->GetTarget()->GetComponent<Transform>();

			math::Vector2 pos = tr->GetPosition();

			if (mbSetFlag == true)
			{
				mDepartPos = tr_owner->GetPosition();				// �߻�����
				mTargetPos = tr_target->GetPosition();				// ��������
				mDirect = (mTargetPos - mDepartPos).Normalize();	// ���⺤��

				mbSetFlag = false;
			}

			pos.x += mDirect.x * OBJECT_SPEED * Time::GetDeltaTime();
			pos.y += mDirect.y * OBJECT_SPEED * Time::GetDeltaTime();

			tr->SetPosition(pos);
		}
	}
}
