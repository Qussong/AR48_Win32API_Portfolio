#pragma once
#include "CommonInclude.h"

namespace van
{
	class Entity							
	{
	public:
		Entity();
		virtual ~Entity();	// �Ҹ��ڿ� �׻� virtual Ű���带 �ٿ��ָ� �Ŀ� ��ӵǾ ���� �߻��� ��������.

		__forceinline void SetName(const std::wstring& name) 
												{ mName = name; }	// setter
		__forceinline std::wstring& GetName() { return mName; }		// getter

	private:
		std::wstring mName;	// �̸� �����ϴ� �뵵 
	};
}