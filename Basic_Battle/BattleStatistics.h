#pragma once
#include "BattleMode.h"

//2014/07/25
//һ��ս����ͳ������
//�Ľ�ԭ��ʤ��֮������

class BattleStatistics
{
public:
	int numRobots;		//��ս������

	int winnerID;		//ʤ��ID��vec::pRobot�е��±꣩
	
	int battleFrames;	//ս������֡��
	int numSurvivors;	//�Ҵ�����
	
	//BattleMode battleMode;	//ս��ģʽ����
	
	//...
	//ս��ʱ������
	//ʤ�߻�����
	//��ս��Vector��
	//ս����������������������λ����������������


	BattleStatistics(){}

	//TODO:...
	void ReplaceFlag(ofstream& out,const string & f);

	void Output(const char * filename);
};