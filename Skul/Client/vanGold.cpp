#include "vanGold.h"
#include "vanSpriteRenderer.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanRigidBody.h"
#include "vanPlayer.h"
#include "vanCollisionManager.h"

namespace van
{
	Gold::Gold()
		: mState(GoldState::None)
		, mPastState(GoldState::None)
		, mbPlayAnimation(true)
	{
		AddComponent<RigidBody>()->SetGround(false);
	}

	Gold::~Gold()
	{
		// nothing
	}

	void Gold::Init()
	{
		GameObject::Init();

		MakeAnimation();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		sr->SetTexture(ResourceManager::Find<Texture>(L"Gold"));
		sr->SetScale(math::Vector2(2.0f, 2.0f));
		sr->SetAffectCamera(true);

		SetGoldState(GoldState::Gen);
		GetComponent<Collider>()->SetSize(math::Vector2(20, 20));
	}

	void Gold::Update()
	{
		GameObject::Update();

		// Animation ������� ����_1
		SetGoldPastState(GetGoldState());			// ���� ������ ���¸� ����

		switch (GetGoldState())
		{
		case GoldState::Gen:
			Gen();
			break;
		case GoldState::Idle:
			Idle();
			break;
		case GoldState::Dead:
			Dead();
			break;
		default:
			__noop;
		}

		// Animation ������� ����_2
		// ���� ������ ����,������ �ٲ��ٸ�
		if (GetGoldState() != GetGoldPastState())
		{
			SetPlayAnimation(true);
		}
	}

	void Gold::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Gold::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->CreateAnimation(L"Gold_Idle", ResourceManager::Find<Texture>(L"Gold_Idle"), math::Vector2(0.0f, 0.0f), math::Vector2(50.0f, 30.0f), 9);
		at->CreateAnimation(L"Gold_Dead", ResourceManager::Find<Texture>(L"Gold_Dead"), math::Vector2(0.0f, 0.0f), math::Vector2(59.0f, 54.0f), 29, math::Vector2::Zero, 0.02F);
	}

	void Gold::OnCollisionEnter(Collider* _other)
	{
		// Player�� �浹���� �� �����
		GameObject* obj = _other->GetOwner();
		Player* player = dynamic_cast<Player*>(obj);

		if (player != nullptr)
		{
			// Player ��� ȹ��
			player->AddCoin(100.0f);
			// ��� ��ü ����
			SetGoldState(GoldState::Dead);
			SetPlayAnimation(true);
		}

	}

	void Gold::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Gold::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void Gold::Gen()
	{
		// Ƣ�� �ö��ٰ� ���� �������������� ����
		RigidBody* rb = GetComponent<RigidBody>();
		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		if (rb->GetGround() == true)
		{
			sr->SetTexture(ResourceManager::Find<Texture>(L"Gold_Disappear"));
			SetGoldState(GoldState::Idle);
		}
	}

	void Gold::Idle()
	{
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Drop, true);

		// ���� �پ��������� ����
		Animator* at = GetComponent<Animator>();
		if (GetPlayAnimation() == true)
		{
			at->PlayAnimation(L"Gold_Idle", true);	
			SetPlayAnimation(false);
		}
	}

	void Gold::Dead()
	{
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Drop, false);

		// ������ �浹�Ͽ��� ���� ����
		Animator* at = GetComponent<Animator>();
		if (GetPlayAnimation() == true)
		{
			at->SetScale(math::Vector2(2.0f, 2.0f));
			at->PlayAnimation(L"Gold_Dead", false);
			SetPlayAnimation(false);
		}
		if (at->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}
}