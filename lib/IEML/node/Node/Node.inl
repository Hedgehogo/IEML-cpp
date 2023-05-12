//included into Node.hpp
#include "../../helpers/readFile/readFile.hpp"
#include "../../helpers/getTypeName/getTypeName.hpp"
#include "../../parser/Parser/Parser.hpp"
#include "get/get.hpp"
#include "getFrom.inl"

namespace ieml {
	template<typename Char_>
	BasicNode<Char_> BasicNode<Char_>::undefined = BasicNode<Char_>{NullData{}, Mark{0, 0}};
	
	template<typename Char_>
	BasicNode<Char_>::BasicNode(BasicNodeData<Char_> data, Mark mark) :
		data_(BasicNodeData<Char_>{std::move(data)}), mark_(mark) {
	}
	
	template<typename Char_>
	template<typename T>
	BasicNode<Char_>::BasicNode(T data, Mark mark) :
		data_(BasicNodeData<Char_>{std::move(data)}), mark_(mark) {
	}
	
	template<typename Char_>
	template<typename T>
	BasicNode<Char_>::BasicNode(T data, FilePath filePath, Mark mark) :
		data_(BasicNodeData<Char_>{BasicFileData<Char_>{BasicNodeData<Char_>{std::move(data)}, filePath}}), mark_(mark) {
	}
	
	template<typename Char_>
	template<typename T, NodeType Type>
	Result<T, NodeAnotherTypeException> BasicNode<Char_>::makeTypeError() const {
		return GetResult<T>::Error(NodeAnotherTypeException{getMark(), Type, getType()});
	}
	
	template<typename Char_>
	template<NodeType Type>
	GetResult<const ToNodeData<Type, Char_>&> BasicNode<Char_>::getTypedDataOrError() const {
		if(auto typeData = std::get_if<ToNodeData<Type, Char_>>(&data_.data_))
			return GetResult<const ToNodeData<Type, Char_>&>::Ok(*typeData);
		return makeTypeError<const ToNodeData<Type, Char_>&, Type>();
	}
	
	template<typename Char_>
	template<NodeType Type>
	GetResult<ToNodeData<Type, Char_>&> BasicNode<Char_>::getTypedDataOrError() {
		if(auto typeData = std::get_if<ToNodeData<Type, Char_>>(&data_.data_))
			return GetResult<ToNodeData<Type, Char_>&>::Ok(*typeData);
		return makeTypeError<ToNodeData<Type, Char_>&, Type>();
	}
	
	template<typename Char_>
	template<NodeType Type>
	Option<const ToNodeData<Type, Char_>&> BasicNode<Char_>::getTypedData() const {
		if(auto typeData = std::get_if<ToNodeData<Type, Char_>>(&data_.data_))
			return {*typeData};
		return {};
	}
	
	template<typename Char_>
	template<NodeType Type>
	Option<ToNodeData<Type, Char_>&> BasicNode<Char_>::getTypedData() {
		if(auto typeData = std::get_if<ToNodeData<Type, Char_>>(&data_.data_))
			return {*typeData};
		return {};
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
		return mark_;
	}
	
	template<typename Char_>
	NodeType BasicNode<Char_>::getType() const {
		return getNodeTypeFromIndex(data_.data_.index());
	}
	
