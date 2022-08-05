#include <tgSystem.h>
#include <tgCQuadManager.h>
#include <tgCFontManager.h>
#include <tgCTextureManager.h>
#include <tgCCore.h>

#include "CWeapon.h"
#include "CClock.h"
#include "Specialization/Components/Ammos/CAmmo.h"
#include "Specialization/Components/CModelComponent.h"
#include "Specialization/Components/Attatchments/Handles/CHandle.h"
#include "Specialization/Components/Attatchments/Magazines/CMagazine.h"
#include "Specialization/Components/Attatchments/Muzzles/CMuzzle.h"
#include "Specialization/Components/Attatchments/Scopes/CScope.h"
#include "Specialization/Components/Attatchments/Stocks/CStock.h"
#include "Specialization/CEntity.h"
#include "Specialization/CWorld.h"
#include "Specialization/CPlayer.h"
#include "Managers/CModelManager.h"
#include "CApplication.h"
#include "Camera/CCamera.h"

CWeapon::CWeapon(void)
: m_pModel( NULL )
, m_pMuzzle( NULL )
, m_pHandle( NULL )
, m_pScope( NULL )
, m_pMagazine( NULL )
, m_pStock( NULL )
, m_pAmmo( NULL )
, m_WeaponModelOffset( 0.0f, 0.0f, 0.0f )
, m_WeaponModelRotation( 0.0f, 180.0f, 0.0f )
, m_WeaponModelScale( 0.003f, 0.003f, 0.003f )
, m_CurrentRotation ( 0.0f, 0.0f, 0.0f )
, m_TargetRotation ( 0.0f, 0.0f, 0.0f )
, m_DefaultRecoil( 2.0f, 2.0f, 0.35f )
, m_Recoil ( 2.0f, 2.0f, 0.35f )
, m_DefaultScopedRecoil ( 1.0f, 1.0f, 0.175f )
, m_ScopedRecoil( 1.0f, 1.0f, 0.175f )
, m_ScopeOffset( 0.0f, 0.0f, 0.0f )
, m_ScopeRotation( 0.0f, 0.0f, 0.0f )
, m_MuzzleOffset( 0.0f, 0.0f, 0.0f )
, m_MuzzleRotation( 0.0f, 0.0f, 0.0f )
, m_WeaponName()
, m_WeaponModelPath()
, m_Type( TYPE_BOLTACTION )
, m_BulletIndex( 0 )
, m_DefaultMaxAmmo( 20 )
, m_MaxAmmo( 20 )
, m_Ammo( 20 )
, m_DefaultDamage( 10 )
, m_Damage( 10 )
, m_BulletCount( 1 )
, m_ScopeIndex( 0 )
, m_MagazineIndex( 0 )
, m_HandleIndex( 0 )
, m_MuzzleIndex( 0 )
, m_StockIndex( 0 )
, m_AmmoIndex( 0 )
, m_DefaultTimeToReload( 2.0f )
, m_TimeToReload( 2.0f )
, m_ReloadTime( 0.0f )
, m_ZoomFov( 90.0f )
, m_DefaultFov ( 90.0f )
, m_DefaultBulletSpread( 1.0f )
, m_BulletSpread( 1.0f )
, m_DefaultScopedBulletSpread( 0.1f )
, m_ScopedBulletSpread( 0.1f )
, m_Snappiness ( 6.0f )
, m_ScopedSnappiness ( 3.0f )
, m_DefaultRecoverySpeed( 2.0f )
, m_RecoverySpeed ( 2.0f )
, m_DefaultScopedRecoverySpeed ( 1.5f )
, m_ScopedRecoverySpeed( 1.5f )
, m_DefaultWeight( 10.0f )
, m_Weight( 10.0f )
, m_RenderTargetWidth( 0.0f )
, m_RenderTargetHeight( 0.0f )
, m_HasAmmo( true )
, m_TriggerHeld( false )
, m_IsReloading( false )
, m_IsScoped( false )
, m_HasMuzzle( false )
, m_HasHandle( false )
, m_HasScope( false )
, m_HasMagazine( false )
, m_HasStock( false )
, m_HasAmmoComponent( false )
{
	m_DefaultFov = CApplication::GetInstance().Get3DCamera()->GetCamera()->GetFov();

	m_RenderTargetWidth = tgCCore::GetInstance().GetWindowWidth();
	m_RenderTargetHeight = tgCCore::GetInstance().GetWindowHeight();
}

CWeapon::~CWeapon(void)
{
}

