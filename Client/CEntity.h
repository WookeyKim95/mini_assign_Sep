#pragma once


class CEntity
{
private:
	static UINT	g_iNextID;

private:
	wstring		m_strName;
	const UINT	m_id;


public:
	void SetName(const wstring& _str) { m_strName = _str; }
	const wstring& GetName() { return m_strName; }
	UINT GetID() { return m_id; }

public:
	CEntity();
	CEntity(const CEntity& _Origin);
	~CEntity();
};

