#include "vanYggdrasill.h"
#include "vanCollider.h"
#include "vanPlayerAttack.h"
#include "vanPlayer.h"
#include "vanObject.h"

namespace van
{
	Yggdrasill::Yggdrasill()
	{
		// nothing
	}

	Yggdrasill::~Yggdrasill()
	{
		// nothing
	}

	void Yggdrasill::Init()
	{
		Boss::Init();		// �ƹ��͵� ����

		MakeAnimation();	// �ƹ��͵� ����

		SetBossState(BossState::Gen);
		SetBossDirection(BossDirection::Center);

		mBody = Object::Instantiate<YggdrasillBody>(enums::eLayerType::Yggdrasill_Body);
		mHead = Object::Instantiate<YggdrasillHead>(enums::eLayerType::Yggdrasill_Head);
		mChin = Object::Instantiate<YggdrasillChin>(enums::eLayerType::Yggdrasill_Chin);
		mHandLeft = Object::Instantiate<YggdrasillHand>(enums::eLayerType::Yggdrasill_Hand);
		mHandRight = Object::Instantiate<YggdrasillHand>(enums::eLayerType::Yggdrasill_Hand);
		
		mHandLeft->SetHandPos(YggdrasillHand::HandPos::Left);
		mHandRight->SetHandPos(YggdrasillHand::HandPos::Right);

		mBody->SetPos(math::Vector2(Window_X / 2, Window_Y / 2));
		mHead->SetPos(math::Vector2(Window_X / 2 - 10.0f, Window_Y / 2 - 60.0f));
		mChin->SetPos(math::Vector2(Window_X / 2 + 20.0f, Window_Y / 2 + 100.0f));
		mHandLeft->SetPos(math::Vector2(Window_X / 2 - 400.0f + 20.0f, Window_Y / 2 + 100.0f));
		mHandRight->SetPos(math::Vector2(Window_X / 2 + 400.0f + 20.0f, Window_Y / 2 + 100.0f));
	}

	void Yggdrasill::Update()
	{
		Boss::Update();	// �ش� ��ü�� ������ �ִ� Component �Ӽ����� ���� ������Ʈ���ش�.
	}

	void Yggdrasill::Render(HDC _hdc)
	{
		Boss::Render(_hdc);	// GameObject�� ������ �ִ� Component Ŭ������ ����ϰ� �ִ� Ŭ�������� Render()ȣ��
	}

	void Yggdrasill::MakeAnimation()
	{
		// nothing
	}

	void Yggdrasill::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void Yggdrasill::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Yggdrasill::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void Yggdrasill::Gen()
	{

	}

	void Yggdrasill::Idle()
	{

	}

	void Yggdrasill::AttackReady()
	{

	}

	void Yggdrasill::Attack()
	{

	}

	void Yggdrasill::AttackEnd()
	{
	}

	void Yggdrasill::Hit()
	{

	}

	void Yggdrasill::Dead()
	{

	}

	void Yggdrasill::AttackMelee()
	{

	}

	void Yggdrasill::AttackSmash()
	{

	}

	void Yggdrasill::AttackRange()
	{

	}

}