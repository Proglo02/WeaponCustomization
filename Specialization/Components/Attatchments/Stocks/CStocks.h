#pragma once

#include "Specialization/CWorld.h"
#include "Specialization/CEntity.h"

#include <tgMemoryDisable.h>
#include <vector>
#include <tgMemoryEnable.h>

class CStock;

class CStocks
{
public:

	CStocks(CWorld* pWorld);
	~CStocks();

	CEntity*		GetStock				(tgUInt32 index)	{ return m_pStocks[index]; }
	CStock*			GetStockComponent		(tgUInt32 index)	{ return m_pStockComponents[index]; }

	std::vector<tgCString>		GetStockNames	(void)			{ return m_StockNames; }

	tgUInt32		GetNumStocks			(void)				{ return m_NumStocks; }

	template< typename T>
	void AddStock(tgCString name)
	{
		m_NumStocks++;

		CEntity* pStock = m_pWorld->CreateEntity(tgCV3D(0.0f, 0.0f, 0.0f), name);
		CStock* pStockComponent = pStock->AddComponent<T>();

		m_pStocks.insert(m_pStocks.begin() + (m_NumStocks - 2), pStock);
		m_pStockComponents.insert(m_pStockComponents.begin() + (m_NumStocks - 2), pStockComponent);
		m_StockNames.insert(m_StockNames.begin() + (m_NumStocks - 2), name);
	}

	void	RemoveStock		(CStock* pStock);
	void	CreateStock		(tgCString name);
	void	AddStocksFromFile();


private:

	CWorld* m_pWorld;

	std::vector<CEntity*>	m_pStocks;
	std::vector<CStock*>	m_pStockComponents;
	std::vector<tgCString>	m_StockNames;

	tgUInt32 m_NumStocks;

};

