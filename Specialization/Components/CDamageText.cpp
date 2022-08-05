#include <tgSystem.h>
#include <tgCFontManager.h>
#include <tgCDebugManager.h>
#include <tgCSphere.h>

#include "CDamageText.h"
#include "Specialization/CWorld.h"

CDamageText::CDamageText( tgUInt32 Damage )
: m_TimeAlive( 1.0f )
, m_Timer( 0.0f )
, m_Damage( Damage )
{
}

CDamageText::~CDamageText()
{
}

void CDamageText::Load()
{

}

void CDamageText::Update(tgFloat DeltaTime)
{
	if (m_Timer < m_TimeAlive)
	{
		m_pEntity->GetTransform().GetMatrixLocal().Pos.y += DeltaTime;
		tgCDebugManager::GetInstance().AddText3D(m_pEntity->GetTransform().GetMatrixWorld().Pos, tgCColor::White, tgCString("%d", m_Damage));

	}
	else
	{
		m_pEntity->GetWorld()->DestroyEntityLater(m_pEntity->GetName());
		return;
	}

	m_Timer += DeltaTime;
}
