#pragma once

#include "ecs_config.hpp"

#include <cstdio>
#include <tuple>

ECS_NAMESPACE_BEGIN

template <typename type>
struct _type_info_base 
{
	using init_arg_tuple = type;
};

ECS_NAMESPACE_END

#define ECS_INIT_ARG(...) std::tuple< __VA_ARGS__ >
#define ECS_TYPE_INFO(type_name, args) struct _type_info : public ecs::_type_info_base<args> \
		{\
			static  const char *name() \
			{\
				return type_name;\
			}\
		};


