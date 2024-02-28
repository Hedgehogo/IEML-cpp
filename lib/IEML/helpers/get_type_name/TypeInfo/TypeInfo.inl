//included into TypeInfo.hpp

namespace ieml {
	namespace detail {
		template<typename T>
		StringView TypeInfoImpl<T>::get_name() const {
			return tnl::type_name<T>();
		}
		
		template<typename T>
		std::type_info const& TypeInfoImpl<T>::get_info() const {
			return typeid(T);
		}
	}
	
	template<typename T>
	TypeInfo const& get_type_info() {
		return detail::TypeInfoImpl<T>::object;
	}
}