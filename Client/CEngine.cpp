#include "pch.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"


CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_hDC(nullptr)
	, m_hMemDC(nullptr)
	, m_hMemBit(nullptr)
	, m_ptResolution{}
	, m_arrPen{}
{

}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_hDC);

	DeleteDC(m_hMemDC);
	DeleteObject(m_hMemBit);
}


void CEngine::init(HWND _hwnd, UINT _iWidth, UINT _iHeight)
{
	m_hMainWnd = _hwnd;
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;

	// 윈도우 크기 설정
	RECT rt = {0, 0, (LONG)_iWidth, (LONG)_iHeight};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// HDC 초기화
	m_hDC = GetDC(m_hMainWnd);

	// 자주 사용하는 Pen 및 Brush 생성해둠
	CreatePenBrush();		

	// 별도의 비트맵을 윈도우와 동일한 해상도로 생성시킴
	m_hMemBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);

	// 생성시킨 비트맵을 목적지로 하는 DC 를 생성함
	m_hMemDC = CreateCompatibleDC(m_hDC);
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hMemDC, m_hMemBit);
	DeleteObject(hPrevBit);


	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();

	
}

void CEngine::progress()
{
	// 논리적인 연산
	tick();


	// 화면 렌더링 갱신
	render();

	// 다음 프레임에 적용할 이벤트 처리
	CEventMgr::GetInst()->tick();
}

void CEngine::tick()
{
	// FPS, DeltaTime 계산
	CTimeMgr::GetInst()->tick();
	// 키 이벤트 체크
	CKeyMgr::GetInst()->tick();
	// 카메라 업데이트
	CCamera::GetInst()->tick();
	// Level 업데이트
	CLevelMgr::GetInst()->tick();
	// 변경점 기반, 충돌체크
	CCollisionMgr::GetInst()->tick();
}

void CEngine::render()
{
	// 화면 클리어
	Rectangle(m_hMemDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// 레벨 렌더
	CLevelMgr::GetInst()->render(m_hMemDC);

	// MemBitMap -> MainWindowBitmap
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hMemDC, 0, 0, SRCCOPY);

	// TIME 렌더링
	CTimeMgr::GetInst()->render();
}

void CEngine::CreatePenBrush()
{
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
