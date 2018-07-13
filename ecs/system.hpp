#pragma once

#include <vector>
#include <tuple>
#include <ecs/ecs_config.hpp>

#include <ecs/entity.hpp>

ECS_NAMESPACE_BEGIN

//class system
//{
//public:
//	virtual ~system() {}
//
//	virtual void tick(float delta, entity * e) = 0;
//};

class system
{
public:
	template <typename T>
	void tick(float delta, T *entity)
	{

	}

	virtual ~system() {}

//	virtual void dispatch_tick(float delta, entity_base *entity) = 0;
};

class system_wrapper
{
public:
};


template <typename ...Types>
struct do_create_system
{
};

template <typename T>
struct do_create_system<T>
{
	template <typename FunType>
	static void create(FunType fun)
	{
		T *s = new T;
		fun(s);
	}
};

template <typename Head, typename ... Tails>
struct do_create_system<Head, Tails...>
{
	template <typename FunType>
	static void create(FunType fun)
	{
		do_create_system<Head>::create(fun);
		do_create_system<Tails...>::create(fun);
	}
};

template <typename T>
struct create_systems
{
};

template <typename ...Types>
struct create_systems<std::tuple<Types...> >
{
	template <typename FunType>
	static void create(FunType fun)
	{
		do_create_system<Types...>::create(fun);
	}
};

template <typename system_list>
class system_mgr
{
	using system_vector = std::vector<system_list>;
public:
	system_mgr()
	{

	}

	typename system_vector::iterator begin()
	{
		return systems_.begin();
	}

	typename system_vector::iterator end()
	{
		return systems_.end();
	}

private:
	system_vector systems_;
};

template <typename system, typename entity_list>
struct do_make_system
{
	using type = system;
};

template <typename system_list, typename entity_list>
struct make_system_list {};

template <typename system, typename entity_list>
struct make_system_list<std::tuple<system>, entity_list>
{
	using type = std::tuple<typename do_make_system<system, entity_list>::type>;
};

template <typename system_head, typename ...system_tails, typename entity_list>
struct make_system_list<std::tuple<system_head, system_tails...>, entity_list>
{
	//using head_type = typename do_make_system<system_head, entity_list>::type;
	using head_tuple = typename make_system_list<std::tuple<system_head>, entity_list>::type;
	using tail_type = std::tuple<system_tails...>;
	using tail_tuple = typename make_system_list<tail_type, entity_list>::type;
	//using type = std::tuple_cat<head_tuple, tail_tuple>::type;
	using type = decltype(std::tuple_cat(head_tuple(), tail_tuple()));
};

ECS_NAMESPACE_END
