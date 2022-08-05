#include <tgSystem.h>

#include "CHandle.h"
#include "Specialization/CEntity.h"

CHandle::CHandle()
: m_VerticalRecoil( 1.0f )
, m_HorizontalRecoil( 1.0f )
, m_ShakeRecoil( 1.0f )
, m_Recovery( 1.0f)
, m_Wheight( 1.0f )
, m_HandleName ( "" )
{
}

CHandle::~CHandle()
{
}

void CHandle::Load()
{
	if (m_pEntity)
		m_HandleName = m_pEntity->GetName();
}
