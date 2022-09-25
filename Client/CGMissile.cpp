#include "pch.h"
#include "CGMissile.h"
#include "CTimeMgr.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CEngine.h"
#include "CCollider.h"

CGMissile::CGMissile() :
	m_fSpeed(001.f),
	m_fDistance(0.f),
	m_fMaxDistance(500.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 20.f));
}

CGMissile::~CGMissile()
{
}

void CGMissile::tick()
{

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	// 미사일 포지션 변경하는 곳
	
	// 마우스 커서를 따라감. 현재 정상 작동하지 않음. 해결 방안 연구 필요.
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(CEngine::GetInst()->GetMainWnd(), &pt);

	// 속력을 일정하게 바꿔주는 부분. (정규화)
	m_fSpeed = 500.f / sqrt(pow(pt.x - vPos.x, 2) + pow(pt.y - vPos.y, 2));

	// 유도탄 구현을 위한 부분


	float	delta_x = m_fSpeed * (pt.x - vPos.x) * DT;
	float	delta_y = m_fSpeed * (pt.y - vPos.y) * DT;

	vPos.x += delta_x;
	vPos.y += delta_y;

	// 거리 기록하는 변수에 이동거리 누적
	m_fDistance += sqrt(pow(delta_x, 2) + pow(delta_y, 2));

	SetPos(vPos);
	
	// 일정사거리 이상 진행하면 삭제
	if (m_fDistance > m_fMaxDistance)
		SetDead();

	CObj::tick();
}

void CGMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetScale();

	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);
	
	Ellipse(_dc, (int)(vPos.x - vSize.x / 2.f)
		, (int)(vPos.y - vSize.y / 2.f)
		, (int)(vPos.x + vSize.x / 2.f)
		, (int)(vPos.y + vSize.y / 2.f));

	SelectObject(_dc, hOriginBrush);

	CObj::render(_dc);

}

void CGMissile::BeginOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->returnLayer() == LAYER::MONSTER)
		SetDead();
}

LAYER CGMissile::returnLayer()
{
	return LAYER::PLAYER_PROJECTILE;
}
