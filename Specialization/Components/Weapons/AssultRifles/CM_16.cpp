#include "CM_16.h"

CM_16::CM_16()
{
	SetRecoil(tgCV3D(2.5f, 1.0f, 0.5f), 20.0f, 20.0f);
	SetScopedRecoil(tgCV3D(2.5f, 0.5f, 1.5f), 10.0f, 10.0f);

	m_WeaponModelPath = "models/fmg9";
	m_WeaponModelOffset = tgCV3D(-0.12f, -0.16f, 0.0f);
	m_ScopeOffset = tgCV3D(-0.105f, -0.005f, 0.39f);
	m_MuzzleOffset = tgCV3D(-0.105f, -0.065f, 0.48f);

	m_BulletSpread = 1.0f;
	m_DefaultScopedBulletSpread = 1.0f;

	m_TimeToReload = 1.5f;
	m_FireRate = 0.09f;

	m_DefaultMaxAmmo = 30;

	m_Damage = 25;

	m_DefaultWeight = 15.0f;

	m_HasMuzzle = true;
	m_HasHandle = true;
	m_HasScope = true;
	m_HasMagazine = true;
	m_HasStock = true;
}

CM_16::~CM_16()
{
}
