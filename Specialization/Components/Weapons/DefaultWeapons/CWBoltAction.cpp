#include "CWBoltAction.h"

#include "Specialization/Components/Ammos/CAmmo.h"
#include "Specialization/CEntity.h"
#include "CClock.h"

CWBoltAction::CWBoltAction()
: m_BulletChambered( true )
, m_TimeToChamber( 0.2f )
{
	m_Type = TYPE_BOLTACTION;
	m_DefaultMaxAmmo = 5;
	m_Ammo = 5;

	m_DefaultBulletSpread = 10.0f;
	m_DefaultScopedBulletSpread = 0.001f;

	SetRecoil(tgCV3D(20.0f, 1.0f, 0.1f), 20.0f, 20.0f);
	SetScopedRecoil(tgCV3D(5.0f, 0.25f, 0.1f), 20.0f, 20.0f);
}

CWBoltAction::~CWBoltAction()
{
}

void CWBoltAction::Shoot()
{
	if (m_HasAmmo && m_BulletChambered)
	{
		if (m_TriggerHeld)
		{
			SpawnBullet();
			Recoil();

			m_TriggerHeld = false;

			m_Ammo--;

			if (m_Ammo > 0)
				m_BulletChambered = false;
		}

		if (m_Ammo <= 0)
			m_HasAmmo = false;
	}
}

void CWBoltAction::Reload()
{
	if (!m_BulletChambered && m_ReloadTime >= m_TimeToChamber)
	{
		m_ReloadTime = 0.0f;
		m_BulletChambered = true;
		m_IsReloading = false;
		return;
	}

	if (m_ReloadTime >= m_TimeToReload)
	{
		m_Ammo = m_MaxAmmo;
		m_ReloadTime = 0.0f;
		m_IsReloading = false;
		m_HasAmmo = true;
		return;
	}

	m_ReloadTime += CClock::GetInstance().GetDeltaTimeReal();
}

tgCV2D CWBoltAction::SetQuadSize()
{
	if (!m_BulletChambered)
		return tgCV2D(50, (m_ReloadTime / m_TimeToChamber) * 200);
	else
		return tgCV2D(50, (m_ReloadTime / m_TimeToReload) * 200);
}

tgCV3D CWBoltAction::SetQuadPos()
{
	if (!m_BulletChambered)
		return tgCV3D(m_RenderTargetWidth * 0.5f * 1.1f, m_RenderTargetHeight - 100 - (m_ReloadTime / m_TimeToChamber) * 100, 0);
	else
		return tgCV3D(m_RenderTargetWidth * 0.5f * 1.1f, m_RenderTargetHeight - 100 - (m_ReloadTime / m_TimeToReload) * 100, 0);
}
