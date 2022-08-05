#include <tgSystem.h>

#include "CSuppressor.h"

CSuppressor::CSuppressor()
{
	m_MuzzleModelPath = "models/suppressor";
	m_VerticalRecoil = 0.75f;
	m_HorizontalRecoil = 0.75f;
	m_ShakeRecoil = 0.5f;
	m_Spread = 0.9f;
	m_Damage = 1.1f;
}

CSuppressor::~CSuppressor()
{
}
