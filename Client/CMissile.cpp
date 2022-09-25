#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CCollider.h"

CMissile::CMissile()
	: m_fSpeed(200.f)
	, m_fDegree(80.f)
	, m_fDistance(0.f)
	, m_fMaxDistance(500.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 20.f));
}

CMissile::~CMissile()
{
}

void CMissile::tick()
{
	Vec2 vPos = GetPos();	

	// 60분법 -> 라디안
	float fRadian = (m_fDegree * PI) / 180.f;

	// 미사일 포지션 변경하는 곳

	float	delta_x = m_fSpeed * cosf(fRadian) * DT;
	float	delta_y = m_fSpeed * sinf(fRadian) * DT;

	vPos.x += delta_x;
	vPos.y -= delta_y;

	m_fDistance += sqrt(pow(delta_x, 2) + pow(delta_y, 2));

	SetPos(vPos);

	if (m_fDistance > m_fMaxDistance)
		SetDead();

	CObj::tick();
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
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

void CMissile::BeginOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->returnLayer() == LAYER::MONSTER)
		SetDead();
}

LAYER CMissile::returnLayer()
{
	return LAYER::PLAYER_PROJECTILE;
}