void CWeapon::Load()
{
	if (m_pEntity)
		m_WeaponName = m_pEntity->GetName();

	m_pModel = CModelManager::GetInstance().LoadModel(m_WeaponModelPath, m_WeaponName, true);
	m_pModel->GetTransform().GetMatrixLocal().Scale(m_WeaponModelScale, tgCMatrix::COMBINE_REPLACE);
	m_pModel->GetTransform().GetMatrixLocal().Pos += m_WeaponModelOffset;
	m_pModel->GetTransform().GetMatrixLocal().RotateX(m_WeaponModelRotation.x, tgCMatrix::COMBINE_POST_MULTIPLY);
	m_pModel->GetTransform().GetMatrixLocal().RotateY(m_WeaponModelRotation.y, tgCMatrix::COMBINE_POST_MULTIPLY);
	m_pModel->GetTransform().GetMatrixLocal().RotateZ(m_WeaponModelRotation.z, tgCMatrix::COMBINE_POST_MULTIPLY);
	CApplication::GetInstance().Get3DCamera()->GetCamera()->GetTransform().AddChild(m_pModel->GetTransform());

	if (m_pModel)
		for (int i = 0; i < m_pModel->GetNumMeshes(); i++)
			m_pModel->GetMesh(i)->SetFlags(0);

	m_Recoil = m_DefaultRecoil;
	m_ScopedRecoil = m_DefaultScopedRecoil;

	m_RecoverySpeed = m_DefaultRecoverySpeed;
	m_ScopedRecoverySpeed = m_DefaultScopedRecoverySpeed;

	m_BulletSpread = m_DefaultBulletSpread;

	m_ScopedBulletSpread = m_DefaultScopedBulletSpread;

	m_Damage = m_DefaultDamage;

	m_TimeToReload = m_DefaultTimeToReload;

	m_MaxAmmo = m_DefaultMaxAmmo;
	m_Ammo = m_MaxAmmo;

	m_Weight = m_DefaultWeight;
}

