#pragma once
#include "Specialization/IComponent.h"
class CFire : public IComponent
{
public:

	CFire(tgUInt32 Damage, tgFloat Duration);

	void Update(tgFloat DeltaTime) override;

private:

	tgUInt32 m_FireDamage;
	tgUInt32 m_FireIndex;

	tgFloat m_FireDamageInterval;
	tgFloat m_FireDamageTimer;
	tgFloat m_FireTimeAlive;
	tgFloat m_FireTime;
};

