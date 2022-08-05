#pragma once
#include "Specialization/IComponent.h"

#include <tgCTransform.h>

class CModelComponent final : public IComponent
{
public:

	CModelComponent(tgCString FilePath);

	void		Load		(void) override;
	void		Unload		(void) override;
	void		Update		(const tgFloat DeltaTime) override;

	tgCModel&	GetModel	(void) { return *m_pModel; }

private:

	tgCModel*		m_pModel;

	tgCString		m_FilePath;
	tgCString		m_Name;
};

