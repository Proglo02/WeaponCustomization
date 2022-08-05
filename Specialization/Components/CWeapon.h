#pragma once
#include <tgSystem.h>

#include "Specialization/IComponent.h"

#include <tgCV3D.h>
#include <Specialization/Components/Attatchments/Muzzles/CMuzzle.h>
#include <Specialization/Components/Attatchments/Handles/CHandle.h>
#include <Specialization/Components/Attatchments/Scopes/CScope.h>
#include <Specialization/Components/Attatchments/Magazines/CMagazine.h>
#include <Specialization/Components/Attatchments/Stocks/CStock.h>

class CPlayer;

class CMuzzle;
class CHandle;
class CScope;
class CMagazine;
class CStock;
class CAmmo;

class CWeapon : public IComponent
{
public:

	CWeapon(void);
	~CWeapon(void);

	void Load() override;

	void Update( tgFloat DeltaTime ) override;

	virtual void Shoot();
	virtual void Reload();

	virtual tgCV2D SetQuadSize();
	virtual tgCV3D SetQuadPos();

	void SpawnBullet();

	void SetRecoil			(tgCV3D Recoil, tgFloat Snappiness, tgFloat ReturnSpeed);
	void SetScopedRecoil	(tgCV3D ScopedRecoil, tgFloat ScopedSnappiness, tgFloat ScopedReturnSpeed);
	void SetComponents		(tgBool muzzle, tgBool handle, tgBool scope, tgBool magazine, tgBool stock, tgBool ammo);
	void ReplaceWeaponModel	();

	void ZoomIn();
	void ZoomOut();
	void Recoil();

	void		SetModelPath			(tgCString modelPath)			{ m_WeaponModelPath = modelPath; }
	void		SetModelOffset			(tgCV3D offset)					{ m_WeaponModelOffset = offset; }
	void		SetModelRotation		(tgCV3D rotation)				{ m_WeaponModelRotation = rotation; }
	void		SetModelScale			(tgCV3D scale)					{ m_WeaponModelScale = scale; }
	void		SetWeaponName			(tgCString name)				{ m_WeaponName = name; }

	void		SetTriggerHeld			(tgBool triggerState)			{ m_TriggerHeld = triggerState; }
	void		SetReloading			(tgBool reloadState)			{ m_IsReloading = reloadState; }
	void		SetZoomFov				(tgFloat fov)					{ m_ZoomFov = fov; }

	void		SetMaxAmmo				(tgUInt32 maxAmmo)				{ m_MaxAmmo = maxAmmo; }
	void		SetDefaultMaxAmmo		(tgUInt32 maxAmmo)				{ m_DefaultMaxAmmo = maxAmmo; }
	void		SetAmmo					(tgUInt32 ammo)					{ m_Ammo = ammo; }
	void		SetBulletCount			(tgUInt32 count)				{ m_BulletCount = count; }

	void		SetDefaultTimeToReload	(tgFloat time)					{ m_DefaultTimeToReload = time; }

	void		SetDefaultRecoil		(tgCV3D recoil)					{ m_DefaultRecoil = recoil; }
	void		SetDefaultScopedRecoil	(tgCV3D recoil)					{ m_DefaultScopedRecoil = recoil; }

	void		SetDefaultBulletSpread			(tgFloat spread)		{ m_DefaultBulletSpread = spread; }
	void		SetDefaultScopedBulletSpread	(tgFloat spread)		{ m_DefaultScopedBulletSpread = spread; }
	void		SetBulletSpread					(tgFloat spread)		{ m_BulletSpread = spread; }

	void		SetDefaultDamage		(tgUInt32 damage)				{ m_DefaultDamage = damage; }

	void		SetDefaultWeight		(tgFloat wheight)				{ m_DefaultWeight = wheight; }

	void		SetScope				(CScope* pScope)				{ m_pScope = pScope; }
	void		SetScopeIndex			(tgUInt32 scopeIndex)			{ m_ScopeIndex = scopeIndex; }
	void		SetScopeOffset			(tgCV3D offset)					{ m_ScopeOffset = offset; }
	void		SetScopeRotation		(tgCV3D rotation)				{ m_ScopeRotation = rotation; }

	void		SetMagazine				(CMagazine* pMagazine)			{ m_pMagazine = pMagazine; }
	void		SetMagazineIndex		(tgUInt32 magazineIndex)		{ m_MagazineIndex = magazineIndex; }

