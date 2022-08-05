#pragma once
#include "Specialization/IComponent.h"
class CExplosion : public IComponent
{
public:

	CExplosion(tgUInt32 Damage, tgFloat Radius);

	void Update(tgFloat DeltaTime) override;

	void HandleCollision();

private:

	tgUInt32 m_ExplosionDamage;
	tgFloat m_ExplosionRadius;
	tgFloat m_ExplosionTimeAlive;
	tgFloat m_ExplosionTimer;

	tgBool m_HasExploded;
};

