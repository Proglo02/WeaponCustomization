#include "CWSemiAutomatic.h"

#include "Specialization/Components/Ammos/CAmmo.h"
#include "Specialization/CEntity.h"
#include "CClock.h"

CWSemiAutomatic::CWSemiAutomatic()
{
	m_Type = TYPE_SEMIAUTOMATIC;

	m_BulletSpread = 0.5f;
	m_BulletSpread = 0.01f;

	SetRecoil(tgCV3D(10.0f, 1.0f, 0.35f), 12.0f, 12.0f);
	SetScopedRecoil(tgCV3D(5.0f, 0.2f, 0.1f), 12.0f, 12.0f);
}

CWSemiAutomatic::~CWSemiAutomatic()
{
}

void CWSemiAutomatic::Shoot()
{
	if (m_HasAmmo)
	{
		if (m_TriggerHeld)
		{
			SpawnBullet();
			Recoil();

			m_TriggerHeld = false;

			m_Ammo--;
		}

		if (m_Ammo <= 0)
			m_HasAmmo = false;
	}
}
