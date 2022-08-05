#include <tgSystem.h>

#include "CRemovedStock.h"

CRemovedStock::CRemovedStock()
{
	m_VerticalRecoil = 1.1f;
	m_HorizontalRecoil = 1.1f;
	m_ShakeRecoil = 1.1f;

	m_Weight = -3.0f;
}

CRemovedStock::~CRemovedStock()
{
}
