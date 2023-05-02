//included into Node.hpp
#include "../../helpers/readFile/readFile.hpp"
#include "../../helpers/getTypeName/getTypeName.hpp"
#include "../../parser/Parser/Parser.hpp"
#include "../exception/NodeAnotherTypeException.hpp"
#include "exception/FailedConvertDataException.hpp"
#include "getFrom.inl"

namespace ieml {
	template<typename Char_>
	BasicNode<Char_> BasicNode<Char_>::undefined = BasicNode<Char_>{NullData{}, Mark{0, 0}};
	
	template<typename Char_>
	BasicNode<Char_>::BasicNode(BasicNodeData<Char_> data, Mark mark) :
		data(BasicNodeData<Char_>{std::move(data)}), mark(mark) {
	}
	
	template<typename Char_>
	template<typename T>
	BasicNode<Char_>::BasicNode(T data, Mark mark) :
		data(BasicNodeData<Char_>{std::move(data)}), mark(mark) {
	}
	
	template<typename Char_>
	template<typename T>
	BasicNode<Char_>::BasicNode(T data, FilePath filePath, Mark mark) :
		data(BasicNodeData<Char_>{BasicFileData<Char_>{BasicNodeData<Char_>{std::move(data)}, filePath}}), mark(mark) {
	}
	
	template<typename Char_>
	const BasicNodeData<Char_>& BasicNode<Char_>::getDataFrom(const BasicNodeData<Char_>& data) {
		return getFrom<const BasicNodeData<Char_>, BasicTagData<Char_>, BasicFileData<Char_>, BasicTakeAnchorData<Char_>, BasicGetAnchorData<Char_>>(data);
	}
	
	template<typename Char_>
	BasicNodeData<Char_>& BasicNode<Char_>::getDataFrom(BasicNodeData<Char_>& data) {
		return getFrom<BasicNodeData<Char_>, BasicTagData<Char_>, BasicFileData<Char_>, BasicTakeAnchorData<Char_>, BasicGetAnchorData<Char_>>(data);
	}
	
	template<typename Char_>
	const BasicFileData<Char_>* BasicNode<Char_>::getFileFrom(const BasicNodeData<Char_>& data) {
		auto& getData{getFrom<const BasicNodeData<Char_>, BasicTagData<Char_>, BasicTakeAnchorData<Char_>, BasicGetAnchorData<Char_>>(data)};
		return std::get_if<BasicFileData<Char_>>(&getData.data);
	}
	
	template<typename Char_>
	BasicFileData<Char_>* BasicNode<Char_>::getFileFrom(BasicNodeData<Char_>& data) {
		auto& getData{getFrom<BasicNodeData<Char_>, BasicTagData<Char_>, BasicTakeAnchorData<Char_>, BasicGetAnchorData<Char_>>(data)};
		return std::get_if<BasicFileData<Char_>>(&getData.data);
	}
	
	template<typename Char_>
	const BasicTagData<Char_>* BasicNode<Char_>::getTagFrom(const BasicNodeData<Char_>& data) {
		auto& getData{getFrom<const BasicNodeData<Char_>, BasicFileData<Char_>, BasicTakeAnchorData<Char_>, BasicGetAnchorData<Char_>>(data)};
		return std::get_if<BasicTagData<Char_>>(&getData.data);
	}
	
	template<typename Char_>
	BasicTagData<Char_>* BasicNode<Char_>::getTagFrom(BasicNodeData<Char_>& data) {
		auto& getData{getFrom<BasicNodeData<Char_>, BasicFileData<Char_>, BasicTakeAnchorData<Char_>, BasicGetAnchorData<Char_>>(data)};
		return std::get_if<BasicTagData<Char_>>(&getData.data);
	}
	
	template<typename Char_>
	const BasicTakeAnchorData<Char_>* BasicNode<Char_>::getTakeAnchorFrom(const BasicNodeData<Char_>& data) {
		auto& getData{getFrom<const BasicNodeData<Char_>, BasicTagData<Char_>, BasicFileData<Char_>, BasicGetAnchorData<Char_>>(data)};
		return std::get_if<BasicTakeAnchorData<Char_>>(&getData.data);
	}
	
