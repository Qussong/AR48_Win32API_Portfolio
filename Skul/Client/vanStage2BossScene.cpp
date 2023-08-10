#include "vanStage2BossScene.h"
#include "vanCamera.h"

namespace van
{
	Stage2BossScene::Stage2BossScene()
	{
		// nothing
	}

	Stage2BossScene::~Stage2BossScene()
	{
		// nothing
	}

	void Stage2BossScene::Init()
	{
		//SetSceneTarget(nullptr);	// �⺻�� nullptr�̶� ���� ����
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage2BossScene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
	}

	void Stage2BossScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene ����
		const wchar_t* str = L"[ Stage2BossScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
	void Stage2BossScene::SceneIN()
	{
	}
	void Stage2BossScene::SceneOut()
	{
	}
}