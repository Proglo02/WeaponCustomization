#include <tgSystem.h>

#include "CFire.h"
#include "Specialization/CEntity.h"
#include "Specialization/CWorld.h"
#include "Specialization/Components/CDamageText.h"

CFire::CFire(tgUInt32 Damage, tgFloat Duration)
: m_FireDamage( Damage )
, m_FireIndex( 0 )
, m_FireDamageInterval( 0.25f )
, m_FireDamageTimer( 0.0f )
, m_FireTimeAlive( Duration )
, m_FireTime( 0.0f )
{
}

void CFire::Update(tgFloat DeltaTime)
{
	if (m_pEntity)
	{
		if (m_FireTime < m_FireTimeAlive)
		{
			if (m_FireDamageTimer >= m_FireDamageInterval)
			{
				CEntity* pDamageText = m_pEntity->GetWorld()->CreateEntity(m_pEntity->GetTransform().GetMatrixWorld().Pos, m_pEntity->GetName() + tgCString("%d", m_FireIndex));
				if (pDamageText)
					pDamageText->AddComponent<CDamageText>(m_FireDamage);

				m_FireIndex++;
				m_FireDamageTimer = 0.0f;
			}
			m_FireDamageTimer += DeltaTime;
		}
		else
		{
			m_pEntity->GetWorld()->DestroyEntityLater(m_pEntity->GetName());
		}
		m_FireTime += DeltaTime;
	}
}