	template<typename Char_>
	BasicTakeAnchorData<Char_>* BasicNode<Char_>::getTakeAnchorFrom(BasicNodeData<Char_>& data) {
		auto& getData{getFrom<BasicNodeData<Char_>, BasicTagData<Char_>, BasicFileData<Char_>, BasicGetAnchorData<Char_>>(data)};
		return std::get_if<BasicTakeAnchorData<Char_>>(&getData.data);
	}
	
	template<typename Char_>
	const BasicGetAnchorData<Char_>* BasicNode<Char_>::getGetAnchorFrom(const BasicNodeData<Char_>& data) {
		auto& getData{getFrom<const BasicNodeData<Char_>, BasicTagData<Char_>, BasicFileData<Char_>, BasicTakeAnchorData<Char_>>(data)};
		return std::get_if<BasicGetAnchorData<Char_>>(&getData.data);
	}
	
	template<typename Char_>
	BasicGetAnchorData<Char_>* BasicNode<Char_>::getGetAnchorFrom(BasicNodeData<Char_>& data) {
		auto& getData{getFrom<BasicNodeData<Char_>, BasicTagData<Char_>, BasicFileData<Char_>, BasicTakeAnchorData<Char_>>(data)};
		return std::get_if<BasicGetAnchorData<Char_>>(&getData.data);
	}
	
	template<typename Char_>
	template<typename T, typename E>
	const T& BasicNode<Char_>::getType(E e) const {
		auto& clearData = getDataFrom(data);
		if(auto typeData = std::get_if<T>(&clearData.data))
			return *typeData;
		throw e;
	}
	
