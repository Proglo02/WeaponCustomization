#pragma once
#include <tgSystem.h>

#include "Specialization/Components/CWeapon.h"
#include "Specialization/CWorld.h"

class CWBoltAction : public CWeapon
{
public:

	CWBoltAction();
	~CWBoltAction();

	void Shoot() override;
	void Reload() override;

	void		SetTimeToChamber	(tgFloat time)		{ m_TimeToChamber = time; }
	tgFloat		GetTimeToChamber	(void)				{ return m_TimeToChamber; }

	tgCV2D SetQuadSize() override;
	tgCV3D SetQuadPos() override;

private:

	tgFloat m_TimeToChamber;

	tgBool m_BulletChambered;

};

