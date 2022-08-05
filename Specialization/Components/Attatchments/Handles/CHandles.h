#pragma once

#include "Specialization/CWorld.h"
#include "Specialization/CEntity.h"
#include "Specialization/Components/Attatchments/Handles/CHandle.h"

#include <tgMemoryDisable.h>
#include <vector>
#include <tgMemoryEnable.h>

class CHandles
{
public:

	CHandles(CWorld* pWorld);
	~CHandles();

	CEntity*		GetHandle				(tgUInt32 index)	{ return m_pHandles[index]; }
	CHandle*		GetHandleComponent		(tgUInt32 index)	{ return m_pHandleComponents[index]; }

	std::vector<tgCString>	GetHandleNames	(void)				{ return m_HandleNames; }

	tgUInt32		GetNumHandles			(void)				{ return m_NumHandles; }

	template< typename T>
	void AddHandle(tgCString name)
	{
		m_NumHandles++;

		CEntity*	pHandle = m_pWorld->CreateEntity(tgCV3D(0.0f, 0.0f, 0.0f), name);
		CHandle*	pHandleComponent = pHandle->AddComponent<T>();

		m_pHandles.insert(m_pHandles.begin() + (m_NumHandles - 2), pHandle);
		m_pHandleComponents.insert(m_pHandleComponents.begin() + (m_NumHandles - 2), pHandleComponent);
		m_HandleNames.insert(m_HandleNames.begin() + (m_NumHandles - 2), name);

	}

	void	RemoveHandle	(CHandle* pHandle);
	void	CreateHandle	(tgCString name);
	void	AddHandlesFromFile();

private:

	CWorld* m_pWorld;

	std::vector<CEntity*> m_pHandles;
	std::vector<CHandle*> m_pHandleComponents;
	std::vector<tgCString> m_HandleNames;

	tgUInt32 m_NumHandles;

};

