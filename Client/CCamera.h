#pragma once

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2		m_vLook;
	Vec2		m_vDiff;
	Vec2		m_aroundPoint;

public:
	void SetLook(Vec2 _vLook) { m_vLook = _vLook; }

public:
	void tick();


public:
	Vec2 GetRenderPos(Vec2 _vRealPos)
	{
		return _vRealPos - m_vDiff;
	}

	Vec2 GetRealPos(Vec2 _vRenderPos)
	{
		return _vRenderPos + m_vDiff;
	}
};

