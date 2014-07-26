#pragma once
#include "Basic_Battle\Robot\RobotAIstruct.h"

struct Record_RobotInformation
{
	//����RobotAI��Execute(..)�������ṩ������AI��Robot��Ϣ
	int id;		//Battlefield.pRobot���±�

	int entityID;	//����MovieClip��Ψһ��ʶ

	int style_Weapon;		//������ʽ
	int style_Engine;		//������ʽ
	//long color		//��ɫ��
	/*
	int weapon_red;
	int weapon_green;
	int weapon_blue;
	int engine_red;
	int engine_green;
	int engine_blue;
	*/


	weapontypename weaponTypeName;	//��������
	enginetypename engineTypeName;	//��������		//�ܸо�����Щ����������ô��������İ취����һ��������ʾ��ͬ��������ʵ�á���
	//�������Ը������������������У�����DataLoader.hҲҪ��RobotAIFactoryһ��

	//��ǰ����
	//Circle circle;		//engine��Բ(x,y,radium)
	double x;
	double y;

	double engineRotation;	//����Ƕ�
	double weaponRotation;	//�����Ƕȣ�������
	//double vx,vy,vr;
	
	int hp;

	int remainingAmmo;		
	int cooling;

	//��ǰ֡��������(ֱ�ӰѲ��������)
	int fire;	//����Fire(int mnplt)�Ĳ�����
	int wturn;	//����Turn(int mnplt)�Ĳ�����
	int run;	//����Run(int mnplt)�Ĳ�����
	int eturn;	//����Turn(int mnplt)�Ĳ�����


	Record_RobotInformation(){fire=false;wturn=false;run=false;eturn=false;}
	void Init()
	{
		//����ʹ��ʱ����µ����Գ�ʼ��
		fire=0;
		wturn=0;
		run=0;
		eturn=0;
	}
};


struct Record_BulletInformation
{
	//temp
	int entityID;	//����MovieClip��Ψһ��ʶ

	bullettypename type;		//�ӵ�����,�������ݲ����

	//Circle circle;		//bullet��Բ(x,y,radium)
	double x;
	double y;

	double rotation;	//����Ƕ�
	//double vx,vy,vr;

	int explode;		//�Ƿ��ж���ը���򷴵�֮�ࣩ
};

struct Record_HitInformation
{
	int entityID;	//����MovieClip��Ψһ��ʶ

	bullettypename type;

	double x;
	double y;

	//ֱ�����ӵ�ר��
	double ex;
	double ey;
};

struct Record_ArsenalInformation
{
	int respawning_time_left;
};



struct Record_FrameInformation
{
	//Robot
	Record_RobotInformation robotInformation[Info_MaxRobots];

	//Bullet
	Record_BulletInformation bulletInformation[Info_MaxBullets];

	//Bullet����Ч��
	Record_HitInformation hitInformation[Info_MaxBullets];

	//�����֡��Ϣ
	Record_ArsenalInformation arsenalInformation[Info_MaxArsenals];


	//Obstacle Info
	//Circle obstacle[Info_MaxObstacles];		//�ϰ���
	//����Ƿ�Ҫ������
};