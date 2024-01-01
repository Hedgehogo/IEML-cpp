//included into Node.hpp
#include "IEML/helpers/read_file/read_file.hpp"
#include "../../helpers/get_type_name/get_type_name.hpp"
#include "get/get.hpp"
#include "get_from.inl"

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
	NodeAnotherTypeException BasicNode<Char_>::make_type_error() const {
		return {get_mark(), Type, get_type()};
	}
	
	template<typename Char_>
	template<NodeType Type>
	TypeResult<ToNodeData<Type, Char_> const&> BasicNode<Char_>::get_typed_data_or_error() const {
		if(auto type_data = std::get_if<ToNodeData<Type, Char_> >(&data_.data_))
			return TypeResult<ToNodeData<Type, Char_> const&>::Ok(*type_data);
		return TypeResult<ToNodeData<Type, Char_> const&>::Error(make_type_error<Type>());
	}
	
	template<typename Char_>
	template<NodeType Type>
	TypeResult<ToNodeData<Type, Char_>&> BasicNode<Char_>::get_typed_data_or_error() {
		if(auto type_data = std::get_if<ToNodeData<Type, Char_> >(&data_.data_))
			return TypeResult<ToNodeData<Type, Char_>&>::Ok(*type_data);
		return TypeResult<ToNodeData<Type, Char_>&>::Error(make_type_error<Type>());
	}
	
	template<typename Char_>
	template<NodeType Type>
	Option<ToNodeData<Type, Char_> const&> BasicNode<Char_>::get_typed_data() const {
		if(auto type_data = std::get_if<ToNodeData<Type, Char_> >(&data_.data_))
			return {*type_data};
		return {};
	}
	
	template<typename Char_>
	template<NodeType Type>
	Option<ToNodeData<Type, Char_>&> BasicNode<Char_>::get_typed_data() {
		if(auto type_data = std::get_if<ToNodeData<Type, Char_> >(&data_.data_))
			return {*type_data};
		return {};
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::is_defined(BasicNode<Char_> const& node) {
		return &node != &undefined;
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::is_defined() const {
		return this != &undefined;
	}
	
	template<typename Char_>
	Mark BasicNode<Char_>::get_mark() const {
		return mark_;
	}
	
	template<typename Char_>
	NodeType BasicNode<Char_>::get_type() const {
		return get_node_type_from_index(data_.data_.index());
	}
	
	template<typename Char_>
	template<NodeType Type>
	bool BasicNode<Char_>::is() const {
		return data_.data_.index() == get_index_from_node_type(Type);
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::is_null() const {
		return is_defined() && get_clear().template is<NodeType::Null>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::is_raw() const {
		return is_defined() && get_clear().template is<NodeType::Raw>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::is_string() const {
		return is_defined() && get_clear().template is<NodeType::String>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::is_list() const {
		return is_defined() && get_clear().template is<NodeType::List>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::is_map() const {
		return is_defined() && get_clear().template is<NodeType::Map>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::is_with_tag() const {
		auto& clear_node{get_clear<NodeType::File, NodeType::TakeAnchor, NodeType::GetAnchor>()};
		return is_defined() && clear_node.template is<NodeType::Tag>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::is_file() const {
		auto& clear_node{get_clear<NodeType::Tag, NodeType::TakeAnchor, NodeType::GetAnchor>()};
		return is_defined() && clear_node.template is<NodeType::File>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::is_take_anchor() const {
		auto& clear_node{get_clear<NodeType::Tag, NodeType::File, NodeType::GetAnchor>()};
		return is_defined() && clear_node.template is<NodeType::TakeAnchor>();
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::is_get_anchor() const {
		auto& clear_node{get_clear<NodeType::Tag, NodeType::File, NodeType::TakeAnchor>()};
		return is_defined() && clear_node.template is<NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	template<NodeType... Types>
	BasicNode<Char_>& BasicNode<Char_>::get_clear() {
		return get_from<BasicNode<Char_>, ToNodeData<Types, Char_>...>(*this);
	}
	
	template<typename Char_>
	template<NodeType... Types>
	BasicNode<Char_> const& BasicNode<Char_>::get_clear() const {
		return get_from<const BasicNode<Char_>, ToNodeData<Types, Char_>...>(*this);
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::get_clear() {
		return get_clear<NodeType::Tag, NodeType::File, NodeType::TakeAnchor, NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::get_clear() const {
		return get_clear<NodeType::Tag, NodeType::File, NodeType::TakeAnchor, NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	template<NodeType... Types>
	BasicNode<Char_> const& BasicNode<Char_>::get_clear_data() const {
		if(auto clear_node{get_from_step<const BasicNode<Char_>, ToNodeData<Types, Char_>...>(*this)}) {
			return *clear_node;
		}
		return *this;
	}
	
	template<typename Char_>
	template<NodeType... Types>
	BasicNode<Char_>& BasicNode<Char_>::get_clear_data() {
		if(auto clear_node{get_from_step<BasicNode<Char_>, ToNodeData<Types, Char_>...>(*this)}) {
			return *clear_node;
		}
		return *this;
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::get_clear_tag() {
		return get_clear_data<NodeType::Tag>();
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::get_clear_tag() const {
		return get_clear_data<NodeType::Tag>();
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::get_clear_file() {
		return get_clear_data<NodeType::File>();
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::get_clear_file() const {
		return get_clear_data<NodeType::File>();
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::get_clear_take_anchor() {
		return get_clear_data<NodeType::TakeAnchor>();
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::get_clear_take_anchor() const {
		return get_clear_data<NodeType::TakeAnchor>();
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::get_clear_get_anchor() {
		return get_clear_data<NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::get_clear_get_anchor() const {
		return get_clear_data<NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::get_clear_anchor() {
		return get_clear_data<NodeType::TakeAnchor, NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::get_clear_anchor() const {
		return get_clear_data<NodeType::TakeAnchor, NodeType::GetAnchor>();
	}
	
	template<typename Char_>
	Option<BasicTag<Char_>&> BasicNode<Char_>::get_tag() {
		auto& clear_node{get_clear<NodeType::File, NodeType::TakeAnchor, NodeType::GetAnchor>()};
		if(auto tag_data{std::get_if<BasicTagData<Char_>>(&clear_node.data_.data_)}) {
			return {tag_data->tag_};
		}
		return {};
	}
	
	template<typename Char_>
	Option<BasicTag<Char_> const&> BasicNode<Char_>::get_tag() const {
		auto& clear_node{get_clear<NodeType::File, NodeType::TakeAnchor, NodeType::GetAnchor>()};
		if(auto tag_data{std::get_if<BasicTagData<Char_>>(&clear_node.data_.data_)}) {
			return {tag_data->tag_};
		}
		return {};
	}
	
	template<typename Char_>
	Option<FilePath const&> BasicNode<Char_>::get_file_path() const {
		auto& clear_node{get_clear<NodeType::Tag, NodeType::TakeAnchor, NodeType::GetAnchor>()};
		if(auto file_data{std::get_if<BasicFileData<Char_>>(&clear_node.data_.data_)}) {
			if(!file_data->file_path_.empty()) {
				return {file_data->file_path_};
			}
		}
		return {};
	}
	
	template<typename Char_>
	Option<BasicAnchorKeeper<Char_> const&> BasicNode<Char_>::get_file_anchor_keeper() const {
		auto& clear_node{get_clear<NodeType::Tag, NodeType::TakeAnchor, NodeType::GetAnchor>()};
		if(auto file_data{std::get_if<BasicFileData<Char_>>(&clear_node.data_.data_)}) {
			return {*file_data->anchor_keeper_};
		}
		return {};
	}
	
	template<typename Char_>
	Option<BasicString<Char_> const&> BasicNode<Char_>::get_take_anchor_name() const {
		auto& clear_node{get_clear<NodeType::Tag, NodeType::File, NodeType::GetAnchor>()};
		if(auto take_anchor_data{std::get_if<BasicTakeAnchorData<Char_>>(&clear_node.data_.data_)}) {
			return {take_anchor_data->name_};
		}
		return {};
	}
	
	template<typename Char_>
	Option<BasicString<Char_> const&> BasicNode<Char_>::get_get_anchor_name() const {
		auto& clear_node{get_clear<NodeType::Tag, NodeType::File, NodeType::TakeAnchor>()};
		if(auto get_anchor_data{std::get_if<BasicGetAnchorData<Char_>>(&clear_node.data_.data_)}) {
			return {get_anchor_data->name_};
		}
		return {};
	}
	
	template<typename Char_>
	Option<BasicString<Char_> const&> BasicNode<Char_>::get_anchor_name() const {
		auto& clear_node{get_clear<NodeType::Tag, NodeType::File>()};
		if(auto take_anchor_data{std::get_if<BasicTakeAnchorData<Char_>>(&clear_node.data_.data_)}) {
			return {take_anchor_data->name_};
		}
		if(auto get_anchor_data{std::get_if<BasicGetAnchorData<Char_>>(&clear_node.data_.data_)}) {
			return {get_anchor_data->name_};
		}
		return {};
	}
	
	template<typename Char_>
	TypeResult<Size> BasicNode<Char_>::get_list_size() const {
		if(auto list_data{std::get_if<BasicListData<Char_>>(&get_clear().data_.data_)})
			return TypeResult<Size>::Ok(list_data->size());
		return TypeResult<Size>::Error(make_type_error<NodeType::List>());
	}
	
	template<typename Char_>
	TypeResult<Size> BasicNode<Char_>::get_map_size() const {
		if(auto map_data{std::get_if<BasicMapData<Char_>>(&get_clear().data_.data_)})
			return TypeResult<Size>::Ok(map_data->size());
		return TypeResult<Size>::Error(make_type_error<NodeType::Map>());
	}
	
	template<typename Char_>
	TypeResult<Size> BasicNode<Char_>::get_size() const {
		auto& clear_node{get_clear()};
		if(auto list_data{std::get_if<BasicListData<Char_>>(&clear_node.data_.data_)})
			return TypeResult<Size>::Ok(list_data->size());
		if(auto map_data{std::get_if<BasicMapData<Char_>>(&clear_node.data_.data_)})
			return TypeResult<Size>::Ok(map_data->size());
		return TypeResult<Size>::Error(make_type_error<NodeType::List>());
	}
	
	template<typename Char_>
	TypeResult<ieml::BasicRawData<Char_>&> BasicNode<Char_>::get_raw() {
		return get_clear().template get_typed_data_or_error<NodeType::Raw>();
	}
	
	template<typename Char_>
	TypeResult<const ieml::BasicRawData<Char_>&> BasicNode<Char_>::get_raw() const {
		return get_clear().template get_typed_data_or_error<NodeType::Raw>();
	}
	
	template<typename Char_>
	TypeResult<ieml::BasicStringData<Char_>&> BasicNode<Char_>::get_string() {
		return get_clear().template get_typed_data_or_error<NodeType::String>();
	}
	
	template<typename Char_>
	TypeResult<const ieml::BasicStringData<Char_>&> BasicNode<Char_>::get_string() const {
		return get_clear().template get_typed_data_or_error<NodeType::String>();
	}
	
	template<typename Char_>
	TypeResult<BasicListData<Char_> const&> BasicNode<Char_>::get_list() const {
		return get_clear().template get_typed_data_or_error<NodeType::List>();
	}
	
	template<typename Char_>
	TypeResult<BasicMapData<Char_> const&> BasicNode<Char_>::get_map() const {
		return get_clear().template get_typed_data_or_error<NodeType::Map>();
	}
	
	template<typename Char_>
	TypeResult<BasicListView<Char_> > BasicNode<Char_>::get_list_view() const {
		auto& clear_node{get_clear()};
		auto list{clear_node.template get_typed_data_or_error<NodeType::List>()};
		if(list.is_ok()) {
			return TypeResult<BasicListView<Char_> >::Ok({list.ok(), clear_node.mark_});
		}
		return TypeResult<BasicListView<Char_> >::Error(std::move(list.error()));
	}
	
	template<typename Char_>
	TypeResult<BasicMapView<Char_> > BasicNode<Char_>::get_map_view() const {
		auto& clear_node{get_clear()};
		auto map{clear_node.template get_typed_data_or_error<NodeType::Map>()};
		if(map.is_ok()) {
			return TypeResult<BasicMapView<Char_> >::Ok({map.ok(), clear_node.mark_});
		}
		return TypeResult<BasicMapView<Char_> >::Error(std::move(map.error()));
	}
	
	template<typename Char_>
	ListResult<BasicNode<Char_>&> BasicNode<Char_>::at(Size index) {
		return get_clear()[index];
	}
	
	template<typename Char_>
	ListResult<BasicNode<Char_> const&> BasicNode<Char_>::at(Size index) const {
		return get_clear()[index];
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::at_or(Size index) {
		auto list{get_clear().template get_typed_data<NodeType::List>()};
		if(list.is_some() && (index < list.some().size()))
			return list.some().at(index);
		return undefined;
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::at_or(Size index) const {
		auto list{get_clear().template get_typed_data<NodeType::List>()};
		if(list.is_some() && (index < list.some().size()))
			return list.some().at(index);
		return undefined;
	}
	
	template<typename Char_>
	MapResult<Char_, BasicNode<Char_>&> BasicNode<Char_>::at(BasicString<Char_> const& key) {
		return get_clear()[key];
	}
	
	template<typename Char_>
	MapResult<Char_, BasicNode<Char_> const&> BasicNode<Char_>::at(BasicString<Char_> const& key) const {
		return get_clear()[key];
	}
	
	template<typename Char_>
	BasicNode<Char_>& BasicNode<Char_>::at_or(BasicString<Char_> const& key) {
		auto map{get_clear().template get_typed_data<NodeType::Map>()};
		if(map.is_some())
			if(auto find{map.some().find(key)}; find != map.some().end())
				return find->second;
		return undefined;
	}
	
	template<typename Char_>
	BasicNode<Char_> const& BasicNode<Char_>::at_or(BasicString<Char_> const& key) const {
		auto map{get_clear().template get_typed_data<NodeType::Map>()};
		if(map.is_some())
			if(auto find{map.some().find(key)}; find != map.some().end())
				return find->second;
		return undefined;
	}
	
	template<typename Char_>
	template<typename T>
	DecodeResult<T> BasicNode<Char_>::as() const {
		if(!is_defined())
			return DecodeResult<T>::Error({mark_, get_type_info<T>()});
		try {
			auto object{detail::DecodeImpl<Char_, T>::decode(*this)};
			if(object.is_some()) {
				return DecodeResult<T>::Ok(std::forward<T>(object.some()));
			}
		} catch(NodeException& e) {
			return DecodeResult<T>::Error({mark_, get_type_info<T>(), BoxPtr<NodeException>{e.clone()}});
		}
		return DecodeResult<T>::Error({mark_, get_type_info<T>()});
	}
	
	template<typename Char_>
	template<typename... Steps>
	GetResult<Char_, BasicNode<Char_>&> BasicNode<Char_>::get(Steps&& ... steps) {
		return detail::get_node<Char_>(*this, std::forward<Steps>(steps)...);
	}
	
	template<typename Char_>
	template<typename... Steps>
	GetResult<Char_, BasicNode<Char_> const&> BasicNode<Char_>::get(Steps&& ... steps) const {
		return detail::get_node<Char_>(*this, std::forward<Steps>(steps)...);
	}
	
	template<typename Char_>
	template<typename T, typename... Steps>
	GetAsResult<Char_, T> BasicNode<Char_>::get_as(Steps&& ... steps) const {
		auto item{get(std::forward<Steps>(steps)...)};
		if(item.is_ok()) {
			auto object{item.ok().template as<T>()};
			if(object.is_ok()) {
				return GetAsResult<Char_, T>::Ok(std::forward<T>(object.ok()));
			} else {
				return GetAsResult<Char_, T>::Error({std::move(object.error())});
			}
		}
		return GetAsResult<Char_, T>::Error(item.error().template move_upcast<FailedDecodeDataException>());
	}
	
	template<typename Char_>
	BasicNode<Char_>::operator bool() const {
		return this->is_defined();
	}
	
	template<typename Char_>
	ListResult<BasicNode<Char_>&> BasicNode<Char_>::operator[](Size index) {
		auto list{get_typed_data<NodeType::List>()};
		if(list.is_some()) {
			auto size{list.some().size()};
			if(size > index) {
				return ListResult<BasicNode<Char_>&>::Ok(list.some().at(index));
			}
			return ListResult<BasicNode<Char_>&>::Error({ListException{mark_, index, size}});
		}
		return ListResult<BasicNode<Char_>&>::Error({make_type_error<NodeType::List>()});
	}
	
	template<typename Char_>
	ListResult<BasicNode<Char_> const&> BasicNode<Char_>::operator[](Size index) const {
		auto list{get_typed_data<NodeType::List>()};
		if(list.is_some()) {
			auto size{list.some().size()};
			if(size > index) {
				return ListResult<BasicNode<Char_> const&>::Ok(list.some().at(index));
			}
			return ListResult<BasicNode<Char_> const&>::Error({ListException{mark_, index, size}});
		}
		return ListResult<BasicNode<Char_> const&>::Error({make_type_error<NodeType::List>()});
	}
	
	template<typename Char_>
	MapResult<Char_, BasicNode<Char_>&> BasicNode<Char_>::operator[](BasicString<Char_> const& key) {
		auto map{get_typed_data<NodeType::Map>()};
		if(map.is_some()) {
			if(auto find{map.some().find(key)}; find != map.some().end()) {
				return MapResult<Char_, BasicNode<Char_>&>::Ok(find->second);
			}
			return MapResult<Char_, BasicNode<Char_>&>::Error({MapException{mark_, key}});
		}
		return MapResult<Char_, BasicNode<Char_>&>::Error({make_type_error<NodeType::Map>()});
	}
	
	template<typename Char_>
	MapResult<Char_, BasicNode<Char_> const&> BasicNode<Char_>::operator[](BasicString<Char_> const& key) const {
		auto map{get_typed_data<NodeType::Map>()};
		if(map.is_some()) {
			if(auto find{map.some().find(key)}; find != map.some().end()) {
				return MapResult<Char_, BasicNode<Char_> const&>::Ok(find->second);
			}
			return MapResult<Char_, BasicNode<Char_> const&>::Error({MapException{mark_, key}});
		}
		return MapResult<Char_, BasicNode<Char_> const&>::Error({make_type_error<NodeType::Map>()});
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::operator==(const BasicNode<Char_>& other) const {
		return data_ == other.data_;
	}
	
	template<typename Char_>
	bool BasicNode<Char_>::operator!=(const BasicNode<Char_>& other) const {
		return !operator==(other);
	}
}