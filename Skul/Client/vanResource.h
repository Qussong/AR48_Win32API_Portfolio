#pragma once
#include "vanEntity.h"

namespace van
{
	class Resource : public Entity	// ���������Լ��� ���� �߻�Ŭ������ �ȴ�.
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& _path) = 0;	// ���������Լ�

		__forceinline std::wstring& GetPath() { return mPath; }
		__forceinline void SetPath(const std::wstring& _path) { mPath = _path; }

	private:
		std::wstring mPath;	// ���ҽ��� ���
	};
}

