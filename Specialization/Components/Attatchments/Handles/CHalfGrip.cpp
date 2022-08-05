#include <tgSystem.h>

#include "CHalfGrip.h"

CHalfGrip::CHalfGrip()
{
	m_VerticalRecoil = 0.85f;
	m_HorizontalRecoil = 0.9f;
	m_ShakeRecoil = 0.85f;

	m_Recovery = 1.15f;
}

CHalfGrip::~CHalfGrip()
{
}
