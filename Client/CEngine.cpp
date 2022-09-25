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

	// ������ ũ�� ����
	RECT rt = {0, 0, (LONG)_iWidth, (LONG)_iHeight};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// HDC �ʱ�ȭ
	m_hDC = GetDC(m_hMainWnd);

	// ���� ����ϴ� Pen �� Brush �����ص�
	CreatePenBrush();		

	// ������ ��Ʈ���� ������� ������ �ػ󵵷� ������Ŵ
	m_hMemBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);

	// ������Ų ��Ʈ���� �������� �ϴ� DC �� ������
	m_hMemDC = CreateCompatibleDC(m_hDC);
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hMemDC, m_hMemBit);
	DeleteObject(hPrevBit);


	// Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();

	
}

void CEngine::progress()
{
	// ������ ����
	tick();


	// ȭ�� ������ ����
	render();

	// ���� �����ӿ� ������ �̺�Ʈ ó��
	CEventMgr::GetInst()->tick();
}

void CEngine::tick()
{
	// FPS, DeltaTime ���
	CTimeMgr::GetInst()->tick();
	// Ű �̺�Ʈ üũ
	CKeyMgr::GetInst()->tick();
	// ī�޶� ������Ʈ
	CCamera::GetInst()->tick();
	// Level ������Ʈ
	CLevelMgr::GetInst()->tick();
	// ������ ���, �浹üũ
	CCollisionMgr::GetInst()->tick();
}

void CEngine::render()
{
	// ȭ�� Ŭ����
	Rectangle(m_hMemDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// ���� ����
	CLevelMgr::GetInst()->render(m_hMemDC);

	// MemBitMap -> MainWindowBitmap
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hMemDC, 0, 0, SRCCOPY);

	// TIME ������
	CTimeMgr::GetInst()->render();
}

void CEngine::CreatePenBrush()
{
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
