//#include "stdafx.h"
#include "../stdafx.h"

#include "BaseEntity.h"
#include "Robot\Robot.h"
#include "DataLoader.h"
//#include "Achievementstruct.h"
//#include "AchievementManager.h"

#include "Battlefield.h"

//�˴��޸���
Battlefield::Battlefield(void):pRobot(0,NULL),pBullet(0,NULL)//,pObstacle(0,NULL)
{
	//AchievementData
	
}


Battlefield::~Battlefield(void)
{
	SweepBattlefield(true,true,true,true);
}

Battlefield* Battlefield::Instance()
{
	static Battlefield instance;
	return &instance;
}




void Battlefield::HandleEvent(events msg, void* extraInfo)
{
	int i,k;
	switch(msg)
	{
	case Add_Bullet:
		//extraInfo���Ѵ���õ�Bullet,ֱ�Ӽӵ�����ʾ�����б��С�
		pBullet.insert(pBullet.end(),(Bullet*)extraInfo);
		//ע��EntityID
		//pmngr->RegisterEntity((Bullet*)extraInfo);
		break;
	
	case Explode:
		//�����grenade��ը
		//TODO:�������RPGBall�ľ�̬����
		k=pRobot.size();
		for(i=0;i<k;i++)
		{
			if(HitTestCircles(pRobot[i]->GetEngine().GetCircle(),*((Circle*)extraInfo)))
			{
				//�˺�,���Խű���ȡ�൥��
				pRobot[i]->GetEngine().ModifyHp(-(pDataLoader->GetGameData()->damage_Bullet[BT_RPGBall]));//temp
			}
		}
		delete extraInfo;
		break;
	}

}



void Battlefield::BattleStart()
{
	//ս����ʼ����

	int i;

	weapontypename wtn;
	enginetypename etn;


	Init_Map();


	//��for_each�ٶ��е�����˵���죬��ͼд�ŷ����ô�ͳ��[]
	for(i=0;i<pRobot.size();i++)
	{
		pRobot.at(i)->GetAI().ChooseArmor(wtn,etn,false);
		pRobot.at(i)->SetWeapon(wtn);
		pRobot.at(i)->SetEngine(etn);
		pRobot.at(i)->Init();

		//��λ��������
		pRobot.at(i)->SetX(birthPoint[i].x);
		pRobot.at(i)->SetY(birthPoint[i].y);


		//2014_3_1���� temp
		pRobot.at(i)->GetWeapon().SetRotation(180*i);
		pRobot.at(i)->GetEngine().SetRotation(180*i);
		//AchievementData_Battle��ʼ��
		//pAchievementData_Battle.push_back(new AchievementData_Battle());
		//pAchievementData_Battle[i]->Init();
	}


	//���ó�ʼʱ��
	if(battleMode.limitTime)
	{
		timeLeft=battleMode.limit_time_frame;
	}
	
	
	//TODO:battleStatistics.Init(...);
	
	
	
	//�ṩ��AI��info��ʼ��
	Init_Info();

	//2014-03-15
	Update_Info();

	
	//���ø���Robot��onBattleStart()
	for(i=0;i<pRobot.size();i++)
	{
		pRobot.at(i)->GetAI().onBattleStart(info,i);
		pRobot.at(i)->GetAchievementData().Init();
	}
	
	pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),Battle_Start,NULL);

	//TODO:BattleStart��info
}

