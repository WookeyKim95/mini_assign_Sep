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
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	vResolution /= 2.f;

	// �÷��̾ ���� �����̴� ī�޶�
	if (IsPressed(KEY::UP) && m_vAround.y <= 0)
		m_vLook.y -= 200.f * DT;
	if (IsPressed(KEY::DOWN) && m_vAround.y <= 0)
		m_vLook.y += 200.f * DT;
	if (IsPressed(KEY::LEFT) && m_vAround.x <= 0)
		m_vLook.x -= 200.f * DT;
	if (IsPressed(KEY::RIGHT) && m_vAround.x <= 0)
		m_vLook.x += 200.f * DT;


	// �����ڸ��� ���� �� ī�޶� �̵� ���߱� ���� ����
	if ((IsPressed(KEY::UP) && m_vLook.y <= vResolution.y) || (IsPressed(KEY::DOWN) && m_vLook.y >= 3000 - vResolution.y))
		m_vAround.y += 200.f * DT;

	if ((IsPressed(KEY::DOWN) && m_vLook.y <= vResolution.y) || (IsPressed(KEY::UP) && m_vLook.y >= 3000 - vResolution.y))
		m_vAround.y -= 200.f * DT;

	if ((IsPressed(KEY::LEFT) && m_vLook.x <= vResolution.x) || (IsPressed(KEY::RIGHT) && m_vLook.x >= 3000 - vResolution.x))
		m_vAround.x += 200.f * DT;

	if ((IsPressed(KEY::RIGHT) && m_vLook.x <= vResolution.x) || (IsPressed(KEY::LEFT) && m_vLook.x >= 3000 - vResolution.x))
		m_vAround.x -= 200.f * DT;


	// WSAD Ű�� ���� ī�޶� �̵�
	/*if (IsPressed(KEY::W))
		m_vLook.y -= 300.f * DT;
	if (IsPressed(KEY::S))
		m_vLook.y += 300.f * DT;
	if (IsPressed(KEY::A))
		m_vLook.x -= 300.f * DT;
	if (IsPressed(KEY::D))
		m_vLook.x += 300.f * DT;*/

	
	m_vDiff = m_vLook - vResolution;
}
