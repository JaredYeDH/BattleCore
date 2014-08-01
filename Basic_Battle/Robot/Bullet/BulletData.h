#pragma once

class BulletData
{
protected:
	bullettypename type;

	string name;		//�ӵ�������
	double speed;		//�ӵ������ٶ�
	int damage;			//����
	int flyTime;			//����ʱ��
public:
	BulletData();
	BulletData(bullettypename);
	~BulletData();

	bullettypename getType(){return type;}
	string getName(){return name;}
	double getSpeed(){return speed;}
	int getDamage(){return damage;}
	int getFlyTime(){return flyTime;}

	void LoadStaticData(bullettypename);
};