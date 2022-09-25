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
	// ��Ʈ�� �ε�
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE); // 0, 0�� �Ǹ� �߸��°� �ƴ϶� �̹��� ��ü�� �ε��ȴ�!
	GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);

	if (m_hBit == nullptr) // �ΰ���?
	{
		return 0;
	}

	// ��Ʈ�ʰ� �����ų DC ����
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBit);

	return S_OK;
}