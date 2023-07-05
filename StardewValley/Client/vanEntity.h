#pragma once
#include "CommonInclude.h"

namespace van
{
	class Entity							// ����ؼ� ������� �� 
											// -> Question) ������ ����ҰŸ� �߻� Ŭ������ ������ָ� �ȵǳ�?
	{
	public:
		Entity();
		virtual ~Entity();					// �Ҹ��ڿ� �׻� virtual Ű���带 �ٿ��ָ� �Ŀ� ��ӵǾ ���� �߻��� ��������.

		void SetName(std::wstring& name);	// setter
		std::wstring& GetName();			// getter

	private:
		std::wstring mName;					// �̸� �����ϴ� �뵵 
	};
}