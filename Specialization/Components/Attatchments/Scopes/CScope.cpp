#include <tgSystem.h>

#include "CScope.h"
#include "Specialization/CEntity.h"
#include "Managers/CModelManager.h"
#include "CApplication.h"
#include "Camera/CCamera.h"

#include <tgCDebugManager.h>

CScope::CScope()
: m_pModel( NULL )
, m_Magnification( 4 )
, m_Weight( 1.0f )
, m_ScopeName( "" )
, m_ScopeModelPath( "" )
, m_ModelScale( 0.0002f, 0.0002f, 0.0002f )
, m_ModelRotation( 0.0f, -90.0f, 0.0f )
{
}

CScope::~CScope()
{
}

void CScope::Load()
{
	if (m_pEntity)
		m_ScopeName = m_pEntity->GetName();

	m_pModel = CModelManager::GetInstance().LoadModel(m_ScopeModelPath, m_ScopeName, true);
	m_pModel->GetTransform().GetMatrixLocal().Scale(m_ModelScale, tgCMatrix::COMBINE_REPLACE);
	m_pModel->GetTransform().GetMatrixLocal().RotateY(m_ModelRotation.y, tgCMatrix::COMBINE_POST_MULTIPLY);
	CApplication::GetInstance().Get3DCamera()->GetCamera()->GetTransform().AddChild(m_pModel->GetTransform());
	m_pModel->GetTransform().GetMatrixLocal().Pos = tgCV3D::Zero;

	if (m_pModel)
		for (int i = 0; i < m_pModel->GetNumMeshes(); i++)
			m_pModel->GetMesh(i)->SetFlags(0);
}

void CScope::ReplaceScopeModel()
{
	if (m_pModel)
	{
		CApplication::GetInstance().Get3DCamera()->GetCamera()->GetTransform().RemoveChild(m_pModel->GetTransform());
		CModelManager::GetInstance().DestroyModel(m_pModel);
		m_pModel = NULL;
	}

	m_pModel = CModelManager::GetInstance().LoadModel(m_ScopeModelPath, m_ScopeName, true);
	m_pModel->GetTransform().GetMatrixLocal().Scale(m_ModelScale, tgCMatrix::COMBINE_REPLACE);
	m_pModel->GetTransform().GetMatrixLocal().RotateX(m_ModelRotation.x, tgCMatrix::COMBINE_POST_MULTIPLY);
	m_pModel->GetTransform().GetMatrixLocal().RotateY(m_ModelRotation.y, tgCMatrix::COMBINE_POST_MULTIPLY);
	m_pModel->GetTransform().GetMatrixLocal().RotateZ(m_ModelRotation.z, tgCMatrix::COMBINE_POST_MULTIPLY);
	CApplication::GetInstance().Get3DCamera()->GetCamera()->GetTransform().AddChild(m_pModel->GetTransform());

	if (m_pModel)
		for (int i = 0; i < m_pModel->GetNumMeshes(); i++)
			m_pModel->GetMesh(i)->SetFlags(0);
}

void CScope::SetScopePos(tgCV3D Pos)
{
	m_pModel->GetTransform().GetMatrixLocal().Pos = Pos;
}
