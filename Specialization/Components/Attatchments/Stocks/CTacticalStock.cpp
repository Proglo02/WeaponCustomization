#include <tgSystem.h>

#include "CTacticalStock.h"

CTacticalStock::CTacticalStock()
{
	m_VerticalRecoil	= 0.75f;
	m_HorizontalRecoil	= 0.75f;
	m_ShakeRecoil		= 0.75f;

	m_Weight = 1.0f;
}

CTacticalStock::~CTacticalStock()
{
}
