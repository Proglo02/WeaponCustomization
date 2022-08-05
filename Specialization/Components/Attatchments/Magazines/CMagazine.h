#pragma once

#include "Specialization/IComponent.h"
#include "Specialization/Components/CWeapon.h"

class CMagazine : public IComponent
{
public:

	CMagazine();
	~CMagazine();

	void Load() override;

	void		SetMagazineSize		(tgFloat size)		{ m_MagazineSize = size; }
	void		SetReloadTime		(tgFloat time)		{ m_RealoadTime = time; }

	void		SetWeight			(tgFloat whieght)	{ m_Weight = whieght; }

	void		SetMagazineName		(tgCString name)	{ m_MagazineName = name; }

	CEntity*	GetEntity			(void)				{ return m_pEntity; }

	tgFloat		GetMagazineSize		(void)				{ return m_MagazineSize; }
	tgFloat		GetReloadTime		(void)				{ return m_RealoadTime; }

	tgFloat		GetWeight			(void)				{ return m_Weight; }

	tgCString	GetMagazineName		(void)				{ return m_MagazineName; }

protected:

	tgFloat m_MagazineSize;
	tgFloat m_RealoadTime;

	tgFloat m_Weight;

	tgCString m_MagazineName;
};

