#include <tgSystem.h>

#include "CVerticalGrip.h"

CVerticalGrip::CVerticalGrip()
{
	m_VerticalRecoil = 0.75f;
	m_HorizontalRecoil = 1.0f;
	m_ShakeRecoil = 0.9f;
	m_Recovery = 1.2f;
}

CVerticalGrip::~CVerticalGrip()
{
}
