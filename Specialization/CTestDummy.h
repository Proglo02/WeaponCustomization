#pragma once

#include "Specialization/IComponent.h"

class CTestDummy : public IComponent
{
public:

	CTestDummy();
	~CTestDummy();

	void Load() override;
	void Unload() override;

	void Update(tgFloat DeltaTime) override;

private:



};