	void		SetHandle				(CHandle* pHandle)				{ m_pHandle = pHandle; }
	void		SetHandleIndex			(tgUInt32 handleIndex)			{ m_HandleIndex = handleIndex; }

	void		SetMuzzle				(CMuzzle* pMuzzle)				{ m_pMuzzle = pMuzzle; }
	void		SetMuzzleIndex			(tgUInt32 muzzleIndex)			{ m_MuzzleIndex = muzzleIndex; }
	void		SetMuzzleOffset			(tgCV3D offset)					{ m_MuzzleOffset = offset; }
	void		SetMuzzleRotation		(tgCV3D rotation)				{ m_MuzzleRotation = rotation; }

	void		SetAmmoComponent		(CAmmo* pAmmo)					{ m_pAmmo = pAmmo; }
	void		SetAmmoComponentIndex	(tgUInt32 ammoIndex)			{ m_AmmoIndex = ammoIndex; }

	void		SetStock				(CStock* pStock)				{ m_pStock = pStock; }
	void		SetStockIndex			(tgUInt32 stockIndex)			{ m_StockIndex = stockIndex; }

	CEntity*		GetEntity			(void)						{ return m_pEntity; }

	tgCModel*		GetModel			(void)						{ return m_pModel; }
	tgCString		GetModelPath		(void)						{ return m_WeaponModelPath; }
	tgCV3D			GetCurrentRotation	(void)						{ return m_CurrentRotation; }
	tgCV3D			GetModelOffset		(void)						{ return m_WeaponModelOffset; }
	tgCV3D			GetModelRotation	(void)						{ return m_WeaponModelRotation; }
	tgCV3D			GetModelScale		(void)						{ return m_WeaponModelScale; }
	tgUInt32		GetType				(void)						{ return m_Type; }

	tgBool			GetTriggerHeld			(void)					{ return m_TriggerHeld; }
	tgBool			GetIsReloading			(void)					{ return m_IsReloading; }
	tgFloat			GetDefaultTimeToReload	(void)					{ return m_DefaultTimeToReload; }

	tgUInt32		GetAmmo				(void)						{ return m_Ammo; }
	tgUInt32		GetMaxAmmo			(void)						{ return m_MaxAmmo; }
	tgUInt32		GetDefaultMaxAmmo	(void)						{ return m_DefaultMaxAmmo; }
	tgUInt32		GetBulletCount		(void)						{ return m_BulletCount; }

	tgBool			GetHasScope			(void)						{ return m_HasScope; }
	tgUInt32		GetScopeIndex		(void)						{ return m_ScopeIndex; }
	CScope*			GetScope			(void)						{ return m_pScope; }
	tgCV3D			GetScopeOffset		(void)						{ return m_ScopeOffset; }
	tgCV3D			GetScopeRotation	(void)						{ return m_ScopeRotation; }

	tgBool			GetHasMagazine		(void)						{ return m_HasMagazine; }
	tgUInt32		GetMagazineIndex	(void)						{ return m_MagazineIndex; }
	CMagazine*		GetMagazine			(void)						{ return m_pMagazine; }

	tgBool			GetHasHandle		(void)						{ return m_HasHandle; }
	tgUInt32		GetHandleIndex		(void)						{ return m_HandleIndex; }
	CHandle*		GetHandle			(void)						{ return m_pHandle; }

	tgBool			GetHasMuzzle		(void)						{ return m_HasMuzzle; }
	tgUInt32		GetMuzzleIndex		(void)						{ return m_MuzzleIndex; }
	CMuzzle*		GetMuzzle			(void)						{ return m_pMuzzle; }
	tgCV3D			GetMuzzleOffset		(void)						{ return m_MuzzleOffset; }
	tgCV3D			GetMuzzleRotation	(void)						{ return m_MuzzleRotation; }

	tgBool			GetHasStock			(void)						{ return m_HasStock; }
	tgUInt32		GetStockIndex		(void)						{ return m_StockIndex; }
	CStock*			GetStock			(void)						{ return m_pStock; }

	tgBool			GetHasAmmoComponent		(void)					{ return m_HasAmmoComponent; }
	tgUInt32		GetAmmoComponentIndex	(void)					{ return m_AmmoIndex; }
	CAmmo*			GetAmmoComponent		(void)					{ return m_pAmmo; }

	tgCV3D			GetDefaultRecoil		(void)					{ return m_DefaultRecoil; }
	tgCV3D			GetDefaultScopedRecoil	(void)					{ return m_DefaultScopedRecoil; }
	tgCV3D			GetRecoil				(void)					{ return m_Recoil; }

