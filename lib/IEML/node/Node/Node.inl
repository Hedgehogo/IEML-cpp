//included into getTypeName.hpp
#include "../../toValue/toValue.hpp"
#include "../../isValue/isValue.hpp"
#include "../../getTypeName/getTypeName.hpp"
#include "../NodeData/exception/NodeAnotherTypeException.hpp"
#include "exception/FailedConvertDataException.hpp"

namespace ieml {
	namespace detail {
		template<typename T>
		std::enable_if_t<!std::is_arithmetic_v<T>, bool> decode(const Node &node, T &object) {
			return Decode<T>::func(node, object);
		}
		
		template<typename T>
		std::enable_if_t<std::is_integral_v<T>, bool> decode(const Node &node, T &object) {
			if(node.getType() == NodeType::Scalar) {
				std::string str{node.as<std::string>()};
				if(isInt(str.cbegin(), str.cend())) {
					object = static_cast<T>(toInt(str.cbegin(), str.cend()));
					return true;
				}
			}
			return false;
		}
		
		template<typename T>
		std::enable_if_t<std::is_floating_point_v<T>, bool> decode(const Node &node, T &object) {
			if(node.getType() == NodeType::Scalar) {
				std::string str{node.as<std::string>()};
				if(isDouble(str.cbegin(), str.cend())) {
					object = static_cast<T>(toDouble(str.cbegin(), str.cend()));
					return true;
				}
			}
			return false;
		}
		
		template <typename T>
		bool DecodeImpl<T>::func(const Node &node, T &object) {
			return decode(node, object);
		}
	}
	
	template <typename T>
	T Node::as() const {
		T object;
		if(detail::DecodeImpl<T>::func(*this, object))
			return object;
		throw FailedConvertDataException{mark, getTypeName<T>()};
	}
	
	template <typename T>
	T Node::asDefault(T &&defaultValue) const {
		if(!isDefined())
			return defaultValue;
		T object;
		if(detail::DecodeImpl<T>::func(*this, object))
			return object;
		throw FailedConvertDataException{mark, getTypeName<T>()};
	}
	
	template <typename Type, typename... ArgsTypes>
	Type *Node::asDefaultPtr(ArgsTypes... args) const {
		if(!isDefined())
			return new Type{args...};
		Type* object;
		if(detail::DecodeImpl<Type*>::func(*this, object))
			return object;
		throw FailedConvertDataException{mark, getTypeName<Type>()};
	}
}