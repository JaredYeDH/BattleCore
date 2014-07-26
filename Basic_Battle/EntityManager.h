#pragma once


#define pmngr EntityManager::Instance()

//����ģʽ
class EntityManager
{
private:

	typedef map<int,BaseEntity*> EntityMap;

	EntityManager(void);
	~EntityManager(void);

	//static EntityManager* pEntityManager;

	//�洢id��entity֮��һһ��Ӧ��ϵ�����ݽṹ,std::map?
	EntityMap entityMap;
	//map<int,BaseEntity*> entityMap;


	static int currentID;	//��ǰ��ע��ID��

public:
	static EntityManager* Instance();

	void RegisterEntity(BaseEntity * newEntity);

	BaseEntity* GetEntityFromID(int id)const;

	//���б��Ƴ�ע���Entity
	void RemoveEntity(BaseEntity * pEntity);
};

