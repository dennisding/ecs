//#pragma once
//
//#include <map>
//#include <functional>
//#include <cassert>
//
//#include "ecs/ecs_config.hpp"
//
//ECS_NAMESPACE_BEGIN
//
//class component;
//
//template <typename T1, typename T2>
//struct creator_base {};
//
//template <typename R, typename ...Args>
//struct creator_base<R *(Args...), std::true_type>
//{
//	virtual component *create(Args ...args)
//	{
//		return nullptr;
//	}
//};
//
//template <typename R, typename ...Args, typename base_type>
//struct creator_base<R *(Args...), base_type> : base_type
//{
//	using base_type::create;
//
//	virtual component *create(Args ...args)
//	{
//		return nullptr;
//	}
//};
//
//template <typename T, typename creator_base, typename fun_type>
//struct concreate_creator : public virtual creator_base
//{
//};
//
//template <typename T, typename creator_base, typename Return, typename ...Types>
//struct concreate_creator<T, creator_base, Return (Types...)> : public virtual creator_base
//{
//	virtual component *create(Types... args)
//	{
//		auto c = new T(args...);
//		return c;
//	}
//};
//
//template <typename ...Types>
//struct inherite_type {};
//
//template <typename T>
//struct inherite_type<T>
//{
//	using type = creator_base<decltype(T::create), std::true_type>;
//};
//
//template <typename Head, typename ...Tails>
//struct inherite_type<Head, Tails...>
//{
//	using head_type = typename inherite_type<Head>::type;
//	using tail_type = typename inherite_type<Tails...>::type;
//
//	using type = creator_base<decltype(Head::create), tail_type>;
//};
//
//template <typename T>
//struct make_creator_base {};
//
//template <typename ...Types>
//struct make_creator_base<std::tuple<Types...>>
//{
//	using type = typename inherite_type<Types...>::type;
//};
//
//template <typename component_list, typename creator_base>
//struct register_components
//{
//};
//
//template <typename Head, typename creator_base>
//struct register_components<std::tuple<Head>, creator_base>
//{
//	using concreate_type = concreate_creator<Head, creator_base, decltype(Head::create)>;
//	static void do_register(std::function<void(const std::string &name, creator_base *)> fun)
//	{
//		fun(Head::name(), new concreate_type);
//	}
//};
//
//template <typename Head, typename ...Tails, typename creator_base>
//struct register_components<std::tuple<Head, Tails...>, creator_base>
//{
//	static void do_register(std::function<void (const std::string &name, creator_base *)> fun)
//	{
//		register_components<std::tuple<Head>, creator_base>::do_register(fun);
//		register_components<std::tuple<Tails...>, creator_base>::do_register(fun);
//	}
//};
//
//template <typename component_list>
//class component_factory
//{
//	using component_creator_base = typename make_creator_base<component_list>::type;
//	using component_map = std::map<std::string, component_creator_base *>;
//
//public:
//	component_factory()
//	{
//		register_components<component_list, component_creator_base>::do_register(
//			[this](const std::string &name, component_creator_base *c) {
//				this->creators_[name] = c;
//			}
//		);
//	}
//
//	template <typename ...Types>
//	component * create(const std::string &name, Types ...args)
//	{
//		auto it = creators_.find(name);
//		assert( it != creators_.end() );
//
//		return it->second->create(args...);
//	}
//
//	template <typename T, typename ...Types>
//	T *create(Types ...args)
//	{
//		T *c = new T(args...);
//		return c;
//	}
//
//private:
//	component_map creators_;
//};
//
//ECS_NAMESPACE_END
