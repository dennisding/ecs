#pragma once

#include <tuple>
#include <iostream>
#include <ecs/system.hpp>

#include "test_component.hpp"

class move_system : public ecs::system
{
public:
	template <typename T>
	void tick(float delta, T *entity)
	{
		auto p = entity->get_component<pos>();
		std::cout << "move_system::tick " << delta << std::endl;
	}
};

class rotate_system : public ecs::system
{
public:
	template <typename T>
	void tick(float delta, T *entity)
	{
		std::cout << "rotate_system::tick" << delta << std::endl;
	}
};

using system_list = std::tuple<move_system, rotate_system>;