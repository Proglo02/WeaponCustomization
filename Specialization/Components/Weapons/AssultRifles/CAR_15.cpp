#include "CAR_15.h"

CAR_15::CAR_15()
{
	SetRecoil(tgCV3D(2.5f, 1.0f, 0.5f), 20.0f, 20.0f);
	SetScopedRecoil(tgCV3D(2.5f, 0.5f, 1.5f), 10.0f, 10.0f);

	m_WeaponModelPath = "models/rn50";
	m_WeaponModelOffset = tgCV3D(-0.1f, -0.1f, 0.51f);
	m_ScopeOffset = tgCV3D(-0.1f, -0.04f, 0.2f);
	m_MuzzleOffset = tgCV3D(-0.105f, -0.065f, 0.49f);

	m_BulletSpread = 0.1f;
	m_DefaultScopedBulletSpread = 0.01f;

	m_TimeToReload = 1.5f;

	m_DefaultMaxAmmo = 20;

	m_Damage = 25;

	m_DefaultWeight = 12.5f;

	m_HasMuzzle = true;
	m_HasHandle = true;
	m_HasScope = true;
	m_HasMagazine = true;
	m_HasStock = true;
}

CAR_15::~CAR_15()
{
}
