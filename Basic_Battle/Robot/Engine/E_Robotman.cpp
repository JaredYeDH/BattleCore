//#include "../../stdafx.h"
//#include "stdafx.h"
#include "../../../stdafx.h"
#include "E_Robotman.h"

E_Robotman::E_Robotman(void)
{
	shapeType=S_Circle;
	LoadData(ET_Robotman);
	InitData();
	Init_GameEntity();
}


E_Robotman::~E_Robotman(void)
{
}


//��õİ취�����ֶ����ýű�д�����ھͼ��������ˡ�����
bool E_Robotman::Run(int mnplt)
{
	//���λ���(Robotman)û�м��ٹ���ֱ������ǰ��
	//�������mnplt>0ȫ��ǰ��,mnplt<0ȫ�ٺ���,mnplt=0����ֹͣ
	double tempr;
	if(mnplt>0)
	{
		tempr=AngleToRadian(rotation);
		vr=0;
		vx=maxSpeed*cos(tempr);
		vy=maxSpeed*sin(tempr);
		return true;
	}
	else if(mnplt<0)
	{
		tempr=AngleToRadian(rotation);
		vr=0;
		vx=-maxSpeed*cos(tempr);
		vy=-maxSpeed*sin(tempr);
		return true;
	}
	else
	{
		//mnplt==0
		vx=0;
		vy=0;
		return false;
	}
}

bool E_Robotman::Turn(int mnplt)
{
	//���λ���(Robotman)ֻ����վ��ʱת��
	//mnplt>0˳ʱ��,mnplt<0��ʱ��,==0ֹͣת��
	if(mnplt>0)
	{
		vx=0;
		vy=0;
		vr=rotationSpeed;
		return true;
	}
	else if(mnplt<0)
	{
		vx=0;
		vy=0;
		vr=-rotationSpeed;
		return true;
	}
	else
	{
		//mnplt==0
		//vx=0;
		//vy=0;
		vr=0;
		return false;
	}
}