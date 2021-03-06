#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"
class B_ShotgunBall :
	public Bullet
{
public:
	B_ShotgunBall(void);
	B_ShotgunBall(double,double,double,int launcherIDX);
	virtual bullettypename GetType(){return type;}
	virtual ~B_ShotgunBall(void);
	virtual bool HitObstcale(Obstacle &);
	virtual bool Hit(Robot &);
	virtual bool HitFlyEnd();
	//virtual void AdjustDirection(Robot &);
};

