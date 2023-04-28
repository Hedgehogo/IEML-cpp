//included into Node.hpp
#include "../../helpers/toValue//toValue.hpp"
#include "../../helpers/isValue/isValue.hpp"
#include "../../helpers/getTypeName/getTypeName.hpp"
#include "../exception/NodeAnotherTypeException.hpp"
#include "exception/FailedConvertDataException.hpp"

namespace ieml {
	template <typename T>
	Node::Node(T data, Mark mark) :
		data(std::move(data)), mark(mark) {
	}
	
	template <typename T>
	Node::Node(T data, FilePath filePath, Mark mark) :
		data(FileData{NodeData{std::move(data)}, filePath}), mark(mark) {
	}
	
	template <typename T, typename E>
	const T& Node::getType(E e) const {
		auto& clearData = getDataFrom(data);
		if(auto typeData = std::get_if<T>(&clearData))
			return *typeData;
		throw e;
	}
	
	template <typename T, typename E>
	T& Node::getType(E e) {
		auto& clearData = getDataFrom(data);
		if(auto typeData = std::get_if<T>(&clearData))
			return *typeData;
		throw e;
	}
	
	template <NodeType Type>
	bool Node::is() const {
		auto& clearData = getDataFrom(data);
		return clearData.index() == getIndexFromNodeType(Type);
	}
	
	namespace detail {
		template <typename T>
		bool DecodeImpl<T>::decode(const Node& node, T& object) {
			if constexpr(std::is_arithmetic_v<T>) {
				if(node.isRaw()) {
					String str{node.as<RawData>()};
					if(auto number{toNumber<T, String::value_type>(str.cbegin(), str.cend())}) {
						object = *number;
						return true;
					}
				}
			} else {
				return Decode<T>::decode(node, object);
			}
			return false;
		}
	}
	
	template <typename T>
	T Node::as() const {
		T object;
		if(detail::DecodeImpl<T>::decode(*this, object))
			return object;
		throw FailedConvertDataException{mark, getTypeInfo<T>()};
	}
	
	template <typename T>
	T Node::asOr(T&& defaultValue) const {
		if(!isDefined())
			return defaultValue;
		T object;
		if(detail::DecodeImpl<T>::decode(*this, object))
			return object;
		return defaultValue;
	}
	
	template <typename Type, typename... ArgsTypes>
	Type* Node::asPtrOr(ArgsTypes... args) const {
		if(!isDefined())
			return new Type{args...};
		Type* object;
		if(detail::DecodeImpl<Type*>::decode(*this, object))
			return object;
		return new Type{args...};
	}
}