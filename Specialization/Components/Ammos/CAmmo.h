#pragma once

#include "Specialization/CPlayer.h"
#include "Specialization/IComponent.h"


#include <tgCV3D.h>

class CAmmo : public IComponent
{
public:

	CAmmo();

	void	Load(void) override;
	void	Unload(void) override;
	void	Update(tgFloat deltaTime) override;

	void	HandleCollision();

	void	SetTransform		(tgCTransform* pTransform)	{ m_pTransform = pTransform; }

	void	SetAmmoActive		(tgBool active)			{ m_IsActive = active; }
	void	SetHasExplosion		(tgBool explosion)		{ m_HasExplosion = explosion; }
	void	SetHasFire			(tgBool fire)			{ m_HasFire = fire; }

	void	SetDamage			(tgUInt32 damage)		{ m_Damage = damage; }
	void	SetExplosionDamage	(tgUInt32 damage)		{ m_ExplosionDamage = damage; }
	void	SetFireDamge		(tgUInt32 damage)		{ m_FireDamage = damage; }

	void	SetDispersion		(tgFloat dispersion)	{ m_Dispersion = dispersion; }
	void	SetExplosionRadius	(tgFloat radius)		{ m_ExplosionRadius = radius; }
	void	SetFireDuration		(tgFloat duration)		{ m_FireDuration = duration; }
	void	SetTravelSpeed		(tgFloat speed)			{ m_TravelSpeed = speed; }

	void	SetAmmoName			(tgCString name)		{ m_AmmoName = name; }

	CEntity*	GetEntity			(void)				{ return m_pEntity; }

	tgBool		GetHasExplosion		(void)				{ return m_HasExplosion; }
	tgBool		GetHasFire			(void)				{ return m_HasFire; }

	tgUInt32	GetExplosionDamage	(void)				{ return m_ExplosionDamage; }
	tgUInt32	GetFireDamage		(void)				{ return m_FireDamage; }

	tgFloat		GetExplosionRadius	(void)				{ return m_ExplosionRadius; }
	tgFloat		GetFireDuration		(void)				{ return m_FireDuration; }
	tgFloat		GetTravelSpeed		(void)				{ return m_TravelSpeed; }

	tgCString	GetAmmoName			(void)				{ return m_AmmoName; }

private:

	const tgCTransform* m_pTransform;

	tgBool m_IsActive;
	tgBool m_CanHit;
	tgBool m_HasExplosion;
	tgBool m_HasFire;

	tgCV3D m_WeaponOffset;
	tgCV3D m_PrevPos;

	tgUInt32 m_Damage;
	tgUInt32 m_ExplosionDamage;
	tgUInt32 m_FireDamage;

	tgFloat m_ExplosionRadius;
	tgFloat m_FireDuration;
	tgFloat m_TravelSpeed;
	tgFloat m_MaxTimeAlive;
	tgFloat m_TimeAlive;
	tgFloat m_Dispersion;

	tgCString m_AmmoName;
};

