//#include "stdafx.h"
#include "../stdafx.h"
#include "struct.h"

//last update: 2013-10-30	optimize Circle����ײ���


Point myRotate(double x,double y,double s,double c,bool re)
{
	Point result;
	if(re)
	{
		result.x=x*c+y*s;
		result.y=y*c-x*s;
	}
	else
	{
		result.x=x*c-y*s;
		result.y=y*c+x*s;
	}
	return result;
}




double AngleAdjust(double &c)
{
	while(c>180)
	{
		c-=360;
	}
	while(c<=-180)
	{
		c+=360;
	}
	return c;
}

double AnglePlus(double a,double b)
{
	//�Ƕ���Ӽ�
	double c=a+b;
	AngleAdjust(c);
	return c;
}

double AngleToRadian(double angle)
{
	//�Ƕ�ת����
	return angle/180*PI;
}

double RadianToAngle(double radian)
{
	return radian/PI*180;
}


bool HitTestCirclePoint(const Circle &c,const double &x,const double &y)
{
	//���ص�(x,y)�Ƿ���Բc��
	//newly added 2013-10-30
	double dx=c.x-x,	dy=c.y-y;

	if(abs(dx)>c.r || abs(dy)>c.r)
	{
		return false;
	}

	double dis2=dx*dx+dy*dy;
	return (c.r*c.r>dis2);
}


bool HitTestCircles(const Circle &c1, const Circle &c2)
{
	//������Բ�Ƿ��ཻ�����������ཻ

	//2013-10-30�Ż�
	//��׼����ǰ�������Բ���
	
	double xx=c1.x-c2.x,	yy=c1.y-c2.y;
	double rr=c1.r+c2.r;

	if(abs(xx)>rr || abs(yy)>rr)
	{
		return false;
	}

	double dis2=xx*xx+yy*yy;
	
	return (rr*rr>=dis2);
}

bool HitTestBeamCircle(const Beam &b,const Circle &c)
{
	/*
	//2014_3_1 �� ԭ����b.x>c.y
	if(b.x>c.x && b.rotation>=-90 && b.rotation<=90)
	{
		//����
		return false;
	}
	else if(b.x<c.x && (b.rotation<=-90 || b.rotation>=90))
	{
		//����
		return false;
	}
	*/
	double br=AngleToRadian(b.rotation);
	double k=tan(br);
	double g=k*c.x-c.y-k*b.x+b.y;	//ֱ��һ��ʽ��ֵ
	double d2=g*g/(k*k+1);			//Բ�ĵ�ֱ�߾���ƽ��
	//return (c.r*c.r>=d2);
	if(c.r*c.r>=d2)
	{
		//ֱ����Բ�Ѿ��ཻ�������жϷ���
		double dy=c.y-b.y;
		//double dx=c.x-b.x;
		double ss=sin(br);
		
		//2014-3-19 �޸�
		if(abs(ss)>0.707)	//root2/2  45o
		{
			//2014-3-19
			//�����������������
			//k->0ʱ���������ſ����෴���ǻ���Ŀ���
			if((ss>0 && dy>0)||(ss<0 && dy<0))
			{
				return true;
			}
		}
		else
		{
			double dx=c.x-b.x;
			double cc=cos(br);
			if((cc>0 && dx>0)||(cc<0 && dx<0))
			{
				return true;
			}
		}
	}
	return false;
}

bool HitTestBeamBox(const Beam &bm,const Box &bx)
{
	//���Ǻ����ƣ��߽��y=m,x=n
	double k=tan(AngleToRadian(bm.rotation));
	double x1,y1,x2,y2;
	if(k>0)
	{
		x1=bx.x+bx.width/2;
		y1=bx.y-bx.height/2;

		x2=bx.x-bx.width/2;
		y2=bx.y+bx.height/2;
	}
	else if(k<0)
	{
		x1=bx.x+bx.width/2;
		y1=bx.y+bx.height/2;

		x2=bx.x-bx.width/2;
		y2=bx.y-bx.height/2;
	}
	else
	{
		//k==0	y=m
	}

	double v1=k*x1-y1-k*bm.x+bm.y;
	double v2=k*x2-y2-k*bm.x+bm.y;

	//���߲����ཻ?
	if((v1>0 && v2<0) ||(v1<0 && v2>0))
	{
		return true;
	}


	return false;

}


