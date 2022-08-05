#include "CAK_47.h"

CAK_47::CAK_47()
{
	SetRecoil(tgCV3D(3.0f, 1.5f, 0.65f), 20.0f, 20.0f);

	m_WeaponModelPath = "models/tompson";
	m_WeaponModelOffset = tgCV3D(-0.13f, -0.29f, 0.55f);
	m_MuzzleOffset = tgCV3D(-0.105f, -0.045f, 0.49f);

	m_BulletSpread = 2.0f;

	m_TimeToReload = 2.0f;
	m_FireRate = 0.1f;

	m_DefaultMaxAmmo = 30;

	m_DefaultDamage = 30;

	m_HasMuzzle = true;
	m_HasMagazine = true;

	m_DefaultWeight = 12.5f;
}

CAK_47::~CAK_47()
{
}
