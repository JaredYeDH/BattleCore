#pragma once
#include "BattleStatistics.h"




//����ģʽ��
#define pBattlefield Battlefield::Instance()






class Battlefield
	:public BaseEntity,public BattleMap
{
private:
	Battlefield(void);
	virtual ~Battlefield(void);


	


	//2013-9-15 �Ż��������Ϣ��ÿ֡��д�Ҿ������˷ѵ�
	//bulletinfoʲô��struct���Լ�����Bullet�����ָ��ķ�ʽָ������
	//
	RobotAI_BattlefieldInformation info;	//ս����Ϣ


	

	//const static int maxRobots=2;		//ս������������
	//const static int initBullets=20;	//��ʼ�ӵ�list����

	BattleMode battleMode;		//ս��ģʽ���

	int timeLeft;		//��ʱģʽ��ʱ��ʣ��
	
	BattleStatistics battleStatistics;

	//2013-12-8 �⡣����stl��������ָ��+new��Ϊ�����ԲС���

	//����

	vector<Robot*> pRobot;
	list<Bullet*> pBullet;
 

public:
	//���ⷽ��
	static Battlefield* Instance();

	//RecordManagerʹ�õĻ�ȡ��Ϣ����
	//int GetMaxRobots(){return maxRobots;}
	string GetRobotInfo_Name(int);
	string GetRobotInfo_Author(int);
	int GetRobotInfo_Weapon_Red(int);
	int GetRobotInfo_Weapon_Green(int);
	int GetRobotInfo_Weapon_Blue(int);
	int GetRobotInfo_Engine_Red(int);
	int GetRobotInfo_Engine_Green(int);
	int GetRobotInfo_Engine_Blue(int);

	int GetRobotInfo_MaxHp(int);
	int GetRobotInfo_MaxAmmo(int);



	Box GetBoundary(){return boundary;}
	double Get_B_Left(){return B_Left;}
	double Get_B_Right(){return B_Right;}
	double Get_B_Up(){return B_Up;}
	double Get_B_Down(){return B_Down;}


	//const? &
	AchievementData_Battle & GetAchievementData(int index)
	{
		return pRobot.at(index)->GetAchievementData();
	}

	BattleStatistics & GetBattleStatistivs()
	{
		return battleStatistics;
	}

	Robot* GetRobotPointer(int id)
	{
		return pRobot.at(id);
	}
	

	//ս����������
	void SetBattleMode(const BattleMode & battle_mode){battleMode=battle_mode;}

	void SetMode_LimitTime(bool a){battleMode.limitTime=a;}
	void SetMode_Record(bool a,string filename="Record_1"){battleMode.record=a;pRecordManager->SetFileName(filename);}



	//��ս����������
	int AddRobotAI(RobotAI_Interface*,int);	//��Ӳ�սAI��������pRobot���±�

	//��ʼս��������ս���Ƿ�ɹ����У���ֹRobot��������ⲿ����ڲ���
	//2014-1-24 ����ʤ����AIManager�е��±�
	//TODO:ս����Ϣ����Ӧһ��ս����ȫ����Ϣ
	int NewBattle();



	///////////////////////////////////////////////////////////////////

	void BattleStart();
	int BattleEnd();	//����ʤ��AIManager�е��±�

	//TODO:�����Ĵ���ɶ��Բ�����ǲ���ĸ�����
	void SweepBattlefield_Bullet();
	void SweepBattlefield_Robot();
	void SweepBattlefield_Map();
	//�����ֱ�Ϊ�Ƿ�����pBullet,pRobot,pObstacle,pArsenal
	void SweepBattlefield(bool f_bullet,bool f_robot,bool f_obstacle,bool f_arsenal);	//��ɨս��
	


	void Update();//round_start,round_end������ͷ


	void Init_Map();		//��ʼ����ͼ

	void Init_BattleStatistics();
	//void Finish_BattleStatistics();

	void Init_Info();	//��ʼ������AI��info
	void Update_Info();	//����ս����Ϣ

	bool IsFinished();	//�ж�һ��ս���Ƿ���ֹ
	
	RobotAI_BattlefieldInformation& GetInfo(){return info;}


	void RemoveBulletFromBattlefield(list<Bullet*>::iterator & ii,bool);


	virtual void HandleEvent(events msg,void* extraInfo);
};

