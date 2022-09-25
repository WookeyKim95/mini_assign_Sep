#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CPlayer.h"

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

void CCamera::tick()
{
	// 어떻게 해야 플레이어의 위치를 따라갈까나
	// 사실 간단한 방법은 플레이어랑 같이 움직이는건데..
	if (IsPressed(KEY::UP))
		m_vLook.y -= 200.f * DT;
	if (IsPressed(KEY::DOWN))
		m_vLook.y += 200.f * DT;
	if (IsPressed(KEY::LEFT))
		m_vLook.x -= 200.f * DT;
	if (IsPressed(KEY::RIGHT))
		m_vLook.x += 200.f * DT;


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
