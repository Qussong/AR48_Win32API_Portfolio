#include "vanStage2EnterScene.h"
#include "vanCamera.h"

namespace van
{
	Stage2EnterScene::Stage2EnterScene()
	{
		// nothing
	}

	Stage2EnterScene::~Stage2EnterScene()
	{
		// nothing
	}

	void Stage2EnterScene::Init()
	{
		//SetSceneTarget(nullptr);	// �⺻�� nullptr�̶� ���� ����
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage2EnterScene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
	}

	void Stage2EnterScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene ����
		const wchar_t* str = L"[ Stage2EnterScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
	void Stage2EnterScene::SceneIN()
	{
	}
	void Stage2EnterScene::SceneOut()
	{
	}
}