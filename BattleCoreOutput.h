#pragma once

//---------------------------------------
//����BattleCore.lib���������
//ʹ��lib��Ҫinclude��ͷ�ļ�
//������һЩ֧���Ե�struct
//---------------------------------------


extern "C"
{

	void LoadGameData();

	void InitNewBattle(/*...*/);

	void SetBattleMode(const BattleMode & battleMode);

	int AddRobotAI(RobotAI_Interface* pAI);

	AchievementData_Battle& GetAchievementData(int robotID);

	BattleStatistics& GetBattleStatistivs();

	bool LaunchBattle();




#ifdef ROBOT_AI_TEST

void StartTestingBattleWithRandomEquipment();
void StartTestingBattleWithAssignedEquipment(int weapon0=0,int engine0=0,int weapon1=4,int engine1=1);

#endif

}