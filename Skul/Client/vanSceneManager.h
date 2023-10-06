#pragma once
#include "vanScene.h"

namespace van
{
	class SceneManager
	{
	public:
		static void Init();
		static void Update();
		static void Render(HDC _hdc);
		static void Release();

		template <typename T>
		__forceinline static T* CreateScene(const std::wstring& name)
		{
			T* scene = new T();
			scene->SetName(name);
			mScenes.insert(std::make_pair(name, scene));	// mScenes �� ������ scene �ֱ�
			mActiveScene = scene;							// mActiveScene ����
			scene->Init();									// GameObject ��ü ����

			return scene;
		}
		__forceinline static Scene* LoadScene(const std::wstring& name);
		__forceinline static Scene* GetActiveScene() { return mActiveScene; }

		static void Next(const std::wstring& name);
		static void Previous(const std::wstring& name);
		__forceinline static bool GetColliderVisibleFlag() { return mbColliderVisible; }

	private:
		/*
			Ʈ�� �ڷᱸ�� ����� ����
			-> ���� : �־��� ��츦 �������� �� ���ϴ� �� ã�� �ӵ��� ������.

			[ map ]
			- key,value ������ �̷�����ִ�.
			- key�� ���ϴ� ���� �˻��ϴ� �뵵
			- value�� ����� ��(=ã�� ��)
		 */
		static std::map<std::wstring, Scene*> mScenes;
		static Scene* mActiveScene;
		static bool mbColliderVisible;
	};
}

