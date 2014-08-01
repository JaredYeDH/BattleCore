#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"

//�̻�һ���߶εıر�Ҫ�أ�
//�ؼ����߶��յ�Ļ��

class B_Prism_Laser :
	public Bullet
{
protected:
	//Beam line;	//����

public:
	B_Prism_Laser(void);
	B_Prism_Laser(double x,double y,double rr,int launcherIDX);
	virtual ~B_Prism_Laser(void);
	virtual bullettypename GetType(){return BT_Prism_Laser;}
	virtual bool HitObstcale(Obstacle &);
	virtual void Hit(Robot &);
	//virtual void AdjustDirection(Robot &);
};

