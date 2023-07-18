#pragma once
#include "vanResource.h"

namespace van
{
	class ResourceManager
	{
	public:
		// ���ҽ��� �̹� �ε� �Ǿ� �ִ��� Ȯ��
		template <typename T>
		static T* Find(const std::wstring& _name)	
		{
			auto iter = mResources.find(_name);		// map.find()�� �ش� ��ü�� ã�� ���ϸ� map.end()�� ��ȯ�Ѵ�.
			if (iter == mResources.end())			// �ش� �̸��� ���� ���ҽ��� ������ nullptr return 
				return nullptr;

			return dynamic_cast<T*>(iter->second);	// �ش� �̸��� ���� ���ҽ��� ������ �ش� ���ҽ��� �ּҰ� ��ȯ
		}

		// ���ҽ��� �ҷ��� mResources�� �����Ѵ�.
		template <typename T>
		static T* Load(const std::wstring& _name
						, const std::wstring& _path)	
		{
			T* resource = ResourceManager::Find<T>(_name);	// �ش� ���ҽ��� mResources���� Ž��

			if (resource != nullptr)
				return resource;
			
			resource = new T();
			if (FAILED(resource->Load(_path)))				// �ش� ���� 0���� ������ false
			{
				MessageBox(nullptr, L"Resource Load Failed!", L"Error", MB_OK);
				delete resource;
				return nullptr;
			}

			resource->SetName(_name);
			resource->SetPath(_path);
			mResources.insert(std::make_pair(_name, resource));

			return resource;
		}

		// Ư�� Resource�� mResources�� �����Ѵ�.
		template <typename T>
		static void Insert(const::std::wstring& _name, T* _resource)
		{
			_resource->SetName(_name);
			mResources.insert(std::make_pair(_name, _resource));
		}

	private:
		static std::map<std::wstring, Resource*> mResources;
	};
}

