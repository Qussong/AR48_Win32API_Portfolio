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
#include <cstdlib>		//rand(), srand()
#include <ctime>		//time()

// �����Ǵ� ���
#include "framework.h"

// �������� ���
#include "vanMath.h"
#include "vanTime.h"
#include "vanInput.h"
#include "vanText.h"

// ��ũ�� ����
#define HD_X			1280
#define HD_Y			720
#define FHD_X			1920
#define FHD_Y			1080
#define Window_X		HD_X
#define Window_Y		HD_Y
#define FLOOR_HEIGHT	5.0f
#define WALL_WIDTH		2.0f
#define WALL_HEIGHT		10.0f

namespace van::enums
{
	enum class eLayerType
	{
		BackGround,
		Floor,
		Wall,
		Boos_Mage,
		Yggdrasill,
		Yggdrasill_Body,
		Yggdrasill_Head,
		Yggdrasill_Chin,
		Yggdrasill_Hand,
		Door,
		NPC,
		Range_Monster_Trace,
		Range_Monster_Attack,
		Trap,
		Monster,
		FrontFloor,
		Range_Attack,
		Skill,
		Drop,
		Player,
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