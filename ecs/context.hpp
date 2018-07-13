#pragma once

#include <vector>
#include <functional>

#include <ecs/ecs_config.hpp>
#include <ecs/entity.hpp>
#include <ecs/system.hpp>

ECS_NAMESPACE_BEGIN

template <typename system_list, typename entity_list, typename component_list>
class context
{
	using entity_type = entity<component_list>;
	using entity_vector = std::vector<entity_type *>;
	using system_vector = std::vector<system *>;

	using ticker_tuple = typename make_ticker_tuple<entity_list>::type;

public:
	void init()
	{
		ticker_tuple t;
		create_systems<system_list>::create([this](system *s) {
			systems_.push_back(s); 
		});
	}

	void tick(float delta)
	{
		// dispatch the entities
		for (auto s : systems_) {
			for (auto e : entities_) {
//				e->dispatch_tick(delta, s);
//				e->dispatch_tick(delta, s);
				//auto fun = e->get_ticker(s);
				//fun(delta, fun);
			}
		}
	}


	void add_entity(entity_type *entity)
	{
		entities_.push_back(entity);
	}

private:
	entity_vector entities_;
	system_vector systems_;
	system_mgr<system_list> system_mgr_;
};

ECS_NAMESPACE_END
