#pragma once

#include <type-name/type-name.hpp>
#include "../../../usings/usings.hpp"

namespace ieml {
	class TypeInfo {
	public:
		virtual StringView get_name() const = 0;
		
		virtual std::type_info const& get_info() const = 0;
		
		operator std::type_info const&() const;
	};
	
	namespace detail {
		template<typename T>
		class TypeInfoImpl : public TypeInfo {
		public:
			static TypeInfoImpl<T> const object;
			
		private:
			TypeInfoImpl() = default;
			
		public:
			TypeInfoImpl(TypeInfoImpl<T> const& type_info) = delete;
			
			TypeInfoImpl(TypeInfoImpl<T>&& type_info) = delete;
			
			StringView get_name() const override;
			
			std::type_info const& get_info() const override;
		};
		
		template<typename T>
		TypeInfoImpl<T> const TypeInfoImpl<T>::object{};
	}
	
	template<typename T>
	TypeInfo const& get_type_info();
}

#include "TypeInfo.inl"