int Battlefield::BattleEnd()
{
	//2014-1-24 ����ʤ����AIManager�е��±�
	//�´���ʱ�䵽�ˣ�Ѫ����ʤ
	//ȷ��ÿ�ֶ���ʤ��
	//Ѫһ������ô�죿

	//�����ɾʹ����ܳɾ���
	int max_hp=0;

	int num_Surviver=pRobot.size();
	int i,k=num_Surviver;

	int max_hp_idx=0;

	for(i=0;i<k;i++)
	{
		if(pRobot[i]->Survive()==false)
		{
			num_Surviver--;
		}
		else if(max_hp<pRobot.at(i)->GetEngine().GetHp())
		{
			max_hp=pRobot.at(i)->GetEngine().GetHp();
			max_hp_idx=i;
		}
	}

	//2014-2-24ע��
	//pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),Battle_End,&info);
	

	

	
	int winner_single_battle=-1;	//����ǵ���ս����vector<robot>���±�
	int winner=-1;//�����AI�±��ʤ��
	//bool win;
	int rn=pRobot.size();


	if(num_Surviver==1)
	{
		//���ҽ���һ������
		//max_hp_idx��ʤ��
		winner_single_battle=max_hp_idx;
		winner=pRobot.at(winner_single_battle)->GetAIIndex();
		for(i=0;i<rn;i++)
		{
			//TODO:����ս�����Ĵ˴��޸�
			//pAchievement->Add_AchievementData(pRobot.at(i)->GetAchievementData(),pRobot.at(i)->GetAIIndex(),i==winner_single_battle);

			pRobot.at(i)->GetAI().onBattleEnd(info,i);
		}
	}
	else if(num_Surviver==0)
	{
		//������
		//ȫ�䣬��ʤ��

		//��̭��������
		cout<<"��һ�������ˣ���̭������\n";

		for(i=0;i<rn;i++)
		{
			//TODO:����ս�����Ĵ˴��޸�
			//pAchievement->Add_AchievementData(pRobot.at(i)->GetAchievementData(),pRobot.at(i)->GetAIIndex(),false);

			pRobot.at(i)->GetAI().onBattleEnd(info,i);
		}


	}
	else
	{
		//����һ���˻�����


		//TODO:�˴�����������
		//����ֻ��������
		if(rn==2)
		{
			//����ʣ��Ѫ���Ӯ�ɡ�����

			//ʧѪ�ٵ��Ǹ�Ӯ
			//��ʧѪһ���࣬ʣ���ӵ����Ӯ����̭����
			//int damage0=pRobot.at(0)->GetEngine().getMaxHp()-pRobot.at(0)->GetEngine().GetHp();
			//int damage1=pRobot.at(1)->GetEngine().getMaxHp()-pRobot.at(1)->GetEngine().GetHp();

			int hp0=pRobot.at(0)->GetEngine().GetHp();
			int hp1=pRobot.at(1)->GetEngine().GetHp();

			if(hp0>hp1)
			{
				winner_single_battle=0;
				winner=pRobot.at(winner_single_battle)->GetAIIndex();
			}
			else if(hp0<hp1)
			{
				winner_single_battle=1;
				winner=pRobot.at(winner_single_battle)->GetAIIndex();
			}
			else
			{
				//damage0==damage1
				//����ҩʣ��
				int a0=pRobot.at(0)->GetWeapon().GetRemainingAmmo();
				int a1=pRobot.at(1)->GetWeapon().GetRemainingAmmo();

				if(a0>a1)
				{
					winner_single_battle=0;
					winner=pRobot.at(winner_single_battle)->GetAIIndex();
				}
				else if( a0<a1 )
				{
					winner_single_battle=1;
					winner=pRobot.at(winner_single_battle)->GetAIIndex();
				}
				else
				{
					//������
				}
			}
		}


		for(i=0;i<rn;i++)
		{
			//TODO:����ս�����Ĵ˴��޸�
			//pAchievement->Add_AchievementData(pRobot.at(i)->GetAchievementData(),pRobot.at(i)->GetAIIndex(),i==winner_single_battle);

			pRobot.at(i)->GetAI().onBattleEnd(info,i);
		}

		
	}

	
	

	//pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),Battle_End,&info);
	if(battleMode.record)
	{
		pRecordManager->ReleaseRecord(winner_single_battle);
	}

	for(i=0;i<rn;i++)
	{
		pRobot.at(i)->GetAchievementData().Init();
	}

	//TODO:�����ƺ�����
	SweepBattlefield(true,false,false,false);	//ֻ�����ӵ�


	battleStatistics.winnerID=winner_single_battle;

	return winner;	//pAI�е�AI�±�(�˴�һ����AIManager�е��±�)������ʤ��Ϊ-1
	
}




bool Battlefield::IsFinished()
{
	//2014-2-24 TODO:
	//�������ʤ���±����Ϣ�����

	//��ʱ

	//��ʱս��ָ��
	if(battleMode.limitTime && timeLeft<=0)
	{
		return true;	//ս������
	}


	//�������������ָ��
	int num_Surviver=pRobot.size();
	int i,k=num_Surviver;
	for(i=0;i<k;i++)
	{
		if(pRobot[i]->Survive()==false)
		{
			num_Surviver--;
		}
	}
	if(num_Surviver<=1)
	{
		return true;
	}


	return false;
}







