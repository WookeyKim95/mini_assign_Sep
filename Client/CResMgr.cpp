#include "pch.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "CPathMgr.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
    // 리소스 사라질 시 일괄적으로 삭제
    map<wstring, CTexture*>::iterator iter = m_mapTex.begin();

    for (; iter != m_mapTex.end(); ++iter)
    {
        delete iter->second;
    }
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
    map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

    // 로딩된 텍스쳐가 없을 경우
    if(iter == m_mapTex.end())
        return nullptr;

    return iter->second;
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    // 이 텍스쳐가 로딩되어있나요?
    CRes* pTexture = FindTexture(_strKey);
    
    // 이미 로딩되어있다면?
    if (pTexture != nullptr)
        return (CTexture*)pTexture;

    // 아니요! 로딩 안되어있습니다!

    // 붙일 경로 설정!
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    // 텍스쳐 생성 및 로딩
    pTexture = new CTexture;
    pTexture->Load(strFilePath);
    pTexture->SetKey(_strKey);
    pTexture->SetRelativePath(_strRelativePath);

    // 로딩이 완료되었으면 맵에 등록을 해야하지.
    m_mapTex.insert(make_pair(_strKey, (CTexture*)pTexture));
    
    return (CTexture*)pTexture;
}
