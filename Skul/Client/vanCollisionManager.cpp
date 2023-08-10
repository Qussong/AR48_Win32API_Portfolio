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
        //mLayerMasks->reset();   // ��Ʈ���� ��Ʈ���� ���� 0���� ���� (����)
        for (int i = 0; i < LAYER_MAX; i++)
        {
            mLayerMasks[i].reset();
        }
        mCollisionMap.clear();  // map�� ��� ��Ҹ� �����. ��, map�� ����. (����)
    }

    void CollisionManager::SetCollisionLayerCheck(eLayerType _left, eLayerType _right, bool _enable)
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

        mLayerMasks[row][col] = _enable;    // ���̾�� ���� �浹üũ ���� ����
    }

    bool CollisionManager::Intersect(Collider* _left, Collider* _right)
    {
        math::Vector2 leftPos = _left->GetPos();    // _left ������ ��ġ ��ǥ ����
        math::Vector2 rightPos = _right->GetPos();  // _right ������ ��ġ ��ǥ ����

        math::Vector2 leftSize = _left->GetSize();      // _left ������ ũ�� ����
        math::Vector2 rightSize = _right->GetSize();    // _right ������ ũ�� ����

        // �� �簢���� �߽ɻ����� �Ÿ��� �� �簢���� �ʺ�/���� ���� ������ �պ��� ������ �浹����
        if (::fabs(leftPos.x - rightPos.x) < ::fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
            && ::fabs(leftPos.y - rightPos.y) < ::fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
        {
            return true;
        }

        return false;
    }

    void CollisionManager::ColliderCollision(Collider* _left, Collider* _right)
    {
        // �� �浹ü�� ID�� Ȯ��
        ColliderID ID;
        ID.left = (UINT)_left->GetCollisionNum();   // �Ķ���ͷ� ���� ù��° ������ �浹ü ID ����
        ID.right = (UINT)_right->GetCollisionNum(); // �Ķ���ͷ� ���� �ι�° ������ �浹ü ID ����


        // ���� �浹ü�� ������ �����ͼ� Ȯ���Ѵ�.
        std::map<UINT64, bool>::iterator iter
            = mCollisionMap.find(ID.id);    // ������ ���ٸ� map.end() ��ȯ

        // Ȥ�� �浹������ ���ٸ� �������ָ�ȴ�
        if (iter == mCollisionMap.end())
        {
            mCollisionMap.insert(std::make_pair(ID.id, false));
            iter = mCollisionMap.find(ID.id);
        }

        // �浹�Լ� ȣ��
        if (Intersect(_left, _right))   // �浹����
        {
            if (iter->second == false)  // ó�� �浹�ϴ� ����
            {
                _left->OnCollisionEnter(_right);
                _right->OnCollisionEnter(_left);

                iter->second = true;
            }
            else  // �浹 ���λ���
            {
                _left->OnCollisionStay(_right);
                _right->OnCollisionStay(_left);
            }
        }
        else  // ���浹����
        {
            if (iter->second == true)   // �浹�� ������������
            {
                _left->OnCollisionExit(_right);
                _right->OnCollisionExit(_left);

                iter->second = false;
            }
        }
    }

    void CollisionManager::LayerCollision(Scene* _scene, eLayerType _left, eLayerType _right)
    {
        // finds left layer objects
        Layer& leftLayer = _scene->GetLayer(_left); // �ش� Scene���� _left�� �ش��ϴ� layer�� ����
        std::vector<GameObject*>& lefts = leftLayer.GetGameObjects();   // �ش� ���̾�(leftLayer)�� GameObject ��ü���� ����Ű�� ���� ����

        Layer& rightLayer = _scene->GetLayer(_right);   // �ش� Scene���� _right�� �ش��ϴ� layer�� ����
        std::vector<GameObject*>& rights = rightLayer.GetGameObjects(); // �ش� ���̾�(rightLayer)�� GameObject ��ü���� ����Ű�� ���� ����

        // finds right layer Objects
        for (GameObject* leftObj : lefts)   // leftLayer �� ���ϴ� GameObject�� �ϳ��� ȣ��
        {
            Collider* leftCol = leftObj->GetComponent<Collider>();  // leftLayer �� ���ϴ� GameObject�� Collider �Ӽ� ����
            if (leftCol == nullptr) // �ش� GameObject ��ü�� Collider �Ӽ��� ���ٸ� ���� GameObject ��ü ȣ��
                continue;

            for (GameObject* rightObj : rights) // rightLayer �� ���ϴ� GameObject�� �ϳ��� ȣ��
            {
                Collider* rightCol = rightObj->GetComponent<Collider>();    // �ش� GameObject ��ü�� Collider �Ӽ� ����
                if (rightCol == nullptr)    // �ش� GameObject ��ü�� Collider �Ӽ��� ���ٸ� ���� ��ü ȣ��
                    continue;
                if (leftObj == rightObj)    // �񱳴���� �����̸� ���� ��ü ȣ��
                    continue;

                ColliderCollision(leftCol, rightCol);   // �� ��ü�� �浹������(enter, stay, exit)���� ���� ���
            }
        }
    }
}