#pragma once

#include "Specialization/IComponent.h"
#include "Specialization/Components/CWeapon.h"

class CHandle : public IComponent
{
public:

	CHandle();
	~CHandle();

	void Load() override;

	void		SetVerticalRecoil		(tgFloat recoil)	{ m_VerticalRecoil = recoil; }
	void		SetHorizontalRecoil		(tgFloat recoil)	{ m_HorizontalRecoil = recoil; }
	void		SetShakeRecoil			(tgFloat recoil)	{ m_ShakeRecoil = recoil; }
	void		SetRecovery				(tgFloat recovery)	{ m_Recovery = recovery; }

	void		SetWeight				(tgFloat whieght)	{ m_Wheight = whieght; }

	void		SetHandleName			(tgCString name)	{ m_HandleName = name; }

	CEntity*	GetEntity			(void)	{ return m_pEntity; }

	tgFloat		GetVerticalRecoil	(void)	{ return m_VerticalRecoil; }
	tgFloat		GetHorizontalRecoil	(void)	{ return m_HorizontalRecoil; }
	tgFloat		GetShakeRecoil		(void)	{ return m_ShakeRecoil; }
	tgFloat		GetRecovery			(void)	{ return m_Recovery; }

	tgFloat		GetWeight			(void)	{ return m_Wheight; }

	tgCString	GetHandleName		(void)	{ return m_HandleName; }

protected:

	tgFloat m_VerticalRecoil;
	tgFloat m_HorizontalRecoil;
	tgFloat m_ShakeRecoil;
	tgFloat m_Recovery;

	tgFloat m_Wheight;

	tgCString m_HandleName;

};