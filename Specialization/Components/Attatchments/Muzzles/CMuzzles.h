#pragma once

#include "Specialization/CWorld.h"
#include "Specialization/CEntity.h"
#include "Specialization/Components/Attatchments/Muzzles/CMuzzle.h"

#include <tgMemoryDisable.h>
#include <vector>
#include <tgMemoryEnable.h>

class CMuzzles
{
public:

	CMuzzles(CWorld* pWorld);
	~CMuzzles();

	CEntity*		GetMuzzle				(tgUInt32 index)	{ return m_pMuzzles[index]; }
	CMuzzle*		GetMuzzleComponent		(tgUInt32 index)	{ return m_pMuzzleComponents[index]; }

	std::vector<tgCString>		GetMuzzleNames		( void )	{ return m_MuzzleNames; }

	tgUInt32		GetNumMuzzles			(void)				{ return m_NumMuzzles; }

	template< typename T>
	void AddMuzzle(tgCString name, tgCString modelPath)
	{
		m_NumMuzzles++;

		CEntity* pMuzzle = m_pWorld->CreateEntity(tgCV3D(0.0f, 0.0f, 0.0f), name);
		CMuzzle* pMuzzleComponent = pMuzzle->AddComponent<T>();
		pMuzzleComponent->SetModelPath(modelPath);

		m_pMuzzles.insert(m_pMuzzles.begin() + (m_NumMuzzles - 2), pMuzzle);
		m_pMuzzleComponents.insert(m_pMuzzleComponents.begin() + (m_NumMuzzles - 2), pMuzzleComponent);
		m_MuzzleNames.insert(m_MuzzleNames.begin() + (m_NumMuzzles - 2), name);
	}

	void	RemoveMuzzle		(CMuzzle* pMuzzle);
	void	CreateMuzzle		(tgCString name, tgCString modelPath);
	void	AddMuzzlesFromFile();

private:

	CWorld* m_pWorld;

	std::vector<CEntity*> m_pMuzzles;
	std::vector<CMuzzle*> m_pMuzzleComponents;
	std::vector<tgCString> m_MuzzleNames;

	tgUInt32 m_NumMuzzles;

};

