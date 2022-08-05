#pragma once

#include "Specialization/CWorld.h"
#include "Specialization/CEntity.h"
#include "Specialization/Components/Ammos/CAmmo.h"

class CAmmos
{
public:

	CAmmos(CWorld* pWorld);

	CEntity* GetAmmo			(tgUInt32 index)		{ return m_pAmmos[index]; }
	CAmmo* GetAmmoComponent		(tgUInt32 index)		{ return m_pAmmoComponents[index]; }

	std::vector<tgCString>	GetAmmoName		(void)		{ return m_AmmoNames; }

	tgUInt32				GetNumAmmo		(void)		{ return m_NumAmmo; }

	template< typename T>
	void AddAmmo(tgCString name)
	{
		m_NumAmmo++;

		CEntity* pAmmo = m_pWorld->CreateEntity(tgCV3D(0.0f, 0.0f, 0.0f), name);
		CAmmo* pAmmoComponent = pAmmo->AddComponent<T>();
		pAmmoComponent->SetAmmoName(name);

		m_pAmmos.insert(m_pAmmos.begin() + (m_NumAmmo - 2), pAmmo);
		m_pAmmoComponents.insert(m_pAmmoComponents.begin() + (m_NumAmmo - 2), pAmmoComponent);
		m_AmmoNames.insert(m_AmmoNames.begin() + (m_NumAmmo - 2), name);

	}

	void	RemoveAmmo		(CAmmo* pAmmo);
	void	CreateAmmo		(tgCString name);
	void	AddAmmosFromFile();

private:

	CWorld* m_pWorld;

	std::vector<CEntity*> m_pAmmos;
	std::vector<CAmmo*> m_pAmmoComponents;
	std::vector<tgCString> m_AmmoNames;

	tgUInt32 m_NumAmmo;

};

