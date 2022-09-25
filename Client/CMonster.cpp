#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CResMgr.h"

#include "CPlayer.h"
#include "CHP_Potion.h"
#include "CMMissile.h"
#include "CCollider.h"

#include "CResMgr.h"
#include "CTexture.h"

CMonster::CMonster()
	: m_HP(10)
	, m_fSpeed(50.f)
	, m_CoolTime(0)
	, m_MovingTime(0)
	, m_Dir(rand() % 360)
	, m_pTarget(nullptr)
	, m_pTexture(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	m_pTexture = CResMgr::GetInst()->LoadTexture(L"MonsterImg", L"texture\\mutalisk.bmp");
}

CMonster::~CMonster()
 {
}

void CMonster::tick()
{
	// �� ���� �ϴ°�

	// 5�ʸ��� �÷��̾ �ִ� ������ �̻����� ��.
	if (m_CoolTime > 5.f)
	{
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

		CMMissile* pMMissile = new CMMissile;
		pMMissile->SetPos(GetPos());
		pMMissile->SetScale(Vec2(25.f, 25.f));
		pMMissile->SetTarget((CPlayer*)m_pTarget);
		pMMissile->SetDir((m_pTarget->GetPos() - GetPos()).Normalize()); // �÷��̾ �ִ� �������� ���� �̻����� ��� �ϱ� ���� ��ġ
		pCurLevel->AddObject(pMMissile, LAYER::MONSTER_PROJECTILE);

		m_CoolTime = 0;
	}

	// 3�ʸ��� �����ϰ� �ٸ� �������� �����̸� �� ��հ���
	if (m_MovingTime > 3.f)
	{
		SetDir();
		m_MovingTime = 0;
	}

	// ��Ÿ���� ���� �� ���� ������� ������ �����ٵ�.. ������ ���� ������ �ʰ�.
	m_CoolTime += DT;
	m_MovingTime += DT;


	// �����̴� ��.
	Vec2 vPos = GetPos();

	float fRadian = ((float)GetDir() * PI) / 180.f;

	float	delta_x = m_fSpeed * cosf(fRadian) * DT;
	float	delta_y = m_fSpeed * sinf(fRadian) * DT;

	vPos.x += delta_x;
	vPos.y += delta_x;

	// ��ġ ������ ����� �ʵ��� �ϴ� ��ġ.
	if (vPos.x < 0)
		vPos.x = 0;
	if (vPos.x > 3000)
		vPos.x = 3000;
	if (vPos.y < 0)
		vPos.y = 0;
	if (vPos.y > 3000)
		vPos.y = 3000;


	SetPos(vPos);


	

	CObj::tick();
}

void CMonster::render(HDC _dc)
{

	// ���� �簢��

	/*Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();

	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Rectangle(_dc, (int)(vPos.x - vSize.x / 2.f)
		, (int)(vPos.y - vSize.y / 2.f)
		, (int)(vPos.x + vSize.x / 2.f)
		, (int)(vPos.y + vSize.y / 2.f));

	SelectObject(_dc, hOriginBrush);*/

	// �̹��� ���

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();

	Vec2 vLeftTop = Vec2(vPos.x - m_pTexture->Width() / 2.f, vPos.y - m_pTexture->Height() / 2.f);

	// ���� ���� �̹��� ����ϱ�
	TransparentBlt(_dc, (int)vLeftTop.x, (int)vLeftTop.y
		, (int)m_pTexture->Width(), (int)m_pTexture->Height()
		, m_pTexture->GetDC()
		, 0, 0
		, (int)m_pTexture->Width(), (int)m_pTexture->Height()
		, RGB(255, 0, 255));

	// ���� HP ǥ�� ����.
	for (int i = 1; i <= m_HP; ++i)
	{
		HBRUSH hHPBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH hOrigin_HPBrush = (HBRUSH)SelectObject(_dc, hHPBrush);

		Rectangle(_dc, (int)(vPos.x - vSize.x / 3.f + 8.f * (float)i)
			, (int)(vPos.y - vSize.y / 2.f)
			, (int)((vPos.x - vSize.x / 3.f + 8.f * (float)i + 5.f))
			, (int)(vPos.y - vSize.y / 2.f + 5.f));

		SelectObject(_dc, hOrigin_HPBrush);
		DeleteObject(hHPBrush);
	}


	CObj::render(_dc);
}

LAYER CMonster::returnLayer()
{
	return LAYER::MONSTER;
}

void CMonster::BeginOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->returnLayer() == LAYER::PLAYER_PROJECTILE)
	{
		--m_HP;

		// �ǵ� : ū ���Ͱ� ������ ���� �ڸ��� HP ���� ���
		// ���� �߻�. ������ �����ڸ��� 2�� �����. (���� tick()�� �־���.)
		// ���� �ذ�: tick()�Լ����� BeginOverlap (���� ���ڸ�)���� �ű�� �ذ�Ǿ���.

		if (m_HP <= 0)
		{
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

			CHP_Potion* pHP_Potion = new CHP_Potion;
			pHP_Potion->SetScale(Vec2(40.f, 40.f));

			Instantiate(pHP_Potion, GetPos(), LAYER::ITEM);
			SetDead();
		}
	}
		

}

void CMonster::OnOverlap(CCollider* _pOther)
{
}

void CMonster::EndOverlap(CCollider* _pOther)
{

}
