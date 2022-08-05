#include <tgSystem.h>

#include "CAmplifier.h"

CAmplifier::CAmplifier()
{
	m_MuzzleModelPath = "models/amplifier";
	m_VerticalRecoil = 1.2f;
	m_HorizontalRecoil = 1.1f;
	m_ShakeRecoil = 1.1f;
	m_Spread = 1.0f;
	m_Damage = 1.5f;
}

CAmplifier::~CAmplifier()
{
}
