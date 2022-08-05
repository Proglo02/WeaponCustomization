#include <tgSystem.h>

#include "CModelComponent.h"
#include "Managers/CModelManager.h"
#include "Specialization/CEntity.h"

CModelComponent::CModelComponent(tgCString FilePath)
: m_pModel( NULL )
, m_FilePath( FilePath )
{
}

void CModelComponent::Load(void)
{
	if (m_pEntity)
	{
		m_Name = m_pEntity->GetName();
		m_pModel = CModelManager::GetInstance().LoadModel(m_FilePath, m_Name, true);
		m_pEntity->GetTransform().AddChild(m_pModel->GetTransform());
	}
}

void CModelComponent::Unload(void)
{
}

void CModelComponent::Update(const tgFloat DeltaTime)
{
}
