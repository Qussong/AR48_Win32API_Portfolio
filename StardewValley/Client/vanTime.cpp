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
		// �����Ӵ� �������� �˾ƾ� �Ѵ�
		// ���� �������� ���� �����ӿ��� ������ �������� �Ǳ⿡ 'Prev = Cur' �� ���ش�
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		const int SIZE = 50;
		static float timeCheck = 0.0f;						// ��ŸŸ�� �״� ��

		timeCheck += mDeltaTime;							// �� �����Ӹ��� ��ŸŸ���� �����ȴ�.
		if (timeCheck >= 1.0f)								// �� ��Ÿ Ÿ���� 1�� �̻��� �Ǹ� �Ʒ� ���� ����
		{
			wchar_t szFloat[SIZE] = {};						// ???
			float FPS = 1.0f / mDeltaTime;					// ���� ��Ÿ Ÿ���� 1�� �̻��� �Ǵ� ������ FPS ���

			// Question) ���� ��Ĵ�� FPS�� ����ϸ� �ᱹ ��� FPS�� ����ϴ°� �ƴѰ���?
			swprintf_s(szFloat, SIZE, L"FPS : %f", FPS);	// ???
			int strLen = wcsnlen_s(szFloat, SIZE);			// ???, szFloat �� ���ڿ� ���̸� �޾ƿ��� �� ����...

			TextOut(hdc, 10, 10, szFloat, strLen);			// ȭ�鿡 �� ���?

			timeCheck = 0.0f;								// �ٽ� 0���� 1�ʰ� �ɶ����� 
															// ��ŸŸ�ӵ��� �޾ƾ� �ϱ⿡ 0���� �ʱ�ȭ
		}
	}
}
