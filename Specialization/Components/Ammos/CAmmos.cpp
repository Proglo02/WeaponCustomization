#include <tgSystem.h>

#include "CAmmos.h"
#include "Specialization/CReadData.h"
#include "CStringParser.h"

#include <tgCFileSystem.h>
#include <tgMemoryDisable.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <tgMemoryEnable.h>

CAmmos::CAmmos(CWorld* pWorld)
: m_pWorld( pWorld )
, m_pAmmos( NULL )
, m_pAmmoComponents( NULL )
, m_AmmoNames( NULL )
, m_NumAmmo( 0 )
{
	m_pAmmos.push_back(NULL);
	m_pAmmoComponents.push_back(NULL);
	m_AmmoNames.push_back("");
	m_NumAmmo++;

	AddAmmosFromFile();
}

void CAmmos::RemoveAmmo(CAmmo* pAmmo)
{
	for (CAmmo* pAmmoComponent : m_pAmmoComponents)
	{
		if (pAmmoComponent == pAmmo)
		{
			for (CEntity* pEntity : m_pAmmos)
			{
				if (pEntity == pAmmoComponent->GetEntity())
				{
					m_pAmmos.erase(std::remove(m_pAmmos.begin(), m_pAmmos.end(), pEntity), m_pAmmos.end());
				}
			}

			for (tgCString name : m_AmmoNames)
			{
				if (name == pAmmoComponent->GetAmmoName())
				{
					m_AmmoNames.erase(std::remove(m_AmmoNames.begin(), m_AmmoNames.end(), name), m_AmmoNames.end());
				}
			}

			m_pAmmoComponents.erase(std::remove(m_pAmmoComponents.begin(), m_pAmmoComponents.end(), pAmmoComponent), m_pAmmoComponents.end());
			m_NumAmmo--;
		}
	}
}

void CAmmos::CreateAmmo(tgCString name)
{
	AddAmmo<CAmmo>(name);
}

void CAmmos::AddAmmosFromFile()
{
	tgCString path = "data/saveInfo/savedAmmo/";

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
			AddAmmo<CAmmo>(fileName);
			CAmmo* pAmmo = m_pAmmoComponents.at(m_NumAmmo - 2);

			tgBool HasExplosion = false;
			tgBool HasFire = false;
			CReadData::ReadBool("HasExplosion:", &HasExplosion);
			CReadData::ReadBool("HasFire:", &HasFire);
			pAmmo->SetHasExplosion(HasExplosion);
			pAmmo->SetHasFire(HasFire);

			tgUInt32 ExplosionDamage = 0;
			tgUInt32 FireDamage = 0;
			CReadData::ReadInt("ExplosionDamage:", &ExplosionDamage);
			CReadData::ReadInt("FireDamage:", &FireDamage);
			pAmmo->SetExplosionDamage(ExplosionDamage);
			pAmmo->SetFireDamge(FireDamage);

			tgFloat ExplosionRadius = 0.0f;
			tgFloat FireDuration = 0.0f;
			tgFloat TravelSpeed = 100.0f;
			CReadData::ReadFloat("ExplosionRadius:", &ExplosionRadius);
			CReadData::ReadFloat("FireDuration:", &FireDuration);
			CReadData::ReadFloat("TravelSpeed:", &TravelSpeed);
			pAmmo->SetExplosionRadius(ExplosionRadius);
			pAmmo->SetFireDuration(FireDuration);
			pAmmo->SetTravelSpeed(TravelSpeed);
		}
		CReadData::UnloadCurrentFile();
	}
}
