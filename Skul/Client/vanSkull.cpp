#include "vanSkull.h"
#include "vanRigidBody.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanCollisionManager.h"
#include "vanWall.h"
#include "vanTransform.h"
#include "vanSceneManager.h"

#define VELOCITY_X      150.0f
#define SKILL_DAMAGE    30.0f

namespace van
{
    Skull::Skull()
        : mSkillDamage(SKILL_DAMAGE)
    {
        AddComponent<RigidBody>()->SetGround(true);
        AddComponent<SpriteRenderer>();
    }

    Skull::~Skull()
    {
        // nothing
    }

    void Skull::Init()
    {
        GameObject::Init();

        SpriteRenderer* sr = GetComponent<SpriteRenderer>();
        sr->SetTexture(ResourceManager::Find<Texture>(L"Head"));
        sr->SetScale(math::Vector2(2.0f, 2.0f));
        sr->SetAffectCamera(true);

        // ��ü�� ��ġ ����
        Scene* scene = SceneManager::GetActiveScene();
        GameObject* obj = scene->GetSceneTarget();
        math::Vector2 pos = obj->GetComponent<Transform>()->GetPosition();
        Transform* tr = GetComponent<Transform>();
        tr->SetPosition(pos);

        // ��ü�� �浹ü ��ġ ����
        // Render �� ź ���Ŀ� ���ΰ�ü�� Transform�� ���󰡱⿡ �浹������ �����ϱ����ؼ� ���� �������ش�.
        Collider* col = GetComponent<Collider>();
        col->SetSize(math::Vector2(35, 35));
        col->SetPos(pos);

        CollisionManager::SetCollisionLayerCheck(eLayerType::Skill, eLayerType::Floor, true);
        CollisionManager::SetCollisionLayerCheck(eLayerType::Skill, eLayerType::FrontFloor, true);
        CollisionManager::SetCollisionLayerCheck(eLayerType::Skill, eLayerType::Wall, true);
        CollisionManager::SetCollisionLayerCheck(eLayerType::Skill, eLayerType::Monster, true);
        CollisionManager::SetCollisionLayerCheck(eLayerType::Skill, eLayerType::Boss_Mage, true);
        CollisionManager::SetCollisionLayerCheck(eLayerType::Skill, eLayerType::Yggdrasill_Head, true);
        CollisionManager::SetCollisionLayerCheck(eLayerType::Skill, eLayerType::Yggdrasill_Hand, true);
    }

    void Skull::Update()
    {
        GameObject::Update();

        if (mbCollision == true)
        {
            math::Vector2 velocity = GetComponent<RigidBody>()->GetVelocity();
            if (velocity.y == 0)
            {
                GetComponent<RigidBody>()->SetVelocity(math::Vector2::Zero);
            }
        }
    }

    void Skull::Render(HDC _hdc)
    {
        GameObject::Render(_hdc);
    }

    void Skull::MakeAnimation()
    {
        // nothing
    }

    void Skull::OnCollisionEnter(Collider* _other)
    {
        GameObject* obj = _other->GetOwner();
        Wall* wall = dynamic_cast<Wall*>(obj);

        // ���� ���뺮�϶� ��� (�Ʒ��� ������ Ÿ���ʰ� �ٷ� Ż���Ѵ�.)
        if (wall != nullptr)
        {
            if (wall->GetFloorLimit() == true)
            {
                return;
            }
        }

        CollisionManager::SetCollisionLayerCheck(eLayerType::Skill, eLayerType::Monster, false);
        CollisionManager::SetCollisionLayerCheck(eLayerType::Skill, eLayerType::Boss_Mage, false);
        CollisionManager::SetCollisionLayerCheck(eLayerType::Skill, eLayerType::Yggdrasill_Head, false);
        CollisionManager::SetCollisionLayerCheck(eLayerType::Skill, eLayerType::Yggdrasill_Hand, false);

        // �Ӹ� ���� ����
        mbCollision = true;
        RigidBody* rb = GetComponent<RigidBody>();
        rb->SetGround(false);
        if (mDirection == HeadDirection::Left)
        {
            rb->SetVelocity(math::Vector2(VELOCITY_X, 0.0f));
        }

        if (mDirection == HeadDirection::Right)
        {
            rb->SetVelocity(math::Vector2(-VELOCITY_X, 0.0f));
        }
    }

    void Skull::OnCollisionStay(Collider* _other)
    {
        // nothing
    }

    void Skull::OnCollisionExit(Collider* _other)
    {
        // nothing
    }
}