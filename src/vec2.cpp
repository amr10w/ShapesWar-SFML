#include "vec2.h"
#include <cmath>

vec2::vec2(){}
vec2::vec2(float xin, float yin) :x(xin), y(yin) {}



bool vec2::operator ==(const vec2& rhs) const
{
	return (x == rhs.x && y == rhs.y);
}
bool vec2::operator != (const vec2& rhs) const
{
	return (x != rhs.x && y != rhs.y);
}



vec2 vec2::operator + (const vec2& rhs) const
{
	return vec2(x + rhs.x, y + rhs.y);
}
vec2 vec2::operator - (const vec2& rhs) const
{
	return vec2(x - rhs.x, y - rhs.y);
}
vec2 vec2::operator * (const float val) const
	{
		return vec2(x * val, y * val);
	}
vec2 vec2::operator / (const float val) const
	{
		return vec2(x / val, y / val);
	}



void vec2::operator += (const vec2& rhs) 
	{
		x += rhs.x;
		y += rhs.y;
	}
void vec2::operator -= (const vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}
void vec2::operator *= (const float val)
{
	x *= val;
	y *= val;
}
void vec2::operator /= (const float val)
{
	x /= val;
	y /= val;
}



float vec2::dist(const vec2& rhs) const
{
	return sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y));
}

float vec2::length() const
{
	return sqrt(x * x + y * y);
}

vec2 vec2::normalization() const
{
	float len = length();
	if (len == 0) return vec2(0, 0); // Avoid division by zero
	return vec2(x / len, y / len); // Normalize the vector
}

vec2 vec2::normalization(const float& length) const
{
	return vec2(x / length, y / length);
}
