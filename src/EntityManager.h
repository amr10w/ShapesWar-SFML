#pragma once
#include "Entity.h"
#include<string>
#include<vector>
#include<map>
#include<memory>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager
{
	EntityVec m_entities;
	EntityVec m_toAdd;
	EntityMap m_entityMap;
	size_t m_totalEntities = 0;
public:
	EntityManager();
	void update();
	std::shared_ptr<Entity> addEntity(const std::string& tag);
	EntityVec& get_Entities();
	EntityVec& get_Entities(const std::string & tag);
	void removeDeadEntities(EntityVec& vec);
};

