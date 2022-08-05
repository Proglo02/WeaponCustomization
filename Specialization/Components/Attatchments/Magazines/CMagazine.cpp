#include <tgSystem.h>

#include "CMagazine.h"
#include "Specialization/CEntity.h"

CMagazine::CMagazine()
: m_MagazineSize( 1.5f )
, m_RealoadTime( 1.2f )
, m_Weight( 1.0f )
, m_MagazineName( "" )
{
}

CMagazine::~CMagazine()
{
}

void CMagazine::Load()
{
	if (m_pEntity)
		m_MagazineName = m_pEntity->GetName();
}
