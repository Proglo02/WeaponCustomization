#include "CWSingleShot.h"

CWSingleShot::CWSingleShot()
{
	m_DefaultMaxAmmo = 1;
	m_Ammo = 1;
	m_BulletCount = 3;

	m_BulletSpread = 0.5f;

	SetRecoil(tgCV3D(30.0f, 5.0f, 0.1f), 10.0f, 10.0f);
}

CWSingleShot::~CWSingleShot()
{
}