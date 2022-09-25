#pragma once

class CCollider;

union CollisionID
{
	struct
	{
		UINT	LeftID;
		UINT	RightID;
	};

	UINT_PTR id;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	WORD					m_matrix[(UINT)LAYER::END];
	map<UINT_PTR, bool>		m_mapPrevInfo;		// ���� �����ӿ� �� �浹ü�� �浹����

public:
	void LayerCheck(LAYER _left, LAYER _right);

	void Clear()
	{
		for (int i = 0; i < (UINT)LAYER::END; i++)
		{
			m_matrix[i] = 0;
		}
	}

public:
	void tick();
private:
	void CollisionBtwLayer(LAYER _left, LAYER _right);
	bool CollisionBtwCollider(CCollider* _pLeft, CCollider* _pRight);

};

