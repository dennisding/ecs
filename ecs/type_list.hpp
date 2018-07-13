#pragma once

#include <tuple>
#include <type_traits>

#include "ecs_config.hpp"

ECS_NAMESPACE_BEGIN

template <class is_true, size_t N, class T, class ...Types>
struct tuple_index_imp {
	enum { value = N };
};

template <size_t N, class T, class Head, class ...Tails>
struct tuple_index_imp<std::true_type, N, T, Head, Tails...>
{
	enum { value = N};
};

template <size_t N, class T, class Head, class ...Tails>
struct tuple_index_imp<std::false_type, N, T, Head, Tails...>
{
	using tail_types = tuple_index_imp<typename std::is_same<Head, T>::type, N + 1, Tails...>;
	enum { value = tail_types::value };
};

template <typename Tuple, typename T>
struct tuple_index
{
};

template <typename Head, typename ...Tail, typename T>
struct tuple_index<std::tuple<Head, Tail...>, T>
{
	using type = tuple_index_imp<typename std::is_same<Head, T>::type, 0, T, Head, Tail...>;
	enum { value = type::value };
};

// type_in_tuple_imp
template <typename I, typename T, typename ...Types>
struct type_in_tuple_imp {
	using type = std::false_type; 
};

template <typename T, typename Head, typename ...Tails>
struct type_in_tuple_imp<std::false_type, T, Head, Tails...>
{
	using type = typename type_in_tuple_imp<typename std::is_same<T, Head>::type, Tails...>::type;
};

template <typename T, typename ...Types>
struct type_in_tuple_imp<std::true_type, T, Types...>
{
	using type = std::true_type;
};

template <typename T, typename Head, typename ...Tails>
struct type_in_tuple_imp<std::true_type, T, Head, Tails...>{
	using type = std::true_type;
};

template <typename T, typename Types>
struct type_in_tuple { using type = std::false_type;  };

template <typename T, typename Head, typename ...Tails>
struct type_in_tuple<T, std::tuple<Head, Tails...> >
{
	using type = typename type_in_tuple_imp<typename std::is_same<T, Head>::type, T, Tails...>::type;
};

ECS_NAMESPACE_END
