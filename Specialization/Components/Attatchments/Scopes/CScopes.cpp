#include <tgSystem.h>

#include "CScopes.h"
#include "CScope_4X.h"
#include "CScope_8X.h"
#include "CScope_16X.h"
#include "Specialization/CReadData.h"
#include "CStringParser.h"

#include <tgCFileSystem.h>
#include <tgMemoryDisable.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <tgMemoryEnable.h>

CScopes::CScopes(CWorld* pWorld)
: m_pWorld( pWorld )
, m_pScopes( NULL )
, m_pScopeComponents ( NULL )
, m_NumScopes ( 0 )
{
	m_pScopes.push_back(NULL);
	m_pScopeComponents.push_back(NULL);
	m_ScopeNames.push_back("");
	m_NumScopes++;

	AddScopesFromFile();

	//AddScope<CScope_4X>("Scope-4X", "");
	//AddScope<CScope_8X>("Scope-8X", "");
	//AddScope<CScope_16X>("Scope-16X", "");
}

CScopes::~CScopes()
{
}

void CScopes::RemoveScope(CScope* pScope)
{
	for (CScope* pScopeComponent : m_pScopeComponents)
	{
		if (pScopeComponent == pScope)
		{
			for (CEntity* pEntity : m_pScopes)
			{
				if (pEntity == pScopeComponent->GetEntity())
				{
					m_pScopes.erase(std::remove(m_pScopes.begin(), m_pScopes.end(), pEntity), m_pScopes.end());
				}
			}

			for (tgCString name : m_ScopeNames)
			{
				if (name == pScopeComponent->GetScopeName())
				{
					m_ScopeNames.erase(std::remove(m_ScopeNames.begin(), m_ScopeNames.end(), name), m_ScopeNames.end());
				}
			}

			m_pScopeComponents.erase(std::remove(m_pScopeComponents.begin(), m_pScopeComponents.end(), pScopeComponent), m_pScopeComponents.end());
			m_NumScopes--;
		}
	}
}

void CScopes::CreateScope(tgCString name, tgCString modelPath)
{
	AddScope<CScope>(name, modelPath);
}

void CScopes::AddScopesFromFile()
{
	tgCString path = "data/saveInfo/savedScopes/";

	for (const auto& weaponFile : std::filesystem::directory_iterator(path.String()))
	{
		std::string fileInput = "";
		const tgChar* fileName = fileInput.c_str();

		std::ifstream file(weaponFile.path());

		std::getline(file, fileInput);
		fileName = fileInput.c_str();
		const tgCString& fullFilePath = path + fileName + ".ini";

		if (CReadData::LoadFile(fullFilePath))
		{
			tgCString ModelPath = "";
			CReadData::ReadString("ModelPath:", &ModelPath);

			AddScope<CScope>(fileName, ModelPath);
			CScope* pScope = m_pScopeComponents.at(m_NumScopes - 2);
			pScope->ReplaceScopeModel();

			tgFloat Magnification = 0.0f;
			tgFloat Weight = 0.0f;
			CReadData::ReadFloat("Magnification:", &Magnification);
			CReadData::ReadFloat("Weight:", &Weight);
			pScope->SetMagnification(Magnification);
			pScope->SetWeight(Weight);
		}
		CReadData::UnloadCurrentFile();
	}
}
