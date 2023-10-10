#pragma once

#include <memory>

namespace ieml {
	namespace pointers {
		template<typename T>
		using RcPtr = std::shared_ptr<T>;
		template<typename T>
		using WeakPtr = std::weak_ptr<T>;
		template<typename T>
		using BoxPtr = std::unique_ptr<T>;
		
		template<typename T, typename... A>
		auto make_box_ptr(A&& ... args) -> decltype(std::make_unique<T>(std::forward<A>(args)...)) {
			return std::make_unique<T>(std::forward<A>(args)...);
		}
		
		template<typename T, typename... A>
		BoxPtr<T> clone_box_ptr(const BoxPtr<T>& other) {
			static_assert(!std::is_abstract_v<T>);
			if(other.get() != nullptr) {
				return make_box_ptr<T>(*other);
			} else {
				return BoxPtr<T>{nullptr};
			}
		}
		
		template<typename T, typename... A>
		auto make_rc_ptr(A&& ... args) -> decltype(std::make_shared<T>(std::forward<A>(args)...)) {
			return std::make_shared<T>(std::forward<A>(args)...);
		}
	}
	
	using namespace pointers;
}
