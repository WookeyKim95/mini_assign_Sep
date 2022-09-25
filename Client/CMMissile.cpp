#include "pch.h"
#include "CMMissile.h"

#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CCollider.h"

CMMissile::CMMissile()
	: m_fSpeed(200.f)
	, m_fDistance(0.f)
	, m_fMaxDistance(800.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(25.f, 25.f));
}

CMMissile::~CMMissile()
{
}


void CMMissile::tick()
{
	Vec2 vDir = GetDir();
	Vec2 vPos = GetPos();

	float	delta_x = m_fSpeed * vDir.x * DT;
	float	delta_y = m_fSpeed * vDir.y * DT;

	vPos.x += delta_x;
	vPos.y += delta_y;

	m_fDistance += sqrt(pow(delta_x, 2) + pow(delta_y, 2));

	SetPos(vPos);


	if (m_fDistance > m_fMaxDistance)
		SetDead();

	CObj::tick();
}

void CMMissile::render(HDC _dc)
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

void CMMissile::BeginOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->returnLayer() == LAYER::PLAYER)
		SetDead();
}

LAYER CMMissile::returnLayer()
{
	return LAYER::MONSTER_PROJECTILE;
}
