#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#define ent_manager (EntityManager::get_instance())

#include <map>
#include "BaseGameEntity.h"

class BaseGameEntity;
class EntityManager {

private:
	typedef std::map<int, BaseGameEntity*> entities;

private:
	entities entity_map;

	EntityManager() {}
	EntityManager(const EntityManager&);
	EntityManager& operator=(const EntityManager&);

public:
	static EntityManager* get_instance();

	BaseGameEntity* get_entity(int id) const;
	void add_entity(BaseGameEntity* entity);
	void remove_entity(BaseGameEntity* entity);
	void reset() {entity_map.clear();}
};

#endif