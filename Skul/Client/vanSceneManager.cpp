#include "vanSceneManager.h"
#include "CommonInclude.h"
#include "vanCamera.h"

#include "vanTitleScene.h"
#include "vanLoadingScene.h"
#include "vanTestScene.h"
#include "vanHomeScene.h"
#include "vanStage1EnterScene.h"
#include "vanStage1Monster1Scene.h"
#include "vanStage1Monster2Scene.h"
#include "vanStage1MiddleBossScene.h"
#include "vanStage1BossEnterScene.h"
#include "vanStage1BossScene.h"
#include "vanStage2BossEnterScene.h"
#include "vanStage2BossScene.h"
#include "vanEndingScene.h"

namespace van
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Init()
	{
		CreateScene<LoadingScene>(L"LoadingScene");	// ���� ���� ����������Ѵ�.

		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<EndingScene>(L"EndingScene");
		CreateScene<TestScene>(L"TestScene");

		CreateScene<HomeScene>(L"HomeScene");
		CreateScene<Stage1EnterScene>(L"Stage1EnterScene");
		CreateScene<Stage1Monster1Scene>(L"Stage1Monster1Scene");
		CreateScene<Stage1Monster2Scene>(L"Stage1Monster2Scene");
		CreateScene<Stage1MiddleBossScene>(L"Stage1MiddleBossScene");
		CreateScene<Stage1BossEnterScene>(L"Stage1BossEnterScene");
		CreateScene<Stage1BossScene>(L"Stage1BossScene");

		LoadScene(L"TitleScene");
	}

	void SceneManager::Update()
	{
		// ȭ�� ��ȯ
		if (Input::GetKey(eKeyCode::M))
		{
			LoadScene(L"Stage1MiddleBossScene");	// ������
		}
		// ȭ����ȯ_Test
		if (Input::GetKeyDown(eKeyCode::T))
		{
			LoadScene(L"TestScene");
		}
		// ȭ����ȯ_Next6
		if (Input::GetKeyDown(eKeyCode::N))
		{
			std::wstring name = mActiveScene->GetName();
			Next(name);
		}
		// ȭ����ȯ_Previous
		if (Input::GetKeyDown(eKeyCode::P))
		{
			std::wstring name = mActiveScene->GetName();
			Previous(name);
		}

		mActiveScene->Update();
	}

	void SceneManager::Render(HDC _hdc)
	{
		mActiveScene->Render(_hdc);
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		// ���ο� Scene�� �ҷ��������� ���� Scene�� ���� ������ �ʱ�ȭ���ش�.
		mActiveScene->SceneOut();

		// find(key) : �ش� Ű ���� ���� pair Ÿ�� ���� ��ȯ�Ѵ�.
		// ���� ã�� ���ϸ� map.end() �� ��ȯ�Ѵ�.
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);
		if (iter == mScenes.end())
		{
			return nullptr;
		}
		mActiveScene = iter->second;

		// ���ο� Scene�� ���� ������ ���ش�.
		mActiveScene->SceneIN();

		return iter->second;
	}

	void SceneManager::Next(const std::wstring& name)
	{
		if (name == L"TitleScene")
		{
			LoadScene(L"LoadingScene");
		}

		if (name == L"LoadingScene")
		{
			LoadScene(L"HomeScene");
		}

		if (name == L"HomeScene")
		{
			LoadScene(L"Stage1EnterScene");
		}

		if (name == L"Stage1EnterScene")
		{
			LoadScene(L"Stage1Monster1Scene");
		}

		if (name == L"Stage1Monster1Scene")
		{
			LoadScene(L"Stage1Monster2Scene");
		}

		if (name == L"Stage1Monster2Scene")
		{
			LoadScene(L"Stage1MiddleBossScene");
		}

		if (name == L"Stage1MiddleBossScene")
		{
			LoadScene(L"Stage1BossEnterScene");
		}

		if (name == L"Stage1BossEnterScene")
		{
			LoadScene(L"Stage1BossScene");
		}

		if (name == L"Stage1BossScene")
		{
			LoadScene(L"EndingScene");
		}
	}

	void SceneManager::Previous(const std::wstring& name)
	{
		if (name == L"LoadingScene")
		{
			LoadScene(L"TitleScene");
		}

		if (name == L"HomeScene")
		{
			LoadScene(L"LoadingScene");
		}

		if (name == L"Stage1EnterScene")
		{
			LoadScene(L"HomeScene");
		}

		if (name == L"Stage1Monster1Scene")
		{
			LoadScene(L"Stage1EnterScene");
		}

		if (name == L"Stage1Monster2Scene")
		{
			LoadScene(L"Stage1Monster1Scene");
		}

		if (name == L"Stage1MiddleBossScene")
		{
			LoadScene(L"Stage1Monster2Scene");
		}

		if (name == L"Stage1BossEnterScene")
		{
			LoadScene(L"Stage1MiddleBossScene");
		}

		if (name == L"Stage1BossScene")
		{
			LoadScene(L"Stage1BossEnterScene");
		}

		if (name == L"EndingScene")
		{
			LoadScene(L"Stage1BossScene");
		}
	}
}