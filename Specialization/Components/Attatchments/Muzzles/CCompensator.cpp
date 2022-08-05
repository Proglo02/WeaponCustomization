#include <tgSystem.h>

#include "CCompensator.h"

CCompensator::CCompensator()
{
	m_MuzzleModelPath = "models/compensator";
	m_VerticalRecoil = 0.9f;
	m_HorizontalRecoil = 0.9f;
	m_ShakeRecoil = 0.9f;
	m_Spread = 0.9f;
	m_Damage = 1.1f;
}

CCompensator::~CCompensator()
{
}
