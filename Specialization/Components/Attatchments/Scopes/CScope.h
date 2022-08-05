#pragma once

#include "Specialization/IComponent.h"
#include "Specialization/Components/CWeapon.h"

class CScope : public IComponent
{
public:

	CScope();
	~CScope();

	void		Load() override;

	void		ReplaceScopeModel();

	void		SetModelPath		(tgCString modelPath)		{ m_ScopeModelPath = modelPath; }
	void		SetModelScale		(tgCV3D scale)				{ m_ModelScale = scale; }
	void		SetModelRotation	(tgCV3D rotation)			{ m_ModelRotation = rotation; }
	void		SetScopePos			(tgCV3D Pos);

	void		SetMagnification	(tgUInt32 magnificatioon)	{ m_Magnification = magnificatioon; }

	void		SetWeight			(tgFloat whieght)			{ m_Weight = whieght; }

	void		SetScopeName		(tgCString name)			{ m_ScopeName = name; }

	CEntity*	GetEntity			(void)		{ return m_pEntity; }
	tgCModel*	GetModel			(void)		{ return m_pModel; }
	tgCString	GetModelPath		(void)		{ return m_ScopeModelPath; }
	tgCV3D		GetModelScale		(void)		{ return m_ModelScale; }
	tgCV3D		GetModelRotation	(void)		{ return m_ModelRotation; }

	tgUInt32	GetMagnification	(void)		{ return m_Magnification; }

	tgFloat		GetWeight			(void)		{ return m_Weight; }

	tgCString	GetScopeName		(void)		{ return m_ScopeName; }

protected:

	tgCModel*	m_pModel;

	tgUInt32	m_Magnification;

	tgFloat		m_Weight;

	tgCString	m_ScopeName;
	tgCString	m_ScopeModelPath;

	tgCV3D		m_ModelScale;
	tgCV3D		m_ModelRotation;
};