void Battlefield::Update()
{
	//�൱��һ֡
	pRecordManager->EnterFrame_Init();


	int i,j,k,l;
	Robot* pR=NULL;
	Robot* pRt=NULL;
	Obstacle* pO=NULL;
	Arsenal* pA=NULL;


	//Robot��Ϊ
	k=pRobot.size();
	//l=pObstacle.size();
	l=num_obstacle;

	//�ɸĽ����õ�����������for_each
	for(i=0;i<k;i++)
	{
		if(pRobot.at(i)->Survive())
		{
			pR=pRobot.at(i);
			pR->Update(i);
			//Robot����ײ
			//!!!������һ�����⣬1�Ÿ�����λ�þ�ֱ����ײ����ˣ��������и��������ײ���
			for(j=i+1;j<k;j++)
			{
				pRt=pRobot.at(j);
				
				if(pR->GetEngine().HitTest(pRt->GetEngine()))
				{
					//9-2 ����������ܻ�������
					//Ӧ������Ʈ���ٶȶ���vx,vy,���ǻᱻ���׸ı�
					GameEntity::MomentumHit(pR->GetEngine(),pRt->GetEngine());
					//Weapon��λУ׼
					pR->GetWeapon().AjustPosition(pR->GetEngine());
					pRt->GetWeapon().AjustPosition(pRt->GetEngine());
				}
			}

			//Robot��Obstacle֮����ײ���
			//TODO:����
			for(j=0;j<l;j++)
			{
				pO=pObstacle[j];

				if(pR->GetEngine().HitTest(*pO))
				{
					GameEntity::MomentumHit_Half(pR->GetEngine(),*pO);
					//Weapon��λУ׼
					//pR->GetWeapon().AjustPosition(pR->GetEngine());
				}

			}


			//2013-9-2�˴��ɷ�װ���д��Ľ�
			//Robot��߽��Box֮�����ײ
			double rx=pR->GetEngine().GetCircle().x;
			double ry=pR->GetEngine().GetCircle().y;
			double rr=pR->GetEngine().GetCircle().r;

			if(rx-rr<B_Left)
			{
				//������߽�
				pR->GetEngine().SetVX(-pR->GetEngine().GetVX());
				//pR->GetEngine().SetX(B_Left+rr);		//������û���ס�Ŀ��ܣ�
				pR->SetX(B_Left+rr);
			}
			else if(rx+rr>B_Right)
			{
				//�����ұ߽�
				pR->GetEngine().SetVX(-pR->GetEngine().GetVX());
				//pR->GetEngine().SetX(B_Right-rr);		//������û���ס�Ŀ��ܣ�
				pR->SetX(B_Right-rr);
			}

			if(ry-rr<B_Up)
			{
				//�����ϱ߽�
				pR->GetEngine().SetVY(-pR->GetEngine().GetVY());
				//pR->GetEngine().SetY(B_Up+rr);		//������û���ס�Ŀ��ܣ�
				pR->SetY(B_Up+rr);
			}
			else if(ry+rr>B_Down)
			{
				//�����±߽�
				pR->GetEngine().SetVY(-pR->GetEngine().GetVY());
				//pR->GetEngine().SetY(B_Down-rr);		//������û���ס�Ŀ��ܣ�
				pR->SetY(B_Down-rr);
			}

			//������Weapon��λ��У׼
			pR->GetWeapon().AjustPosition(pR->GetEngine());



			//���Arsenal
			for(j=0;j<num_arsenal;j++)
			{
				pA=pArsenal[j];
				if(pR->GetEngine().HitTest(*pA) && pA->IsActive())
				{
					pA->Touch(*pR);
				}
			}

			
		}
	}


	for(j=0;j<num_arsenal;j++)
	{
		pArsenal[j]->Update_Trigger();
	}



	//Bullet��Ϊ
	

	list<Bullet*>::iterator iter;

	//�򵥵��ˣ���С��
	//���ܵ���ײ��
	//Point hit_point[Info_MaxRobots+Info_MaxObstacles];
	//int robot_or_obstacle[Info_MaxRobots+Info_MaxObstacles];//��¼������ײ��robot�±꣬�����obstacle��-1

	Point hit_point_nearest;

	

	Point temp;
	int robot_or_obstacle;	//�߽�

	//int num_points;


	bool disappear;
	
	

	//�ӵ�
	for(iter=pBullet.begin();iter!=pBullet.end();)
	{
		
		//TODO:�˴���÷�װ���ˣ�¶������̫��ª

		if((*iter)->GetType()==BT_Prism_Laser || (*iter)->GetType()==BT_Tesla_Lightning)
		{
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//ֱ��˲�����ӵ�
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			hit_point_nearest.x=9999;
			hit_point_nearest.y=9999;

			robot_or_obstacle=-2;
			//��������������ײ���
			//����ײ�ļ������ײ��
			//����Beam������rotation����ȷ��������Ǹ�
			//�յ㸳ֵ��Beam����������˺���recordinfo��ҲҪ��ظĶ���
			

			//2014-3-17
			//��ֹ���ⷢ��������ϰ�������µĴ�ǽ
			disappear=false;
			double tmp_x=(*iter)->GetBeam().x;
			double tmp_y=(*iter)->GetBeam().y;
			if(tmp_x<B_Left || tmp_x>B_Right || tmp_y<B_Up || tmp_y>B_Down)
			{
				disappear=true;
				(*iter)->SetEX(tmp_x);
				(*iter)->SetEY(tmp_y);
			}
			else
			{
				for(i=0;i<l;i++)
				{
					if(HitTestCirclePoint(pObstacle.at(i)->GetCircle(),tmp_x,tmp_y))
					{
						disappear=true;
						(*iter)->SetEX(tmp_x);
						(*iter)->SetEY(tmp_y);
						break;
					}
				}
			}
			///////////////////////////////




			//2014-3-17 ��ǽ����ʱ�з���

			if(!disappear)
			{

				//num_points=0;
				//Robot
				for(i=0;i<k;i++)
				{
					pR=pRobot[i];
					if(pR->Survive() && (*iter)->GetLauncher()!=pR->GetID())
					{

						if((*iter)->HitTest(pR->GetEngine()))
						{
							//������ײ��������ײ��
							temp=GetHitPoint((*iter)->GetBeam(),pR->GetEngine().GetCircle());
							//TODO
							if(abs(temp.x-(*iter)->GetBeam().x)<abs(hit_point_nearest.x-(*iter)->GetBeam().x))
							{
								hit_point_nearest=temp;
								//���±�
								robot_or_obstacle=i;
							}

						}
					}
				}

				//Obstacle
				for(i=0;i<l;i++)
				{
					pO=pObstacle[i];

					if((*iter)->HitTest(*pO))
					{
						temp=GetHitPoint((*iter)->GetBeam(),pO->GetCircle());
						if(abs(temp.x-(*iter)->GetBeam().x)<abs(hit_point_nearest.x-(*iter)->GetBeam().x))
						{
							hit_point_nearest=temp;
							//���±�
							robot_or_obstacle=-1;//obstacle
						}


					}

				}

				//�ѻ�������
				if(robot_or_obstacle>=0)
				{
					//���е���robot
					(*iter)->Hit(*pRobot[robot_or_obstacle]);
					(*iter)->SetEX(hit_point_nearest.x);
					(*iter)->SetEY(hit_point_nearest.y);

					//2014_03_01���д���
					pR->GetAI().onHit((*iter)->GetType());
				}
				else if(robot_or_obstacle==-1)
				{
					//�����ϰ�
					(*iter)->SetEX(hit_point_nearest.x);
					(*iter)->SetEY(hit_point_nearest.y);
				}
				else
				{
					//���б߽�
					//ȷ���յ�
					//TODO
					Beam bb=(*iter)->GetBeam();
					double rrrr=AngleToRadian(bb.rotation);
					double gap_up=0-bb.y;
					double gap_down=-bb.y+boundary.height;
					double gap_left=0-bb.x;
					double gap_right=-bb.x+boundary.width;

					double r_ur=atan2(gap_up,gap_right);	//up right
					double r_ul=atan2(gap_up,gap_left);	
					double r_dr=atan2(gap_down,gap_right);
					double r_dl=atan2(gap_down,gap_left);

					if(rrrr<=r_ur && rrrr>=r_ul)
					{
						//��
						(*iter)->SetEY(0);
						(*iter)->SetEX(gap_up/tan(rrrr)+bb.x);
					}
					else if(rrrr>r_ur && rrrr<=r_dr)
					{
						//��
						(*iter)->SetEY(gap_right*tan(rrrr)+bb.y);
						(*iter)->SetEX(boundary.width);
					}
					else if(rrrr>r_dr && rrrr<=r_dl)
					{
						//��
						(*iter)->SetEY(boundary.height);
						(*iter)->SetEX(gap_down/tan(rrrr)+bb.x);
					}
					else if(rrrr<=r_ul || rrrr>=r_dl)
					{
						//��
						(*iter)->SetEY(gap_left*tan(rrrr)+bb.y);
						(*iter)->SetEX(0);
					}
					else
					{
						(*iter)->SetEY(bb.x);
						(*iter)->SetEX(bb.y);
					}

				}

			}

			//ɾ����
			//�����Ľ���͵��¼���ֻ�����¼���ʽ��ΪhitInfo��
			RemoveBulletFromBattlefield(iter,true);
		}
		else
		{
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//�����ӵ�
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


			disappear=false;
			(*iter)->Update();
			//��ײ���,��Robot
			//k=pRobot.size();
			for(i=0;i<k;i++)
			{
				pR=pRobot[i];
				if(pR->Survive() && (*iter)->GetLauncher()!=pR->GetID())
				{
					//���ٵ�������
					//�����װ�ֲ�����
					(*iter)->AdjustDirection(*pR);


					//bug 8-23 �Լ�������ӵ�������ȴ��Լ�
					//ͨ����launcherID(Weapon)�ķ�ʽ���
					//(*iter)->HitTest(pR->GetEngine())
					if((*iter)->HitTest(pR->GetEngine()))
					{
						//HitReact()
						(*iter)->Hit(*pR);

						//2014_03_01���д���
						pR->GetAI().onHit((*iter)->GetType());


						//ɾ��TODO
						RemoveBulletFromBattlefield(iter,true);
						disappear=true;
						break;
					}
				}
			}

			



			//��ײ��⣬��Obstcal
			//l=pObstacle.size();
			if(!disappear)
			{
				for(i=0;i<l;i++)
				{
					pO=pObstacle[i];

					//Բ��(������Բ�ΰɣ���һ��)
					//(*iter)->HitTest(*pO)
					if((*iter)->HitTest(*pO))
					{
						if((*iter)->HitObstcale(*pO))
						{
							RemoveBulletFromBattlefield(iter,true);
							disappear=true;
						}
						//TODO
						
						break;
					}

				}
			}



			if(!disappear)
			{
				double bx=(*iter)->GetCircle().x,by=(*iter)->GetCircle().y;
				double br=(*iter)->GetCircle().r;

				if(bx<B_Left+br || bx>B_Right-br || by<B_Up+br || by>B_Down-br)
				{
					//ը
					
					pO=new Obstacle();
					
					pO->SetR(0);	//������뾶Ϊ0ָʾ��Ϊ�߽�����ϰ�
					pO->SetX(bx);
					pO->SetY(by);

					bool ddd=(*iter)->HitObstcale(*pO);
					delete pO;
					
					

					if(ddd)
					{
						RemoveBulletFromBattlefield(iter,true);
						disappear=true;
					}
				}
			}


			if(!disappear && (*iter)->GetType()==BT_ElectricSaw)
			{
				//��ս�ӵ�������ʧ
				RemoveBulletFromBattlefield(iter,false);//������hit
				disappear=true;
			}

			if(!disappear)
			{
				iter++;
			}
		}

	}

	//����ս����Ϣ
	//AI��õ�ս����Ϣ����ǰһ֡��
	Update_Info();

	//RecordInfo����Ҫ���£����˿���ըɶ�ģ�
	//���������Ӧ�ñȽϺð�
	if(battleMode.record)
	{
		//Battlefield��RecordManager���ͳһ�ĳ����¼��������
		pRecordManager->Update_FrameInfo(info);
	}

	

	timeLeft--;

	

}


