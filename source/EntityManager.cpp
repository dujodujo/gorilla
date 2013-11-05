#include "BaseGameEntity.h"
#include "EntityManager.h"

EntityManager* EntityManager::get_instance() {
	static EntityManager instance;
	return &instance;
}

BaseGameEntity* EntityManager::get_entity(int id) const {
	entities::const_iterator ent_iterator = entity_map.find(id);
	return ent_iterator->second;
}

void EntityManager::remove_entity(BaseGameEntity* entity) {
	entity_map.erase(entity_map.find(entity->get_id()));
}

void EntityManager::add_entity(BaseGameEntity* entity) {
	entity_map.insert(std::make_pair(entity->start_id(), entity));
}