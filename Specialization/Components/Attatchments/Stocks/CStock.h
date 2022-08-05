#pragma once

#include "Specialization/IComponent.h"
#include "Specialization/Components/CWeapon.h"

class CStock : public IComponent
{
public:

	CStock();
	~CStock();

	void Load() override;

	void		SetVerticalRecoil		(tgFloat recoil)		{ m_VerticalRecoil = recoil; }
	void		SetHorizontalRecoil		(tgFloat recoil)		{ m_HorizontalRecoil = recoil; }
	void		SetShakeRecoil			(tgFloat recoil)		{ m_ShakeRecoil = recoil; }

	void		SetWeight				(tgFloat whieght)		{ m_Weight = whieght; }

	void		SetStockName			(tgCString name)		{ m_StockName = name; }

	CEntity*	GetEntity				(void)		{ return m_pEntity; }

	tgFloat		GetVerticalRecoil		(void)		{ return m_VerticalRecoil; }
	tgFloat		GetHorizontalRecoil		(void)		{ return m_HorizontalRecoil; }
	tgFloat		GetShakeRecoil			(void)		{ return m_ShakeRecoil; }

	tgFloat		GetWeight				(void)		{ return m_Weight; }

	tgCString	GetStockName			(void)		{ return m_StockName; }

protected:

	tgFloat		m_VerticalRecoil;
	tgFloat		m_HorizontalRecoil;
	tgFloat		m_ShakeRecoil;

	tgFloat		m_Weight;

	tgCString	m_StockName;
};

