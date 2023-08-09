#include "vanStage1Scene.h"
#include "vanCamera.h"

namespace van
{
	Stage1Scene::Stage1Scene()
	{
		// nothing
	}

	Stage1Scene::~Stage1Scene()
	{
		// nothing
	}

	void Stage1Scene::Init()
	{
		//SetSceneTarget(nullptr);	// �⺻�� nullptr�̶� ���� ����
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage1Scene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
	}

	void Stage1Scene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene ����
		const wchar_t* str = L"[ Stage1Scene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
}