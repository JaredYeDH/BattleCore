//#include "stdafx.h"
#include "../stdafx.h"
#include "struct.h"
#include "GameEntity.h"

GameEntity::GameEntity(void)
{
}


GameEntity::~GameEntity(void)
{
}


void GameEntity::Update()
{
	//onEnterFrame
	circle.x+=vx;
	circle.y+=vy;
	rotation=AnglePlus(rotation,vr);
}


/*
void GameEntity::MomentumHit(GameEntity &g1,GameEntity &g2)
{
	//�򻯺����������ײ
	//�����˺���Ե�ǰ���ٶ�
	//��ʵ���Ƕ�����ײ
	g1.SetX(g1.GetCircle().x-g1.GetVX());
	g1.SetY(g1.GetCircle().y-g1.GetVY());

	g2.SetX(g2.GetCircle().x-g2.GetVX());
	g2.SetY(g2.GetCircle().y-g2.GetVY());

	//2014_3_1
	//��Ӧ���ٶȷ���
	g1.SetVX(-g1.GetVX());
	g1.SetVY(-g1.GetVY());

	g2.SetVX(-g2.GetVX());
	g2.SetVY(-g2.GetVY());
}

void GameEntity::MomentumHit_Half(GameEntity &g1,GameEntity &g2)
{
	g1.SetX(g1.GetCircle().x-g1.GetVX());
	g1.SetY(g1.GetCircle().y-g1.GetVY());

	//2014_3_1
	//��Ӧ���ٶȷ��򣬲�Ȼ�ͻ���ɵ���ס
	g1.SetVX(-g1.GetVX());
	g1.SetVY(-g1.GetVY());

	//g2�̶�
	//g2.SetX(g2.GetCircle().x-g2.GetVX());
	//g2.SetY(g2.GetCircle().y-g2.GetVY());
}
*/


void GameEntity::MomentumHit(GameEntity &g1,GameEntity &g2)
{
	//ֻ����������Բ

	//�ο�flash

	


	//ȷ���Ѿ���ײ��
	double vx1,vy1,vr1;
	double vx2,vy2,vr2;

	//2014-3-15
	double vx1o,vy1o,vr1o;
	double vx2o,vy2o,vr2o;
	g1.GetVelocity(vx1o,vy1o,vr1o);
	g2.GetVelocity(vx2o,vy2o,vr2o);
	//���ڴֱ�����λ��


	g1.GetVelocity(vx1,vy1,vr1);
	g2.GetVelocity(vx2,vy2,vr2);




	double r1=g1.GetCircle().r,r2=g2.GetCircle().r;

	double dx=g2.GetCircle().x-g1.GetCircle().x;
	double dy=g2.GetCircle().y-g1.GetCircle().y;
	double dist=sqrt(dx*dx+dy*dy);



	double angle=atan2(dy,dx);
	double s=sin(angle);
	double c=cos(angle);

	


	Point pos1;
	pos1.x=0;
	pos1.y=0;
	//g2���g1����ϵ
	Point pos2=myRotate(dx,dy,s,c,true);


	//g1�ٶȵ���
	Point vel1=myRotate(vx1,vy1,s,c,true);
	//g2�ٶȵ���
	Point vel2=myRotate(vx2,vy2,s,c,true);


	//����ֻ��vx�����ã�vy�����ٶȲ��ÿ���


	
	//��ײ��Ӧ
	double vxTotal=vel1.x-vel2.x;

	//��������������
	//vel1.x=((mass1-mass2)*vel1.x+2*mass2*vel2.x)/(mass1+mass2);
	//vel2.x=vxTotal+vel1.x;

	//�����������
	vel1.x=vel2.x;
	vel2.x=vxTotal+vel1.x;
	

	

	//����λ�ã���ֹ��ס
	//3_11,������Ϊ��
	double absV=abs(vel1.x)+abs(vel2.x);
	if(absV==0)
	{
		double overlap=(r1+r2)-abs(pos1.x-pos2.x);	//���������Robot��Bullet������������ײ���뾶��һ���ֿɼ�

		double tmp=pos1.x>pos2.x ? 1 : -1;
		pos1.x+=tmp*overlap;
		pos2.x+=-tmp*overlap;
	}
	else
	{
		double overlap=(r1+r2)-abs(pos1.x-pos2.x);	//���������Robot��Bullet������������ײ���뾶��һ���ֿɼ�
		pos1.x+=vel1.x/absV*overlap;
		pos2.x+=vel2.x/absV*overlap;
	}



	//��ת��ȥ
	Point pos1F=myRotate(pos1.x,pos1.y,s,c,false);
	Point pos2F=myRotate(pos2.x,pos2.y,s,c,false);


	/*
	//��������Ļ����ϵ
	g2.SetX(g1.GetCircle().x+pos2F.x);
	g2.SetY(g1.GetCircle().y+pos2F.y);
	g1.SetX(g1.GetCircle().x+pos1F.x);
	g1.SetY(g1.GetCircle().y+pos1F.y);
	*/
	//2014-3-15�ֱ�����λ��
	g2.SetX(g2.GetCircle().x-vx2o);
	g2.SetY(g2.GetCircle().y-vy2o);
	g1.SetX(g1.GetCircle().x-vx1o);
	g1.SetY(g1.GetCircle().y-vy1o);




	//���ٶ���ת��ȥ
	Point vel1F=myRotate(vel1.x,vel1.y,s,c,false);
	Point vel2F=myRotate(vel2.x,vel2.y,s,c,false);







	//����ֱ���趨vx,vy��������(��֩��ͻ�����)
	//��Ϊ����vxvyʱ��ֱ���趨ֵ���ǵ���

	g1.SetVX(vel1F.x);
	g1.SetVY(vel1F.y);
	g2.SetVX(vel2F.x);
	g2.SetVY(vel2F.y);
}

