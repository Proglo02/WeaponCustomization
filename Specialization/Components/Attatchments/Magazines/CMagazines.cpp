#include <tgSystem.h>

#include "CMagazines.h"
#include "CMagazineSmall.h"
#include "CMagazineMedium.h"
#include "CMagazineBig.h"
#include "CMagazineQuickLoad.h"
#include "Specialization/CReadData.h"
#include "CStringParser.h"

#include <tgCFileSystem.h>
#include <tgMemoryDisable.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <tgMemoryEnable.h>

CMagazines::CMagazines(CWorld* pWorld)
: m_pWorld( pWorld )
, m_pMagazines( NULL )
, m_pMagazineComponents( NULL )
, m_NumMagazines( 0 )
{
	m_pMagazines.push_back(NULL);
	m_pMagazineComponents.push_back(NULL);
	m_MagazineNames.push_back("");
	m_NumMagazines++;

	AddMagazinesFromFile();

	//AddMagazine<CMagazineSmall>("Small");
	//AddMagazine<CMagazineMedium>("Medium");
	//AddMagazine<CMagazineBig>("Big");
	//AddMagazine<CMagazineQuickLoad>("Quick Load");
}

CMagazines::~CMagazines()
{
}

void CMagazines::RemoveMagazine(CMagazine* pMagazine)
{
	for (CMagazine* pMagazineComponent : m_pMagazineComponents)
	{
		if (pMagazineComponent == pMagazine)
		{
			for (CEntity* pEntity : m_pMagazines)
			{
				if (pEntity == pMagazineComponent->GetEntity())
				{
					m_pMagazines.erase(std::remove(m_pMagazines.begin(), m_pMagazines.end(), pEntity), m_pMagazines.end());
				}
			}

			for (tgCString name : m_MagazineNames)
			{
				if (name == pMagazineComponent->GetMagazineName())
				{
					m_MagazineNames.erase(std::remove(m_MagazineNames.begin(), m_MagazineNames.end(), name), m_MagazineNames.end());
				}
			}

			m_pMagazineComponents.erase(std::remove(m_pMagazineComponents.begin(), m_pMagazineComponents.end(), pMagazineComponent), m_pMagazineComponents.end());
			m_NumMagazines--;
		}
	}
}

void CMagazines::CreateMagazine(tgCString name)
{
	AddMagazine<CMagazine>(name);
}

void CMagazines::AddMagazinesFromFile()
{
	tgCString path = "data/saveInfo/savedMagazines/";

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
			AddMagazine<CMagazine>(fileName);
			CMagazine* pMagazine = m_pMagazineComponents.at(m_NumMagazines - 2);

			tgFloat MagazineSize = 0;
			tgFloat ReloadTime = 0;
			CReadData::ReadFloat("MagazineSize:", &MagazineSize);
			CReadData::ReadFloat("ReloadTime:", &ReloadTime);
			pMagazine->SetMagazineSize(MagazineSize);
			pMagazine->SetReloadTime(ReloadTime);

			tgFloat Weigth = 0;
			CReadData::ReadFloat("Weight:", &Weigth);
			pMagazine->SetWeight(Weigth);
		}
		CReadData::UnloadCurrentFile();
	}
}
