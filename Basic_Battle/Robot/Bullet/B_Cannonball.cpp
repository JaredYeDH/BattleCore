//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_Cannonball.h"


B_Cannonball::B_Cannonball(void)
{
	LoadData(BT_Cannonball);
	shapeType=S_Circle;
	Init_GameEntity();
}

B_Cannonball::B_Cannonball(double x,double y,double rr,int launcherIDX)
{
	shapeType=S_Circle;
	LoadData(BT_Cannonball);

	GeneralInit(x,y,rr,launcherIDX);

}


B_Cannonball::~B_Cannonball(void)
{
}

/*
void B_Cannonball::Hit(Robot & robot)
{
	//��ũ�ڵ�������ͨ���ڵ�
	robot.GetEngine().ModifyHp(-damage);
	//����һ��Hit��Ϣ��RecordManager��
	//д��flash��Ķ�����Ϣ����RecordManager��ɣ�
}
*/
bool B_Cannonball::HitObstcale(Obstacle& ob)
{
	//��ʧ����true
	return true;
}

void B_Cannonball::Hit(Robot& robot)
{
	robot.GetEngine().ModifyHp(-damage);

	Robot* r=pBattlefield->GetRobotPointer(launcherID);
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);
}