void Battlefield::RemoveBulletFromBattlefield(list<Bullet*>::iterator & ii,bool dis)
{
	//������¼����ƾͲ������ˣ�Ϊ�˷��㣩
	Record_HitInformation* hi=NULL;
	if(battleMode.record && dis)
	{

		//Record������
		//����һ����hitЧ��
		hi=new Record_HitInformation;

		//bug 8-23 ��ʱBullet�ѱ��Ƴ����������Ҳ����������
		hi->type=(*ii)->GetType();
		

		if(hi->type==BT_Prism_Laser || hi->type==BT_Tesla_Lightning)
		{
			hi->x=(*ii)->GetBeam().x;
			hi->y=(*ii)->GetBeam().y;
			hi->ex=(*ii)->GetBeam().ex;
			hi->ey=(*ii)->GetBeam().ey;
		}
		else
		{
			hi->x=(*ii)->GetCircle().x;
			hi->y=(*ii)->GetCircle().y;
		}

		pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),R_HitInfo,hi);
		delete hi;
		hi=NULL;

	}




	ii=pBullet.erase(ii);
	//Entityע���Ƴ�
	//pmngr->RemoveEntity(*ii);
}


void Battlefield::Init_Info()
{
	//Obstacle,Boundary
	info.boundary=boundary;
	info.num_obstacle=num_obstacle;
	info.num_arsenal=num_arsenal;
	int i;
	int k=num_obstacle;
	//int k=pObstacle.size();
	for(i=0;i<k;i++)
	{
		info.obstacle[i]=pObstacle[i]->GetCircle();
	}
	k=num_arsenal;
	for(i=0;i<k;i++)
	{
		info.arsenal[i].circle=pArsenal[i]->GetCircle();
		info.arsenal[i].respawning_time=pArsenal[i]->GetRespawningTime();
	}
}







