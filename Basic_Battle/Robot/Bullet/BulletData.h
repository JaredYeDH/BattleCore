#pragma once

class BulletData
{
protected:
	bullettypename type;

	string name;		//�ӵ�������
	double speed;		//�ӵ������ٶ�
	int damage;			//����
public:
	BulletData();
	BulletData(bullettypename);
	~BulletData();

	bullettypename getType();
	string getName();
	double getSpeed();
	int getDamage();

	void LoadStaticData(bullettypename);
};