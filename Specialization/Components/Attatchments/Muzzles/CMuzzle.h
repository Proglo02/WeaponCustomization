#pragma once

#include "Specialization/IComponent.h"
#include "Specialization/Components/CWeapon.h"

class CMuzzle : public IComponent
{
public:

	CMuzzle();
	~CMuzzle();

	void		Load() override;

	void		ReplaceMuzzleModel();

	void		SetModelPath			(tgCString modelPath)	{ m_MuzzleModelPath = modelPath; }
	void		SetModelScale			(tgCV3D scale)			{ m_ModelScale = scale; }
	void		SetModelRotation		(tgCV3D rotation)		{ m_ModelRotation = rotation; }
	void		SetMuzzlePos			(tgCV3D Pos);

	void		SetVerticalRecoil	(tgFloat recoil)		{ m_VerticalRecoil = recoil; }
	void		SetHorizontalRecoil	(tgFloat recoil)		{ m_HorizontalRecoil = recoil; }
	void		SetShakeRecoil		(tgFloat recoil)		{ m_ShakeRecoil = recoil; }
	void		SetSpread			(tgFloat spread)		{ m_Spread = spread; }
	void		SetDamage			(tgFloat damage)		{ m_Damage = damage; }

	void		SetMuzzleName		(tgCString name)		{ m_MuzzleName = name; }

	CEntity*	GetEntity			(void)		{ return m_pEntity; }
	tgCModel*	GetModel			(void)		{ return m_pModel; }
	tgCString	GetModelPath		(void)		{ return m_MuzzleModelPath; }
	tgCV3D		GetModelScale		(void)		{ return m_ModelScale; }
	tgCV3D		GetModelRotation	(void)		{ return m_ModelRotation; }

	tgFloat		GetVerticalRecoil	(void)		{ return m_VerticalRecoil; }
	tgFloat		GetHorizontalRecoil	(void)		{ return m_HorizontalRecoil; }
	tgFloat		GetShakeRecoil		(void)		{ return m_ShakeRecoil; }
	tgFloat		GetSpread			(void)		{ return m_Spread; }
	tgFloat		GetDamage			(void)		{ return m_Damage; }

	tgCString	GetMuzzleName		(void)		{ return m_MuzzleName; }

protected:

	tgCModel*	m_pModel;

	tgCV3D		m_Pos;

	tgFloat		m_VerticalRecoil;
	tgFloat		m_HorizontalRecoil;
	tgFloat		m_ShakeRecoil;
	tgFloat		m_Spread;
	tgFloat		m_Damage;

	tgCString	m_MuzzleName;
	tgCString	m_MuzzleModelPath;

	tgCV3D		m_ModelScale;
	tgCV3D		m_ModelRotation;
};