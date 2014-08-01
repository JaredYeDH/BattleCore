//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_RPGBall.h"

//double B_RPGBall::Explode_R=pDataLoader->GetGameData()->explodeR_RPGBall;

B_RPGBall::B_RPGBall(void)
{
}


B_RPGBall::B_RPGBall(double x,double y,double rr,int launcherIDX)
{
	Explode_R=pDataLoader->GetGameData()->explodeR_RPGBall;
	acceleration_rpgball=pDataLoader->GetGameData()->acceleration_RPGBall;


	shapeType=S_Circle;
	LoadData(BT_RPGBall);
	//Explode_R=pDataLoader->GetGameData()->explodeR_RPGBall;


	GeneralInit(x,y,rr,launcherIDX);

	/*
	launcherID=launcherIDX;

	circle.x=x;
	circle.y=y;
	//
	circle.r=0;

	rotation=rr;
	rr=AngleToRadian(rotation);
	//...
	//speed=.....//���Խű�������
	vx=speed*cos(rr);
	vy=speed*sin(rr);

	vr=0;
	*/
}

B_RPGBall::~B_RPGBall(void)
{
}


void B_RPGBall::Hit(Robot & robot)
{
	//������Χ��ը
	Circle* expld=new Circle;
	expld->x=circle.x;
	expld->y=circle.y;
	expld->r=Explode_R;

	pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
		Explode,expld);
	//Dispatch_Remove_Event();ɾ����Battlefield.cpp����

	//TODO:��Χ�˺���ͳ�Ƽ��㣿
	Robot* r=pBattlefield->GetRobotPointer(launcherID);
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);
}

bool B_RPGBall::HitObstcale(Obstacle & ob)
{
	//������Χ��ը
	Circle* expld=new Circle;
	expld->x=circle.x;
	expld->y=circle.y;
	expld->r=Explode_R;

	pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
		Explode,expld);

	return true;
	//Dispatch_Remove_Event();ɾ����Battlefield.cpp����
}



void B_RPGBall::Update()
{
	//��������٣�����GameEntity::Update
	circle.x+=vx;
	circle.y+=vy;
	//rotation=AnglePlus(rotation,vr);
	vx*=acceleration_rpgball;
	vy*=acceleration_rpgball;

	//test
	//cout<<"RPG�����õ����µ�Update\n";
}

void B_RPGBall::HitFlyEnd()
{
}