void CWeapon::Update(tgFloat DeltaTime)
{
	if (m_HasMagazine)
	{
		if (m_pMagazine)
		{
			m_MaxAmmo = m_DefaultMaxAmmo * m_pMagazine->GetMagazineSize();
			m_TimeToReload = m_DefaultTimeToReload * m_pMagazine->GetReloadTime();
		}
		else
		{
			m_MaxAmmo = m_DefaultMaxAmmo;
			m_TimeToReload = m_DefaultTimeToReload;
		}

		if (m_Ammo > m_MaxAmmo)
			m_Ammo = m_MaxAmmo;

	}

	if (!m_IsScoped)
	{
		tgFloat HandleRecovery = 1.0f;
		if (m_pHandle)
			HandleRecovery = m_pHandle->GetRecovery();

		m_RecoverySpeed = m_DefaultRecoverySpeed * HandleRecovery;

		m_TargetRotation.InterpolateLinear(m_TargetRotation, tgCV3D::Zero, m_RecoverySpeed * DeltaTime);
		m_CurrentRotation.InterpolateLinear(m_CurrentRotation, m_TargetRotation, m_Snappiness * DeltaTime);
	}
	else
	{
		tgFloat HandleRecovery = 1.0f;
		if (m_pHandle)
			HandleRecovery = m_pHandle->GetRecovery();

		m_ScopedRecoverySpeed = m_DefaultScopedRecoverySpeed * HandleRecovery;

		m_TargetRotation.InterpolateLinear(m_TargetRotation, tgCV3D::Zero, m_ScopedRecoverySpeed * DeltaTime);
		m_CurrentRotation.InterpolateLinear(m_CurrentRotation, m_TargetRotation, m_ScopedSnappiness * DeltaTime);
	}

	if (m_pEntity && m_pModel)
	{
		m_pModel->GetTransform().GetMatrixLocal().Pos = m_pEntity->GetTransform().GetMatrixWorld().Pos + m_WeaponModelOffset;
	}

	if (m_pScope)
	{
		m_pScope->SetScopePos(m_ScopeOffset);
		m_pScope->Update(DeltaTime);
	}

	if (m_pMuzzle)
	{
		m_pMuzzle->SetMuzzlePos(m_MuzzleOffset);
		m_pMuzzle->Update(DeltaTime);
	}

	m_Weight = m_DefaultWeight;

	if (m_pHandle)
		m_Weight += m_pHandle->GetWeight();
	if (m_pScope)
		m_Weight += m_pScope->GetWeight();
	if (m_pMagazine)
		m_Weight += m_pMagazine->GetWeight();
	if (m_pStock)
		m_Weight += m_pStock->GetWeight();

	if (m_IsReloading)
		Reload();

	tgFloat HandleVertical = 1.0f;
	tgFloat HandleHorizontal = 1.0f;
	tgFloat HandleShake = 1.0f;

	tgFloat MuzzleVertical = 1.0f;
	tgFloat MuzzleHorizontal = 1.0f;
	tgFloat MuzzleShake = 1.0f;

	tgFloat StockVertical = 1.0f;
	tgFloat StockHorizontal = 1.0f;
	tgFloat StockShake = 1.0f;

	if (m_HasHandle && m_pHandle)
	{
		HandleVertical = m_pHandle->GetVerticalRecoil();
		HandleHorizontal = m_pHandle->GetHorizontalRecoil();
		HandleShake = m_pHandle->GetShakeRecoil();
	}

	if (m_HasMuzzle && m_pMuzzle)
	{
		MuzzleVertical = m_pMuzzle->GetVerticalRecoil();
		MuzzleHorizontal = m_pMuzzle->GetHorizontalRecoil();
		MuzzleShake = m_pMuzzle->GetShakeRecoil();
	}

	if (m_HasStock && m_pStock)
	{
		StockVertical = m_pStock->GetVerticalRecoil();
		StockHorizontal = m_pStock->GetHorizontalRecoil();
		StockShake = m_pStock->GetShakeRecoil();
	}

	if (!m_IsScoped)
	{
		m_Recoil.x = m_DefaultRecoil.x * HandleVertical * MuzzleVertical * StockVertical;
		m_Recoil.y = m_DefaultRecoil.y * HandleHorizontal * MuzzleHorizontal * StockHorizontal;
		m_Recoil.z = m_DefaultRecoil.z * HandleShake * MuzzleShake * StockShake;
	}
	else
	{
		m_ScopedRecoil.x = m_DefaultScopedRecoil.x * HandleVertical * MuzzleVertical * StockVertical;
		m_ScopedRecoil.y = m_DefaultScopedRecoil.y * HandleHorizontal * MuzzleHorizontal * StockHorizontal;
		m_ScopedRecoil.z = m_DefaultScopedRecoil.z * HandleShake * MuzzleShake * StockShake;
	}

	tgFloat MuzzleSpread = 1.0f;
	tgFloat MuzzleDamage = 1.0f;

	if (m_HasMuzzle && m_pMuzzle)
	{
		MuzzleSpread = m_pMuzzle->GetSpread();
		MuzzleDamage = m_pMuzzle->GetDamage();
	}

	m_Damage = m_DefaultDamage * MuzzleDamage;

	if (!m_IsScoped)
		m_BulletSpread = m_DefaultBulletSpread * MuzzleSpread;
	else
		m_ScopedBulletSpread = m_DefaultScopedBulletSpread * MuzzleSpread;
}

void 
CWeapon::Shoot()
{
	if (m_HasAmmo)
	{
		SpawnBullet();
		Recoil();

		m_Ammo--;

		if (m_Ammo <= 0)
			m_HasAmmo = false;
	}
}

void CWeapon::Reload()
{
	if (m_ReloadTime >= m_TimeToReload)
	{
		m_Ammo = m_MaxAmmo;
		m_ReloadTime = 0.0f;
		m_IsReloading = false;
		m_HasAmmo = true;
		return;
	}

	m_ReloadTime += CClock::GetInstance().GetDeltaTimeReal();
}

void CWeapon::SpawnBullet()
{
	for (tgUInt32 i = 0; i < m_BulletCount; i++)
	{
		tgFloat Spread = 0.0f;

		if (m_IsScoped)
			Spread = m_ScopedBulletSpread;
		else
			Spread = m_BulletSpread;

		m_BulletIndex++;
		CEntity* pAmmo = m_pEntity->GetWorld()->CreateEntity(m_pModel->GetTransform().GetMatrixWorld().Pos, m_pEntity->GetName() + tgCString("Bullet%d", m_BulletIndex));
		CAmmo* pAmmoComponent = pAmmo->AddComponent<CAmmo>();
		pAmmoComponent->SetTransform(&CApplication::GetInstance().Get3DCamera()->GetCamera()->GetTransform());
		pAmmoComponent->SetDispersion(Spread);
		pAmmoComponent->SetDamage(m_Damage);
		pAmmoComponent->SetAmmoActive(true);
		if (m_pAmmo)
		{
			pAmmoComponent->SetHasExplosion(m_pAmmo->GetHasExplosion());
			pAmmoComponent->SetHasFire(m_pAmmo->GetHasFire());
			pAmmoComponent->SetExplosionDamage(m_pAmmo->GetExplosionDamage());
			pAmmoComponent->SetFireDamge(m_pAmmo->GetFireDamage());
			pAmmoComponent->SetExplosionRadius(m_pAmmo->GetExplosionRadius());
			pAmmoComponent->SetFireDuration(m_pAmmo->GetFireDuration());
			pAmmoComponent->SetTravelSpeed(m_pAmmo->GetTravelSpeed());
		}
		//pBullet->AddComponent<CModelComponent>("models/Bullet.tfm");

	}
}

