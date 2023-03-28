#pragma once

#include <memory>

namespace ieml {
	template<typename T>
	using Rc = std::shared_ptr<T>;
	template<typename T>
	using Weak = std::weak_ptr<T>;
	template<typename T>
	using Box = std::unique_ptr<T>;
	
	template<typename T, typename... A>
	auto makeBox(A&&... args) -> decltype(std::make_unique<T>(std::forward<A>(args)...)) {
		return std::make_unique<T>(std::forward<A>(args)...);
	}
	
	template<typename T, typename... A>
	auto makeRc(A&&... args) -> decltype(std::make_shared<T>(std::forward<A>(args)...)) {
		return std::make_shared<T>(std::forward<A>(args)...);
	}
}
