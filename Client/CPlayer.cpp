#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"

#include "CMissile.h"
#include "CGMissile.h"
#include "CHP_Potion.h"

#include "CCollider.h"
#include "CResMgr.h"

CPlayer::CPlayer()
	: m_fSpeed(200.f),
	CurDir(PLAYER_DIR::PD_END),
	m_HP(5),
	m_MaxHP(5),
	m_boomCount(2),
	m_pTexture(nullptr)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 20.f));
	GetCollider()->SetScale(Vec2(30.f, 50.f));

	// 이미지 로딩 (상하좌우)
	m_pTexture = CResMgr::GetInst()->LoadTexture(L"PlayerImg_U", L"texture\\Fighter.bmp");
	m_pTexture_L = CResMgr::GetInst()->LoadTexture(L"PlayerImg_L", L"texture\\Fighter_L.bmp");
	m_pTexture_D = CResMgr::GetInst()->LoadTexture(L"PlayerImg_D", L"texture\\Fighter_D.bmp");
	m_pTexture_R = CResMgr::GetInst()->LoadTexture(L"PlayerImg_R", L"texture\\Fighter_R.bmp");

}

CPlayer::~CPlayer()
{

}

void CPlayer::tick()
{
	Vec2 vPos = GetPos();

	if (IsPressed(KEY::LEFT))
	{
		// 바라보는 방향 왼쪽으로 저장 및 이동
		GetCollider()->SetOffsetPos(Vec2(20.f, 0.f));
		GetCollider()->SetScale(Vec2(50.f, 30.f));
		CurDir = PLAYER_DIR::PD_LEFT;
		vPos.x -= m_fSpeed * DT;
	}

	if (IsPressed(KEY::RIGHT))
	{
		// 바라보는 방향 오른쪽으로 저장 및 이동
		GetCollider()->SetOffsetPos(Vec2(-20.f, 0.f));
		GetCollider()->SetScale(Vec2(50.f, 30.f));
		CurDir = PLAYER_DIR::PD_RIGHT;
		vPos.x += m_fSpeed * DT;
	}

	if (IsPressed(KEY::UP))
	{
		// 바라보는 방향 위로 저장 및 이동
		GetCollider()->SetOffsetPos(Vec2(0.f, 20.f));
		GetCollider()->SetScale(Vec2(30.f, 50.f));
		CurDir = PLAYER_DIR::PD_UP;
		vPos.y -= m_fSpeed * DT;
	}

	if (IsPressed(KEY::DOWN))
	{
		// 바라보는 방향 아래로 저장 및 이동
		GetCollider()->SetOffsetPos(Vec2(0.f, -20.f));
		GetCollider()->SetScale(Vec2(30.f, 50.f));
		CurDir = PLAYER_DIR::PD_DOWN;
		vPos.y += m_fSpeed * DT;
	}

	if (IsTap(KEY::SPACE))
	{
		// 현재 레벨에 생성한 미사일을 추가
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

		// 미사일 생성

		CMissile* pMissile = new CMissile;
		pMissile->SetScale(Vec2(20.f, 20.f));
		pMissile->SetSpeed(400.f);

		// 왼쪽으로 발사
		if (CurDir == PLAYER_DIR::PD_LEFT)
			pMissile->SetDir(180.f);

		// 위로 발사
		if (CurDir == PLAYER_DIR::PD_UP)
			pMissile->SetDir(90.f);

		// 오른쪽으로 발사
		if (CurDir == PLAYER_DIR::PD_RIGHT)
			pMissile->SetDir(0.f);

		// 아래로 발사
		if (CurDir == PLAYER_DIR::PD_DOWN)
			pMissile->SetDir(-90.f);
				
		Instantiate(pMissile, GetPos(), LAYER::PLAYER_PROJECTILE);
		// pCurLevel->AddObject(pMissile, LAYER::PLAYER_PROJECTILE); 이젠 주석처리 안하면 터지넹.. 왤까
	}

	// Q 누르면 8방향 발사되게 해보자!
	if (IsTap(KEY::Q) && m_boomCount > 0)
	{
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

		// 미사일 생성
		for (int i = 0; i < 8; ++i)
		{
			CMissile* pMissile = new CMissile;
			pMissile->SetScale(Vec2(20.f, 20.f));
			pMissile->SetSpeed(400.f);

			pMissile->SetDir(45.f * (float)i);

			Instantiate(pMissile, GetPos(), LAYER::PLAYER_PROJECTILE);
			// pCurLevel->AddObject(pMissile, LAYER::PLAYER_PROJECTILE);
		}

		--m_boomCount;
	}
	
	// W 누르면 마우스 커서쪽으로 유도탄! (움직이면 더이상 발사되지 않는 버그 발생)
	//if (IsTap(KEY::W))
	//{
	//	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	//	// 미사일 생성

	//	CGMissile* pGMissile = new CGMissile;
	//	pGMissile->SetPos(GetPos());
	//	pGMissile->SetScale(Vec2(20.f, 20.f));

	//	Instantiate(pGMissile, GetPos(), LAYER::PLAYER_PROJECTILE);
	//	// pCurLevel->AddObject(pGMissile, LAYER::PLAYER_PROJECTILE);
	//	
	//}


	
	// R 누르면 포션 생성
	/*if (IsTap(KEY::R))
	{
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

		CHP_Potion* pHP_Potion = new CHP_Potion;
		pHP_Potion->SetPos(Vec2((float)(rand() % 1400), (float)(rand() % 50)));
		pHP_Potion->SetScale(Vec2(40.f, 40.f));

		pCurLevel->AddObject(pHP_Potion, LAYER::ITEM);
	}*/
	
	// 일정 위치 밖으로 벗어나지 않도록 하는 장치.
	if (vPos.x < 0)
		vPos.x = 0;
	if (vPos.x > 3000)
		vPos.x = 3000;
	if (vPos.y < 0)
		vPos.y = 0;
	if (vPos.y > 3000)
		vPos.y = 3000;


	SetPos(vPos);

	if (m_HP == 0)
		SetDead();

	CObj::tick();
}

