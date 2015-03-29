//#include "../../stdafx.h"
//#include "stdafx.h"
#include "../../../stdafx.h"
#include "E_UFO.h"


E_UFO::E_UFO(enginetypename t)
{
	shapeType=S_Circle;
	LoadData(t);
	InitData();
	Init_GameEntity();
}


E_UFO::~E_UFO(void)
{
}


bool E_UFO::Run(int mnplt)
{
	//�ĸ�(UFO)
	//Ʈ������ʽ�����ٶ����ٶ���ȫ�ֿ�
	//==0�����٣�������rotation������������
	

	

	if(mnplt!=0)
	{
		double tempr=AngleToRadian(rotation);
		//����UFO��acceleration�Ǿ���ֵ������AFV�ı���
		vx+=acceleration*cos(tempr);
		vy+=acceleration*sin(tempr);

		if(maxSpeed*maxSpeed<vx*vx+vy*vy)
		{
			//2014-3-25����
			double new_tempr=atan2(vy,vx);
			vx=maxSpeed*cos(new_tempr);
			vy=maxSpeed*sin(new_tempr);
		}

		return true;
	}
	return false;
	
}

bool E_UFO::Turn(int mnplt)
{
	//>0˳ʱ��,<0��ʱ��
	if(mnplt>0)
	{
		vr=rotationSpeed;
		return true;
	}
	else if(mnplt<0)
	{
		vr=-rotationSpeed;
		return true;
	}
	else
	{
		vr=0;
		return false;
	}
}