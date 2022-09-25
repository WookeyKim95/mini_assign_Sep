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
	// �������� ������Ʈ ����
	for (size_t i = 0; i < m_vecGarbage.size(); ++i)
	{
		delete m_vecGarbage[i];
	}
	m_vecGarbage.clear();


	// �̺�Ʈ ó��
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
			// �������� ������Ʈ�� Dead ���·� �ΰ� Garbage �� �ִ´�.
			CObj* pObj = (CObj*)m_vecEvent[i].wParam;

			// ���� Ȯ���� ���� tick ���� ���ÿ� ���� ������Ʈ�� ������û �� ��츦 ���
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
