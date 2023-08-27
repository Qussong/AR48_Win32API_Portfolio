#include "vanCatSeol.h"
#include "vanAnimator.h"
#include "vanCollider.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanRigidBody.h"
#include "vanTransform.h"

#define WALK_SPEED			150.0f

namespace van
{
	CatSeol::CatSeol()
	{
		// nothing
	}

	CatSeol::~CatSeol()
	{
		// nothing
	}

	void CatSeol::Init()
	{
		MakeAnimation();

		// NPC �ʱ⼳��
		SetNPCDirection(NPCDirection::Left);
		SetNPCState(NPCState::Patrol);
		GetComponent<Collider>()->SetSize(math::Vector2(58.0f, 40.0f));
	}

	void CatSeol::Update()
	{
		NPC::Update();

		// Animation ������� ����_1
		SetNPCPastState(GetNPCState());			// ���� NPC�� ���¸� ����
		SetNPCPastDirection(GetNPCDirection());	// ���� NPC�� ������ ����

		switch (GetNPCState())
		{
		case NPCState::Idle:
			Idle();
			break;
		case NPCState::Walk:
			Walk();
			break;
		case NPCState::Patrol:
			Patrol();
			break;
		default:
			__noop;
		}

		// Animation ������� ����_2
		// ���� ������ ����,������ �ٲ��ٸ�
		if (GetNPCState() != GetNPCPastState()
			|| GetNPCDirection() != GetNPCPastDirection())
		{
			SetPlayAnimation(true);
		}
	}

	void CatSeol::Render(HDC _hdc)
	{
		NPC::Render(_hdc);
	}

	void CatSeol::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		// Idle
		at->CreateAnimation(L"Cat_Seol_Idle_L", ResourceManager::Find<Texture>(L"Cat_Seol_Idle_L"), math::Vector2(0.0f, 0.0f), math::Vector2(27.0f, 20.0f), 2);
		at->CreateAnimation(L"Cat_Seol_Idle_R", ResourceManager::Find<Texture>(L"Cat_Seol_Idle_R"), math::Vector2(0.0f, 0.0f), math::Vector2(27.0f, 20.0f), 2);
		// Walk
		at->CreateAnimation(L"Cat_Seol_Walk_L", ResourceManager::Find<Texture>(L"Cat_Seol_Walk_L"), math::Vector2(0.0f, 0.0f), math::Vector2(29.0f, 20.0f), 6);
		at->CreateAnimation(L"Cat_Seol_Walk_R", ResourceManager::Find<Texture>(L"Cat_Seol_Walk_R"), math::Vector2(0.0f, 0.0f), math::Vector2(29.0f, 20.0f), 6);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void CatSeol::Idle()
	{
		Animator* at = GetComponent<Animator>();

		// Patrol ������ �� 
		if (GetPatrolFlag() == true)
		{
			// �ð� ����
			AddTimer(Time::GetDeltaTime());

			// ������ �ð��� 3�� �̻��̵Ǹ�
			if (GetTimer() >= 3.0f)
			{
				SetTimer(0.0f);					// �����ð� 0�ʷ� �ʱ�ȭ
				SetNPCState(NPCState::Walk);	// Monster�� ���¸� Walk �� ����

				// ������ȯ
				if (GetNPCDirection() == NPCDirection::Left)
				{
					SetNPCDirection(NPCDirection::Right);
				}
				else
				{
					SetNPCDirection(NPCDirection::Left);
				}
			}
			// ������ �ð��� 3�� �̻��� �ƴ϶��
			else
			{
				if (GetNPCDirection() == NPCDirection::Left)
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Cat_Seol_Idle_L", true);
						SetPlayAnimation(false);
					}
				}
				else
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Cat_Seol_Idle_R", true);
						SetPlayAnimation(false);
					}
				}
			}
		}
		// Patrol ���°� �ƴҶ�
		else
		{
			__noop;
		}
	}

	void CatSeol::Walk()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		Animator* at = GetComponent<Animator>();

		// Patrol ������ �� 
		if (GetPatrolFlag() == true)
		{
			// �ð� ����
			AddTimer(Time::GetDeltaTime());

			// ������ �ð��� 2�� �̻��̵Ǹ�
			if (GetTimer() >= 2.0f)
			{
				SetTimer(0.0f);
				SetNPCState(NPCState::Idle);
			}
			// ������ �ð��� 2�� �̻��� �ƴ϶��
			else
			{
				// Walk_L
				if (GetNPCDirection() == NPCDirection::Left)
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Cat_Seol_Walk_L", true);
						SetPlayAnimation(false);
					}
					pos.x -= (WALK_SPEED * Time::GetDeltaTime());
					tr->SetPosition(pos);
				}
				// Walk_R
				if (GetNPCDirection() == NPCDirection::Right)
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Cat_Seol_Walk_R", true);
						SetPlayAnimation(false);
					}
					pos.x += (WALK_SPEED * Time::GetDeltaTime());
					tr->SetPosition(pos);
				}
			}
		}
		// Patrol ���°� �ƴҶ�
		else
		{
			__noop;
		}
	}

	void CatSeol::Patrol()
	{
		// ���Ͱ� ��� ���¿��� Patrol �ൿ�� ���̵��� ����
		SetPatrolFlag(true);
		// Patrol ���·� ��ȯ�Ʊ⿡ Trace Flag�� ���ش�.
		//SetTraceFlag(false);
		// Patrol�� Idle ���� �����ϵ��� �Ѵ�.
		SetNPCState(NPCState::Idle);
	}

}