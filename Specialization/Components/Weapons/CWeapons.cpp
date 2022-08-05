#include <tgSystem.h>

#include "CWeapons.h"
#include "DefaultWeapons/CWAutomatic.h"
#include "DefaultWeapons/CWSemiAutomatic.h"
#include "DefaultWeapons/CWBoltAction.h"
#include "DefaultWeapons/CWSingleShot.h"
#include "AssultRifles/CAK_47.h"
#include "AssultRifles/CAR_15.h"
#include "AssultRifles/CM_16.h"
#include "Shotguns/CStoeger_M3500.h"
#include "Pistols/CGlock_18.h"
#include "SMGs/CMP5A4.h"
#include "Specialization/CReadData.h"
#include "CStringParser.h"

#include <tgCFileSystem.h>
#include <tgMemoryDisable.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <tgMemoryEnable.h>
#include <CApplication.cpp>

CWeapons::CWeapons(CWorld* pWorld, tgCTransform* pTransform)
: m_pWorld( pWorld )
, m_pTransform( pTransform )
, m_pWeapons( NULL )
, m_pWeaponComponents( NULL )
, m_WeaponNames( NULL )
, m_NumWeapons( 0 )
{

	AddWeaponsFromFile();
	//AddWeapon<CAK_47>("AK-47", "");
	//AddWeapon<CAR_15>("AR-15", "");
	//AddWeapon<CM_16>("M-16", "");
	//AddWeapon<CStoeger_M3500>("Stoeger-M3500", "");
	//AddWeapon<CGlock_18>("Glock-18", "");
	//AddWeapon<CMP5A4>("MP5A4", "");
}

CWeapons::~CWeapons()
{
}

tgFloat CWeapons::GetAvrageVerticalRecoil()
{
	tgFloat recoil = 0.0f;
	tgUInt32 numWeapons = 0;

	for (CWeapon* pWeapon : m_pWeaponComponents)
	{
		if (pWeapon)
		{
			recoil += pWeapon->GetDefaultRecoil().x;
			numWeapons++;
		}
	}

	if (numWeapons > 0)
		recoil /= numWeapons;

	return recoil;
}

tgFloat CWeapons::GetAvrageHorizontalRecoil()
{
	tgFloat recoil = 0.0f;
	tgUInt32 numWeapons = 0;

	for (CWeapon* pWeapon : m_pWeaponComponents)
	{
		if (pWeapon)
		{
			recoil += pWeapon->GetDefaultRecoil().y;
			numWeapons++;
		}
	}

	if (numWeapons > 0)
		recoil /= numWeapons;

	return recoil;
}

tgFloat CWeapons::GetAvrageShakeRecoil()
{
	tgFloat recoil = 0.0f;
	tgUInt32 numWeapons = 0;

	for (CWeapon* pWeapon : m_pWeaponComponents)
	{
		if (pWeapon)
		{
			recoil += pWeapon->GetDefaultRecoil().z;
			numWeapons++;
		}
	}

	if (numWeapons > 0)
		recoil /= numWeapons;

	return recoil;
}

tgFloat CWeapons::GetAvrageRecovery()
{
	tgFloat recovery = 0.0f;
	tgUInt32 numWeapons = 0;

	for (CWeapon* pWeapon : m_pWeaponComponents)
	{
		if (pWeapon)
		{
			recovery += pWeapon->GetDefaultRecovery();
			numWeapons++;
		}
	}

	if (numWeapons > 0)
		recovery /= numWeapons;

	return recovery;
}

tgFloat CWeapons::GetAvrageSpread()
{
	tgFloat spread = 0.0f;
	tgUInt32 numWeapons = 0;

	for (CWeapon* pWeapon : m_pWeaponComponents)
	{
		if (pWeapon)
		{
			spread += pWeapon->GetDefaultBulletSpread();
			numWeapons++;
		}
	}

	if (numWeapons > 0)
		spread /= numWeapons;

	return spread;
}

tgFloat CWeapons::GetAvrageDamage()
{
	tgFloat damage = 0.0f;
	tgUInt32 numWeapons = 0;

	for (CWeapon* pWeapon : m_pWeaponComponents)
	{
		if (pWeapon)
		{
			damage += pWeapon->GetDefaultDamage();
			numWeapons++;
		}
	}

	if (numWeapons > 0)
		damage /= numWeapons;

	return damage;
}

