#pragma once
#include "vec2.h"

#include <SFML/Graphics.hpp>
class cTransform
{
public:
	vec2 pos = { 0.0,0.0 };
	vec2 velocity = { 0.0,0.0 };
	float anagle = 0;

	cTransform(const vec2& p, const vec2& v, float a)
		:pos(p), velocity(v), anagle(a) {}

};
class cShape
{
public:
	sf::CircleShape circle;

	cShape(float radius, int points, const sf::Color& fill, const sf::Color outline, float thickness)
		: circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);

	}

};

class cCollision
{
public:
	float radius = 0;

	cCollision(float r)
		:radius(r){}
};

class cInput
{
public:
	bool up     = false;
	bool left   = false;
	bool right  = false;
	bool down   = false;
	bool shoot  = false;
	cInput() {}
};

class cScore
{
public:
	int score = 0;

	cScore(int s)
		:score(s){}

};

class cLifespan
{
public:
	int remaining = 0;     // amount of lifespan remaining on the entity
	int total = 0;          // the total initial amount of lifespan
	
	cLifespan(int total)
		:remaining(total), total(total) {}
};