void CPlayer::render(HDC _dc)
{

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());;
	Vec2 vSize = GetScale();


	//카메라 액션
	// 남은과제 : 충돌체도 이미지 따라가도록 해야..
	/*if (GetPos().x < 800)
		vPos.x -= 800 - GetPos().x;
		
	if (GetPos().x > 2200)
		vPos.x += GetPos().x - 2200;

	if (GetPos().y < 450)
		vPos.y -= 450 - GetPos().y;

	if (GetPos().y > 2200)
		vPos.y += GetPos().y - 2200;*/

	// 플레이어를 그리는 부분
	

	if (CurDir == PLAYER_DIR::PD_UP || CurDir == PLAYER_DIR::PD_END)
	{
		ImagePrint(m_pTexture, _dc, vPos);
	}

	if (CurDir == PLAYER_DIR::PD_DOWN)
	{
		ImagePrint(m_pTexture_D, _dc, vPos);
	}

	if (CurDir == PLAYER_DIR::PD_LEFT)
	{
		ImagePrint(m_pTexture_L, _dc, vPos);
	}

	if (CurDir == PLAYER_DIR::PD_RIGHT)
	{
		ImagePrint(m_pTexture_R, _dc, vPos);
	}
	


	// 왼쪽 하단에 HP 표시하기

	HBRUSH hHPBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH hOrigin_HPBrush = (HBRUSH)SelectObject(_dc, hHPBrush);

	for (int i = 1; i <= m_HP; ++i)
	{
		Vec2 vPos_HP = {50.f * (float)i, 750.f};
		Vec2 vSize_HP = { 40.f, 40.f };

		Rectangle(_dc, (int)(vPos_HP.x - vSize_HP.x / 2.f)
			, (int)(vPos_HP.y - vSize_HP.y / 2.f)
			, (int)(vPos_HP.x + vSize_HP.x / 2.f)
			, (int)(vPos_HP.y + vSize_HP.y / 2.f));

	}
	SelectObject(_dc, hOrigin_HPBrush);
	DeleteObject(hHPBrush);

	// 오른쪽 하단에 BOOM 개수 표시하기

	HBRUSH hBOOMBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255));
	HBRUSH hOrigin_BOOMBrush = (HBRUSH)SelectObject(_dc, hBOOMBrush);

	for (int i = 1; i <= m_boomCount; ++i)
	{
		Vec2 vPos_BOOM = { 1500 - 50.f * (float)i, 750.f };
		Vec2 vSize_BOOM = { 40.f, 40.f };

		Rectangle(_dc, (int)(vPos_BOOM.x - vSize_BOOM.x / 2.f)
			, (int)(vPos_BOOM.y - vSize_BOOM.y / 2.f)
			, (int)(vPos_BOOM.x + vSize_BOOM.x / 2.f)
			, (int)(vPos_BOOM.y + vSize_BOOM.y / 2.f));

	}
	SelectObject(_dc, hOrigin_BOOMBrush);
	DeleteObject(hBOOMBrush);

	CObj::render(_dc);
}

void CPlayer::BeginOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->returnLayer() == LAYER::ITEM && m_HP < m_MaxHP)
	{
		// HP를 1 증가시키고 난 뒤에 포션을 SetDead 처리
		++m_HP;
		_pOther->GetOwner()->SetDead();
	}

	if (_pOther->GetOwner()->returnLayer() == LAYER::MONSTER || _pOther->GetOwner()->returnLayer() == LAYER::MONSTER_PROJECTILE)
		--m_HP; // 몬스터나 몬스터의 미사일이랑 충돌시에는 정상적으로 1회 충돌 판정.
}

void CPlayer::OnOverlap(CCollider* _pOther)
{

}

void CPlayer::EndOverlap(CCollider* _pOther)
{
	
}

LAYER CPlayer::returnLayer()
{
	return LAYER::PLAYER;
}

void CPlayer::ImagePrint(CTexture* pTexture, HDC _dc, Vec2 Pos)
{
	Vec2 vLeftTop = Vec2(Pos.x - pTexture->Width() / 2.f, Pos.y - pTexture->Height() / 2.f);

	TransparentBlt(_dc, (int)vLeftTop.x, (int)vLeftTop.y
		, (int)pTexture->Width(), (int)pTexture->Height()
		, pTexture->GetDC()
		, 0, 0
		, (int)pTexture->Width(), (int)pTexture->Height()
		, RGB(255, 0, 255));
}
