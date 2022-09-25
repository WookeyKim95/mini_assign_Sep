#include "pch.h"
#include "CEventMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::tick()
{
	// 삭제예정 오브젝트 삭제
	for (size_t i = 0; i < m_vecGarbage.size(); ++i)
	{
		delete m_vecGarbage[i];
	}
	m_vecGarbage.clear();


	// 이벤트 처리
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		switch (m_vecEvent[i].eType)
		{
		case EVENT_TYPE::CREATE_OBJECT: // wParam : Object Adress, lParam : Layer
		{
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

			CObj* pNewObj = (CObj*)m_vecEvent[i].wParam;
			LAYER eLayer = (LAYER)m_vecEvent[i].lParam;

			pCurLevel->AddObject(pNewObj, eLayer);
		}
		break;

		case EVENT_TYPE::DELETE_OBJECT:
		{
			// 삭제예정 오브젝트를 Dead 상태로 두고 Garbage 에 넣는다.
			CObj* pObj = (CObj*)m_vecEvent[i].wParam;

			// 낮을 확률로 같은 tick 에서 동시에 같은 오브젝트를 삭제요청 한 경우를 방어
			if (pObj->m_bDead == false)
			{
				m_vecGarbage.push_back(pObj);
				pObj->m_bDead = true;
			}
		}
		break;


		case EVENT_TYPE::LEVEL_CHANGE:



			break;
		default:
			break;
		}
	}

	m_vecEvent.clear();
}
