//included into Node.hpp
#include "../../helpers/readFile/readFile.hpp"
#include "../../helpers/getTypeName/getTypeName.hpp"
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
	template<NodeType Type>
	NodeAnotherTypeException BasicNode<Char_>::makeTypeError() const {
		return {getMark(), Type, getType()};
	}
	
	template<typename Char_>
	template<NodeType Type>
	TypeResult<ToNodeData<Type, Char_> const&> BasicNode<Char_>::getTypedDataOrError() const {
		if(auto typeData = std::get_if<ToNodeData<Type, Char_>>(&data_.data_))
			return TypeResult<ToNodeData<Type, Char_> const&>::Ok(*typeData);
		return TypeResult<ToNodeData<Type, Char_> const&>::Error(makeTypeError<Type>());
	}
	
	template<typename Char_>
	template<NodeType Type>
	TypeResult<ToNodeData<Type, Char_>&> BasicNode<Char_>::getTypedDataOrError() {
		if(auto typeData = std::get_if<ToNodeData<Type, Char_>>(&data_.data_))
			return TypeResult<ToNodeData<Type, Char_>&>::Ok(*typeData);
		return TypeResult<ToNodeData<Type, Char_> const&>::Error(makeTypeError<Type>());
	}
	
	template<typename Char_>
	template<NodeType Type>
	Option<ToNodeData<Type, Char_> const&> BasicNode<Char_>::getTypedData() const {
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
	bool BasicNode<Char_>::isDefined(BasicNode<Char_> const& node) {
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
	BasicNode<Char_> const& BasicNode<Char_>::getClear() const {
		return getFrom<const BasicNode<Char_>, ToNodeData<Types, Char_>...>(*this);
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::getClear() {
		return getClear<NodeType::Tag, NodeType::File, NodeType::TakeAnchor, NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::getClear() const {
		return getClear<NodeType::Tag, NodeType::File, NodeType::TakeAnchor, NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	template<NodeType... Types>
	BasicNode<Char_> const& BasicNode<Char_>::getClearData() const {
		if(auto clearNode{getFromStep<const BasicNode<Char_>, ToNodeData<Types, Char_>...>(*this)}) {
			return *clearNode;
		}
		return *this;
	}
	
	template<typename Char_>
	template<NodeType... Types>
	BasicNode<Char_>& BasicNode<Char_>::getClearData() {
		if(auto clearNode{getFromStep<BasicNode<Char_>, ToNodeData<Types, Char_>...>(*this)}) {
			return *clearNode;
		}
		return *this;
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::getClearTag() {
		return getClearData<NodeType::Tag>();
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::getClearTag() const {
		return getClearData<NodeType::Tag>();
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::getClearFile() {
		return getClearData<NodeType::File>();
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::getClearFile() const {
		return getClearData<NodeType::File>();
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::getClearTakeAnchor() {
		return getClearData<NodeType::TakeAnchor>();
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::getClearTakeAnchor() const {
		return getClearData<NodeType::TakeAnchor>();
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::getClearGetAnchor() {
		return getClearData<NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::getClearGetAnchor() const {
		return getClearData<NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::getClearAnchor() {
		return getClearData<NodeType::TakeAnchor, NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::getClearAnchor() const {
		return getClearData<NodeType::TakeAnchor, NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	Option<BasicTag<Char_>&> BasicNode<Char_>::getTag() {
		auto& clearNode{getClear<NodeType::File, NodeType::TakeAnchor, NodeType::GetAnchor>()};
		if(auto tagData{std::get_if<BasicTagData<Char_>>(&clearNode.data_.data_)}) {
			return {tagData->tag_};
		}
		return {};
	}
	
	template<typename Char_>
	Option<BasicTag<Char_> const&> BasicNode<Char_>::getTag() const {
		auto& clearNode{getClear<NodeType::File, NodeType::TakeAnchor, NodeType::GetAnchor>()};
		if(auto tagData{std::get_if<BasicTagData<Char_>>(&clearNode.data_.data_)}) {
			return {tagData->tag_};
		}
		return {};
	}
	
	template<typename Char_>
	Option<FilePath const&> BasicNode<Char_>::getFilePath() const {
		auto& clearNode{getClear<NodeType::Tag, NodeType::TakeAnchor, NodeType::GetAnchor>()};
		if(auto fileData{std::get_if<BasicFileData<Char_>>(&clearNode.data_.data_)}) {
			if(!fileData->filePath_.empty()) {
				return {fileData->filePath_};
			}
		}
		return {};
	}
	
	template<typename Char_>
	Option<BasicAnchorKeeper<Char_> const&> BasicNode<Char_>::getFileAnchorKeeper() const {
		auto& clearNode{getClear<NodeType::Tag, NodeType::TakeAnchor, NodeType::GetAnchor>()};
		if(auto fileData{std::get_if<BasicFileData<Char_>>(&clearNode.data_.data_)}) {
			return {*fileData->anchorKeeper_};
		}
		return {};
	}
	
	template<typename Char_>
	Option<BasicString<Char_> const&> BasicNode<Char_>::getTakeAnchorName() const {
		auto& clearNode{getClear<NodeType::Tag, NodeType::File, NodeType::GetAnchor>()};
		if(auto takeAnchorData{std::get_if<BasicTakeAnchorData<Char_>>(&clearNode.data_.data_)}) {
			return {takeAnchorData->name_};
		}
		return {};
	}
	
	template<typename Char_>
	Option<BasicString<Char_> const&> BasicNode<Char_>::getGetAnchorName() const {
		auto& clearNode{getClear<NodeType::Tag, NodeType::File, NodeType::TakeAnchor>()};
		if(auto getAnchorData{std::get_if<BasicGetAnchorData<Char_>>(&clearNode.data_.data_)}) {
			return {getAnchorData->name_};
		}
		return {};
	}
	
	template<typename Char_>
	Option<BasicString<Char_> const&> BasicNode<Char_>::getAnchorName() const {
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
	TypeResult<Size> BasicNode<Char_>::getListSize() const {
		if(auto listData{std::get_if<BasicListData<Char_>>(&getClear().data_.data_)})
			return TypeResult<Size>::Ok(listData->size());
		return TypeResult<Size>::Error(makeTypeError<NodeType::List>());
	}
	
	template<typename Char_>
	TypeResult<Size> BasicNode<Char_>::getMapSize() const {
		if(auto mapData{std::get_if<BasicMapData<Char_>>(&getClear().data_.data_)})
			return TypeResult<Size>::Ok(mapData->size());
		return TypeResult<Size>::Error(makeTypeError<NodeType::Map>());
	}
	
	template<typename Char_>
	TypeResult<Size> BasicNode<Char_>::getSize() const {
		auto& clearNode{getClear()};
		if(auto listData{std::get_if<BasicListData<Char_>>(&clearNode.data_.data_)})
			return TypeResult<Size>::Ok(listData->size());
		if(auto mapData{std::get_if<BasicMapData<Char_>>(&clearNode.data_.data_)})
			return TypeResult<Size>::Ok(mapData->size());
		return TypeResult<Size>::Error(makeTypeError<NodeType::List>());
	}
	
	template<typename Char_>
	TypeResult<ieml::BasicRawData<Char_>&> BasicNode<Char_>::getRaw() {
		return getClear().template getTypedDataOrError<NodeType::Raw>();
	}
	
	template<typename Char_>
	TypeResult<const ieml::BasicRawData<Char_>&> BasicNode<Char_>::getRaw() const {
		return getClear().template getTypedDataOrError<NodeType::Raw>();
	}
	
	template<typename Char_>
	TypeResult<ieml::BasicStringData<Char_>&> BasicNode<Char_>::getString() {
		return getClear().template getTypedDataOrError<NodeType::String>();
	}
	
	template<typename Char_>
	TypeResult<const ieml::BasicStringData<Char_>&> BasicNode<Char_>::getString() const {
		return getClear().template getTypedDataOrError<NodeType::String>();
	}
	
	template<typename Char_>
	TypeResult<BasicListData<Char_> const&> BasicNode<Char_>::getList() const {
		return getClear().template getTypedDataOrError<NodeType::List>();
	}
	
	template<typename Char_>
	TypeResult<BasicMapData<Char_> const&> BasicNode<Char_>::getMap() const {
		return getClear().template getTypedDataOrError<NodeType::Map>();
	}
	
	template<typename Char_>
	ListResult<BasicNode<Char_>&> BasicNode<Char_>::at(Size index) {
		return getClear()[index];
	}
	
	template<typename Char_>
	ListResult<BasicNode<Char_> const&> BasicNode<Char_>::at(Size index) const {
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
	BasicNode<Char_> const& BasicNode<Char_>::at_or(Size index) const {
		auto list{getClear().template getTypedData<NodeType::List>()};
		if(list.is_some() && (index < list.some().size()))
			return list.some().at(index);
		return undefined;
	}
	
	template<typename Char_>
	MapResult<Char_, BasicNode<Char_>&> BasicNode<Char_>::at(BasicString<Char_> const& key) {
		return getClear()[key];
	}
	
	template<typename Char_>
	MapResult<Char_, BasicNode<Char_> const&> BasicNode<Char_>::at(BasicString<Char_> const& key) const {
		return getClear()[key];
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::at_or(BasicString<Char_> const& key) {
		auto map{getClear().template getTypedData<NodeType::Map>()};
		if(map.is_some())
			if(auto find{map.some().find(key)}; find != map.some().end())
				return find->second;
		return undefined;
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::at_or(BasicString<Char_> const& key) const {
		auto map{getClear().template getTypedData<NodeType::Map>()};
		if(map.is_some())
			if(auto find{map.some().find(key)}; find != map.some().end())
				return find->second;
		return undefined;
	}
	
	template<typename Char_>
	template<typename T>
	DecodeResult<T> BasicNode<Char_>::as() const {
		if(!isDefined())
			return DecodeResult<T>::Error({mark_, getTypeInfo<T>()});
		try {
			auto object{detail::DecodeImpl<Char_, T>::decode(*this)};
			if(object.is_some()) {
				return DecodeResult<T>::Ok(std::move(object.some()));
			}
		} catch(NodeException& e) {
			return DecodeResult<T>::Error({mark_, getTypeInfo<T>(), BoxPtr<NodeException>{e.clone()}});
		}
		return DecodeResult<T>::Error({mark_, getTypeInfo<T>()});
	}
	
	template<typename Char_>
	template<typename... Steps>
	GetResult<Char_, BasicNode<Char_>&> BasicNode<Char_>::get(Steps&& ... steps) {
		return detail::getNode<Char_>(*this, std::forward<Steps>(steps)...);
	}
	
	template<typename Char_>
	template<typename... Steps>
	GetResult<Char_, BasicNode<Char_> const&> BasicNode<Char_>::get(Steps&& ... steps) const {
		return detail::getNode<Char_>(*this, std::forward<Steps>(steps)...);
	}
	
	template<typename Char_>
	template<typename T, typename... Steps>
	GetAsResult<Char_, T> BasicNode<Char_>::getAs(Steps&& ... steps) const {
		auto item{get(std::forward<Steps>(steps)...)};
		if(item.is_ok()) {
			auto object{item.ok().template as<T>()};
			if(object.is_ok()) {
				return GetAsResult<Char_, T>::Ok(std::move(object.ok()));
			} else {
				return GetAsResult<Char_, T>::Error({std::move(object.error())});
			}
		}
		return GetAsResult<Char_, T>::Error(item.error().template move_upcast<FailedDecodeDataException>());
	}
	
	template<typename Char_>
	BasicNode<Char_>::operator bool() const {
		return this->isDefined();
	}
	
	template<typename Char_>
	ListResult<BasicNode<Char_>&> BasicNode<Char_>::operator[](Size index) {
		auto list{getTypedData<NodeType::List>()};
		if(list.is_some()) {
			auto size{list.some().size()};
			if(size > index) {
				return ListResult<BasicNode<Char_>&>::Ok(list.some().at(index));
			}
			return ListResult<BasicNode<Char_>&>::Error({ListException{mark_, index, size}});
		}
		return ListResult<BasicNode<Char_>&>::Error({makeTypeError<NodeType::List>()});
	}
	
	template<typename Char_>
	ListResult<BasicNode<Char_> const&> BasicNode<Char_>::operator[](Size index) const {
		auto list{getTypedData<NodeType::List>()};
		if(list.is_some()) {
			auto size{list.some().size()};
			if(size > index) {
				return ListResult<BasicNode<Char_> const&>::Ok(list.some().at(index));
			}
			return ListResult<BasicNode<Char_> const&>::Error({ListException{mark_, index, size}});
		}
		return ListResult<BasicNode<Char_> const&>::Error({makeTypeError<NodeType::List>()});
	}
	
	template<typename Char_>
	MapResult<Char_, BasicNode<Char_>&> BasicNode<Char_>::operator[](BasicString<Char_> const& key) {
		auto map{getTypedData<NodeType::Map>()};
		if(map.is_some()) {
			if(auto find{map.some().find(key)}; find != map.some().end()) {
				return MapResult<Char_, BasicNode<Char_>&>::Ok(find->second);
			}
			return MapResult<Char_, BasicNode<Char_>&>::Error({MapException{mark_, key}});
		}
		return MapResult<Char_, BasicNode<Char_>&>::Error({makeTypeError<NodeType::Map>()});
	}
	
	template<typename Char_>
	MapResult<Char_, BasicNode<Char_> const&> BasicNode<Char_>::operator[](BasicString<Char_> const& key) const {
		auto map{getTypedData<NodeType::Map>()};
		if(map.is_some()) {
			if(auto find{map.some().find(key)}; find != map.some().end()) {
				return MapResult<Char_, BasicNode<Char_> const&>::Ok(find->second);
			}
			return MapResult<Char_, BasicNode<Char_> const&>::Error({MapException{mark_, key}});
		}
		return MapResult<Char_, BasicNode<Char_> const&>::Error({makeTypeError<NodeType::Map>()});
	}
}