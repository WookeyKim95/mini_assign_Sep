#include "pch.h"
#include "CTexture.h"

#include "CEngine.h"

CTexture::CTexture() :
	  m_hBit(nullptr)
	, m_hDC(nullptr)
	, m_tBitmapInfo{}
{
}

CTexture::~CTexture()
{
	DeleteObject(m_hBit);
	DeleteDC(m_hDC);
}

int CTexture::Load(const wstring& _strFilePath)
{
	// 비트맵 로딩
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE); // 0, 0이 되면 잘리는게 아니라 이미지 전체가 로딩된다!
	GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);

	if (m_hBit == nullptr) // 널가드?
	{
		return 0;
	}

	// 비트맵과 연결시킬 DC 생성
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBit);

	return S_OK;
}
