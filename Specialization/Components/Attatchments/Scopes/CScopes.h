#pragma once

#include "Specialization/CWorld.h"
#include "Specialization/CEntity.h"
#include "Specialization/Components/Attatchments/Scopes/CScope.h"

#include <tgMemoryDisable.h>
#include <vector>
#include <tgMemoryEnable.h>

class CScopes
{
public:

	CScopes(CWorld* pWorld);
	~CScopes();

	CEntity*		GetScope			(tgUInt32 index)		{ return m_pScopes[index]; }
	CScope*			GetScopeComponent	(tgUInt32 index)		{ return m_pScopeComponents[index]; }

	std::vector<tgCString>	GetScopeNames	(void)				{ return m_ScopeNames; }

	tgUInt32		GetNumScopes		(void)					{ return m_NumScopes; }

	template< typename T>
	void AddScope(tgCString name, tgCString modelPath)
	{
		m_NumScopes++;

		CEntity* pScope = m_pWorld->CreateEntity(tgCV3D(0.0f, 0.0f, 0.0f), name);
		CScope* pScopeComponent = pScope->AddComponent<T>();
		pScopeComponent->SetModelPath(modelPath);

		m_pScopes.insert(m_pScopes.begin() + (m_NumScopes - 2), pScope);
		m_pScopeComponents.insert(m_pScopeComponents.begin() + (m_NumScopes - 2), pScopeComponent);
		m_ScopeNames.insert(m_ScopeNames.begin() + (m_NumScopes - 2), name);
	}

	void	RemoveScope		(CScope* pScope);
	void	CreateScope		(tgCString name, tgCString modelPath);

	void	AddScopesFromFile();

private:

	CWorld* m_pWorld;

	std::vector<CEntity*> m_pScopes;
	std::vector<CScope*> m_pScopeComponents;
	std::vector<tgCString> m_ScopeNames;

	tgUInt32 m_NumScopes;

};