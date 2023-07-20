#include "vanCollisionManager.h"
#include "vanScene.h"
#include "vanSceneManager.h"

namespace van
{
    std::map<UINT64, bool> CollisionManager::mCollisionMap = {};
    std::bitset<LAYER_MAX> CollisionManager::mLayerMasks[LAYER_MAX] = {};

    void CollisionManager::Init()
    {
        // nothing
    }

    void CollisionManager::Update()
    {
        Scene* activeScene = SceneManager::GetActiveScene();
        for (size_t row = 0; row < LAYER_MAX; ++row)
        {
            for (size_t col = 0; col < LAYER_MAX; ++col)
            {
                if (mLayerMasks[row][col] == true)
                {
                    LayerCollision(activeScene, (eLayerType)row, (eLayerType)col);
                }
            }
        }
    }

    void CollisionManager::Render(HDC hdc)
    {
        // nothing
    }

    void CollisionManager::Release()
    {
        // nothing
    }

    void CollisionManager::Clear()
    {
        mLayerMasks->reset();
        mCollisionMap.clear();
    }

    void CollisionManager::CollisionLayerCheck(eLayerType _left, eLayerType _right, bool _enable)
    {
        int row = -1;
        int col = -1;

        if (_left > _right)
        {
            row = (UINT)_left;
            col = (UINT)_right;
        }
        else
        {
            col = (UINT)_left;
            row = (UINT)_right;
        }

        mLayerMasks[row][col] = _enable;
    }

    void CollisionManager::LayerCollision(Scene* _scene, eLayerType _left, eLayerType _right)
    {
        // finds left layer objects
        Layer& leftLayer = _scene->GetLayer(_left);
        std::vector<GameObject*>& lefts = leftLayer.GetGameObjects();

        Layer& rightLayer = _scene->GetLayer(_right);
        std::vector<GameObject*>& rights = rightLayer.GetGameObjects();

        // finds right layer Objects
        for (GameObject* leftObj : lefts)
        {
            Collider* leftCol = leftObj->GetComponent<Collider>();
            if (leftCol == nullptr)
                continue;

            for (GameObject* rightObj : rights)
            {
                Collider* rightCol = rightObj->GetComponent<Collider>();
                if (rightCol == nullptr)
                    continue;
                if (leftObj == rightObj)
                    continue;

                ColliderCollision(leftCol, rightCol);
            }
        }
    }

    void CollisionManager::ColliderCollision(Collider* _left, Collider* _right)
    {
        // �� �浹ü�� ID�� Ȯ��
        ColliderID ID;
        ID.left = (UINT)_left->GetCollisionNum();
        ID.right = (UINT)_right->GetCollisionNum();


        // ���� �浹ü�� ������ �����ͼ� Ȯ���Ѵ�.
        std::map<UINT64, bool>::iterator iter
            = mCollisionMap.find(ID.id);

        // Ȥ�� �浹������ ���ٸ� �������ָ�ȴ�
        if (iter == mCollisionMap.end())
        {
            mCollisionMap.insert(std::make_pair(ID.id, false));
            iter = mCollisionMap.find(ID.id);
        }


        //�浹�Լ� ȣ��
        if (Intersect(_left, _right))
        {
            // �浹 ���λ���
            if (iter->second == false)
            {
                _left->OnCollisionEnter(_right);
                _right->OnCollisionEnter(_left);

                iter->second = true;
            }
            else // ó�� �浹�ϴ� ����
            {
                _left->OnCollisionStay(_right);
                _right->OnCollisionStay(_left);
            }
        }
        else
        {
            // �浹�� ������������
            if (iter->second == true)
            {
                _left->OnCollisionExit(_right);
                _right->OnCollisionExit(_left);

                iter->second = false;
            }
        }
    }

    bool CollisionManager::Intersect(Collider* _left, Collider* _right)
    {
        math::Vector2 leftPos = _left->GetPos();
        math::Vector2 rightPos = _right->GetPos();

        math::Vector2 leftSize = _left->GetSize();
        math::Vector2 rightSize = _right->GetSize();

        if (::fabs(leftPos.x - rightPos.x) < ::fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
            && ::fabs(leftPos.y - rightPos.y) < ::fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
        {
            return true;
        }

        return false;
    }
}