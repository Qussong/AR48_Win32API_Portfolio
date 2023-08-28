#pragma once
// �����Ǵ� ���̺귯��
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>	// �Լ� ������
#include <string>
#include <filesystem>
#include <bitset>
#include <typeinfo>		// Ÿ�Ժ�
#include <cstdlib>		//rand(), srand()
#include <ctime>		//time()
#include <assert.h>
#pragma comment(lib, "Msimg32.lib")

// �����Ǵ� ���
#include "framework.h"

#include <mmsystem.h>	// sound ����
#include <dsound.h>		// sound ����
#include <dinput.h>		// sound ����
#pragma comment(lib, "winmm.lib")	// sound ����
#pragma comment(lib, "dsound.lib")	// sound ����

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
		Boss_Mage,
		Boss_Mage_Effect,
		Boss_Mage_Skill_FireBall,
		Boss_Mage_Skill_RangeFire,
		Boss_Mage_Skill_PhoenixLanding,
		Yggdrasill,
		Yggdrasill_Body,
		Yggdrasill_Head,
		Yggdrasill_Chin,
		Yggdrasill_Hand,
		Yggdrasill_Effect,
		Yggdrasill_Skill_EnergyBomb,
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
		Cat_Seol,
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