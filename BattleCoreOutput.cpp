//#include "stdafx.h"

#include "Basic_Battle\Robot\RobotAITest.h"

#include "stdafx.h"
#include "BattleCoreOutput.h"


void LoadGameData()
{
	pDataLoader->LoadDataFromLuaScript("GameData.lua");
}


void InitNewBattle()
{
	//�������������
	SetSeed();

	//��ɨ֮ǰ��ս��
	pBattlefield->SweepBattlefield(true,true,true,true);


	/*
	pAIManager->AddToBattlefield(ai0);
	pAIManager->AddToBattlefield(ai1);

	pBattlefield->SetBattleMode(battle_mode);
	
	pBattlefield->NewBattle();

	pAchievement->Calculate_Single(ai0);
	pAchievement->Calculate_Single(ai1);

	pBattlefield->SweepBattlefield(true,true,true,true);
	*/
}


void SetBattleMode(const BattleMode & battleMode)
{
	pBattlefield->SetBattleMode(battleMode);
}



int AddRobotAI(RobotAI_Interface* pAI)
{
	//��Battlefield���AI
	//ΪpAIָ���AI�����µĻ����˼��뵽ս��
	
	
	//����ָ�븳ֵ
	pAI->trace=trace_global;		//�����������ָ��
	
	pAI->getWeaponName=getWeaponName;
	pAI->getWeaponDamage=getWeaponDamage;
	pAI->getWeaponAmmo=getWeaponAmmo;
	pAI->getWeaponCoolingTime=getWeaponCoolingTime;
	pAI->getWeaponInaccuracy=getWeaponInaccuracy;
	pAI->getWeaponRotationSpeed=getWeaponRotationSpeed;
	
	pAI->getEngineName=getEngineName;
	pAI->getEngineMaxSpeed=getEngineMaxSpeed;
	pAI->getEngineMaxHp=getEngineMaxHp;
	pAI->getEngineRotationSpeed=getEngineRotationSpeed;
	pAI->getEngineAcceleration=getEngineAcceleration;
	///////////////////
	

	//TODO:�����indexԭ����AIManager�е�AI�±�
	//���ڲ���Ҫ��
	//��װ��BattleCore����������������AI����Ϣ

	//ֻҪ���ص�ǰ����AI��pRobot���±�
	return (pBattlefield->AddRobotAI(pAI,0));	//��0����һ��
}

AchievementData_Battle& GetAchievementData(int robotID)
{
	return (pBattlefield->GetAchievementData(robotID));
}


BattleStatistics& GetBattleStatistivs()
{
	return (pBattlefield->GetBattleStatistivs());
}


bool LaunchBattle()
{
	pBattlefield->NewBattle();

	//temp
	return true;
}



#ifdef ROBOT_AI_TEST

void StartTestingBattle()
{
	BattleMode defaultBattleMode(true,4000,true,"zTestingBattle");
	RobotAI_Interface* ai0=new RobotAITest();
	RobotAI_Interface* ai1=new RobotAITest();


	InitNewBattle();
	SetBattleMode(defaultBattleMode);
	int id0=AddRobotAI(ai0);
	int id1=AddRobotAI(ai1);
	LaunchBattle();

	//TODO:��ӡһЩս��ͳ������
	BattleStatistics& battleStatistics=pBattlefield->GetBattleStatistivs();

	cout<<"winner id: "<<battleStatistics.winnerID<<'\n';

	delete ai0;
	delete ai1;
}

#endif