#pragma once
#include "../Robot.h"
#include "../../GameEntity.h"
#include "../../struct.h"
#include "../RobotAIstruct.h"
class Bullet :
	public GameEntity, public BulletData
{
protected:

	//2014/8/1ս����pRobot�±�
	int launcherID;		

	int remainingFlyTime;		//��ǰʣ�����ʱ��
	

public:
	Bullet(void);
	Bullet(double x,double y,double rr);
	virtual ~Bullet(void);


	void GeneralInit(double x,double y,double rr,int launcherIDX);

	//Update����GameEntity��
	virtual bullettypename GetType()=0;


	virtual void Hit(Robot &)=0;
	virtual bool HitObstcale(Obstacle &)=0;
	virtual void HitFlyEnd()=0;


	void GeneralHit(Robot &);
	//�����Ƿ���ʧ
	bool GeneralHitObstcale(Obstacle &){return true;}

	//�����Ƿ����ʱ��ľ�
	bool UpdateFlyTime(){remainingFlyTime--;return remainingFlyTime<=0;}


	void Dispatch_Remove_Event();

	int GetLauncher(){return launcherID;}

	void LoadData(bullettypename);

	virtual void HandleEvent(events msg,void* extraInfo){};

	//virtual void AdjustDirection(Robot &)=0;
};

