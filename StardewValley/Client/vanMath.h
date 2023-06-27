#pragma once

/*
	[ �Ǽ��� ]
	�Ǽ� Ÿ�Կ� double �� float �� �ִ�.
		- double : 8 Byte
		- float : 4 Byte
	float Ÿ������ �Ǽ� ���� ����ϰ��� �Ѵٸ� �� �ڿ� 'f'�� �ٿ���� �Ѵ�.
*/

namespace van::math
{
	struct Vector2
	{
	public:
		Vector2()
			: x(0.0f)
			, y(0.0f)
		{
		}

	public:
		float x;
		float y;
	};
}