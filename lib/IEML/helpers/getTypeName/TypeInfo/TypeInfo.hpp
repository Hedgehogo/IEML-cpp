#pragma once

#include "../../../usings/usings.hpp"

namespace ieml {
	template<typename T>
	struct TypeName;
	
	class TypeInfo {
	public:
		virtual String getName() const = 0;
		
		virtual const std::type_info& getInfo() const = 0;
		
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
			TypeInfoImpl(const TypeInfoImpl<T>& typeInfo) = delete;
			
			TypeInfoImpl(TypeInfoImpl<T>&& typeInfo) = delete;
			
			String getName() const override;
			
			const std::type_info& getInfo() const override;
		};
		
		template<typename T>
		const TypeInfoImpl<T> TypeInfoImpl<T>::object{};
	}
	
	template<typename T>
	const TypeInfo& getTypeInfo();
}

#include "TypeInfo.inl"
