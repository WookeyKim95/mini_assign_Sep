#pragma once

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2		m_vLook;
	Vec2		m_vDiff;
	Vec2		m_vAround; // 가장자리에서는 카메라 이동을 멈추기 위한 수단

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

