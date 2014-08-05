#pragma once
#include "BattleMode.h"

//2014/07/25
//һ��ս����ͳ������
//�Ľ�ԭ��ʤ��֮������

class BattleStatistics
{
public:
	int numRobots;		//��ս������

	int winnerID;		//ʤ��ID��vec::pRobot�е��±꣩
	
	int battleFrames;	//ս������֡��
	int numSurvivors;	//�Ҵ�����
	
	//BattleMode battleMode;	//ս��ģʽ����
	
	//...
	//ս��ʱ������
	//ʤ�߻�����
	//��ս��Vector��
	//ս����������������������λ����������������


	BattleStatistics(){}

	//TODO:...
	void ReplaceFlag(ofstream& out,const string & f)
	{
		if(f=="nr"){ out<<numRobots;}
		else if(f=="wid"){out<<winnerID;}
		else if(f=="bf"){out<<battleFrames;}
		//TODO:...
	}

	void Output(const char * filename)
	{
		//��ȡ battleStatics.xml (�̶�·��) �ĸ�ʽ�ź��ı�
		//���ַ���ȡ���滻�� $bs$ �����������������
		//$...$ �Ĳ�����switch����Ӧλ��
		ofstream out;	//�����XML
		out.open(filename);

		ifstream in;	//����ĸ�ʽ�ź��ı���XML��
		in.open("battle_xml_format.xml");

		char c;
		while(!in.eof())
		{
			in.get(c);

			if(c=='$')
			{
				//�滻��ǩ
				string flag;
				in.get(c);
				while(c!='$')
				{
					flag.push_back(c);
					in.get(c);
				}
				ReplaceFlag(out,flag);
			}
			else
			{
				out<<c;
			}

		}

		in.close();
		out.close();
	}
};