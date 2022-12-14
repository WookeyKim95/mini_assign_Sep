#include "pch.h"
#include "CObj.h"

#include "CEventMgr.h"

#include "CCollider.h"
#include "CAnimator.h"


CObj::CObj()
	: m_vPos{}
	, m_vScale{}	
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bDead(false)
{
}

CObj::~CObj()
{
	DEL(m_pCollider);
	DEL(m_pAnimator);
}

void CObj::renderMap(HDC _dc)
{
	Vec2 realPos = GetPos();

	Vec2 mapPos = { realPos.x / 20.f + 1350, realPos.y / 20.f + 50 };

	if (returnLayer() == LAYER::PLAYER)
	{
		HBRUSH hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
		HBRUSH hOrigin_Brush = (HBRUSH)SelectObject(_dc, hBrush);

		Rectangle(_dc, (int)( mapPos.x - 5.f)
		, (int)(mapPos.y - 5.f)
		, (int)(mapPos.x + 5.f)
		, (int)(mapPos.y + 5.f));

		SelectObject(_dc, hOrigin_Brush);
		DeleteObject(hBrush);
	}

	if (returnLayer() == LAYER::MONSTER)
	{
		HBRUSH hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255));
		HBRUSH hOrigin_Brush = (HBRUSH)SelectObject(_dc, hBrush);

		Rectangle(_dc, (int)(mapPos.x - 5.f)
			, (int)(mapPos.y - 5.f)
			, (int)(mapPos.x + 5.f)
			, (int)(mapPos.y + 5.f));

		SelectObject(_dc, hOrigin_Brush);
		DeleteObject(hBrush);
	}

}

void CObj::tick()
{

	if (nullptr != m_pCollider)
		m_pCollider->tick();

	if (nullptr != m_pAnimator)
		m_pAnimator->tick();
}

void CObj::render(HDC _dc)
{
	if (m_pCollider != nullptr)
		m_pCollider->render(_dc);

	if (m_pAnimator != nullptr)
		m_pAnimator->render(_dc);

}

void CObj::CreateCollider()
{
	m_pCollider = new CCollider(this);
}

void CObj::SetDead()
{
	tEvent evn = {};
	evn.eType = EVENT_TYPE::DELETE_OBJECT;
	evn.wParam = (DWORD_PTR)this;
	CEventMgr::GetInst()->AddEvent(evn);
}

void CObj::Instantiate(CObj* _pNewObj, Vec2 _vPos, LAYER _eLayer)
{
	// 이벤트 추가구역

	_pNewObj->SetPos(GetPos());

	tEvent _evn = {};
	_evn.eType = EVENT_TYPE::CREATE_OBJECT;
	_evn.wParam = (DWORD_PTR)_pNewObj;
	_evn.lParam = (DWORD_PTR)_eLayer;

	CEventMgr::GetInst()->AddEvent(_evn);
}
