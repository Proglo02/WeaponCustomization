#include <tgSystem.h>

#include "CHorizontalGrip.h"

CHorizontalGrip::CHorizontalGrip()
{
	m_VerticalRecoil = 1.0f;
	m_HorizontalRecoil = 0.5f;
	m_ShakeRecoil = 0.5f;

	m_Recovery = 1.1f;
}

CHorizontalGrip::~CHorizontalGrip()
{
}
