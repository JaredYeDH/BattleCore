#pragma once

class WeaponData
{
protected:
	weapontypename type;

	string name;			//��������
	int damage;			//����
	int Ammo;			//���У����ҩ����
	int coolingTime;	//��ȴʱ��
	double inaccuracy;	//��׼ȷ�ȣ���������Ƕȣ�
	double rotationSpeed;	//������ת�ٶȣ���󣿣�

public:
	WeaponData();
	WeaponData(weapontypename);
	~WeaponData();

	weapontypename getType();
	string getName();
	int getDamage();
	int getAmmo();
	int getCoolingTime();
	double getInaccuracy();
	double getRotationSpeed();

	void LoadStaticData(weapontypename);
};