#include <tgSystem.h>

#include "CHandles.h"
#include "CVerticalGrip.h"
#include "CHorizontalGrip.h"
#include "CHalfGrip.h"
#include "Specialization/CReadData.h"
#include "CStringParser.h"

#include <tgCFileSystem.h>
#include <tgMemoryDisable.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <tgMemoryEnable.h>

CHandles::CHandles(CWorld* pWorld)
: m_pWorld( pWorld )
, m_pHandles( NULL )
, m_pHandleComponents( NULL )
, m_NumHandles( 0 )
{
	m_pHandles.push_back(NULL);
	m_pHandleComponents.push_back(NULL);
	m_HandleNames.push_back("");
	m_NumHandles++;

	AddHandlesFromFile();

	/*AddHandle<CVerticalGrip>("Vertical Grip");
	AddHandle<CHorizontalGrip>("Horizontal Grip");
	AddHandle<CHalfGrip>("Half Grip");*/

}

CHandles::~CHandles()
{
}

void CHandles::RemoveHandle(CHandle* pHandle)
{
	for (CHandle* pHandleComponent : m_pHandleComponents)
	{
		if (pHandleComponent == pHandle)
		{
			for (CEntity* pEntity : m_pHandles)
			{
				if (pEntity == pHandleComponent->GetEntity())
				{
					m_pHandles.erase(std::remove(m_pHandles.begin(), m_pHandles.end(), pEntity), m_pHandles.end());
				}
			}

			for (tgCString name : m_HandleNames)
			{
				if (name == pHandleComponent->GetHandleName())
				{
					m_HandleNames.erase(std::remove(m_HandleNames.begin(), m_HandleNames.end(), name), m_HandleNames.end());
				}
			}

			m_pHandleComponents.erase(std::remove(m_pHandleComponents.begin(), m_pHandleComponents.end(), pHandleComponent), m_pHandleComponents.end());
			m_NumHandles--;
		}
	}
}

void CHandles::CreateHandle(tgCString name)
{
	AddHandle<CHandle>(name);
}

void CHandles::AddHandlesFromFile()
{
	tgCString path = "data/saveInfo/savedHandles/";

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
			AddHandle<CHandle>(fileName);
			CHandle* pHandle = m_pHandleComponents.at(m_NumHandles - 2);

			tgFloat VerticalRecoil = 0;
			tgFloat HorizontalRecoil = 0;
			tgFloat ShakeRecoil = 0;
			CReadData::ReadFloat("VerticalRecoil:", &VerticalRecoil);
			CReadData::ReadFloat("HorizontalRecoil:", &HorizontalRecoil);
			CReadData::ReadFloat("ShakeRecoil:", &ShakeRecoil);
			pHandle->SetVerticalRecoil(VerticalRecoil);
			pHandle->SetHorizontalRecoil(HorizontalRecoil);
			pHandle->SetShakeRecoil(ShakeRecoil);

			tgFloat Recovery = 0;
			tgFloat Weigth = 0;
			CReadData::ReadFloat("Recovery:", &Recovery);
			CReadData::ReadFloat("Weigth:", &Weigth);
			pHandle->SetRecovery(Recovery);
			pHandle->SetWeight(Weigth);
		}
		CReadData::UnloadCurrentFile();
	}
}
