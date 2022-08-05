#pragma once

#include "Specialization/CEntity.h"
#include "Specialization/Components/CWeapon.h"

#include	<tgMemoryDisable.h>
#include	<typeinfo>
#include	<vector>
#include	<tgMemoryEnable.h>

class CWeapons
{
public:

	CWeapons(CWorld* pWorld, tgCTransform* pTransform);
	~CWeapons();

	CEntity*		GetWeapon				( tgUInt32 index )		{ return m_pWeapons[index]; }
	CWeapon*		GetWeaponComponent		( tgUInt32 index )		{ return m_pWeaponComponents[index]; }
	tgUInt32		GetNumWeapons			( void )				{ return m_NumWeapons; }

	std::vector<tgCString>	GetWeaponNames		( void )			{ return m_WeaponNames; }

	tgFloat			GetAvrageVerticalRecoil();
	tgFloat			GetAvrageHorizontalRecoil();
	tgFloat			GetAvrageShakeRecoil();
	tgFloat			GetAvrageRecovery();
	tgFloat			GetAvrageSpread();
	tgFloat			GetAvrageDamage();
	tgFloat			GetAvrageWeight();

	template< typename T>
	void AddWeapon(tgCString name, tgCString modelPath)
	{
		m_NumWeapons++;

		CEntity* pWeapon = m_pWorld->CreateEntity(tgCV3D(0.0f, 0.0f, 0.0f), name);
		pWeapon->GetTransform().GetMatrixLocal() = m_pTransform->GetMatrixLocal();
		CWeapon* pWeaponComponent = pWeapon->AddComponent<T>();
		pWeaponComponent->SetModelPath(modelPath);

		m_pWeapons.push_back(pWeapon);
		m_pWeaponComponents.push_back(pWeaponComponent);
		m_WeaponNames.push_back(name);
	}

	void RemoveWeapon		(CWeapon* pWeapon);
	void CreateWeapon		(CWeapon::EType WeaponType, tgCString Name, tgCString ModelPath);
	void AddWeaponsFromFile	();

private:

	CWorld* m_pWorld;

	tgCTransform* m_pTransform;

	std::vector<CEntity*>	m_pWeapons;
	std::vector<CWeapon*>	m_pWeaponComponents;
	std::vector<tgCString>	m_WeaponNames;

	tgUInt32 m_NumWeapons;

};

