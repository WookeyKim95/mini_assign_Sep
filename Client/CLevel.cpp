#include "pch.h"
#include "CLevel.h"
#include "CObj.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	// 오브젝트 삭제
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			DEL(m_arrLayer[i][j]);
		}
	}
}

void CLevel::tick()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
				m_arrLayer[i][j]->tick();
		}
	}
}

void CLevel::render(HDC _dc)
{
	// 미니맵

	HBRUSH hBh = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH hOrigin_Brush = (HBRUSH)SelectObject(_dc, hBh);

	Rectangle(_dc, (int)(1350)
		, (int)(50)
		, (int)(1500)
		, (int)(200));

	SelectObject(_dc, hOrigin_Brush);
	DeleteObject(hBh);

	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		vector<CObj*>::iterator iter = m_arrLayer[i].begin();

		for (; iter != m_arrLayer[i].end();)
		{
			if ((*iter)->IsDead())
			{
				iter = m_arrLayer[i].erase(iter);
			}
			else
			{
				(*iter)->render(_dc);
				(*iter)->renderMap(_dc);
				++iter;
			}
		}
	}
}