tgFloat CWeapons::GetAvrageWeight()
{
	tgFloat weight = 0.0f;
	tgUInt32 numWeapons = 0;

	for (CWeapon* pWeapon : m_pWeaponComponents)
	{
		if (pWeapon)
		{
			weight += pWeapon->GetDefaultWeight();
			numWeapons++;
		}
	}

	if (numWeapons > 0)
		weight /= numWeapons;

	return weight;
}

void CWeapons::RemoveWeapon(CWeapon* pWeapon)
{
	for (CWeapon* pWeaponComponent : m_pWeaponComponents)
	{
		if (pWeaponComponent == pWeapon)
		{
			for (CEntity* pEntity : m_pWeapons)
			{
				if (pEntity == pWeaponComponent->GetEntity())
				{
					tgUInt32 index = std::find(m_pWeapons.begin(), m_pWeapons.end(), pEntity) - m_pWeapons.begin();
					m_pWeapons.erase(m_pWeapons.begin() + index);
				}
			}

			for (tgCString name : m_WeaponNames)
			{
				if (name == pWeaponComponent->GetWeaponName())
				{
					tgUInt32 index = std::find(m_WeaponNames.begin(), m_WeaponNames.end(), name) - m_WeaponNames.begin();
					m_WeaponNames.erase(m_WeaponNames.begin() + index);
				}
			}

			tgUInt32 index = std::find(m_pWeaponComponents.begin(), m_pWeaponComponents.end(), pWeaponComponent) - m_pWeaponComponents.begin();
			m_pWeaponComponents.erase(m_pWeaponComponents.begin() + index);
			m_NumWeapons--;
		}
	}
}

void CWeapons::CreateWeapon(CWeapon::EType WeaponType, tgCString Name, tgCString ModelPath)
{
	switch (WeaponType)
	{
	case CWeapon::TYPE_SINGLESHOT:		{ AddWeapon<CWSingleShot>(Name, ModelPath); } break;
	case CWeapon::TYPE_BOLTACTION:		{ AddWeapon<CWBoltAction>(Name, ModelPath); } break;
	case CWeapon::TYPE_SEMIAUTOMATIC:	{ AddWeapon<CWSemiAutomatic>(Name, ModelPath); } break;
	case CWeapon::TYPE_AUTOMATIC:		{ AddWeapon<CWAutomatic>(Name, ModelPath); } break;
	}
}