void GameEntity::MomentumHit_Half(GameEntity &g1,GameEntity &g2)
{
	//ֻ����������Բ

	//g2�̶�����,ֻҪ��һ���������ϵ��g1���ٶ�
	//�ο�flash

	//ȷ���Ѿ���ײ��
	double vx1,vy1,vr1;
	

	g1.GetVelocity(vx1,vy1,vr1);

	double r1=g1.GetCircle().r,r2=g2.GetCircle().r;
	double dx=g2.GetCircle().x-g1.GetCircle().x;
	double dy=g2.GetCircle().y-g1.GetCircle().y;
	double dist=sqrt(dx*dx+dy*dy);






	double angle=atan2(dy,dx);
	double s=sin(angle);
	double c=cos(angle);

	Point pos1;
	pos1.x=0;
	pos1.y=0;
	//g2���g1����ϵ
	Point pos2=myRotate(dx,dy,s,c,true);


	//g1�ٶȵ���
	Point vel1=myRotate(vx1,vy1,s,c,true);
	


	//����ֻ��vx�����ã�vy�����ٶȲ��ÿ���


	//�����������
	vel1.x=-vel1.x;

	/*
	//����λ�ã���ֹ��ס
	double absV=abs(vel1.x);
	double overlap=(r1+r2)-abs(pos1.x-pos2.x);	//���������Robot��Bullet������������ײ���뾶��һ���ֿɼ�
	pos1.x+=vel1.x/absV*overlap;
	*/
	double tmp=vel1.x>0 ? 1 : -1;		//��vel1.x=0�����

	double overlap=(r1+r2)-abs(pos1.x-pos2.x);

	pos1.x+=tmp*overlap;


	//��ת��ȥ
	Point pos1F=myRotate(pos1.x,pos1.y,s,c,false);
	

	//��������Ļ����ϵ
	
	g1.SetX(g1.GetCircle().x+pos1F.x);
	g1.SetY(g1.GetCircle().y+pos1F.y);

	//���ٶ���ת��ȥ
	Point vel1F=myRotate(vel1.x,vel1.y,s,c,false);
	

	g1.SetVX(vel1F.x);
	g1.SetVY(vel1F.y);

}



/*
void GameEntity::HandleEvent(events msg, void* extraInfo)
{

}
*/


void GameEntity::Init_GameEntity()
{
	vx=0;
	vy=0;
	vr=0;
	rotation=0;

	//shapeType=S_Circle;
}




bool GameEntity::HitTest(GameEntity & ge)
{
	if(shapeType==S_Circle)
	{
		if(ge.GetShape()==S_Circle)
		{
			return HitTestCircles(GetCircle(),ge.GetCircle());
		}
		else if(ge.GetShape()==S_Box)
		{
			//�����ʱû��
			return false;
		}
		else if(ge.GetShape()==S_Beam)
		{
			return HitTestBeamCircle(ge.GetBeam(),circle);
		}
	}
	else if(shapeType==S_Box)
	{
		if(ge.GetShape()==S_Circle)
		{
			//�����ʱû�� circle box
			return false;
		}
		else if(ge.GetShape()==S_Box)
		{
			//�����ʱû�� box box
			return false;
		}
		else if(ge.GetShape()==S_Beam)
		{
			return HitTestBeamBox(ge.GetBeam(),box);
		}
	}
	else if(shapeType==S_Beam)
	{
		if(ge.GetShape()==S_Circle)
		{
			//beam circle
			return HitTestBeamCircle(beam,ge.GetCircle());
		}
		else if(ge.GetShape()==S_Box)
		{
			return HitTestBeamBox(beam,ge.GetBox());
		}
		else if(ge.GetShape()==S_Beam)
		{
			//�����ʱû�� beam beam
			return false;
		}
	}


	return false;
}