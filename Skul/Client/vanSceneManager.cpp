#include "vanSceneManager.h"
#include "vanTitleScene.h"
#include "vanHomeScene.h"
#include "vanStageScene.h"
#include "vanEndingScene.h"
#include "CommonInclude.h"
#include "vanCamera.h"

namespace van
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Init()
	{
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<HomeScene>(L"HomeScene");
		CreateScene<StageScene>(L"StageScene");
		CreateScene<EndingScene>(L"EndingScene");

		LoadScene(L"TitleScene");
	}

	void SceneManager::Update()
	{
		// ȭ�� ��ȯ
		if (Input::GetKey(eKeyCode::Z))
		{
			LoadScene(L"TitleScene");
		}
		if (Input::GetKey(eKeyCode::X))
		{
			LoadScene(L"HomeScene");
		}
		if (Input::GetKey(eKeyCode::C))
		{
			LoadScene(L"StageScene");
		}
		if (Input::GetKey(eKeyCode::V))
		{
			LoadScene(L"EndingScene");
		}

		mActiveScene->Update();
	}

	void SceneManager::Render(HDC _hdc)
	{
		mActiveScene->Render(_hdc);
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);	
		// find(key) : �ش� Ű ���� ���� pair Ÿ�� ���� ��ȯ�Ѵ�.
		// ���� ã�� ���ϸ� map.end() �� ��ȯ�Ѵ�.

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene = iter->second;
		return iter->second;
	}
}