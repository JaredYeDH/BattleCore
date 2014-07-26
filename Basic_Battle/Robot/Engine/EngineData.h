#pragma once

class EngineData
{
protected:
	//����
	enginetypename type;	//ö������

	string name;		//��������
	double maxSpeed;	//���ǣ���ٶ�(����vx2+vy2)
	int maxHp;				//Ѫ������

	double rotationSpeed;	//�����ת�ٶ�
	double acceleration;	//���ٶȣ�ս��̹�˺�UFO���и����ԣ�

public:
	EngineData();
	EngineData(enginetypename);
	~EngineData();

	enginetypename getType();
	string getName();
	double getMaxSpeed();
	int getMaxHp();
	double getRotationSpeed();
	double getAcceleration();

	void LoadStaticData(enginetypename);
};