	template<typename Char_>
	template<typename T, typename E>
	T& BasicNode<Char_>::getType(E e) {
		auto& clearData = getDataFrom(data);
		if(auto typeData = std::get_if<T>(&clearData.data))
			return *typeData;
		throw e;
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isDefined(const BasicNode<Char_>& node) {
		return &node != &undefined;
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isDefined() const {
		return this != &undefined;
	}
	
	template<typename Char_>
	Mark BasicNode<Char_>::getMark() const {
		return mark;
	}
	
	template<typename Char_>
	NodeType BasicNode<Char_>::getType() const {
		auto& clearData = getDataFrom(data);
		return getNodeTypeFromIndex(clearData.data.index());
	}
	
	template<typename Char_>
	template<NodeType Type>
	bool BasicNode<Char_>::is() const {
		auto& clearData = getDataFrom(data);
		return clearData.data.index() == getIndexFromNodeType(Type);
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isNull() const {
		return this->is<NodeType::Null>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isRaw() const {
		return this->is<NodeType::Raw>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isString() const {
		return this->is<NodeType::String>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isList() const {
		return this->is<NodeType::List>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isMap() const {
		return this->is<NodeType::Map>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isTakeAnchor() const {
		return getTakeAnchorFrom(data) != nullptr;
	}
	
	template<typename Char_>
	Option<BasicString<Char_>> BasicNode<Char_>::getTakeAnchorName() const {
		if(auto tagData = getTakeAnchorFrom(data))
			return tagData->name;
		return {};
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isGetAnchor() const {
		return getGetAnchorFrom(data) != nullptr;
	}
	
	template<typename Char_>
	Option<BasicString<Char_>> BasicNode<Char_>::getGetAnchorName() const {
		if(auto tagData = getGetAnchorFrom(data))
			return tagData->name;
		return {};
	}
	
	template<typename Char_>
	Option<BasicString<Char_>> BasicNode<Char_>::getAnchorName() const {
		auto getData{getFrom<const BasicNodeData<Char_>, BasicTagData<Char_>, BasicFileData<Char_>>(data)};
		if(auto takeAnchorData{std::get_if<BasicTakeAnchorData<Char_>>(&getData.data)})
			return takeAnchorData->name;
		if(auto getAnchorData{std::get_if<BasicTakeAnchorData<Char_>>(&getData.data)})
			return getAnchorData->name;
		return {};
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isWithTag() const {
		return getTagFrom(data) != nullptr;
	}
	
	template<typename Char_>
	Option<BasicTag<Char_>> BasicNode<Char_>::getTag() const {
		if(auto tagData = getTagFrom(data))
			return tagData->tag;
		return {};
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isFile() const {
		return getFileFrom(data) != nullptr;
	}
	
	template<typename Char_>
	Option<FilePath> BasicNode<Char_>::getFilePath() const {
		if(auto fileData = getFileFrom(data))
			return fileData->filePath;
		return {};
	}
	
	template<typename Char_>
	Size BasicNode<Char_>::getSize() const {
		auto& clearData = getDataFrom(data);
		if(auto listData = std::get_if<BasicListData<Char_>>(&clearData.data))
			return listData->size();
		if(auto mapData = std::get_if<BasicMapData<Char_>>(&clearData.data))
			return mapData->size();
		throw NodeAnotherTypeException{NodeType::List, getType()};
	}
	
	template<typename Char_>
	const BasicListData<Char_>& BasicNode<Char_>::getList() const {
		return getType<BasicListData<Char_>>(NodeAnotherTypeException{NodeType::List, getType()});
	}
	
	template<typename Char_>
	const BasicMapData<Char_>& BasicNode<Char_>::getMap() const {
		return getType<BasicMapData<Char_>>(NodeAnotherTypeException{NodeType::Map, getType()});
	}
	
	template<typename Char_>
	template<typename T>
	T BasicNode<Char_>::as() const {
		T object;
		if(detail::DecodeImpl<Char_, T>::decode(*this, object))
			return object;
		throw FailedConvertDataException{mark, getTypeInfo<T>()};
	}
	
	template<typename Char_>
	template<typename T>
	T BasicNode<Char_>::asOr(T&& defaultValue) const {
		if(!isDefined())
			return defaultValue;
		T object;
		if(detail::DecodeImpl<Char_, T>::decode(*this, object))
			return object;
		return defaultValue;
	}
	
	template<typename Char_>
	template<typename Type, typename... ArgsTypes>
	Type* BasicNode<Char_>::asPtrOr(ArgsTypes... args) const {
		if(!isDefined())
			return new Type{args...};
		Type* object;
		if(detail::DecodeImpl<Char_, Type*>::decode(*this, object))
			return object;
		return new Type{args...};
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::at(Size index) {
		auto& list = getType<BasicListData<Char_>>(NodeAnotherTypeException{NodeType::List, getType()});
		if(index < list.size())
			return list.at(index);
		return undefined;
	}
	
	template<typename Char_>
	const BasicNode<Char_>& BasicNode<Char_>::at(Size index) const {
		auto& list = getType<BasicListData<Char_>>(NodeAnotherTypeException{NodeType::List, getType()});
		if(index < list.size())
			return list.at(index);
		return undefined;
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::at(const BasicString<Char_>& key) {
		auto& map = getType<BasicMapData<Char_>>(NodeAnotherTypeException{NodeType::Map, getType()});
		if(auto find{map.find(key)}; find != map.end())
			return find->second;
		return undefined;
	}
	
	template<typename Char_>
	const BasicNode<Char_>& BasicNode<Char_>::at(const BasicString<Char_>& key) const {
		auto& map = getType<BasicMapData<Char_>>(NodeAnotherTypeException{NodeType::Map, getType()});
		if(auto find{map.find(key)}; find != map.end())
			return *find->second;
		return undefined;
	}
	
	template<typename Char_>
	BasicNode<Char_>::operator bool() const {
		return this->isDefined();
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::operator[](Size index) {
		return this->at(index);
	}
	
	template<typename Char_>
	const BasicNode<Char_>& BasicNode<Char_>::operator[](Size index) const {
		return this->at(index);
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::operator[](const BasicString<Char_>& key) {
		return this->at(key);
	}
	
	template<typename Char_>
	const BasicNode<Char_>& BasicNode<Char_>::operator[](const BasicString<Char_>& key) const {
		return this->at(key);
	}
	
	template<typename Char_>
	BasicNode<Char_> fromFile(FilePath&& filePath, Rc<BasicAnchorKeeper<Char_>> anchorKeeper) {
		FilePath normalFilePath{filePath.concat(".ieml").lexically_normal().make_preferred()};
		BasicString<Char_> inputStr{readFile<Char_>(normalFilePath)};
		BasicParser<Char_> parser{inputStr, normalFilePath, anchorKeeper};
		return BasicNode{parser.parse()};
	}
	
	template<typename Char_>
	BasicNode<Char_> from(const BasicString<Char_>& inputStr, Rc<BasicAnchorKeeper<Char_>> anchorKeeper) {
		BasicParser<Char_> parser{inputStr, anchorKeeper};
		return BasicNode(parser.parse());
	}
}