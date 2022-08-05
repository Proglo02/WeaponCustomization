#include <tgSystem.h>

#include "CStocks.h"
#include "CTacticalStock.h"
#include "CRemovedStock.h"
#include "Specialization/CReadData.h"
#include "CStringParser.h"

#include <tgCFileSystem.h>
#include <tgMemoryDisable.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <tgMemoryEnable.h>

CStocks::CStocks(CWorld* pWorld)
: m_pWorld( pWorld )
, m_pStocks( NULL )
, m_pStockComponents( NULL )
, m_NumStocks( 0 )
{
	m_pStocks.push_back(NULL);
	m_pStockComponents.push_back(NULL);
	m_StockNames.push_back("");
	m_NumStocks++;

	AddStocksFromFile();

	/*AddStock<CTacticalStock>("Tactical Stock");
	AddStock<CRemovedStock>("Removed Stock");*/
}

CStocks::~CStocks()
{
}

void CStocks::RemoveStock(CStock* pStock)
{
	for (CStock* pStockComponent : m_pStockComponents)
	{
		if (pStockComponent == pStock)
		{
			for (CEntity* pEntity : m_pStocks)
			{
				if (pEntity == pStockComponent->GetEntity())
				{
					m_pStocks.erase(std::remove(m_pStocks.begin(), m_pStocks.end(), pEntity), m_pStocks.end());
				}
			}

			for (tgCString name : m_StockNames)
			{
				if (name == pStockComponent->GetStockName())
				{
					m_StockNames.erase(std::remove(m_StockNames.begin(), m_StockNames.end(), name), m_StockNames.end());
				}
			}

			m_pStockComponents.erase(std::remove(m_pStockComponents.begin(), m_pStockComponents.end(), pStockComponent), m_pStockComponents.end());
			m_NumStocks--;
		}
	}
}

void CStocks::CreateStock(tgCString name)
{
	AddStock<CStock>(name);
}

void CStocks::AddStocksFromFile()
{
	tgCString path = "data/saveInfo/savedStocks/";

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
			AddStock<CStock>(fileName);
			CStock* pStock = m_pStockComponents.at(m_NumStocks - 2);

			tgFloat VerticalRecoil = 0.0f;
			tgFloat HorizontalRecoil = 0.0f;
			tgFloat ShakeRecoil = 0.0f;
			CReadData::ReadFloat("VerticalRecoil:", &VerticalRecoil);
			CReadData::ReadFloat("HorizontalRecoil:", &HorizontalRecoil);
			CReadData::ReadFloat("ShakeRecoil:", &ShakeRecoil);
			pStock->SetVerticalRecoil(VerticalRecoil);
			pStock->SetHorizontalRecoil(HorizontalRecoil);
			pStock->SetShakeRecoil(ShakeRecoil);

			tgFloat Weight = 0.0f;
			CReadData::ReadFloat("Weight:", &Weight);
			pStock->SetWeight(Weight);
		}
		CReadData::UnloadCurrentFile();
	}
}
