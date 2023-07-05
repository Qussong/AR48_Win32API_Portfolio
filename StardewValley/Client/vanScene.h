#pragma once
#include "vanEntity.h"	// Entity Ŭ���� ���
#include "vanLayer.h"	// mLayers ������ Layer��ü�� ����

namespace van
{
	using namespace van::enums;

	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
			
	private:
		std::vector<Layer> mLayers;
		// Scene Ŭ�������� Layer ��ü�� ������ ������ �����ֱ⸸ �� ���̱⿡ ���� �ּҷ� �������� �ʴ´�.
	};
}

