//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_Prism_Laser.h"


B_Prism_Laser::B_Prism_Laser(void)
{
	shapeType=S_Beam;
	//LoadData(BT_Prism_Laser);
}

B_Prism_Laser::B_Prism_Laser(double x,double y,double rr,int launcherIDX)
{
	shapeType=S_Beam;
	LoadData(BT_Prism_Laser);
	launcherID=launcherIDX;

	beam.x=x;
	beam.y=y;
	beam.rotation=rr;

	rotation=0;		//������

	vx=0;
	vy=0;
	vr=0;
}



B_Prism_Laser::~B_Prism_Laser(void)
{
}

bool B_Prism_Laser::HitObstcale(Obstacle& ob)
{
	return GeneralHitObstcale(ob);
}
bool B_Prism_Laser::Hit(Robot& robot)
{
	return GeneralHit(robot);
}

bool B_Prism_Laser::HitFlyEnd()
{
	return false;
}
