#include <tgSystem.h>

#include "CMuzzle.h"
#include "Specialization/CEntity.h"
#include "Managers/CModelManager.h"
#include "CApplication.h"
#include "Camera/CCamera.h"

#include <tgCDebugManager.h>

CMuzzle::CMuzzle()
: m_pModel( NULL )
, m_Pos( 0.0f, 0.0f, 0.0f )
, m_VerticalRecoil( 1.0f )
, m_HorizontalRecoil( 1.0f )
, m_ShakeRecoil( 1.0f )
, m_Spread( 1.0f )
, m_Damage( 1.0f )
, m_MuzzleName( "" )
, m_MuzzleModelPath( "" )
, m_ModelScale( 0.0002f, 0.0002f, 0.0002f )
, m_ModelRotation( 90.0f, 0.0f, 0.0f )
{
}

CMuzzle::~CMuzzle()
{
}

void CMuzzle::Load()
{
	if (m_pEntity)
		m_MuzzleName = m_pEntity->GetName();

	m_pModel = CModelManager::GetInstance().LoadModel(m_MuzzleModelPath, m_MuzzleName, true);
	m_pModel->GetTransform().GetMatrixLocal().Scale(m_ModelScale, tgCMatrix::COMBINE_REPLACE);
	m_pModel->GetTransform().GetMatrixLocal().RotateX(m_ModelRotation.x, tgCMatrix::COMBINE_POST_MULTIPLY);
	m_pModel->GetTransform().GetMatrixLocal().RotateY(m_ModelRotation.y, tgCMatrix::COMBINE_POST_MULTIPLY);
	CApplication::GetInstance().Get3DCamera()->GetCamera()->GetTransform().AddChild(m_pModel->GetTransform());
	m_pModel->GetTransform().GetMatrixLocal().Pos = tgCV3D::Zero;

	if (m_pModel)
		for (int i = 0; i < m_pModel->GetNumMeshes(); i++)
			m_pModel->GetMesh(i)->SetFlags(0);
}

void CMuzzle::ReplaceMuzzleModel()
{
	if (m_pModel)
	{
		CApplication::GetInstance().Get3DCamera()->GetCamera()->GetTransform().RemoveChild(m_pModel->GetTransform());
		CModelManager::GetInstance().DestroyModel(m_pModel);
		m_pModel = NULL;
	}

	m_pModel = CModelManager::GetInstance().LoadModel(m_MuzzleModelPath, m_MuzzleName, true);
	m_pModel->GetTransform().GetMatrixLocal().Scale(m_ModelScale, tgCMatrix::COMBINE_REPLACE);
	m_pModel->GetTransform().GetMatrixLocal().RotateX(m_ModelRotation.x, tgCMatrix::COMBINE_POST_MULTIPLY);
	m_pModel->GetTransform().GetMatrixLocal().RotateY(m_ModelRotation.y, tgCMatrix::COMBINE_POST_MULTIPLY);
	m_pModel->GetTransform().GetMatrixLocal().RotateZ(m_ModelRotation.z, tgCMatrix::COMBINE_POST_MULTIPLY);
	CApplication::GetInstance().Get3DCamera()->GetCamera()->GetTransform().AddChild(m_pModel->GetTransform());

	if (m_pModel)
		for (int i = 0; i < m_pModel->GetNumMeshes(); i++)
			m_pModel->GetMesh(i)->SetFlags(0);
}

void CMuzzle::SetMuzzlePos(tgCV3D Pos)
{
	m_pModel->GetTransform().GetMatrixLocal().Pos = Pos;
	m_Pos = Pos;
}
