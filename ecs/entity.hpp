#pragma once

#include <map>
#include <cassert>
#include <bitset>
#include <functional>
#include <ecs/ecs_config.hpp>
#include <ecs/type_list.hpp>
#include <ecs/component.hpp>

ECS_NAMESPACE_BEGIN

class entity_base
{
public:
	virtual ~entity_base() {}

};

template <typename component_list>
class entity : public entity_base
{
	using component_bit = std::bitset<std::tuple_size<component_list>::value>;
	using component_map = std::map<int, component *>;
public:
	template <typename T, typename ...Types>
	void add_component(Types ...args)
	{
		size_t index = tuple_index<component_list, T>::value;
		T *c = new T(args...);
		assert(component_bits_[index] == false);
		components_[index] = c;
		component_bits_[index] = true;
	}

	template <typename T>
	void del_component()
	{
		size_t index = tuple_index<component_list, T>::value;
		assert(component_bits_[index] == true);

		component_bits_[index] = false;

		auto it = components_.find(index);
		delete it->second;
		components_.erase(it);
	}

	template <typename T>
	T *get_component()
	{
		size_t index = tuple_index<component_list, T>::value;
		return static_cast<T *>(components_[index]);
	}

	template <typename T>
	bool has_component()
	{
		size_t index = tuple_index<component_list, T>::value;
		return component_bits_[index];
	}

	template <typename T>
	void set_value(const T &v)
	{
		*get_component<T>() = v;
	}

protected:
	component_bit component_bits_;
	component_map components_;
};

template <typename ...Types>
struct do_make_ticker_tuple
{
};

template <typename T>
struct do_make_ticker_tuple<T>
{
	using type = std::tuple<std::function<void(float, T*)> >;
};

template <typename Head, typename ...Tails>
struct do_make_ticker_tuple<Head, Tails...>
{
	using type = decltype(std::tuple_cat(do_make_ticker_tuple<Head>::type(), do_make_ticker_tuple<Tails...>::type()));
};

template <typename T>
struct make_ticker_tuple {};

template <typename ...Types>
struct make_ticker_tuple<std::tuple<Types...> >
{
	using type = typename do_make_ticker_tuple<Types...>::type;
};

ECS_NAMESPACE_END
