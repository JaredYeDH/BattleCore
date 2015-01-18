#pragma once

class BattleMap
{
protected:
	double B_Left;
	double B_Right;
	double B_Up;
	double B_Down;
	Box boundary;		//ս���߽��Ǹ�����
	int num_obstacle;
	vector<Obstacle*> pObstacle;		//�ϰ���
	Point birthPoint[Info_MaxRobots];		//������
	int num_arsenal;
	vector<Arsenal*> pArsenal;			//�����
public:
	BattleMap();
	~BattleMap();

	void ConstructMap_Default();


	//construct map according to map config
	void ConstructMap_Config(const char *);
};