#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"
class B_TrackingMissile :
	public Bullet
{
private:
	int chaseID;	//׷�ٵĻ����±�

	double spinSpeed;	//��ת�ٶ�

public:
	B_TrackingMissile(void);
	B_TrackingMissile(double x,double y,double rr,int launcherIDX,int chaseIDX);
	virtual ~B_TrackingMissile(void);
	virtual bullettypename GetType(){return BT_TrackingMissile;}
	virtual bool HitObstcale(Obstacle &);
	virtual void Hit(Robot &);

	//�����켣
	int GetChaseID();
	void AdjustDirection(Robot &);
};