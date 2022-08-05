#pragma once

#include "Specialization/Components/CWeapon.h"
#include "Specialization/CWorld.h"

class CWorld;

class CWAutomatic : public CWeapon
{
public:


	CWAutomatic();
	~CWAutomatic();

	void Shoot() override;

	void		SetFireRate		(tgFloat fireRate)	{ m_FireRate = fireRate; }

	tgFloat		GetFireRate		(void)				{ return m_FireRate; }

protected:

	tgFloat m_FireTime;
	tgFloat m_FireRate;
};

