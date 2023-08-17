#pragma once
#include "vanScene.h"

namespace van
{
	class HomeScene : public Scene
	{
	public:
		HomeScene();
		virtual ~HomeScene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void SceneIN() override;
		virtual void SceneOut() override;
		virtual void CameraMove() override;

		void NextScene();	// ���Ͻ� ������ġ�� �����ϸ� ���� Scene���� ����
		
	private:

	};
}

