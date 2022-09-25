#include "pch.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "CPathMgr.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
    // ���ҽ� ����� �� �ϰ������� ����
    map<wstring, CTexture*>::iterator iter = m_mapTex.begin();

    for (; iter != m_mapTex.end(); ++iter)
    {
        delete iter->second;
    }
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
    map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

    // �ε��� �ؽ��İ� ���� ���
    if(iter == m_mapTex.end())
        return nullptr;

    return iter->second;
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    // �� �ؽ��İ� �ε��Ǿ��ֳ���?
    CRes* pTexture = FindTexture(_strKey);
    
    // �̹� �ε��Ǿ��ִٸ�?
    if (pTexture != nullptr)
        return (CTexture*)pTexture;

    // �ƴϿ�! �ε� �ȵǾ��ֽ��ϴ�!

    // ���� ��� ����!
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    // �ؽ��� ���� �� �ε�
    pTexture = new CTexture;
    pTexture->Load(strFilePath);
    pTexture->SetKey(_strKey);
    pTexture->SetRelativePath(_strRelativePath);

    // �ε��� �Ϸ�Ǿ����� �ʿ� ����� �ؾ�����.
    m_mapTex.insert(make_pair(_strKey, (CTexture*)pTexture));
    
    return (CTexture*)pTexture;
}
