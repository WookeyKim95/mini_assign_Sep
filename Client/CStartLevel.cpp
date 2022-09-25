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
	// Player 생성
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(800.f, 450.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, LAYER::PLAYER);


	// 랜덤위치에 큰 Monster 5마리 생성
	for (int i = 0; i < 5; ++i)
	{
		CMonster* pMonster = new CMonster;
		pMonster->SetPos(Vec2((float)(rand() % 2500), float(rand() % 2500)));
		pMonster->SetScale(Vec2(150.f, 150.f));

		// 플레이어에게 유도탄을 쏘기 위한 타겟 장치
		pMonster->SetTarget((CPlayer*)pObj);
		AddObject(pMonster, LAYER::MONSTER);
	}
	



	// 랜덤위치에 작은 몬스터 10마리 생성
	for (int i = 0; i < 10; ++i)
	{
		CSmallMonster* pSmallMonster = new CSmallMonster;
		pSmallMonster->SetPos(Vec2((float)(rand() % 2500), float(rand() % 2500)));
		pSmallMonster->SetScale(Vec2(50.f, 50.f));

	 // 작은 몬스터는 플레이어를 쫓아오도록 설정하는 것.
		pSmallMonster->SetTarget((CPlayer*)pObj);

		// 몬스터 레이어로 설정함.
		AddObject(pSmallMonster, LAYER::MONSTER);
	}




	// Level 의 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER); // 플레이어 - 몬스터 간
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::MONSTER); // 몬스터 - 몬스터 간
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER_PROJECTILE); // 플레이어 - 몬스터 프로젝타일 간
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::MONSTER); // 플레이어 프로젝타일 - 몬스터 간
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::ITEM); // 플레이어 - 아이템 간

	// 카메라 설정
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
}
