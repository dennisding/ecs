#pragma once

#include <tuple>
#include <string>

#include <ecs/component.hpp>

class pos : public ecs::component
{
public:
	pos(const float x = 0, float y = 0, float z = 0) : x_(x), y_(y), z_(z)
	{}

	static component *create(const float &x, float y, float z)
	{
		return new pos(x, y, z);
	}

	static const std::string name()
	{
		return "pos";
	}

public:
	float x_, y_, z_;
};

class speed : public ecs::component
{
public:
	speed(const std::string s,float x = 0, float y = 0, float z = 0) : x_(x), y_(y), z_(z)
	{}

	static component *create(const std::string )
	{
	}

	static const std::string name()
	{
		return "speed";
	}

public:
	float x_, y_, z_;
};

using component_list = std::tuple<pos, speed>;

// REGISTER_COMPONENT(pos, speed)
// REGISTER_ENTITY(avatar, model)
// REGISTER_SYSTEM(move_system, rotate_system)
