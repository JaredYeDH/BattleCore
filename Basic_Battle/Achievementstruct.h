#pragma once


//ͳ������
#define MAX_INT 99999

//һ�����ף�����ս���ĳɾ�ͳ������
class AchievementData_Battle
{
public:
	//int index;	//��ӦBattlefield��pRobot�±�
	//û��Ҫ��pAchievmentData��pRobot���±걾���Ƕ�Ӧ��

	int fire;	//�������
	int hit;	//���д���
	int damage;	//�ܵ��˺�
	int output;	//����˺�

	//����������ʱ���������������������ٶȰɣ�
	//...
	//���ʱ�䣬���߾���,...


	
	//temp
	void Print()
	{
		cout<<"Fire:"<<fire<<'\n'
			<<"Hit:"<<hit<<'\n'
			<<"Damage:"<<damage<<'\n'
			<<"Output:"<<output<<'\n';
	}

	void Out(ostream& out)
	{
		out<<fire<<','
			<<hit<<','
			<<damage<<','
			<<output;
	}



	void Add_Fire(){fire++;}
	void Add_hit(){hit++;}
	void Add_damage(int d){damage+=d;}
	void Add_output(int o){output+=o;}



	void Init()
	{
		fire=0;
		hit=0;
		damage=0;
		output=0;
	}


	AchievementData_Battle()
	{
		Init();
	}

	void Calculate_Avg(AchievementData_Battle& a,int battles)
	{
		//�����������ƽ��ֵ
		fire=a.fire/battles;
		hit=a.hit/battles;
		damage=a.damage/battles;
		output=a.output/battles;
	}

	int bigger(int x,int y)
	{
		//���ؽϴ�ֵ
		if(x>=y)
		{
			return x;
		}
		return y;
	}

	int smaller(int x,int y)
	{
		//���ؽ�Сֵ
		if(x<=y)
		{
			return x;
		}
		return y;
	}

	void Update_Best(AchievementData_Battle& a)
	{
		//��Ѹ���
		fire=bigger(fire,a.fire);
		hit=bigger(hit,a.hit);
		damage=smaller(damage,a.damage);
		output=bigger(output,a.output);
	}

	

	void Add(AchievementData_Battle& a)
	{
		//����AchievementData_Battle���
		fire+=a.fire;
		hit+=a.hit;
		damage+=a.damage;
		output+=a.output;
	}
};









//��һ��AI����
class AchievementData
{
public:
	//int index;		//��AIManager :: pAI�е��±�


	//global --total
	int battle;		//ս������
	int win;		//ʤ������
	int lose;		//ʧ�ܳ���

	//rate	
	double win_rate;	//ʤ��
	double hit_rate;//������


	AchievementData_Battle data_global;

	AchievementData_Battle data_avg;

	AchievementData_Battle data_best;


	
	
	void Out(ostream& out)
	{
		out<<battle<<','
			<<win<<','
			<<lose<<','
			<<win_rate<<','
			<<hit_rate<<'|';
		data_global.Out(out);
		out<<'|';
		data_avg.Out(out);
		out<<'|';
		data_best.Out(out);
		out<<'|';
	}
	


	void Init()
	{
		//��ʼ��
		battle=0;
		win=0;		//ʤ������
		lose=0;		//ʧ�ܳ���
		//rate	
		win_rate=0;	//ʤ��
		hit_rate=0;//������

		data_global.Init();
		data_avg.Init();
		data_best.Init();
		data_best.damage=MAX_INT;
	}

	AchievementData(/*int in*/)//:data_global(),data_avg(),data_max()
	{
		//index=in;		//����Ŀ��Ӧ��AI��AIManager::pAI�е��±�
		Init();
	}

	
	void Add_Battle(AchievementData_Battle& a,bool w)
	{
		//�����һ��ս������
		data_global.Add(a);
		data_best.Update_Best(a);
		battle+=1;
		
		if(w)
		{
			win+=1;
		}
		else
		{
			lose+=1;
		}
	}

	void Calculate()
	{
		//�������
		data_avg.Calculate_Avg(data_global,battle);		//��������
		win_rate=(double)win/(double) battle;
		if(data_global.fire>0)
		{
			hit_rate=(double)data_global.hit/(double)data_global.fire;
		}
		else
		{
			hit_rate=0;
		}
	}



	//l-less  g-greater  e-equal
	//a��b֮ǰ<=>true
	static bool g_battle(AchievementData * a,AchievementData * b)
	{
		return a->battle>b->battle;
	}

	//ʤ�ʽ���
	static bool g_win_rate(AchievementData  * a,AchievementData * b)
	{
		return a->win_rate>b->win_rate;
	}

	//�����ʽ���
	static bool g_hit_rate(AchievementData * a,AchievementData * b)
	{
		return a->hit_rate>b->hit_rate;
	}


	//�����������
	static bool g_hit_best(AchievementData* a,AchievementData* b)
	{
		return a->data_best.hit>b->data_best.hit;
	}
};