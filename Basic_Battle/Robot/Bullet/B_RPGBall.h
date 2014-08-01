#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"
class B_RPGBall :
	public Bullet
{
protected:
	double Explode_R;
	
	double acceleration_rpgball;	//��������ٶ�

public:
	B_RPGBall(void);
	B_RPGBall(double x,double y,double rr,int launcherIDX);
	virtual ~B_RPGBall(void);
	virtual bullettypename GetType(){return BT_RPGBall;}
	virtual void Hit(Robot &);		//���������ײ��Ч������
	virtual bool HitObstcale(Obstacle &);
	//virtual void AdjustDirection(Robot &);

	virtual void Update();	//����������н�������GameEntity��
};

