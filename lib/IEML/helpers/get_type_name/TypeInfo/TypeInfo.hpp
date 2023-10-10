#pragma once

#include "../../../usings/usings.hpp"

namespace ieml {
	template<typename T>
	struct TypeName;
	
	class TypeInfo {
	public:
		virtual String get_name() const = 0;
		
		virtual const std::type_info& get_info() const = 0;
		
		operator const std::type_info&() const;
	};
	
	namespace detail {
		template<typename T>
		class TypeInfoImpl : public TypeInfo {
		public:
			static const TypeInfoImpl<T> object;
			
		private:
			TypeInfoImpl() = default;
			
		public:
			TypeInfoImpl(const TypeInfoImpl<T>& type_info) = delete;
			
			TypeInfoImpl(TypeInfoImpl<T>&& type_info) = delete;
			
			String get_name() const override;
			
			const std::type_info& get_info() const override;
		};
		
		template<typename T>
		const TypeInfoImpl<T> TypeInfoImpl<T>::object{};
	}
	
	template<typename T>
	const TypeInfo& get_type_info();
}

#include "TypeInfo.inl"
