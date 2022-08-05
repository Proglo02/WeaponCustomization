#include "CWAutomatic.h"

#include <tgSystem.h>

#include "Specialization/Components/Ammos/CAmmo.h"
#include "Specialization/CEntity.h"
#include "CApplication.h"
#include "Camera/CCamera.h"
#include "CClock.h"

CWAutomatic::CWAutomatic()
: CWeapon()
, m_FireTime( 0.0f )
, m_FireRate( 0.1f ) 
{
	m_Type = TYPE_AUTOMATIC;
	m_BulletSpread = 1.0f;
	m_BulletSpread = 0.1f;

	SetRecoil(tgCV3D(4.0f, 2.0f, 0.35f), 12.0f, 6.0f);
	SetScopedRecoil(tgCV3D(1.0f, 0.5f, 0.1f), 12.0f, 6.0f);
}

CWAutomatic::~CWAutomatic()
{
}

void CWAutomatic::Shoot()
{
	if (m_HasAmmo)
	{
		if (m_FireTime >= m_FireRate && m_TriggerHeld)
		{
			SpawnBullet();
			Recoil();

			m_Ammo--;
			m_FireTime = 0.0f;
		}
		else
			m_FireTime += CClock::GetInstance().GetDeltaTimeReal();

		if (m_Ammo <= 0)
			m_HasAmmo = false;
	}
}