void CWeapon::SetRecoil(tgCV3D Recoil, tgFloat Snappiness, tgFloat ReturnSpeed)
{
	m_DefaultRecoil = Recoil;
	m_Snappiness = Snappiness;
	m_DefaultRecoverySpeed = ReturnSpeed;
}

void CWeapon::SetScopedRecoil(tgCV3D ScopedRecoil, tgFloat ScopedSnappiness, tgFloat ScopedReturnSpeed)
{
	m_DefaultScopedRecoil = ScopedRecoil;
	m_ScopedSnappiness = ScopedSnappiness;
	m_DefaultScopedRecoverySpeed = ScopedReturnSpeed;
}

void CWeapon::SetComponents(tgBool muzzle, tgBool handle, tgBool scope, tgBool magazine, tgBool stock, tgBool ammo)
{
	m_HasMuzzle			= muzzle;
	m_HasHandle			= handle;
	m_HasScope			= scope;
	m_HasMagazine		= magazine;
	m_HasStock			= stock;
	m_HasAmmoComponent = ammo;
}

void CWeapon::ReplaceWeaponModel()
{
	if (m_pModel)
	{
		CApplication::GetInstance().Get3DCamera()->GetCamera()->GetTransform().RemoveChild(m_pModel->GetTransform());
		CModelManager::GetInstance().DestroyModel(m_pModel);
		m_pModel = NULL;
	}

	m_pModel = CModelManager::GetInstance().LoadModel(m_WeaponModelPath, m_WeaponName, true);
	m_pModel->GetTransform().GetMatrixLocal().Scale(m_WeaponModelScale, tgCMatrix::COMBINE_REPLACE);
	m_pModel->GetTransform().GetMatrixLocal().RotateX(m_WeaponModelRotation.x, tgCMatrix::COMBINE_POST_MULTIPLY);
	m_pModel->GetTransform().GetMatrixLocal().RotateY(m_WeaponModelRotation.y, tgCMatrix::COMBINE_POST_MULTIPLY);
	m_pModel->GetTransform().GetMatrixLocal().RotateZ(m_WeaponModelRotation.z, tgCMatrix::COMBINE_POST_MULTIPLY);
	CApplication::GetInstance().Get3DCamera()->GetCamera()->GetTransform().AddChild(m_pModel->GetTransform());

	if (m_pModel)
		for (int i = 0; i < m_pModel->GetNumMeshes(); i++)
			m_pModel->GetMesh(i)->SetFlags(0);
}

void CWeapon::ZoomIn()
{
	if (m_HasScope)
	{
		m_IsScoped = true;
		tgFloat ScopeMagnificaton = m_pScope->GetMagnification();
		tgFloat Magnification = m_ZoomFov * (1 / ScopeMagnificaton);
		CApplication::GetInstance().Get3DCamera()->GetCamera()->SetFov(Magnification);
	}
}

void CWeapon::ZoomOut()
{
	if (m_HasScope)
	{
		m_IsScoped = false;
		CApplication::GetInstance().Get3DCamera()->GetCamera()->SetFov(m_DefaultFov);
	}
}

void CWeapon::Recoil()
{
	if (!m_IsScoped)
		m_TargetRotation += tgCV3D(-m_Recoil.x, tgMathRandom(-m_Recoil.y, m_Recoil.y), tgMathRandom(-m_Recoil.z, m_Recoil.z));
	else
		m_TargetRotation += tgCV3D(-m_ScopedRecoil.x, tgMathRandom(-m_ScopedRecoil.y, m_ScopedRecoil.y), tgMathRandom(-m_ScopedRecoil.z, m_ScopedRecoil.z));
}

tgCV2D CWeapon::SetQuadSize()
{
	return tgCV2D(50, (m_ReloadTime / m_TimeToReload) * 200);
}

tgCV3D CWeapon::SetQuadPos()
{
	return tgCV3D(m_RenderTargetWidth * 0.5f * 1.1f, m_RenderTargetHeight - 100 - (m_ReloadTime / m_TimeToReload) * 100, 0);
}
