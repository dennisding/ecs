#include "game.hpp"

#include <locale>

#include <ecs/type_list.hpp>
#include <ecs/component_factory.hpp>
#include <ecs/factory.hpp>
#include "test_component.hpp"
#include "test_system.hpp"
#include "test_entity.hpp"

void game::init()
{
//	ecs::component_factory<component_list> f;

	ecs::factory<component_list, ecs::component> f2;

	const float i = 1;
	auto p = f2.create("pos", i, 1.0f, 1.0f);
	auto s = f2.create("speed", 1.2f, 2.0f, 3.2f);

	auto p2 = f2.create<pos>(i, 4.0f);
}

void game::tick()
{
}