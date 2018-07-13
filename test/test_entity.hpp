#pragma once

#include <tuple>
#include <ecs/entity.hpp>

#include "test_component.hpp"

class avatar : public ecs::entity<component_list>
{
	using avatar_component_list = std::tuple<pos>;
public:

	template <typename T, typename ...Types>
	void add_component(Types...args)
	{
		dispatcher<T, Types...>(ecs::type_in_tuple<T, avatar_component_list>::type(), args...);
	}

	template <typename T, typename ...Types>
	void dispatcher(const std::true_type in_list, Types ...args)
	{
		size_t index = ecs::tuple_index<component_list, T>::value;
		component_bits_[index] = true;
		set_value(T(args...));
	}

	template <typename T, typename ...Types>
	void dispatcher(const std::false_type not_in, Types ...args)
	{
		ecs::entity<component_list>::add_component<T>(args...);
	}

	template <typename T>
	T *get_component()
	{
		return ecs::entity<component_list>::get_component<T>();
	}

	template <>
	pos *get_component<pos>()
	{
		return &pos_;
	}

	void set_value(const pos &pos)
	{
		pos_ = pos;
	}

	pos pos_;
};

using entity_list = std::tuple<avatar, ecs::entity<component_list>>;