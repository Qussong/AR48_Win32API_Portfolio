#include "vanTime.h"

namespace van
{
	// LARGE_INTEGER ����ü �̱⿡ {} �� �ʱ�ȭ
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	float Time::mDeltaTime = 0.0f;

	void Time::Init()
	{
		// CPU�� ���� ������ ��������
		QueryPerformanceFrequency(&mCpuFrequency);
		// ���α׷��� ���۵������� ������ �� �����´�
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Update()
	{
		// ���� �������� �����´�.
		QueryPerformanceCounter(&mCurFrequency);
		// ������ ����
		// ��, �� �������� ����Ǵ� ���� CPU�� ������ Ƚ��
		float diffFrequency
			= static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
		mDeltaTime = diffFrequency / static_cast<float>(mCpuFrequency.QuadPart);
		// ��ŸŸ�� = �� �����Ӵ� ������ / 1�� ��� ������
		// �����Ӵ� �������� �˾ƾ� �Ѵ�
		// ���� �������� ���� �����ӿ��� ������ �������� �Ǳ⿡ 'Prev = Cur' �� ���ش�
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		const int SIZE = 50;
		//static float timeCheck = 0.0f;
		//timeCheck += mDeltaTime;					
		//if (timeCheck >= 1.0f)								
		//{
			wchar_t szFloat[SIZE] = {};
			float FPS = 1.0f / mDeltaTime;

			swprintf_s(szFloat, SIZE, L"FPS : %f", FPS);	// Buffer(szFloat)�� ���ڿ� �־��ֱ�
			int strLen = (int)wcsnlen_s(szFloat, SIZE);		// ���ڿ� ����
			TextOut(hdc, 10, 10, szFloat, strLen);
			//timeCheck = 0.0f;								
		//}
	}
}
