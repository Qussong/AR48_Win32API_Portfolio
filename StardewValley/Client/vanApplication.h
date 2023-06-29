#pragma once
#include "CommonInclude.h"

namespace van
{
	using namespace math;	// == van::math
	class Application
	{
	public:
		Application();
		~Application();

		void Init(HWND hwnd);
		void Proc();		// ��ü���� �۾� (Update, Render)
		void Update();		// Ű �Է��� �޾� ������ ����
		void Render();		// ȭ�鿡 �׷��ش�

	private:
		HWND mHwnd;
		HDC mHdc;
		Vector2 playerPos;	// vanMath.h
	};
}

