#include "pch.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{

}

CPathMgr::~CPathMgr()
{

}

void CPathMgr::init()
{
	GetCurrentDirectory(256, m_szContentPath);

	// 상위 폴더로 가자
	int iLen = wcslen(m_szContentPath);

	// 맨 끝의 \를 널문자로 바꿔주는 부분
	for (int i = iLen - 1; i >= 0; --i)
	{
		if (m_szContentPath[i] == L'\\')
		{
			m_szContentPath[i] = L'\0';
			break;
		}
	}

	// cat함수를 사용하여 뒤에 경로를 덧붙이자. bin 폴더의 content로 가자
	wcscat_s(m_szContentPath, L"\\bin\\content\\");
}