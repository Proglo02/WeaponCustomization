#include "CStoeger_M3500.h"

CStoeger_M3500::CStoeger_M3500()
{
	SetRecoil(tgCV3D(5.0f, 2.0f, 0.1f), 10.0f, 10.0f);

	m_WeaponModelPath = "models/doubleBarrel";
	m_WeaponModelOffset = tgCV3D(-0.12f, -0.07f, 0.3f);

	m_DefaultBulletSpread = 1.0f;
	m_BulletCount = 12;

	m_DefaultMaxAmmo = 6;

	m_Damage = 6;

	m_DefaultWeight = 15.0f;

	m_HasMuzzle = true;
	m_HasStock = true;
}

CStoeger_M3500::~CStoeger_M3500()
{
}
