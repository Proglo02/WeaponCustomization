#pragma once

#include "Specialization/CWorld.h"
#include "Specialization/CEntity.h"
#include "Specialization/Components/Attatchments/Magazines/CMagazine.h"

#include <tgMemoryDisable.h>
#include <vector>
#include <tgMemoryEnable.h>

class CMagazines
{
public:

	CMagazines(CWorld* pWorld);
	~CMagazines();

	CEntity*	GetMagazine				(tgUInt32 index)	{ return m_pMagazines[index]; }
	CMagazine*	GetMagazineComponent	(tgUInt32 index)	{ return m_pMagazineComponents[index]; }

	std::vector<tgCString>	GetMagazineNames	(void)		{ return m_MagazineNames; }

	tgUInt32	GetNumMagazines			(void)				{ return m_NumMagazines; }

	template< typename T>
	void AddMagazine(tgCString name)
	{
		m_NumMagazines++;

		CEntity* pMagazine = m_pWorld->CreateEntity(tgCV3D(0.0f, 0.0f, 0.0f), name);
		CMagazine* pMagazineComponent = pMagazine->AddComponent<T>();

		m_pMagazines.insert(m_pMagazines.begin() + (m_NumMagazines - 2), pMagazine);
		m_pMagazineComponents.insert(m_pMagazineComponents.begin() + (m_NumMagazines - 2), pMagazineComponent);
		m_MagazineNames.insert(m_MagazineNames.begin() + (m_NumMagazines - 2), name);

	}

	void	RemoveMagazine		(CMagazine* pMagazine);
	void	CreateMagazine		(tgCString name);
	void AddMagazinesFromFile();

private:

	CWorld* m_pWorld;

	std::vector<CEntity*> m_pMagazines;
	std::vector<CMagazine*> m_pMagazineComponents;
	std::vector<tgCString> m_MagazineNames;

	tgUInt32 m_NumMagazines;

};

