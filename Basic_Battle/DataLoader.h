#pragma once
#include "MacroTypesEquipment.h"
#include "Robot/Weapon/WeaponData.h"
#include "Robot/Engine/EngineData.h"
#include "Robot/Bullet/BulletData.h"
//Lua�ű���ȡ��Ϸ���� GameData.lua
//����ģʽ


#define pDataLoader DataLoader::getInstance()






struct DataVessel
{
	//��������Ϸ���ݱ���:
	//For all wepaons
	string name_Weapon[Weapon_Number];
	int Ammo_Weapon[Weapon_Number];
	int coolingTime_Weapon[Weapon_Number];
	double inaccuracy_Weapon[Weapon_Number];
	double rotationSpeed_Weapon[Weapon_Number];

	double radium_Weapon[Weapon_Number];		//�����뾶������ֵ����flash�ﻭȻ����ȷ����

	double coolingSpeed_AllWeapon;
	//For Shotgun
	int burst_Shotgun;
	double gapRotation_Shotgun;

	//For Bullets
	string name_Bullet[Bullet_Number];
	double speed_Bullet[Bullet_Number];
	int damage_Bullet[Bullet_Number];		//?
	int flyTime_Bullet[Bullet_Number];
	//For RPGBall
	double explodeR_RPGBall;
	double acceleration_RPGBall;
	//For Grenade
	double explodeR_Grenade;

	//For PlasmaBall
	int bounce_time;
	//For TrackingMissile
	double spinSpeed;



	//For engines
	string name_Engine[Engine_Number];
	double maxSpeed_Engine[Engine_Number];
	int maxHp_Engine[Engine_Number];
	double rotationSpeed_Engine[Engine_Number];
	double acceleration_Engine[Engine_Number];

	double radium_Engine[Engine_Number];		//����뾶������ֵ����flash�ﻭȻ����ȷ����


	//For Trigger
	//For Arsenal
	double radium_Arsenal;
	int respawningTime_Arsenal;


};
class DataLoader
{
private:
	//static DataLoader* m_Instance;
	DataVessel* GameData;
	lua_State* pLuaState;
	DataLoader();
	DataLoader(const DataLoader&);
	DataLoader& operator = (const DataLoader&);
	virtual ~DataLoader();
	void Close();
	template<typename T>
	bool GetNumber(const char* varName,T& Dest);//�������ڸ�����
	bool GetString(const char* varName, string& Dest);//���������ַ���

	//!!!!!�����ĸ�����������table��ջ��������
	/*----------------------------------------------*/
	//�������ڸ�����������
	template<typename T>
	bool GetRawi_num(int key,T& result);
	//���������ַ�������
	bool GetRawi_str(int key,string& result);
	//ͬ��
	template<typename T>
	bool SetRawi_num(int key, const T& value);
	bool SetRawi_str(int key, string value);
	/*----------------------------------------------*/

	bool LoadStrArray(const char* arrayName, int maxNum, string* Dest);
	template<typename T>
	bool LoadNumArray(const char* arrayName, int maxNum, T* Dest);


	//static data
	vector<WeaponData> weapon_data;
	vector<EngineData> engine_data;
	vector<BulletData> bullet_data;

public:
	
	static DataLoader* getInstance();
	DataVessel* GetGameData();
	bool LoadDataFromLuaScript(const char* fileName);
	
	void ConstructDataVector();
	
	WeaponData& getWeaponData(weapontypename);
	EngineData& getEngineData(enginetypename);
	BulletData& getBulletData(bullettypename);


};
//DataLoader.h