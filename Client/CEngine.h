#pragma once


// 디자인 패턴 (설계 방식)
 
// 싱글톤 패턴
class CEngine
{
	SINGLE(CEngine);

private:	
	// static CEngine* m_pInst;
	HWND	m_hMainWnd;
	HDC		m_hDC;

	HDC		m_hMemDC;
	HBITMAP m_hMemBit;


	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	POINT	m_ptResolution;


public:
	HWND GetMainWnd() { return m_hMainWnd; }
	HDC GetMainDC() { return m_hDC; }
	HPEN GetPen(PEN_TYPE _type) { return m_arrPen[(UINT)_type]; }
	POINT GetResolution() { return m_ptResolution; }

public:
	void init(HWND _hwnd, UINT _iWidth, UINT _iHeight);
	void progress();

private:
	void tick();	// 갱신
	void render();	// 렌더링
	void CreatePenBrush();




};

