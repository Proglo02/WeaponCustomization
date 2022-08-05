#pragma once

#include "Specialization/Components/CWeapon.h"
#include "Specialization/CWorld.h"

class CWSemiAutomatic : public CWeapon
{
public:

	CWSemiAutomatic();
	~CWSemiAutomatic();

	void Shoot() override;

private:



};

