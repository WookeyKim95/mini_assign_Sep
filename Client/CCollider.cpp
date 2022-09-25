#include "pch.h"
#include "CCollider.h"

#include "CEngine.h"
#include "CObj.h"

CCollider::CCollider(CObj* _pOwner)
	: CComponent(_pOwner) // CObj 대신에 CComponent 생성자에서 초기화를 진행함.
	, m_iOverlapCount(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::tick()
{
	// 충돌체의 최종 위치값을 결정한다.
	m_vFinalPos = GetOwner()->GetPos() + m_vOffsetPos;

	// 중첩수가 음수인 겨웅는 말이 안되는 상황.
	assert(!(m_iOverlapCount < 0));
}

void CCollider::render(HDC _dc)
{
	// 충돌체를 그린다.
	// 필요한 펜과 브러시를 만든다(또는 가져온다)	
	HPEN hPen = nullptr;

	if (m_iOverlapCount > 0)
	{
		hPen = CEngine::GetInst()->GetPen(PEN_TYPE::RED);
	}
	else
	{
		hPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	}

	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	// DC 의 기존 펜과 브러시를 새로 가져온 것들로 대체한다
	HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

	// 사각형 그리기
	Rectangle(_dc, (int)(vPos.x - m_vScale.x / 2.f)
		, (int)(vPos.y - m_vScale.y / 2.f)
		, (int)(vPos.x + m_vScale.x / 2.f)
		, (int)(vPos.y + m_vScale.y / 2.f));

	// DC 의 GDI 오브젝트들을 기존의 펜과 브러시로 되돌린다.
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);



}

void CCollider::BeginOverlap(CCollider* _pOther)
{
	++m_iOverlapCount;

	GetOwner()->BeginOverlap(_pOther);
}

void CCollider::EndOverlap(CCollider* _pOther)
{
	--m_iOverlapCount;
}

void CCollider::OnOverlap(CCollider* _pOther)
{
}

