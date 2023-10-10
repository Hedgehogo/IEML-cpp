//included into TypeInfo.hpp

namespace ieml {
	namespace detail {
		template<typename T>
		String TypeInfoImpl<T>::get_name() const {
			return TypeName<T>::get();
		}
		
		template<typename T>
		const std::type_info& TypeInfoImpl<T>::get_info() const {
			return typeid(T);
		}
	}
	
	template<typename T>
	const TypeInfo& get_type_info() {
		return detail::TypeInfoImpl<T>::object;
	}
}