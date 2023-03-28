//included into TypeInfo.hpp

namespace ieml {
	namespace detail {
		template<typename T>
		String TypeInfoImpl<T>::getName() const {
			return TypeName<T>::get();
		}
		
		template<typename T>
		const std::type_info& TypeInfoImpl<T>::getInfo() const {
			return typeid(T);
		}
	}
	
	template<typename T>
	const TypeInfo& getTypeInfo() {
		return detail::TypeInfoImpl<T>::object;
	}
}