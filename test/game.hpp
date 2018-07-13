#pragma once

#include "test_component.hpp"
#include "test_entity.hpp"

#include <ecs/context.hpp>

class game
{
public:
	void init();
	void tick();

private:
	//ecs::context context_;
};