#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CStartLevel.h"
#include "CStage01Level.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		DEL(m_arrLevel[i]);		
	}	
}

void CLevelMgr::init()
{
	// Level »ý¼º
	m_arrLevel[(UINT)LEVEL_TYPE::START] = new CStartLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CStage01Level;

	m_pCurLevel = m_arrLevel[(UINT)LEVEL_TYPE::START];
	m_pCurLevel->init();
}

void CLevelMgr::tick()
{
	m_pCurLevel->tick();
}

void CLevelMgr::render(HDC _dc)
{
	m_pCurLevel->render(_dc);
}