Point GetHitPoint(Beam b,Circle c)
{
	Point p;
	p.x=0;
	p.y=0;

	Vector2D co;		//Բ��
	co.x=c.x;
	co.y=c.y;

	Vector2D bb;		//�������
	bb.x=b.x;
	bb.y=b.y;

	//2014-3-17
	//����̫����������������
	Vector2D bs_to_c;	//������㵽Բ��
	Vector2D bs;		//���ߵ�����

	bs_to_c.x=c.x-b.x;
	bs_to_c.y=c.y-b.y;


	double brr=AngleToRadian(b.rotation);
	double k=tan(brr);//ֱ��б��
	double g=k*c.x-c.y-k*b.x+b.y;	//ֱ��һ��ʽ��ֵ
	double d_2=g*g/(k*k+1);			//Բ�ĵ�ֱ�߾���ƽ��

	


	double dbc_2=bs_to_c.LengthSq();	//Բ�ĵ�����������ƽ��
	double d=sqrt(dbc_2-d_2);			//������㵽���㳤��


	bs.x=cos(brr)*d;
	bs.y=sin(brr)*d;



	Vector2D c_to_v=bs-bs_to_c;		//Բ�ĵ�����

	
	double gap=sqrt(c.r*c.r-d_2);		//���߷��򻬶�����

	Vector2D b_slide=bs.GetReverse();		//������ƽ�з���Ļ�������
	b_slide.Normalize();
	b_slide*=gap;

	Vector2D hit_point=co+c_to_v+b_slide;

	p.x=hit_point.x;
	p.y=hit_point.y;

	/*
	//TODO..
	//�Ѿ�ȷ�������ཻ
	//�ҵ�b��c�Ľ���

	//��δ����rotation=90�����
	double brr=AngleToRadian(b.rotation);
	double k=tan(brr);//ֱ��б��
	double g=k*c.x-c.y-k*b.x+b.y;	//ֱ��һ��ʽ��ֵ
	double d=abs(g)/sqrt(k*k+1);			//Բ�ĵ�ֱ�߾���
	
	double rr=AnglePlus(b.rotation,90);		//���߽Ƕ�(��Բ�ķ������ܷ���)
	//����������⣬������ܷ���
	


	double rrr=AngleToRadian(rr);
	
	double gap=sqrt(c.r*c.r-d*d);	//�����ϻ�������/2

	double sign;
	if(g>0)
	{
		//yϵ��Ϊ����g>0Բ����ֱ���·���������
		sign=1;
	}
	else
	{
		sign=-1;
	}


	//��������
	double xc=c.x+sign*d*cos(rrr);
	double yc=c.y+sign*d*sin(rrr);

	//double x1=xc+gap*cos(brr);
	//double x2=xc-gap*cos(brr);

	if(b.x<xc)
	{
		if(cos(brr)>0)
		{
			p.x=xc-gap*cos(brr);
			p.y=yc-gap*sin(brr);
		}
		else
		{
			p.x=xc+gap*cos(brr);
			p.y=yc+gap*sin(brr);
		}
	}
	else
	{
		if(cos(brr)>0)
		{
			p.x=xc+gap*cos(brr);
			p.y=yc+gap*sin(brr);
		}
		else
		{
			p.x=xc-gap*cos(brr);
			p.y=yc-gap*sin(brr);
		}
	}

	//1.������c��Բ����b�Ĵ�����b�Ľ���
	//2.���ɶ��������һֱ�Ǳ߳���
	*/

	return p;
}











void SetSeed()
{
	//ÿ�γ�������ǰ������
	srand( (unsigned)time( 0 )+7); 
}

double Random0_1(){
	//����0-1��������ĺ���,//zz����
	int temp;
	double r;

	//��ʵ���ӷ���ÿһ�����й�����һ�ξ�����
	temp=rand()%1000;
	r=(double)temp/1000;
	return r;
}

int Random(int minv,int maxv)
{
	//����[minv,maxv]֮���������������

	//2014-1-22
	//���Կ��������ؿ��巽��
	if(maxv<minv)
	{
		int temp=maxv;
		maxv=minv;
		minv=temp;
	}

	double r=Random0_1();
	int num_gap=maxv-minv+1;
	double gap=1/(double)num_gap;
	int i;
	double current=gap;

	for(i=0;i<num_gap;i++)
	{
		if(current>r)
		{
			return minv+i;
		}
		current+=gap;
	}
	
	assert("�����������" && 0);
	
	return 0;
	//return rand()%(maxv-minv+1)+minv;

	
}