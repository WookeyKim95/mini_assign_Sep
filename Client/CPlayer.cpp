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

	// �̹��� �ε� (�����¿�)
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
		// �ٶ󺸴� ���� �������� ���� �� �̵�
		GetCollider()->SetOffsetPos(Vec2(20.f, 0.f));
		GetCollider()->SetScale(Vec2(50.f, 30.f));
		CurDir = PLAYER_DIR::PD_LEFT;
		vPos.x -= m_fSpeed * DT;
	}

	if (IsPressed(KEY::RIGHT))
	{
		// �ٶ󺸴� ���� ���������� ���� �� �̵�
		GetCollider()->SetOffsetPos(Vec2(-20.f, 0.f));
		GetCollider()->SetScale(Vec2(50.f, 30.f));
		CurDir = PLAYER_DIR::PD_RIGHT;
		vPos.x += m_fSpeed * DT;
	}

	if (IsPressed(KEY::UP))
	{
		// �ٶ󺸴� ���� ���� ���� �� �̵�
		GetCollider()->SetOffsetPos(Vec2(0.f, 20.f));
		GetCollider()->SetScale(Vec2(30.f, 50.f));
		CurDir = PLAYER_DIR::PD_UP;
		vPos.y -= m_fSpeed * DT;
	}

	if (IsPressed(KEY::DOWN))
	{
		// �ٶ󺸴� ���� �Ʒ��� ���� �� �̵�
		GetCollider()->SetOffsetPos(Vec2(0.f, -20.f));
		GetCollider()->SetScale(Vec2(30.f, 50.f));
		CurDir = PLAYER_DIR::PD_DOWN;
		vPos.y += m_fSpeed * DT;
	}

	if (IsTap(KEY::SPACE))
	{
		// ���� ������ ������ �̻����� �߰�
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

		// �̻��� ����

		CMissile* pMissile = new CMissile;
		pMissile->SetScale(Vec2(20.f, 20.f));
		pMissile->SetSpeed(400.f);

		// �������� �߻�
		if (CurDir == PLAYER_DIR::PD_LEFT)
			pMissile->SetDir(180.f);

		// ���� �߻�
		if (CurDir == PLAYER_DIR::PD_UP)
			pMissile->SetDir(90.f);

		// ���������� �߻�
		if (CurDir == PLAYER_DIR::PD_RIGHT)
			pMissile->SetDir(0.f);

		// �Ʒ��� �߻�
		if (CurDir == PLAYER_DIR::PD_DOWN)
			pMissile->SetDir(-90.f);
				
		Instantiate(pMissile, GetPos(), LAYER::PLAYER_PROJECTILE);
		// pCurLevel->AddObject(pMissile, LAYER::PLAYER_PROJECTILE); ���� �ּ�ó�� ���ϸ� ������.. �ͱ�
	}

	// Q ������ 8���� �߻�ǰ� �غ���!
	if (IsTap(KEY::Q) && m_boomCount > 0)
	{
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

		// �̻��� ����
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
	
	// W ������ ���콺 Ŀ�������� ����ź! (�����̸� ���̻� �߻���� �ʴ� ���� �߻�)
	//if (IsTap(KEY::W))
	//{
	//	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	//	// �̻��� ����

	//	CGMissile* pGMissile = new CGMissile;
	//	pGMissile->SetPos(GetPos());
	//	pGMissile->SetScale(Vec2(20.f, 20.f));

	//	Instantiate(pGMissile, GetPos(), LAYER::PLAYER_PROJECTILE);
	//	// pCurLevel->AddObject(pGMissile, LAYER::PLAYER_PROJECTILE);
	//	
	//}


	
	// R ������ ���� ����
	/*if (IsTap(KEY::R))
	{
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

		CHP_Potion* pHP_Potion = new CHP_Potion;
		pHP_Potion->SetPos(Vec2((float)(rand() % 1400), (float)(rand() % 50)));
		pHP_Potion->SetScale(Vec2(40.f, 40.f));

		pCurLevel->AddObject(pHP_Potion, LAYER::ITEM);
	}*/
	
	// ���� ��ġ ������ ����� �ʵ��� �ϴ� ��ġ.
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


	//ī�޶� �׼�
	// �������� : �浹ü�� �̹��� ���󰡵��� �ؾ�..
	/*if (GetPos().x < 800)
		vPos.x -= 800 - GetPos().x;
		
	if (GetPos().x > 2200)
		vPos.x += GetPos().x - 2200;

	if (GetPos().y < 450)
		vPos.y -= 450 - GetPos().y;

	if (GetPos().y > 2200)
		vPos.y += GetPos().y - 2200;*/

	// �÷��̾ �׸��� �κ�
	

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
	


	// ���� �ϴܿ� HP ǥ���ϱ�

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

	// ������ �ϴܿ� BOOM ���� ǥ���ϱ�

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
		// HP�� 1 ������Ű�� �� �ڿ� ������ SetDead ó��
		++m_HP;
		_pOther->GetOwner()->SetDead();
	}

	if (_pOther->GetOwner()->returnLayer() == LAYER::MONSTER || _pOther->GetOwner()->returnLayer() == LAYER::MONSTER_PROJECTILE)
		--m_HP; // ���ͳ� ������ �̻����̶� �浹�ÿ��� ���������� 1ȸ �浹 ����.
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
