#pragma once

#include <limits>
#include <type_traits>

namespace ieml {
	namespace cond {
		template<typename T>
		struct IsInt {
			static constexpr auto value = std::numeric_limits<T>::is_integer;
		};
		
		template<typename T>
		using IsFloat = std::is_arithmetic<T>;
		
		template<template<typename T> typename C, typename T>
		using EnableIf = std::enable_if_t<C<T>::value, T>;
	}
}
