//#include "../../stdafx.h"
//#include "stdafx.h"
#include "../../../stdafx.h"
#include "Engine.h"
#include "E_AFV.h"


E_AFV::E_AFV(void)
{
	shapeType=S_Circle;
	LoadData(ET_AFV);
	InitData();
	Init_GameEntity();
}


E_AFV::~E_AFV(void)
{
}


bool E_AFV::Run(int mnplt)
{
	//9-6 ���������ƺ�û���ٶ����ޣ�

	//װ�׳���AFV��
	//����������Ϸ�е�vehicle, vr�����ڵ�ǰ�ٶ�
	//accelerationΪ���ٱ�����(0,1)
	//m>0����,<=0ɲ��
	double speed=sqrt(vx*vx+vy*vy);
	double tempr=AngleToRadian(rotation);
	if(mnplt>0)
	{
		speed*=(acceleration+1);

		if(speed>=maxSpeed)
		{
			speed=maxSpeed;
		}
		else if(speed<0.1)
		{
			speed=0.1;
		}

		vx=speed*cos(tempr);
		vy=speed*sin(tempr);



		return true;
		//pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),R_Run,//myid)
	}
	else
	{
		//��δ����friction�����ڰ汾�ɿ��ǵ��β��죨ɳ�أ����ͣ�����ȣ�
		speed*=(1-acceleration);

		if(speed<=0.1)
		{
			speed=0;
		}

		vx=speed*cos(tempr);
		vy=speed*sin(tempr);

		return false;
	}
}

bool E_AFV::Turn(int mnplt)
{
	//����������Ϸ�е�vehicle, vr�����ڵ�ǰ�ٶȣ�ת����������ͬʱ����
	//mnplt>0˳ʱ��,<0��ʱ��,0��ת
	double k=sqrt(vx*vx+vy*vy)/maxSpeed;
	if(mnplt>0)
	{
		vr=rotationSpeed*k;
		return true;
	}
	else if(mnplt<0)
	{
		vr=-rotationSpeed*k;
		return true;
	}
	else
	{
		vr=0;
		return false;
	}
}