void CWeapons::AddWeaponsFromFile()
{
	tgCString path = "data/saveInfo/savedWeapons/";

	for (const auto& weaponFile : std::filesystem::directory_iterator(path.String()))
	{
		std::string fileInput = "";
		const tgChar* fileName = fileInput.c_str();

		std::ifstream file(weaponFile.path());

		std::getline(file, fileInput);
		fileName = fileInput.c_str();
		const tgCString& fullFilePath = path + fileName + ".ini";

		tgCString TypeName = "";

		if (CReadData::LoadFile(fullFilePath))
		{
			CReadData::ReadString("Type:", &TypeName);

			tgCString ModelPath = "";
			CReadData::ReadString("ModelPath:", &ModelPath);

			if (TypeName == "Single Shot")
				AddWeapon<CWSingleShot>(fileName, ModelPath);
			if (TypeName == "Bolt Action")
				AddWeapon<CWBoltAction>(fileName, ModelPath);
			if (TypeName == "Semiautomatic")
				AddWeapon<CWSemiAutomatic>(fileName, ModelPath);
			if (TypeName == "Automatic")
				AddWeapon<CWAutomatic>(fileName, ModelPath);

			tgCV3D ModelOffset = tgCV3D(0.0f, 0.0f, 0.0f);
			CReadData::ReadVector3("ModelOffset:", &ModelOffset);
			m_pWeaponComponents.back()->SetModelOffset(ModelOffset);
			m_pWeaponComponents.back()->ReplaceWeaponModel();

			tgCV3D ModelRotation = tgCV3D(0.0f, 0.0f, 0.0f);
			CReadData::ReadVector3("ModelRotation:", &ModelRotation);
			m_pWeaponComponents.back()->SetModelRotation(ModelRotation);
			m_pWeaponComponents.back()->ReplaceWeaponModel();

			tgCV3D ScopeOffset = tgCV3D(0.0f, 0.0f, 0.0f);
			CReadData::ReadVector3("ScopeOffset:", &ScopeOffset);
			m_pWeaponComponents.back()->SetScopeOffset(ScopeOffset);

			tgCV3D MuzzleOffset = tgCV3D(0.0f, 0.0f, 0.0f);
			CReadData::ReadVector3("MuzzleOffset:", &MuzzleOffset);
			m_pWeaponComponents.back()->SetMuzzleOffset(MuzzleOffset);

			tgCV3D Recoil = tgCV3D(0.0f, 0.0f, 0.0f);
			tgFloat Snappiness = 0.0f;
			tgFloat RecoverySpeed = 0.0f;
			CReadData::ReadVector3("Recoil:", &Recoil);
			CReadData::ReadFloat("Snappiness:", &Snappiness);
			CReadData::ReadFloat("RecoverySpeed:", &RecoverySpeed);
			m_pWeaponComponents.back()->SetRecoil(Recoil, Snappiness, RecoverySpeed);

			tgCV3D ScopedRecoil = tgCV3D(0.0f, 0.0f, 0.0f);
			tgFloat ScopedSnappiness = 0.0f;
			tgFloat ScopedRecoverySpeed = 0.0f;
			CReadData::ReadVector3("ScopedRecoil:", &ScopedRecoil);
			CReadData::ReadFloat("ScopedSnappiness:", &ScopedSnappiness);
			CReadData::ReadFloat("ScopedRecoverySpeed:", &ScopedRecoverySpeed);
			m_pWeaponComponents.back()->SetScopedRecoil(ScopedRecoil, ScopedSnappiness, ScopedRecoverySpeed);

			tgFloat BulletSpread = 0.0f;
			tgFloat ScopedBulletSpread = 0.0f;
			CReadData::ReadFloat("BulletSpread:", &BulletSpread);
			CReadData::ReadFloat("ScopedBulletSpread:", &ScopedBulletSpread);
			m_pWeaponComponents.back()->SetDefaultBulletSpread(BulletSpread);
			m_pWeaponComponents.back()->SetDefaultScopedBulletSpread(ScopedBulletSpread);

			tgFloat TimeToReload = 0.0f;
			CReadData::ReadFloat("TimeToReload:", &TimeToReload);
			m_pWeaponComponents.back()->SetDefaultTimeToReload(TimeToReload);

			if (TypeName == "Automatic")
			{
				CWAutomatic* pAutomatic = static_cast<CWAutomatic*>(m_pWeaponComponents.back());
				tgFloat FireRate = 0.0f;
				CReadData::ReadFloat("FireRate:", &FireRate);
				pAutomatic->SetFireRate(FireRate);
			}

			if (TypeName == "Bolt Action")
			{
				CWBoltAction* pBoltAction = static_cast<CWBoltAction*>(m_pWeaponComponents.back());
				tgFloat TimeToChamber = 0.0f;
				CReadData::ReadFloat("TimeToChamber:", &TimeToChamber);
				pBoltAction->SetTimeToChamber(TimeToChamber);
			}

			tgUInt32 Damage = 0;
			tgUInt32 MaxAmmo = 0;
			tgUInt32 BulletCount = 0;
			CReadData::ReadInt("Damage:", &Damage);
			CReadData::ReadInt("MaxAmmo:", &MaxAmmo);
			CReadData::ReadInt("BulletCount:", &BulletCount);
			m_pWeaponComponents.back()->SetDefaultDamage(Damage);
			m_pWeaponComponents.back()->SetDefaultMaxAmmo(MaxAmmo);
			m_pWeaponComponents.back()->SetMaxAmmo(MaxAmmo);
			m_pWeaponComponents.back()->SetAmmo(MaxAmmo);
			m_pWeaponComponents.back()->SetBulletCount(BulletCount);

			tgFloat Weight = 0.0f;
			CReadData::ReadFloat("Weight:", &Weight);
			m_pWeaponComponents.back()->SetDefaultWeight(Weight);

			tgBool HasMuzzle = false;
			tgBool HasHandle = false;
			tgBool HasScope = false;
			tgBool HasMagazine = false;
			tgBool HasStock = false;
			tgBool HasAmmo = false;
			CReadData::ReadBool("HasMuzzle:", &HasMuzzle);
			CReadData::ReadBool("HasHandle:", &HasHandle);
			CReadData::ReadBool("HasScope:", &HasScope);
			CReadData::ReadBool("HasMagazine:", &HasMagazine);
			CReadData::ReadBool("HasStock:", &HasStock);
			CReadData::ReadBool("HasAmmo:", &HasAmmo);
			m_pWeaponComponents.back()->SetComponents(HasMuzzle, HasHandle, HasScope, HasMagazine, HasStock, HasAmmo);
		}
		CReadData::UnloadCurrentFile();
	}
}
