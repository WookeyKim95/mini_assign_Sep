#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

void CCamera::tick()
{
	// 플레이어를 따라 움직이는 카메라
	if (IsPressed(KEY::UP) && m_vAround.y <= 0)
		m_vLook.y -= 200.f * DT;
	if (IsPressed(KEY::DOWN) && m_vAround.y <= 0)
		m_vLook.y += 200.f * DT;
	if (IsPressed(KEY::LEFT) && m_vAround.x <= 0)
		m_vLook.x -= 200.f * DT;
	if (IsPressed(KEY::RIGHT) && m_vAround.x <= 0)
		m_vLook.x += 200.f * DT;


	// 가장자리에 있을 땐 카메라 이동 멈추기 위한 수단
	if ((IsPressed(KEY::UP) && m_vLook.y <= 450) || (IsPressed(KEY::DOWN) && m_vLook.y >= 2550))
		m_vAround.y += 200.f * DT;

	if ((IsPressed(KEY::DOWN) && m_vLook.y <= 450) || (IsPressed(KEY::UP) && m_vLook.y >= 2550))
		m_vAround.y -= 200.f * DT;

	if ((IsPressed(KEY::LEFT) && m_vLook.x <= 800) || (IsPressed(KEY::RIGHT) && m_vLook.x >= 2200))
		m_vAround.x += 200.f * DT;

	if ((IsPressed(KEY::RIGHT) && m_vLook.x <= 800) || (IsPressed(KEY::LEFT) && m_vLook.x >= 2200))
		m_vAround.x -= 200.f * DT;


	// WSAD 키에 따른 카메라 이동
	/*if (IsPressed(KEY::W))
		m_vLook.y -= 300.f * DT;
	if (IsPressed(KEY::S))
		m_vLook.y += 300.f * DT;
	if (IsPressed(KEY::A))
		m_vLook.x -= 300.f * DT;
	if (IsPressed(KEY::D))
		m_vLook.x += 300.f * DT;*/

	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	vResolution /= 2.f;
	m_vDiff = m_vLook - vResolution;
}