	tgFloat			GetDefaultRecovery			(void)				{ return m_DefaultRecoverySpeed; }
	tgFloat			GetDefaultScopedRecovery	(void)				{ return m_DefaultScopedRecoverySpeed; }
	tgFloat			GetRecovery					(void)				{ return m_RecoverySpeed; }

	tgFloat			GetSnappiness			(void)					{ return m_Snappiness; }
	tgFloat			GetScopedSnappiness		(void)					{ return m_ScopedSnappiness; }

	tgFloat			GetDefaultBulletSpread			(void)			{ return m_DefaultBulletSpread; }
	tgFloat			GetDefaultScopedBulletSpread	(void)			{ return m_DefaultScopedBulletSpread; }
	tgFloat			GetBulletSpread					(void)			{ return m_BulletSpread; }

	tgFloat			GetDefaultDamage		(void)					{ return m_DefaultDamage; }
	tgFloat			GetDamage				(void)					{ return m_Damage; }
	tgFloat			GetWeight				(void)					{ return m_Weight; }
	tgFloat			GetDefaultWeight		(void)					{ return m_DefaultWeight; }
	tgFloat			GetZoomFov				(void)					{ return m_ZoomFov; }
	tgCString		GetWeaponName			(void)					{ return m_WeaponName; }

	enum EType
	{
		TYPE_SINGLESHOT,
		TYPE_BOLTACTION,
		TYPE_SEMIAUTOMATIC,
		TYPE_AUTOMATIC,

		NUM_TYPES
	};

protected:

	tgCModel* m_pModel;

	CMuzzle*	m_pMuzzle;
	CHandle*	m_pHandle;
	CScope*		m_pScope;
	CMagazine*	m_pMagazine;
	CStock*		m_pStock;
	CAmmo*		m_pAmmo;

	tgCV3D m_WeaponModelOffset;
	tgCV3D m_WeaponModelRotation;
	tgCV3D m_WeaponModelScale;
	tgCV3D m_CurrentRotation;
	tgCV3D m_TargetRotation;
	tgCV3D m_DefaultRecoil;
	tgCV3D m_Recoil;
	tgCV3D m_DefaultScopedRecoil;
	tgCV3D m_ScopedRecoil;
	tgCV3D m_ScopeOffset;
	tgCV3D m_ScopeRotation;
	tgCV3D m_MuzzleOffset;
	tgCV3D m_MuzzleRotation;

	tgCString m_WeaponName;
	tgCString m_WeaponModelPath;

	tgUInt32 m_Type;

	tgUInt32 m_BulletIndex;
	tgUInt32 m_DefaultMaxAmmo;
	tgUInt32 m_MaxAmmo;
	tgUInt32 m_Ammo;
	tgUInt32 m_DefaultDamage;
	tgUInt32 m_Damage;
	tgUInt32 m_BulletCount;

	tgUInt32 m_ScopeIndex;
	tgUInt32 m_MagazineIndex;
	tgUInt32 m_HandleIndex;
	tgUInt32 m_MuzzleIndex;
	tgUInt32 m_StockIndex;
	tgUInt32 m_AmmoIndex;

	tgFloat m_DefaultTimeToReload;
	tgFloat m_TimeToReload;
	tgFloat m_ReloadTime;
	tgFloat m_ZoomFov;
	tgFloat m_DefaultFov;
	tgFloat m_DefaultBulletSpread;
	tgFloat m_BulletSpread;
	tgFloat m_DefaultScopedBulletSpread;
	tgFloat m_ScopedBulletSpread;
	tgFloat m_Snappiness;
	tgFloat m_ScopedSnappiness;
	tgFloat m_DefaultRecoverySpeed;
	tgFloat m_RecoverySpeed;
	tgFloat m_DefaultScopedRecoverySpeed;
	tgFloat m_ScopedRecoverySpeed;
	tgFloat m_DefaultWeight;
	tgFloat m_Weight;

	tgFloat m_RenderTargetWidth;
	tgFloat m_RenderTargetHeight;

	tgBool m_HasAmmo;
	tgBool m_TriggerHeld;
	tgBool m_IsReloading;
	tgBool m_IsScoped;
	tgBool m_HasMuzzle;
	tgBool m_HasHandle;
	tgBool m_HasScope;
	tgBool m_HasMagazine;
	tgBool m_HasStock;
	tgBool m_HasAmmoComponent;
};