void Battlefield::Update_Info()
{
	//����info:RobotAI_BattlefieldInformation
	
	//int i,j;
	//pRobot[i]->
	int i,k,l;
	Robot* pR=NULL;
	Robot* pRt=NULL;
	Obstacle* pO=NULL;


	//RobotInfo
	k=pRobot.size();
	info.num_robot=k;
	l=pObstacle.size();
	for(i=0;i<k;i++)
	{
		pR=pRobot[i];
		info.robotInformation[i].entityID=pR->GetID();
		info.robotInformation[i].id=i;
		info.robotInformation[i].weaponTypeName=pR->GetWeapon().GetType();
		info.robotInformation[i].engineTypeName=pR->GetEngine().GetType();
		info.robotInformation[i].circle=pR->GetEngine().GetCircle();
		info.robotInformation[i].weaponRotation=pR->GetWeapon().GetRotation();
		info.robotInformation[i].engineRotation=pR->GetEngine().GetRotation();
		pR->GetEngine().GetVelocity(info.robotInformation[i].vx,
			info.robotInformation[i].vy,
			info.robotInformation[i].vr);
		info.robotInformation[i].hp=pR->GetEngine().GetHp();
		info.robotInformation[i].remainingAmmo=pR->GetWeapon().GetRemainingAmmo();
		info.robotInformation[i].cooling=pR->GetWeapon().GetCooling();
	}

	list<Bullet*>::iterator iter;

	i=0;
	for(iter=pBullet.begin();iter!=pBullet.end();iter++)
	{
		//�ж�i�±��Ƿ����
		if(i>=Info_MaxBullets)
		{
			//�������
			//assert(i>=Info_MaxBullets)
		}
		info.bulletInformation[i].entityID=(*iter)->GetID();
		
		
		info.bulletInformation[i].type=(*iter)->GetType();

		info.bulletInformation[i].circle=(*iter)->GetCircle();
		
		info.bulletInformation[i].rotation=(*iter)->GetRotation();
		(*iter)->GetVelocity(info.bulletInformation[i].vx,
			info.bulletInformation[i].vy,
			info.bulletInformation[i].vr);







		//2014-3-16
		//���н��û��launcherID�İ취
		if((*iter)->GetLauncher()==0)
		{
			info.bulletInformation[i].circle.r=-999;
		}
		else if((*iter)->GetLauncher()==1)
		{
			info.bulletInformation[i].circle.r=999;
		}

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!







		i++;
	}
	//�����һ���ӵ����ں���һ������ض���ʶ���ṩ������Ϣ
	if(i<=Info_MaxBullets)
	{
		//��һ����ʶ
		info.bulletInformation[i].type=BT_NULL;
	}
	info.num_bullet=i-1;

	//Boundary,Obstacle����Ϣֻ��BattleStartʱˢ��һ��
	//����Update()ʱ�ٴ�ˢ����


	//Arsenal
	for(i=0;i<num_arsenal;i++)
	{
		info.arsenal[i].respawning_time=pArsenal[i]->GetRespawningTime();
	}
}




