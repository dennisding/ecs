#pragma once

#include <tuple>
#include <string>

#include <ecs/component.hpp>
#include <ecs/type_utils.hpp>

class pos : public ecs::component
{
public:
	pos(const float x = 0, float y = 0, float z = 0) : x_(x), y_(y), z_(z)
	{}

	ECS_TYPE_INFO("pos", ECS_INIT_ARG(float, float, float))

public:
	float x_, y_, z_;
};

class speed : public ecs::component
{
public:
	speed(float x = 0, float y = 0, float z = 0) : x_(x), y_(y), z_(z)
	{}

	ECS_TYPE_INFO("speed", ECS_INIT_ARG(float, float, float))

public:
	float x_, y_, z_;
};

using component_list = std::tuple<pos, speed>;

// REGISTER_COMPONENT(pos, speed)
// REGISTER_ENTITY(avatar, model)
// REGISTER_SYSTEM(move_system, rotate_system)
