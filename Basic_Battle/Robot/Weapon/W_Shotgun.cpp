//#include "../../stdafx.h"
//#include "stdafx.h"
#include "../../../stdafx.h"
#include "W_Shotgun.h"


int W_Shotgun::burst=pDataLoader->GetGameData()->burst_Shotgun;
double W_Shotgun::gapRotation=pDataLoader->GetGameData()->gapRotation_Shotgun;

W_Shotgun::W_Shotgun(void)
{
	LoadData(WT_Shotgun);
	//burst=pDataLoader->GetGameData()->burst_Shotgun;
	//gapRotation=pDataLoader->GetGameData()->gapRotation_Shotgun;
	burst=pDataLoader->GetGameData()->burst_Shotgun;
	gapRotation=pDataLoader->GetGameData()->gapRotation_Shotgun;

	InitData();
	Init_GameEntity();
}


W_Shotgun::~W_Shotgun(void)
{
}


bool W_Shotgun::Fire(int mnplt)
{
	if(General_Fire(mnplt))
	{
		double p=inaccuracy*(Random0_1()-0.5);//ƫ�ƽǶ�
		//double r=AnglePlus(AnglePlus(rotation,engineRotation),p);//�Ƕ�
		double r=AnglePlus(rotation,p);
		double a=AngleToRadian(r);//����

		double b,c;
		int i;
		for(i=0;i<burst;i++)
		{
			//����burst��
			b=(double)r+gapRotation*(int)(i-burst/2);//��ʽ��ȷ��Ҫʵ��
			c=AngleToRadian(b);
			//b=(double)a+AngleToRadian(gapRotation)*(int)(i-burst/2);	//��ʽ��ȷ��Ҫʵ��
			pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
				Add_Bullet,
				new B_ShotgunBall(circle.r*cos(c)+circle.x,circle.r*sin(c)+circle.y,b,pRobot->GetID()));
		}

		pRobot->GetAchievementData().Add_Fire();
		return true;
	}
	return false;
}