#pragma once
// �����Ǵ� ���̺귯��
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>	// �Լ� ������
#include <string>
#pragma comment(lib, "Msimg32.lib")
#include <filesystem>
#include <bitset>

#include <typeinfo>		// Ÿ�Ժ�

// �����Ǵ� ���
#include "framework.h"

// �������� ���
#include "vanMath.h"
#include "vanTime.h"
#include "vanInput.h"
#include "vanText.h"

// ��ũ�� ����
//#define DIAMETER	200
#define HD_X		1280
#define HD_Y		720
#define FHD_X		1920
#define FHD_Y		1080
#define Window_X	HD_X
#define Window_Y	HD_Y


namespace van::enums
{
	enum class eLayerType
	{
		BackGround,
		Floor,
		Monster,
		Player,
		Effect,
		UI,
		End,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animation,
		Animator,
		Collider,
		RigidBody,
		End,
	};
}