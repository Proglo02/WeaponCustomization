#include "CGlock_18.h"

CGlock_18::CGlock_18()
{
	SetRecoil(tgCV3D(1.0f, 0.1f, 0.05f), 10.0f, 30.0f);

	m_WeaponModelPath = "models/glock";
	m_WeaponModelOffset = tgCV3D(-0.6f, -0.66f, 1.28f);

	m_BulletSpread = 0.1f;

	m_DefaultMaxAmmo = 15;

	m_Damage = 15;

	m_DefaultWeight = 0.75f;

	m_HasMuzzle = true;
	m_HasMagazine = true;
}

CGlock_18::~CGlock_18()
{
}
