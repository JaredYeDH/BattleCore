//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_Grenade.h"
#include "../../DataLoader.h"
#include "../../Battlefield.h"



B_Grenade::B_Grenade(void)
{
	
}

B_Grenade::B_Grenade(double x,double y,double rr,int launcherIDX)
{
	Explode_R=pDataLoader->GetGameData()->explodeR_Grenade;

	shapeType=S_Circle;
	LoadData(BT_Grenade);

	GeneralInit(x,y,rr,launcherIDX);

}


B_Grenade::~B_Grenade(void)
{
}

void B_Grenade::HitCircleBounce(GameEntity * entity)
{
	//��λ�ý���������atan2��ȡ�Ƕ�ѡ��ʵ�ʵ��е�
		double dx=circle.x-(entity->GetCircle().x);
		double dy=circle.y-(entity->GetCircle().y);

		double rar=atan2(dy,dx);


		circle.x=(entity->GetCircle().r)*cos(rar)+(entity->GetCircle().x);
		circle.y=(entity->GetCircle().r)*sin(rar)+(entity->GetCircle().y);

		//vx,vyת��Ϊ�����ٶ�vp�������ٶ�vn
		//�������ٶ�vn

		//9-3 ����������(��ת�ķ���)
		//rar+=PI/2;		//���߽Ƕ�
		if(rar>=0 && rar<=PI)
		{
			rar=rar-PI/2;
		}
		else if(rar<=0 && rar>=-PI)
		{
			rar=rar+PI/2;
		}


		//dx=circle.x-ob.GetCircle().x;
		//dy=circle.y-ob.GetCircle().y;
		double c=cos(rar);	//cos
		double s=sin(rar);	//sin

		//��ת����ϵ���������ٶ�
		//double x2=c*dx+s*dy;
		//double y2=c*dy-s*dx;
		double vx2=c*vx+s*vy;
		double vy2=c*vy-s*vx;

		//��ת�����ٶȣ�vy��
		vy2=-vy2;
		vx=c*vx2-s*vy2;
		vy=c*vy2+s*vx2;
}

bool B_Grenade::HitObstcale(Obstacle & ob)
{
	if(ob.GetCircle().r<=0.01)
	{
		//ս���߽�
		//����������е�������
		if(circle.x<=pBattlefield->Get_B_Left())
		{
			//�򻯵Ľ�������
			circle.x=pBattlefield->Get_B_Left();
			vx=-vx;
		}
		else if(circle.x>=pBattlefield->Get_B_Right())
		{
			circle.x=pBattlefield->Get_B_Right();
			vx=-vx;
		}
		else if(circle.y<=pBattlefield->Get_B_Up())
		{
			circle.y=pBattlefield->Get_B_Up();
			vy=-vy;
		}
		else if(circle.y>=pBattlefield->Get_B_Down())
		{
			circle.y=pBattlefield->Get_B_Down();
			vy=-vy;
		}
	}
	else
	{
		HitCircleBounce(&ob);
	}
	//û��ʧ

	return false;

}

bool B_Grenade::Hit(Robot& robot)
{
	//����������ը
	HitCircleBounce(&robot.GetEngine());
	return false;
}

bool B_Grenade::HitFlyEnd()
{
	//������Χ��ը
	Circle* expld=new Circle;
	expld->x=circle.x;
	expld->y=circle.y;
	expld->r=Explode_R;

	pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
		Explode_Grenade,expld);
	//Dispatch_Remove_Event();ɾ����Battlefield.cpp����

	//TODO:��Χ�˺���ͳ�Ƽ��㣿
	Robot* r=pBattlefield->GetRobotPointer(launcherID);
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);

	return true;
}

