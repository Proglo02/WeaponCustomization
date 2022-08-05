#pragma once

#include "Specialization/IComponent.h"
#include "Specialization/CEntity.h"

#include <tgCV3D.h>

class CEntity;

class CDamageText : public IComponent
{
public:

	CDamageText( tgUInt32 Damage );
	~CDamageText();

	void Load() override;

	void Update(tgFloat DeltaTime) override;

private:

	tgFloat m_TimeAlive;
	tgFloat m_Timer;

	tgUInt32 m_Damage;

};

