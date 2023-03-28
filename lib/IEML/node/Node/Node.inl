//included into Node.hpp
#include "../../parser/helpers/toValue//toValue.hpp"
#include "../../parser/helpers/isValue/isValue.hpp"
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
		std::enable_if_t<!std::is_arithmetic_v<T>, bool> decode(const Node& node, T& object) {
			return Decode<T>::func(node, object);
		}
		
		template <typename T>
		std::enable_if_t<std::is_integral_v<T>, bool> decode(const Node& node, T& object) {
			if(node.isRaw()) {
				String str{node.as<RawData>()};
				if(isInt(str.cbegin(), str.cend())) {
					object = static_cast<T>(toInt(str.cbegin(), str.cend()));
					return true;
				}
			}
			return false;
		}
		
		template <typename T>
		std::enable_if_t<std::is_floating_point_v<T>, bool> decode(const Node& node, T& object) {
			if(node.isRaw()) {
				String str{node.as<RawData>()};
				if(isDouble(str.cbegin(), str.cend()) || isInt(str.cbegin(), str.cend())) {
					object = static_cast<T>(toDouble(str.cbegin(), str.cend()));
					return true;
				}
			}
			return false;
		}
		
		template <typename T>
		bool DecodeImpl<T>::func(const Node& node, T& object) {
			return decode(node, object);
		}
	}
	
	template <typename T>
	T Node::as() const {
		T object;
		if(detail::DecodeImpl<T>::func(*this, object))
			return object;
		throw FailedConvertDataException{mark, getTypeInfo<T>()};
	}
	
	template <typename T>
	T Node::asDefault(T&& defaultValue) const {
		if(!isDefined())
			return defaultValue;
		T object;
		if(detail::DecodeImpl<T>::func(*this, object))
			return object;
		throw FailedConvertDataException{mark, getTypeInfo<T>()};
	}
	
	template <typename Type, typename... ArgsTypes>
	Type* Node::asDefaultPtr(ArgsTypes... args) const {
		if(!isDefined())
			return new Type{args...};
		Type* object;
		if(detail::DecodeImpl<Type*>::func(*this, object))
			return object;
		throw FailedConvertDataException{mark, getTypeInfo<Type>()};
	}
}