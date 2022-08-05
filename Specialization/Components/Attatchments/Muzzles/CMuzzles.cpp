#include <tgSystem.h>

#include "CMuzzles.h"
#include "CCompensator.h"
#include "CAmplifier.h"
#include "CSuppressor.h"
#include "Specialization/CReadData.h"
#include "CStringParser.h"

#include <tgCFileSystem.h>
#include <tgMemoryDisable.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <tgMemoryEnable.h>

CMuzzles::CMuzzles(CWorld* pWorld)
: m_pWorld( pWorld )
, m_pMuzzles( NULL )
, m_pMuzzleComponents( NULL )
, m_MuzzleNames( NULL )
, m_NumMuzzles( 0 )
{
	m_pMuzzles.push_back(NULL);
	m_pMuzzleComponents.push_back(NULL);
	m_MuzzleNames.push_back("");
	m_NumMuzzles++;

	AddMuzzlesFromFile();

	/*AddMuzzle<CCompensator>("Compensator", "");
	AddMuzzle<CAmplifier>("Amplifier", "");
	AddMuzzle<CSuppressor>("Suppressor", "");*/
}

CMuzzles::~CMuzzles()
{
}

void CMuzzles::RemoveMuzzle(CMuzzle* pMuzzle)
{
	for (CMuzzle* pMuzzleComponent : m_pMuzzleComponents)
	{
		if (pMuzzleComponent == pMuzzle)
		{
			for (CEntity* pEntity : m_pMuzzles)
			{
				if (pEntity == pMuzzleComponent->GetEntity())
				{
					m_pMuzzles.erase(std::remove(m_pMuzzles.begin(), m_pMuzzles.end(), pEntity), m_pMuzzles.end());
				}
			}

			for (tgCString name : m_MuzzleNames)
			{
				if (name == pMuzzleComponent->GetMuzzleName())
				{
					m_MuzzleNames.erase(std::remove(m_MuzzleNames.begin(), m_MuzzleNames.end(), name), m_MuzzleNames.end());
				}
			}

			m_pMuzzleComponents.erase(std::remove(m_pMuzzleComponents.begin(), m_pMuzzleComponents.end(), pMuzzleComponent), m_pMuzzleComponents.end());
			m_NumMuzzles--;
		}
	}
}

void CMuzzles::CreateMuzzle(tgCString name, tgCString modelPath)
{
	AddMuzzle<CMuzzle>(name, modelPath);
}

void CMuzzles::AddMuzzlesFromFile()
{
	tgCString path = "data/saveInfo/savedMuzzles/";

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

			AddMuzzle<CMuzzle>(fileName, ModelPath);
			CMuzzle* pMuzzle = m_pMuzzleComponents.at(m_NumMuzzles - 2);
			pMuzzle->ReplaceMuzzleModel();

			tgFloat VerticalRecoil = 0.0f;
			tgFloat HorizontalRecoil = 0.0f;
			tgFloat ShakeRecoil = 0.0f;
			CReadData::ReadFloat("VerticalRecoil:", &VerticalRecoil);
			CReadData::ReadFloat("HorizontalRecoil:", &HorizontalRecoil);
			CReadData::ReadFloat("ShakeRecoil:", &ShakeRecoil);
			pMuzzle->SetVerticalRecoil(VerticalRecoil);
			pMuzzle->SetHorizontalRecoil(HorizontalRecoil);
			pMuzzle->SetShakeRecoil(ShakeRecoil);

			tgFloat BulletSpread = 0.0f;
			tgFloat Damage = 0;
			CReadData::ReadFloat("BulletSpread:", &BulletSpread);
			CReadData::ReadFloat("Damage:", &Damage);
			pMuzzle->SetSpread(BulletSpread);
			pMuzzle->SetDamage(Damage);
		}
		CReadData::UnloadCurrentFile();
	}
}
