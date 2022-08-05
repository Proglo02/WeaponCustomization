#include "CMP5A4.h"
#include "Managers/CModelManager.h"

CMP5A4::CMP5A4()
{
	SetRecoil(tgCV3D(1.5f, 1.0f, 0.2f), 20.0f, 20.0f);
	SetScopedRecoil(tgCV3D(3.0f, 2.0f, 0.2f), 10.0f, 10.0f);

	m_WeaponModelPath = "models/z62";
	m_WeaponModelOffset = tgCV3D(-0.15f, -0.13f, 0.95f);
	m_ScopeOffset = tgCV3D(-0.1f, -0.05f, 0.21f);
	m_MuzzleOffset = tgCV3D(-0.104f, -0.068f, 0.39f);

	m_BulletSpread = 0.1f;

	m_DefaultMaxAmmo = 30;

	m_Damage = 15;

	m_DefaultWeight = 10.0f;

	m_HasMuzzle = true;
	m_HasScope = true;
	m_HasMagazine = true;
	m_HasStock = true;
}

CMP5A4::~CMP5A4()
{
}
