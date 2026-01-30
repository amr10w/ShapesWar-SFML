#include "EntityManager.h"


EntityManager::EntityManager()
{}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto e = std::shared_ptr<Entity>(new Entity (m_totalEntities++, tag));
    m_toAdd.push_back(e);
    return e;
    
}

void EntityManager::update()
{
    for (auto e : m_toAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);

    }

    
    m_toAdd.clear();

    
    // Remove dead entities
    removeDeadEntities(m_entities);

    
    for ( auto& pair : m_entityMap) // Accessing pairs in the map
    {
        EntityVec& entityVec = pair.second; // Get the entity vector for this tag

        // Remove dead entities from this vector
        removeDeadEntities(entityVec);
    }
        
    
    
}

EntityVec& EntityManager::get_Entities()
{
    return m_entities;
}

EntityVec& EntityManager::get_Entities(const std::string& tag)
{
    return m_entityMap[tag];
}

void EntityManager::removeDeadEntities(EntityVec& vec)
{
    //vec.erase(std::remove_if(vec.begin(), vec.end(),
        //[](const std::shared_ptr<Entity>& e) { return !e->isActive(); }), vec.end());

  // std::erase_if(vec, [](auto& e) { return !e->isActive(); });
    for (int i = 0; i < vec.size(); i++)
    {
        vec.erase(std::remove_if(vec.begin(), vec.end(),
            [](const std::shared_ptr<Entity>& e) { return !e->isActive(); }), vec.end());
    }

}