	template<typename Char_>
	template<NodeType Type>
	bool BasicNode<Char_>::is() const {
		return data_.data_.index() == getIndexFromNodeType(Type);
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isNull() const {
		return isDefined() && getClear().template is<NodeType::Null>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isRaw() const {
		return isDefined() && getClear().template is<NodeType::Raw>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isString() const {
		return isDefined() && getClear().template is<NodeType::String>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isList() const {
		return isDefined() && getClear().template is<NodeType::List>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isMap() const {
		return isDefined() && getClear().template is<NodeType::Map>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isWithTag() const {
		auto& clearNode{getClear<NodeType::File, NodeType::TakeAnchor, NodeType::GetAnchor>()};
		return isDefined() && clearNode.template is<NodeType::Tag>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isFile() const {
		auto& clearNode{getClear<NodeType::Tag, NodeType::TakeAnchor, NodeType::GetAnchor>()};
		return isDefined() && clearNode.template is<NodeType::File>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isTakeAnchor() const {
		auto& clearNode{getClear<NodeType::Tag, NodeType::File, NodeType::GetAnchor>()};
		return isDefined() && clearNode.template is<NodeType::TakeAnchor>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::isGetAnchor() const {
		auto& clearNode{getClear<NodeType::Tag, NodeType::File, NodeType::TakeAnchor>()};
		return isDefined() && clearNode.template is<NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	template<NodeType... Types>
	BasicNode<Char_>& BasicNode<Char_>::getClear() {
		return getFrom<BasicNode<Char_>, ToNodeData<Types, Char_>...>(*this);
	}
	
	template<typename Char_>
	template<NodeType... Types>
	const BasicNode<Char_>& BasicNode<Char_>::getClear() const {
		return getFrom<const BasicNode<Char_>, ToNodeData<Types, Char_>...>(*this);
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::getClear() {
		return getClear<NodeType::Tag, NodeType::File, NodeType::TakeAnchor, NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	const BasicNode<Char_>& BasicNode<Char_>::getClear() const {
		return getClear<NodeType::Tag, NodeType::File, NodeType::TakeAnchor, NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	template<NodeType... Types>
	const BasicNode<Char_>& BasicNode<Char_>::getClearData() const {
		if(auto clearNode{getFromStep<const BasicNode<Char_>, ToNodeData<Types, Char_>...>(*this)}) {
			return *clearNode;
		}
		return *this;
	}
	
	template<typename Char_>
	template<NodeType... Types>
	BasicNode<Char_>& BasicNode<Char_>::getClearData() {
		if(auto clearNode{getFromStep<const BasicNode<Char_>, ToNodeData<Types, Char_>...>(*this)}) {
			return *clearNode;
		}
		return *this;
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::getClearTag() {
		return getClearData<NodeType::Tag>();
	}
	
	template<typename Char_>
	const BasicNode<Char_>& BasicNode<Char_>::getClearTag() const {
		return getClearData<NodeType::Tag>();
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::getClearFile() {
		return getClearData<NodeType::File>();
	}
	
	template<typename Char_>
	const BasicNode<Char_>& BasicNode<Char_>::getClearFile() const {
		return getClearData<NodeType::File>();
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::getClearTakeAnchor() {
		return getClearData<NodeType::TakeAnchor>();
	}
	
	template<typename Char_>
	const BasicNode<Char_>& BasicNode<Char_>::getClearTakeAnchor() const {
		return getClearData<NodeType::TakeAnchor>();
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::getClearGetAnchor() {
		return getClearData<NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	const BasicNode<Char_>& BasicNode<Char_>::getClearGetAnchor() const {
		return getClearData<NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::getClearAnchor() {
		return getClearData<NodeType::TakeAnchor, NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	const BasicNode<Char_>& BasicNode<Char_>::getClearAnchor() const {
		return getClearData<NodeType::TakeAnchor, NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	Option<BasicTag<Char_>> BasicNode<Char_>::getTag() const {
		auto& clearNode{getClear<NodeType::File, NodeType::TakeAnchor, NodeType::GetAnchor>()};
		if(auto tagData{std::get_if<BasicTagData<Char_>>(&clearNode.data_.data_)}) {
			return {tagData->tag_};
		}
		return {};
	}
	
	template<typename Char_>
	Option<FilePath> BasicNode<Char_>::getFilePath() const {
		auto& clearNode{getClear<NodeType::Tag, NodeType::TakeAnchor, NodeType::GetAnchor>()};
		if(auto fileData{std::get_if<BasicFileData<Char_>>(&clearNode.data_.data_)}) {
			return {fileData->filePath_};
		}
		return {};
	}
	
	template<typename Char_>
	Option<BasicString<Char_>> BasicNode<Char_>::getTakeAnchorName() const {
		auto& clearNode{getClear<NodeType::Tag, NodeType::File, NodeType::GetAnchor>()};
		if(auto takeAnchorData{std::get_if<BasicTakeAnchorData<Char_>>(&clearNode.data_.data_)}) {
			return {takeAnchorData->name_};
		}
		return {};
	}
	
	template<typename Char_>
	Option<BasicString<Char_>> BasicNode<Char_>::getGetAnchorName() const {
		auto& clearNode{getClear<NodeType::Tag, NodeType::File, NodeType::TakeAnchor>()};
		if(auto getAnchorData{std::get_if<BasicGetAnchorData<Char_>>(&clearNode.data_.data_)}) {
			return {getAnchorData->name_};
		}
		return {};
	}
	
	template<typename Char_>
	Option<BasicString<Char_>> BasicNode<Char_>::getAnchorName() const {
		auto& clearNode{getClear<NodeType::Tag, NodeType::File>()};
		if(auto takeAnchorData{std::get_if<BasicTakeAnchorData<Char_>>(&clearNode.data_.data_)}) {
			return {takeAnchorData->name_};
		}
		if(auto getAnchorData{std::get_if<BasicGetAnchorData<Char_>>(&clearNode.data_.data_)}) {
			return {getAnchorData->name_};
		}
		return {};
	}
	
	template<typename Char_>
	GetResult<Size> BasicNode<Char_>::getListSize() const {
		if(auto listData{std::get_if<BasicListData<Char_>>(&getClear().data_.data_)})
			return GetResult<Size>::Ok(listData->size());
		return makeTypeError<Size, NodeType::List>();
	}
	
	template<typename Char_>
	GetResult<Size> BasicNode<Char_>::getMapSize() const {
		if(auto mapData{std::get_if<BasicMapData<Char_>>(&getClear().data_.data_)})
			return GetResult<Size>::Ok(mapData->size());
		return makeTypeError<Size, NodeType::Map>();
	}
	
	template<typename Char_>
	GetResult<Size> BasicNode<Char_>::getSize() const {
		auto& clearNode{getClear()};
		if(auto listData{std::get_if<BasicListData<Char_>>(&clearNode.data_.data_)})
			return GetResult<Size>::Ok(listData->size());
		if(auto mapData{std::get_if<BasicMapData<Char_>>(&clearNode.data_.data_)})
			return GetResult<Size>::Ok(mapData->size());
		return makeTypeError<Size, NodeType::List>();
	}
	
	template<typename Char_>
	GetResult<const BasicListData<Char_>&> BasicNode<Char_>::getList() const {
		return getClear().template getTypedDataOrError<NodeType::List>();
	}
	
	template<typename Char_>
	GetResult<const BasicMapData<Char_>&> BasicNode<Char_>::getMap() const {
		return getClear().template getTypedDataOrError<NodeType::Map>();
	}
	
	template<typename Char_>
	GetResult<BasicNode<Char_>&> BasicNode<Char_>::at(Size index) {
		return getClear()[index];
	}
	
	template<typename Char_>
	GetResult<const BasicNode<Char_>&> BasicNode<Char_>::at(Size index) const {
		return getClear()[index];
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::at_or(Size index) {
		auto list{getClear().template getTypedData<NodeType::List>()};
		if(list.is_some() && (index < list.some().size()))
			return list.some().at(index);
		return undefined;
	}
	
	template<typename Char_>
	const BasicNode<Char_>& BasicNode<Char_>::at_or(Size index) const {
		auto list{getClear().template getTypedData<NodeType::List>()};
		if(list.is_some() && (index < list.some().size()))
			return list.some().at(index);
		return undefined;
	}
	
	template<typename Char_>
	GetResult<BasicNode<Char_>&> BasicNode<Char_>::at(const BasicString<Char_>& key) {
		return getClear()[key];
	}
	
	template<typename Char_>
	GetResult<const BasicNode<Char_>&> BasicNode<Char_>::at(const BasicString<Char_>& key) const {
		return getClear()[key];
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::at_or(const BasicString<Char_>& key) {
		auto map{getClear().template getTypedData<NodeType::Map>()};
		if(map.is_some())
			if(auto find{map.some().find(key)}; find != map.some().end())
				return find->second;
		return undefined;
	}
	
	template<typename Char_>
	const BasicNode<Char_>& BasicNode<Char_>::at_or(const BasicString<Char_>& key) const {
		auto map{getClear().template getTypedData<NodeType::Map>()};
		if(map.is_some())
			if(auto find{map.some().find(key)}; find != map.some().end())
				return find->second;
		return undefined;
	}
	
	template<typename Char_>
	template<typename T>
	Result<T, FailedConvertDataException> BasicNode<Char_>::as() const {
		if(!isDefined())
			return ConvertResult<T>::Error({mark_, getTypeInfo<T>()});
		T object;
		if(detail::DecodeImpl<Char_, T>::decode(*this, object))
			return ConvertResult<T>::Ok(object);
		return ConvertResult<T>::Error({mark_, getTypeInfo<T>()});
	}
	
	template<typename Char_>
	template<typename... Steps>
	GetResult<BasicNode<Char_>&> BasicNode<Char_>::get(Steps&& ... steps) {
		return detail::getNode<Char_>(*this, std::forward<Steps>(steps)...);
	}
	
	template<typename Char_>
	template<typename... Steps>
	GetResult<const BasicNode<Char_>&> BasicNode<Char_>::get(Steps&& ... steps) const {
		return detail::getNode<Char_>(*this, std::forward<Steps>(steps)...);
	}
	
	template<typename Char_>
	template<typename T, typename... Steps>
	GetAsResult<T> BasicNode<Char_>::getAs(Steps&& ... steps) const {
		auto item{get(std::forward<Steps>(steps)...)};
		if(item.is_ok()) {
			if(!item.ok().isDefined())
				return GetAsResult<T>::Error({FailedConvertDataException{item.ok().mark_, getTypeInfo<T>()}});
			T object;
			if(detail::DecodeImpl<Char_, T>::decode(item.ok(), object))
				return GetAsResult<T>::Ok(object);
			return GetAsResult<T>::Error({FailedConvertDataException{item.ok().mark_, getTypeInfo<T>()}});
		}
		return GetAsResult<T>::Error({item.error()});
	}
	
	template<typename Char_>
	BasicNode<Char_>::operator bool() const {
		return this->isDefined();
	}
	
	template<typename Char_>
	GetResult<BasicNode<Char_>&> BasicNode<Char_>::operator[](Size index) {
		auto list{getTypedData<NodeType::List>()};
		if(list.is_some() && (index < list.some().size()))
			return GetResult<BasicNode<Char_>&>::Ok(list.some().at(index));
		return makeTypeError<BasicNode<Char_>&, NodeType::List>();
	}
	
	template<typename Char_>
	GetResult<const BasicNode<Char_>&> BasicNode<Char_>::operator[](Size index) const {
		auto list{getTypedData<NodeType::List>()};
		if(list.is_some() && (index < list.some().size()))
			return GetResult<const BasicNode<Char_>&>::Ok(list.some().at(index));
		return makeTypeError<const BasicNode<Char_>&, NodeType::List>();
	}
	
	template<typename Char_>
	GetResult<BasicNode<Char_>&> BasicNode<Char_>::operator[](const BasicString<Char_>& key) {
		auto map{getTypedData<NodeType::Map>()};
		if(map.is_some())
			if(auto find{map.some().find(key)}; find != map.some().end())
				return GetResult<BasicNode<Char_>&>::Ok(find->second);
		return makeTypeError<BasicNode<Char_>&, NodeType::Map>();
	}
	
	template<typename Char_>
	GetResult<const BasicNode<Char_>&> BasicNode<Char_>::operator[](const BasicString<Char_>& key) const {
		auto map{getTypedData<NodeType::Map>()};
		if(map.is_some())
			if(auto find{map.some().find(key)}; find != map.some().end())
				return GetResult<const BasicNode<Char_>&>::Ok(find->second);
		return makeTypeError<const BasicNode<Char_>&, NodeType::Map>();
	}
	
	template<typename Char_>
	BasicNode<Char_> fromFile(FilePath&& filePath, RcPtr<BasicAnchorKeeper<Char_>> anchorKeeper) {
		FilePath normalFilePath{filePath.concat(".ieml").lexically_normal().make_preferred()};
		BasicString<Char_> inputStr{readFile<Char_>(normalFilePath)};
		BasicParser<Char_> parser{inputStr, normalFilePath, anchorKeeper};
		return BasicNode{parser.parse()};
	}
	
	template<typename Char_>
	BasicNode<Char_> from(const BasicString<Char_>& inputStr, RcPtr<BasicAnchorKeeper<Char_>> anchorKeeper) {
		BasicParser<Char_> parser{inputStr, anchorKeeper};
		return BasicNode(parser.parse());
	}
}