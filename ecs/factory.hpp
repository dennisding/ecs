#pragma once

#include <map>
#include <tuple>
#include <string>
#include <utility>
#include <cassert>
#include <functional>

#include "ecs_config.hpp"

ECS_NAMESPACE_BEGIN

/// creator_imp
template <typename object, typename fun_type, typename type>
struct creator_imp {};

template <typename object, typename ...arg_types>
struct creator_imp<object, std::tuple<arg_types...>, std::true_type>
{
	virtual object *create(arg_types &&...args)
	{
		assert(false);
		return nullptr;
	}
};

template <typename object, typename ...arg_types, typename base>
struct creator_imp<object, std::tuple<arg_types...>, base> : public virtual base
{
	using base::create;

	virtual object *create(arg_types &&...args)
	{
		assert(false);
		return nullptr;
	}
};

/// make_creator_type
template <typename ...types>
struct make_creator_type {};

template <typename object, typename head>
struct make_creator_type<object, head>
{
	using type = creator_imp<object, typename head::_type_info::init_arg_tuple, std::true_type>;
};

template <typename object, typename head, typename ...tails>
struct make_creator_type<object, head, tails...>
{
	using tail_type = typename make_creator_type<object, tails...>::type;
	using type = creator_imp<object, typename head::_type_info::init_arg_tuple, tail_type>;
};

/// make_creator_base
template <typename object_tuple, typename object>
struct make_creator_base {};

template <typename ...object_types, typename object>
struct make_creator_base<std::tuple<object_types...>, object>
{
	using type = typename make_creator_type<object, object_types...>::type;
};

/// concreate_creator
template <typename type, typename object, typename base, typename arg_type>
struct concreate_creator : public virtual base
{
};

template <typename type, typename object, typename base, typename ...arg_types>
struct concreate_creator<type, object, base, std::tuple<arg_types...>> : public virtual base
{
	using base::create;

	virtual object *create(arg_types && ...args)
	{
		return new type(std::forward<arg_types>(args)...);
	}
};

/// factory creator
template <typename object_tuple, typename object, typename base>
struct factory_creator {};

template <typename head, typename object, typename base>
struct factory_creator<std::tuple<head>, object, base>
{
	using creator = concreate_creator<head, object, base, typename head::_type_info::init_arg_tuple>;
	static void create(std::function<void (const std::string &, base *)> fun)
	{
		fun(head::_type_info::name(), new creator);
	}
};

template <typename head, typename ...tails, typename object, typename base>
struct factory_creator<std::tuple<head, tails...>, object, base> : public virtual base
{
	static void create(std::function<void(const std::string &, base *)> fun)
	{
		factory_creator<std::tuple<head>, object, base>::create(fun);
		factory_creator<std::tuple<tails...>, object, base>::create(fun);
	}
};

template <typename object_tuple, typename object>
class factory
{
	using creator_base = typename make_creator_base<object_tuple, object>::type;
	using creator_map = std::map<std::string, creator_base *>;
public:
	factory()
	{
		factory_creator<object_tuple, object, creator_base>::create(
			[this](const std::string &name, creator_base *c) {
				assert(creators_.find(name) == creators_.end());
				creators_[name] = c;
			}
		);
	}

	template <typename T, typename ...Args>
	T *create(Args&& ...args)
	{
		return new T(std::forward<Args>(args)...);
	}

	template <typename ...Args>
	object *create(const std::string &name, Args ...args)
	{
		auto it = creators_.find(name);
		assert(it != creators_.end());

		return it->second->create(std::forward<Args>(args)...);
	}

private:
	creator_map creators_;
};

ECS_NAMESPACE_END
