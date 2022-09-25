#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_matrix{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::tick()
{
	for (UINT iRow = 0; iRow < (UINT)LAYER::END; iRow++)
	{
		for (UINT iCol = iRow; iCol < (UINT)LAYER::END; iCol++)
		{
			if (!(m_matrix[iRow] & (1 << iCol))) // 행렬에 충돌처리가 체크 되어있지 않다면 컨티뉴.
				continue;

			// 충돌 검사를 진행한다.
			CollisionBtwLayer((LAYER)iRow, (LAYER)iCol);
		}
	}
}

void CCollisionMgr::CollisionBtwLayer(LAYER _left, LAYER _right)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	const vector<CObj*>& vecLeft = pCurLevel->GetLayer(_left);
	const vector<CObj*>& vecRight = pCurLevel->GetLayer(_right);

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 충돌체가 없는 경우
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;

		size_t j = 0;
		if (_left == _right) // Left, Right 동일 레이어인 경우, 이중 검사를 피하기 위함
		{
			j = i;
		}

		for (; j < vecRight.size(); ++j)
		{
			// 충돌체를 보유하고 있지 않거나, 충돌을 진행시킬 두 대상이 동일한 오브젝트인 경우
			if (vecRight[j]->GetCollider() == nullptr || vecLeft[i] == vecRight[j])
				continue;

			// 두 충돌체의 아이디를 조합한다.
			CollisionID ID = {};
			ID.LeftID = vecLeft[i]->GetCollider()->GetID();
			ID.RightID = vecRight[j]->GetCollider()->GetID();

			// 이전 프레임 충돌 확인
			map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
			if (iter == m_mapPrevInfo.end())
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}

			bool bDead = vecLeft[i]->IsDead() || vecRight[j]->IsDead();

			// 충돌검사를 진행한다. 참인가? 거짓인가?
			if (CollisionBtwCollider(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{
				// 오버랩 중이다

				// 이전에도 겹쳐있었다.
				if (iter->second)
				{
					if (bDead) // 그런데 한쪽이 Dead 했을 경우 즉 삭제됐을경우.
					{
						vecLeft[i]->GetCollider()->EndOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->EndOverlap(vecLeft[i]->GetCollider());
					}
					else
					{
						vecLeft[i]->GetCollider()->OnOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnOverlap(vecLeft[i]->GetCollider());
					}
					
				}
				else
				{
					// 둘 중 하나라도 Dead면, 충돌을 없었던 걸로 하자.
					if (!bDead)
					{
						vecLeft[i]->GetCollider()->BeginOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->BeginOverlap(vecLeft[i]->GetCollider());
						iter->second = true;
					}
					
				}
				
			}
			else
			{
				if (iter->second)
				{
					vecLeft[i]->GetCollider()->EndOverlap(vecRight[j]->GetCollider());
					vecRight[j]->GetCollider()->EndOverlap(vecLeft[i]->GetCollider());
					iter->second = false;
				}
				// 떨어져 있다.
				
			}
		}
	}
}

// 충돌 조건 지정
bool CCollisionMgr::CollisionBtwCollider(CCollider* _pLeft, CCollider* _pRight)
{
	Vec2 vLeftPos = _pLeft->GetFinalPos();
	Vec2 vLeftScale = _pLeft->GetScale();

	Vec2 vRightPos = _pRight->GetFinalPos();
	Vec2 vRightScale = _pRight->GetScale();

	if (fabsf(vLeftPos.x - vRightPos.x) > (vLeftScale.x / 2.f + vRightScale.x / 2.f))
		return false;

	if (fabsf(vLeftPos.y - vRightPos.y) > (vLeftScale.y / 2.f + vRightScale.y / 2.f))
		return false;

	return true;
}

// 충돌을 설정할 레이어 체크
void CCollisionMgr::LayerCheck(LAYER _left, LAYER _right)
{
	UINT iRow = (UINT)_left;
	UINT iCol = (UINT)_right;

	if (iRow > iCol)
	{
		UINT iTemp = iCol;
		iCol = iRow;
		iRow = iTemp;
	}

	// 체크 후 저장!
	m_matrix[iRow] |= (1 << iCol);
}