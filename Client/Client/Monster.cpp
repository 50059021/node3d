#include "Monster.h"
#include "CSVFile.h"
#include "Audio.h"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CMonster::CMonster()
{
	m_nType = 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CMonster::~CMonster()
{

}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMonster::setType(unsigned long uType)
{
	m_uType = uType;
	// ----
	CCsvFile csv(MONSTER_CVS_PATCH);
	// ----
	csv.seek(uType);
	// ----
	const char* szName			= csv.GetStr("name");
	const char* szModelFilename	= csv.GetStr("model");
	// ----
	float fScale				= csv.GetFloat("scale");
	// ----
	setName(s2ws(szName).c_str());
	// ----
	load(szModelFilename);
	// ----
	setScale(Vec3D(fScale,fScale,fScale));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void playMonsterSound(unsigned long uType, const char* szName)
{
	/*for (int i=0; i<10; ++i)
	{
		//CCsvFile csv("Data\\CSV\\MonsterV.csv");
		//csv.seek(uType);
	}*/

	CCsvFile csv(MONSTER_CVS_PATCH);
	// ----
	csv.seek(uType);
	// ----
	GetAudio().playSound(csv.GetStr(szName));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMonster::OnFrameMove(float fElapsedTime)
{
	float fSoundIdleTime = 10.0f;
	// ----
	if(m_uActionState == WALK)
	{
		// ----
		if(fElapsedTime < fSoundIdleTime)
		{
			if(rand() % (int)(fSoundIdleTime / fElapsedTime) == 0)
			{
				playMonsterSound(m_uType,"soundIdle");
			}
		}
	}
	// ----
	CRole::OnFrameMove(fElapsedTime);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMonster::setActionState(unsigned char uActionState)
{
	m_uActionState=uActionState;
	// ----
	switch(m_uActionState)
	{
		case STAND:
		{
			CModelComplex::SetAnim("0");
		}
		break;

		case WALK:
		{
			CModelComplex::SetAnim("2");
		}
		break;

		case HIT1:
		{
			playMonsterSound(m_uType,"soundAttack");
			// ----
			CModelComplex::SetAnim("3");
		}
		break;

		case DIE:
		{
			playMonsterSound(m_uType,"soundDie");
			// ----
			CModelComplex::SetAnim("6");
		}
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMonster::renderFocus()const
{
	C3DMapObj::renderFocus(0xFFFF4040);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------