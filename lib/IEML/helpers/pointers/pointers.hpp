#pragma once

#include <memory>

namespace ieml {
	template<typename T>
	using RcPtr = std::shared_ptr<T>;
	template<typename T>
	using WeakPtr = std::weak_ptr<T>;
	template<typename T>
	using BoxPtr = std::unique_ptr<T>;
	
	template<typename T, typename... A>
	auto makeBoxPtr(A&& ... args) -> decltype(std::make_unique<T>(std::forward<A>(args)...)) {
		return std::make_unique<T>(std::forward<A>(args)...);
	}
	
	template<typename T, typename... A>
	auto makeRcPtr(A&& ... args) -> decltype(std::make_shared<T>(std::forward<A>(args)...)) {
		return std::make_shared<T>(std::forward<A>(args)...);
	}
}
