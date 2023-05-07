#pragma once

#include <variant>
#include "../../usings/usings.hpp"

namespace ieml {
	template<Size Key_, typename Value_>
	struct Pair {
		static constexpr Size Key = Key_;
		using Value = Value_;
	};
	
	template<typename... Pairs>
	class Union {
	private:
		using Variant = std::variant<typename Pairs::Value...>;
		
		static constexpr Size variant_size = std::variant_size_v<Variant>;
		static constexpr Size keys[variant_size] = {Pairs::Key...};
		
		template<Size Index>
		static constexpr Size get_key() {
			return keys[Index];
		}
	
	public:
		template<Size Key>
		static constexpr Size get_index() {
			for(Size i = 0; i < variant_size; ++i) {
				if(Key == keys[i])
					return i;
			}
			return 0;
		}
		
	private:
		Variant object;
		
	public:
		template<typename T>
		Union(const T& object) : object(object) {
		}
		
		template<Size Key>
		using Type = std::variant_alternative_t<get_index<Key>(), Variant>;
		
		template<Size Key>
		Type<Key>* get() {
			return std::get_if<get_index<Key>()>(&object);
		}
		
		template<Size Key>
		const Type<Key>* get() const {
			return std::get_if<get_index<Key>()>(&object);
		}
		
		template<Size Key>
		void set(const Type<Key>& value) {
			object.template emplace<get_index<Key>()>(value);
		}
		
		template<Size Key>
		bool is() const {
			return object.index() == get_index<Key>();
		}
	};
}
