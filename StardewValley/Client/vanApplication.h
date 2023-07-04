#pragma once
#include "CommonInclude.h"

#define OBJECT_CNT 5		// Objects cnt control
namespace van
{
	//using namespace math;	// == van::math
	class Application
	{
	public:
		Application();
		~Application();

		void Init(HWND hwnd);
		void Proc();							// ��ü���� �۾� (Update, Render)
		void Update();							// Ű �Է��� �޾� ������ ����
		void Render();							// ȭ�鿡 �׷��ش�
		void ObjectGenerator(					// ��ü�� �������ִ� �Լ�
							float speed,		// ��ü�� �ӵ�
							int diameter,		// ��ü�� ����
							float timeGap);		// ��ü ���� �ֱ�

	private:
		HWND mHwnd;
		HDC mHdc;
		math::Vector2 playerPos;				// vanMath.h

		RECT clientArea = {};
		int curObjectCnt = 0;					// ���� ������ ��ü ����
		std::vector<Object> objectContainer;	// ��ü�� ��Ƶδ� �ٱ���
	};
}

