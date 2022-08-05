#include <tgSystem.h>
#include <tgCDebugManager.h>
#include <tgCSphere.h>
#include <tgCCollision.h>
#include <tgCMesh.h>
#include <tgCModel.h>

#include "CExplosion.h"
#include "Specialization/CEntity.h"
#include "Specialization/CWorld.h"
#include "Specialization/Components/CDamageText.h"
#include "Specialization/Components/CModelComponent.h"
#include "Specialization/Components/CDamageText.h"

CExplosion::CExplosion(tgUInt32 Damage, tgFloat Radius)
: m_ExplosionDamage( Damage )
, m_ExplosionRadius( Radius )
, m_ExplosionTimeAlive( 0.2f )
, m_ExplosionTimer( 0.0f )
, m_HasExploded( false )
{
}

void CExplosion::Update(tgFloat DeltaTime)
{
	if (m_pEntity)
	{
		if (!m_HasExploded)
		{
			m_HasExploded = true;
			HandleCollision();
		}

		if (m_ExplosionTimer >= m_ExplosionTimeAlive)
		{
			m_pEntity->GetWorld()->DestroyEntityLater(m_pEntity->GetName());
		}
		tgCDebugManager::GetInstance().AddLineSphere(tgCSphere(m_pEntity->GetTransform().GetMatrixWorld().Pos, m_ExplosionRadius), tgCColor::Red);
		m_ExplosionTimer += DeltaTime;
	}
}

void CExplosion::HandleCollision()
{
	const tgCSphere Sphere(m_pEntity->GetTransform().GetMatrixWorld().Pos, m_ExplosionRadius);
	tgCCollision Collision(true);
	Collision.SetType(tgCMesh::EType::TYPE_MODEL);

	if (Collision.SphereAllMeshesInModel(Sphere, m_pEntity->GetWorld()->FindEntity("TestDummy")->GetComponent<CModelComponent>()->GetModel()))
	{
		tgCV3D Pos = Collision.GetLocalIntersection();
		Collision.GetLocalIntersection().TransformPoint(Collision.GetMesh()->GetTransform().GetMatrixWorld());
		CEntity* pDamageText = m_pEntity->GetWorld()->CreateEntity(m_pEntity->GetWorld()->FindEntity("TestDummy")->GetComponent<CModelComponent>()->GetModel().GetTransform().GetMatrixWorld().Pos + Collision.GetLocalIntersection() + tgCV3D(0.0f, 0.1f, 0.0f), m_pEntity->GetName() + "Explosion");
		if (pDamageText)
			pDamageText->AddComponent<CDamageText>(m_ExplosionDamage);
	}
}
