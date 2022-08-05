#include <tgSystem.h>

#include "CStock.h"
#include "Specialization/CEntity.h"

CStock::CStock()
: m_VerticalRecoil( 1.0f )
, m_HorizontalRecoil( 1.0f )
, m_ShakeRecoil( 1.0f )
, m_Weight( 1.0f )
, m_StockName( "" )
{
}

CStock::~CStock()
{
}

void CStock::Load()
{
	if (m_pEntity)
		m_StockName = m_pEntity->GetName();
}
