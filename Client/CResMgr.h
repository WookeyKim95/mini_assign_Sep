#pragma once

class CTexture;

class CResMgr
{
	SINGLE(CResMgr);

private:
	map<wstring, CTexture*> m_mapTex;

public:
	CTexture*	FindTexture(const wstring& _strKey);
	CTexture*	LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
};

