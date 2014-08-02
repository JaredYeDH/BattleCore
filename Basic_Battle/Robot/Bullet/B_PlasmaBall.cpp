//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_PlasmaBall.h"
#include "../../DataLoader.h"
#include "../../Battlefield.h"



B_PlasmaBall::B_PlasmaBall(void)
{
	
}

B_PlasmaBall::B_PlasmaBall(double x,double y,double rr,int launcherIDX)
{
	left_bounce_time=pDataLoader->GetGameData()->bounce_time;

	shapeType=S_Circle;
	LoadData(BT_PlasmaBall);

	GeneralInit(x,y,rr,launcherIDX);

}


B_PlasmaBall::~B_PlasmaBall(void)
{
}



bool B_PlasmaBall::HitObstcale(Obstacle & ob)
{

	//�����ӷ���
	if(left_bounce_time>0)
	{
		left_bounce_time--;
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
			//9-3 �������ڻ���bug
			//�ϰ�

			//��λ�ý���������atan2��ȡ�Ƕ�ѡ��ʵ�ʵ��е�
			double dx=circle.x-ob.GetCircle().x;
			double dy=circle.y-ob.GetCircle().y;

			double rar=atan2(dy,dx);


			circle.x=ob.GetCircle().r*cos(rar)+ob.GetCircle().x;
			circle.y=ob.GetCircle().r*sin(rar)+ob.GetCircle().y;

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
		//û��ʧ

		//����һ�������õ�hitinfo

		return false;
	}

	return true;

}

bool B_PlasmaBall::Hit(Robot& robot)
{
	return GeneralHit(robot);
}

bool B_PlasmaBall::HitFlyEnd()
{
	return false;
}

