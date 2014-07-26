#pragma once
#include "../Robot.h"
#include "../../GameEntity.h"
#include "../../struct.h"
#include "../RobotAIstruct.h"
class Bullet :
	public GameEntity, public BulletData
{
protected:
	//��̬����

	int launcherID;		//������Robot��ID,�Ĺ��ˣ�ԭ����Weapon��,��������������СBUG��


	/*
	bullettypename type;

	string name;		//�ӵ�������
	double speed;		//�ӵ������ٶ�
	int damage;			//����		
	*/

public:
	Bullet(void);
	Bullet(double x,double y,double rr);
	virtual ~Bullet(void);


	void GeneralInit(double x,double y,double rr,int launcherIDX);

	//Update����GameEntity��
	virtual bullettypename GetType()=0;


	virtual void Hit(Robot &)=0;		//���Ҫ���ɾ�ϵͳ˵ʲôҲҪ�����¼����ƣ�����
	virtual bool HitObstcale(Obstacle &)=0;

	void Dispatch_Remove_Event();

	int GetLauncher(){return launcherID;}

	void LoadData(bullettypename);

	virtual void HandleEvent(events msg,void* extraInfo){};

	virtual void AdjustDirection(Robot &)=0;
};

