#pragma once
#include "Components.h"
#include<memory>
#include<string>

class Entity
{
	friend class EntityManager;

	size_t m_id = 0;
	std::string m_tag = "Default";
	bool m_active = true;

	// constructor and destructor
	Entity(const size_t id, const std::string& tag);

public:
	// component pointer
	std::shared_ptr<cTransform> cTransform;
	std::shared_ptr<cShape> cShape;
	std::shared_ptr<cInput> cInput;
	std::shared_ptr<cScore> cScore;
	std::shared_ptr<cLifespan> cLifespan;
	std::shared_ptr<cCollision> cCollision;

	// private member access functions
	bool isActive() const;
	const std::string& tag() const;
	const size_t id() const;
	void destroy();

};

