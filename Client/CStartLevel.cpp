#include "pch.h"
#include "CStartLevel.h"

#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CCamera.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CSmallMonster.h"

CStartLevel::CStartLevel()
{
}

CStartLevel::~CStartLevel()
{
}


void CStartLevel::init()
{
	// Player ����
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(800.f, 450.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, LAYER::PLAYER);


	// ������ġ�� ū Monster 5���� ����
	for (int i = 0; i < 5; ++i)
	{
		CMonster* pMonster = new CMonster;
		pMonster->SetPos(Vec2((float)(rand() % 2500), float(rand() % 2500)));
		pMonster->SetScale(Vec2(150.f, 150.f));

		// �÷��̾�� ����ź�� ��� ���� Ÿ�� ��ġ
		pMonster->SetTarget((CPlayer*)pObj);
		AddObject(pMonster, LAYER::MONSTER);
	}
	



	// ������ġ�� ���� ���� 10���� ����
	for (int i = 0; i < 10; ++i)
	{
		CSmallMonster* pSmallMonster = new CSmallMonster;
		pSmallMonster->SetPos(Vec2((float)(rand() % 2500), float(rand() % 2500)));
		pSmallMonster->SetScale(Vec2(50.f, 50.f));

	 // ���� ���ʹ� �÷��̾ �Ѿƿ����� �����ϴ� ��.
		pSmallMonster->SetTarget((CPlayer*)pObj);

		// ���� ���̾�� ������.
		AddObject(pSmallMonster, LAYER::MONSTER);
	}




	// Level �� �浹 ����
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER); // �÷��̾� - ���� ��
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::MONSTER); // ���� - ���� ��
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER_PROJECTILE); // �÷��̾� - ���� ������Ÿ�� ��
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::MONSTER); // �÷��̾� ������Ÿ�� - ���� ��
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::ITEM); // �÷��̾� - ������ ��

	// ī�޶� ����
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
}
