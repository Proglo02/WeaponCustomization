#include <tgSystem.h>
#include <tgCTransform.h>
#include <tgCDebugManager.h>
#include <tgCCollision.h>
#include <tgCLine3D.h>

#include "Specialization/CEntity.h"
#include "Specialization/CWorld.h"
#include "Specialization/Components/CModelComponent.h"
#include "Specialization/Components/CDamageText.h"
#include "Specialization/Components/Ammos/CAmmo.h"
#include "Specialization/Components/Ammos/CExplosion.h"
#include "Specialization/Components/Ammos/CFire.h"
#include "Managers/CModelManager.h"
#include "CAmmo.h"
#include "CClock.h"

#include <tgMemoryDisable.h>
#include <iostream>
#include <tgMemoryEnable.h>
#include <Managers/CWorldManager.h>

CAmmo::CAmmo()
: m_pTransform( NULL )
, m_IsActive( false )
, m_CanHit ( false )
, m_HasExplosion( false )
, m_HasFire( false )
, m_WeaponOffset(0.0f, 1.8f, 0.0f)
, m_PrevPos( 0.0f, 0.0f, 0.0f )
, m_Damage( 10 )
, m_ExplosionDamage( 0 )
, m_FireDamage( 0 )
, m_ExplosionRadius( 0.0f )
, m_FireDuration( 0.0f )
, m_TravelSpeed( 100.0f )
, m_MaxTimeAlive( 10.0f )
, m_TimeAlive( 0.0f )
, m_Dispersion( 1.0f )
{
}

void CAmmo::Load(void)
{
	if (m_pEntity)
	{
		if (m_pTransform)
		{
			m_pEntity->GetTransform().GetMatrixLocal() = m_pTransform->GetMatrixLocal();
			m_PrevPos = m_pTransform->GetMatrixWorld().Pos;
			m_CanHit = true;
		}

		tgFloat randomY = tgMathRandom(-1.0, 1.0);
		tgFloat randomX = tgMathRandom(-1.0, 1.0);
		m_pEntity->GetTransform().GetMatrixLocal().RotateY(m_Dispersion * randomY, tgCMatrix::COMBINE_PRE_MULTIPLY);
		m_pEntity->GetTransform().GetMatrixLocal().RotateX(m_Dispersion * randomX, tgCMatrix::COMBINE_PRE_MULTIPLY);
	}
}

void CAmmo::Unload(void)
{
}

void CAmmo::Update(tgFloat deltaTime)
{
	if (m_IsActive)
	{
		if (m_TimeAlive >= m_MaxTimeAlive)
		{
			m_pEntity->GetWorld()->DestroyEntityLater(m_pEntity->GetName());
			return;
		}

		m_TimeAlive += deltaTime;

		if (m_pEntity)
		{
			m_pEntity->GetTransform().GetMatrixLocal().Translate(tgCV3D(0, 0, m_TravelSpeed * deltaTime), tgCMatrix::COMBINE_PRE_MULTIPLY);

			tgCDebugManager::GetInstance().AddLineSphere(tgCSphere(m_pEntity->GetTransform().GetMatrixWorld().Pos, 0.01f), tgCColor::Yellow);

			if (m_CanHit)
				HandleCollision();
		}
	}
}

void CAmmo::HandleCollision()
{
	const tgCLine3D Line(m_PrevPos, m_pEntity->GetTransform().GetMatrixWorld().Pos);
	tgCCollision Collision( true );
	Collision.SetType( tgCMesh::EType::TYPE_MODEL );

	if (Collision.LineAllMeshesInModel(Line, m_pEntity->GetWorld()->FindEntity("TestDummy")->GetComponent<CModelComponent>()->GetModel()))
	{
		tgCV3D Pos = Collision.GetLocalIntersection();
		Collision.GetLocalIntersection().TransformPoint(Collision.GetMesh()->GetTransform().GetMatrixWorld());
		CEntity* pHit = m_pEntity->GetWorld()->CreateEntity(m_pEntity->GetWorld()->FindEntity("TestDummy")->GetComponent<CModelComponent>()->GetModel().GetTransform().GetMatrixWorld().Pos + Collision.GetLocalIntersection(), m_pEntity->GetName() + "DamageText");
		if (pHit)
		{
			pHit->AddComponent<CDamageText>(m_Damage);
			if (m_HasExplosion)
			{
				CEntity* pExplosion = m_pEntity->GetWorld()->CreateEntity(m_pEntity->GetWorld()->FindEntity("TestDummy")->GetComponent<CModelComponent>()->GetModel().GetTransform().GetMatrixWorld().Pos + Collision.GetLocalIntersection(), m_pEntity->GetName() + "Explosion");
				pExplosion->AddComponent<CExplosion>(m_ExplosionDamage, m_ExplosionRadius);
			}
			if (m_HasFire)
			{
				CEntity* pFire = m_pEntity->GetWorld()->CreateEntity(m_pEntity->GetWorld()->FindEntity("TestDummy")->GetComponent<CModelComponent>()->GetModel().GetTransform().GetMatrixWorld().Pos + Collision.GetLocalIntersection(), m_pEntity->GetName() + "Fire");
				pFire->AddComponent<CFire>(m_FireDamage, m_FireDuration);
			}
		}

		m_pEntity->GetWorld()->DestroyEntityLater(m_pEntity->GetName());
	}
	else
	{
		Collision.SetType(tgCMesh::EType::TYPE_WORLD);

		if (Collision.LineAllMeshesInWorld(Line, *CWorldManager::GetInstance().GetWorld("Level")))
		{
			if (m_HasExplosion)
			{
				CEntity* pExplosion = m_pEntity->GetWorld()->CreateEntity(Collision.GetLocalIntersection(), m_pEntity->GetName() + "Explosion");
				pExplosion->AddComponent<CExplosion>(m_ExplosionDamage, m_ExplosionRadius);
			}
			m_pEntity->GetWorld()->DestroyEntityLater(m_pEntity->GetName());
		}
	}
}