//���addRobot�������ò���Robot����������ͬ��ֻ��pRobotAI_Interface
bool Battlefield::AddRobot(Robot* newRobot)
{
	
	pRobot.push_back(newRobot);

	//temp
	return true;
}


int Battlefield::AddRobotAI(RobotAI_Interface* newRobotAI,int index)
{
	//��AI�Ĳ���ҪС�İ�������һ����Ҫɾ�ˡ���
	pRobot.push_back(new Robot(newRobotAI,index));

	return (pRobot.size()-1);
}

int Battlefield::NewBattle()
{
	//pBullet.clear();����ȫ��û��ҪBattleEndʱ��������

	int winner;
	pRecordManager->SetFileName(battleMode.record_name);

	if(pRobot.size()>1)
	{
		BattleStart();


		while(!IsFinished())
		{
			Update();
		}

		winner=BattleEnd();

		return winner;
	}
	return -1;
}




void Battlefield::SweepBattlefield_Bullet()
{
	//int bn=pBullet.size();
	list<Bullet*>::iterator iter;
	for(iter=pBullet.begin();iter!=pBullet.end();iter++)
	{
		if((*iter)!=NULL)
		{
			delete (*iter);
			(*iter)=NULL;
		}
	}
	pBullet.clear();
}

void Battlefield::SweepBattlefield_Robot()
{
	int i;
	int rn=pRobot.size();
	for(i=0;i<rn;i++)
	{
		delete pRobot.at(i);
		pRobot.at(i)=NULL;
	}
	pRobot.clear();
}


