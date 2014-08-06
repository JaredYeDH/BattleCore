#include "../stdafx.h"
#include "BattleStatistics.h"

void BattleStatistics::ReplaceFlag(ofstream& out,const string & f)
{
	if(f=="nr"){ out<<numRobots;}
	else if(f=="wid"){out<<winnerID;}
	else if(f=="bf"){out<<battleFrames;}
	else if(f=="ns"){out<<numSurvivors;}
	else if (f=="rfn"){out<<(pRecordManager->GetFileName());}

	else if(f=="robotslist")
	{
		int i;
		for(i=0;i<numRobots;i++)
		{
			out<<"<robot>\n";

			//TODO:AI.so/dll�ļ�·���ļ���
			out<<"<name>"<<(pBattlefield->GetRobotInfo_Name(i))<<"</name>\n";
			out<<"<name>"<<(pBattlefield->GetRobotInfo_Author(i))<<"</name>\n";
			out<<"<weapon>"<<(pBattlefield->GetInfo().robotInformation[i].weaponTypeName)<<"</weapon>\n";
			out<<"<engine>"<<(pBattlefield->GetInfo().robotInformation[i].engineTypeName)<<"</engine>\n";
			out<<"<weaponRed>"<<(pBattlefield->GetRobotInfo_Weapon_Red(i))<<"</weaponRed>\n";
			out<<"<weaponGreen>"<<(pBattlefield->GetRobotInfo_Weapon_Green(i))<<"</weaponGreen>\n";
			out<<"<weaponBlue>"<<(pBattlefield->GetRobotInfo_Weapon_Blue(i))<<"</weaponBlue>\n";
			out<<"<engineRed>"<<(pBattlefield->GetRobotInfo_Engine_Red(i))<<"</engineRed>\n";
			out<<"<engineGreen>"<<(pBattlefield->GetRobotInfo_Engine_Green(i))<<"</engineGreen>\n";
			out<<"<engineBlue>"<<(pBattlefield->GetRobotInfo_Engine_Blue(i))<<"</engineBlue>\n";

			out<<"</robot>\n";
		}
	}
	//TODO:...
}




void BattleStatistics::Output(const char * filename)
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