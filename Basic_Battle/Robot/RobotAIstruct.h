//��Ҫ��RobotAIFactoryͬ��

#pragma once

#define Info_MaxArsenals 2
#define Info_MaxObstacles 5
#define Info_MaxRobots 2
#define Info_MaxBullets 200



enum weapontypename
{
	WT_Cannon
	,WT_Shotgun
	,WT_RPG
	,WT_Machinegun
	,WT_Prism
	,WT_Tesla
	,WT_PlasmaTorch
	,WT_MissileLauncher
	,WT_ElectricSaw

	//����
	,WT_GrenadeThrower
};

enum enginetypename
{
	ET_Spider
	,ET_Robotman
	,ET_AFV
	,ET_UFO
};

enum bullettypename
{
	BT_Cannonball
	,BT_ShotgunBall
	,BT_RPGBall
	,BT_MachinegunBall
	,BT_Prism_Laser
	,BT_Tesla_Lightning
	,BT_PlasmaBall
	,BT_TrackingMissile
	,BT_ElectricSaw
	
	//�����������Ϸ��ҿɼ�(Ӧ��������ֱ�ӷ����)����
	,BT_Grenade
	


	//�����ǹ����Ե�����
	
	,BT_NULL
};



struct RobotAI_Order
{
	//����RobotAI��Execute(..)�����ĶԻ������´�Ĳ�������
	int fire;	//����Fire(int mnplt)�Ĳ�����
	int wturn;	//����Turn(int mnplt)�Ĳ�����
	int run;	//����Run(int mnplt)�Ĳ�����
	int eturn;	//����Turn(int mnplt)�Ĳ�����

	RobotAI_Order(){fire=0;wturn=0;run=0;eturn=0;}
};


struct RobotAI_RobotInformation
{
	//����RobotAI��Execute(..)�������ṩ������AI��Robot��Ϣ
	int entityID;

	int id;		//Battlefield.pRobot���±�

	weapontypename weaponTypeName;	//��������
	enginetypename engineTypeName;	//��������		//�ܸо�����Щ����������ô��������İ취����һ��������ʾ��ͬ��������ʵ�á���
	//�������Ը������������������У�����DataLoader.hҲҪ��RobotAIFactoryһ��

	//��ǰ����
	Circle circle;		//engine��Բ(x,y,radium)
	double engineRotation;	//����Ƕ�
	double weaponRotation;	//�����Ƕȣ�������棩
	double vx,vy,vr;
	
	int hp;

	//�������ǲ��ṩ��
	int remainingAmmo;		
	int cooling;

	//bool manipulation;		//�Ƿ�ɲ��ݣ���������
};

struct RobotAI_BulletInformation
{
	//����RobotAI��Execute(..)�������ṩ������AI��Bullet��Ϣ
	int entityID;

	//���������ߵ��±�
	int launcherID;
	

	//temp
	bullettypename type;		//�ӵ�����,�������ݲ����

	Circle circle;		//bullet��Բ(x,y,radium)
	double rotation;	//����Ƕ�
	double vx,vy,vr;
};


struct RobotAI_ArsenalInformation
{
	Circle circle;
	int respawning_time;
};

struct RobotAI_BattlefieldInformation
{
	//2013-8-30�޸�

	//����RobotAI��Execute(..)�������ṩ������AI��Battlefield��Ϣ

	//��ʹ��������������ˣ���Ϊ��Ҫ��������ߵ�

	//Robot
	int num_robot;	//�����Ѿ����˵�

	RobotAI_RobotInformation robotInformation[Info_MaxRobots];

	//Bullet
	int num_bullet;

	RobotAI_BulletInformation bulletInformation[Info_MaxBullets];

	//Obstacle Info
	int num_obstacle;

	Circle obstacle[Info_MaxObstacles];		//�ϰ���

	//Arsenal Info
	int num_arsenal;

	RobotAI_ArsenalInformation arsenal[Info_MaxArsenals];


	//boundary
	Box boundary;		//�߽�
};