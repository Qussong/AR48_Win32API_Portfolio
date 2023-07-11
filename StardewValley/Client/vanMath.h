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
		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Up;

		Vector2()
			: x(0.0f)
			, y(0.0f)
		{
		}

		Vector2(float _x, float _y)
			: x(_x)
			, y(_y)
		{
		}

		float x;
		float y;
	};
}