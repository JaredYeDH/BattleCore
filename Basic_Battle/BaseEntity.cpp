//#include "stdafx.h"
#include "../stdafx.h"
#include "BaseEntity.h"


BaseEntity::BaseEntity(void)
{
	//ע��entity
	pmngr->RegisterEntity(this);
}


BaseEntity::~BaseEntity(void)
{
	pmngr->RemoveEntity(this);
}