//TODO
void Battlefield::SweepBattlefield_Map()
{
	//Sweep Obstacle


	//Sweep Arsenal


}

void Battlefield::SweepBattlefield(bool f_bullet=true,bool f_robot=true,bool f_obstacle=true,bool f_arsenal=true)
{
	//ս������������ս��
	//f_*�Ƿ�����ò���
	int i;
	
	
	if(f_bullet)
	{
		SweepBattlefield_Bullet();
	}


	if(f_robot)
	{
		SweepBattlefield_Robot();
	}

	if(f_obstacle)
	{
		int on=pObstacle.size();
		for(i=0;i<on;i++)
		{
			delete pObstacle[i];
			pObstacle[i]=NULL;
		}
		pObstacle.clear();
	}

	if(f_arsenal)
	{
		int an=pArsenal.size();
		for(i=0;i<an;i++)
		{
			delete pArsenal[i];
			pArsenal[i]=NULL;
		}
		pArsenal.clear();
	}
}













void Battlefield::Init_Map()
{
	//��ʼ��ս����ͼ
	//������д��أ��ǲ���Ҫ�����ӿڣ�

	//�����ϰ��;����
	//TODO:�Ժ��ͼ�໯�淶�Ժ��г�����
	SweepBattlefield(false,false,true,true);


	Construct_Map();
	
	
	
}





string Battlefield::GetRobotInfo_Name(int index)
{
	return pRobot[index]->GetAI().GetName();
}

string Battlefield::GetRobotInfo_Author(int index)
{
	return pRobot[index]->GetAI().GetAuthor();
}

int Battlefield::GetRobotInfo_Weapon_Red(int index)
{
	return pRobot[index]->GetAI().GetWeaponRed();
}
int Battlefield::GetRobotInfo_Weapon_Green(int index)
{
	return pRobot[index]->GetAI().GetWeaponGreen();
}
int Battlefield::GetRobotInfo_Weapon_Blue(int index)
{
	return pRobot[index]->GetAI().GetWeaponBlue();
}

int Battlefield::GetRobotInfo_Engine_Red(int index)
{
	return pRobot[index]->GetAI().GetEngineRed();
}
int Battlefield::GetRobotInfo_Engine_Green(int index)
{
	return pRobot[index]->GetAI().GetEngineGreen();
}
int Battlefield::GetRobotInfo_Engine_Blue(int index)
{
	return pRobot[index]->GetAI().GetEngineBlue();
}

int Battlefield::GetRobotInfo_MaxHp(int index)
{
	return pRobot[index]->GetEngine().GetMaxHp();
}
int Battlefield::GetRobotInfo_MaxAmmo(int index)
{
	return pRobot[index]->GetWeapon().GetMaxAmmo();
}