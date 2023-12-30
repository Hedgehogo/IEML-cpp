//included into Node.hpp
#include "../../../helpers/to_value/to_value.hpp"

namespace ieml {
	namespace detail {
		template<typename Char_, typename T>
		Option<T> DecodeImpl<Char_, T>::decode(BasicNode<Char_> const& node) {
			if constexpr(std::is_arithmetic_v<T>) {
				if(auto raw_data{node.template as<BasicRawData<Char_> >()}) {
					return to_number<T, Char_>(raw_data.ok().str.cbegin(), raw_data.ok().str.cend());
				}
			} else {
				return Decode<Char_, T>::decode(node);
			}
			return {};
		}
		
		template<typename Char_>
		Option<bool> DecodeImpl<Char_, bool>::decode(BasicNode<Char_> const& node) {
			if(auto raw_data{std::get_if<BasicRawData<Char_> >(&node.data_.data_)}) {
				return to_bool<Char_>(raw_data->str.cbegin(), raw_data->str.cend());
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicRawData<Char_> > DecodeImpl<Char_, BasicRawData<Char_> >::decode(BasicNode<Char_> const& node) {
			if(auto raw_data{std::get_if<BasicRawData<Char_> >(&node.data_.data_)}) {
				return {*raw_data};
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicString<Char_> > DecodeImpl<Char_, BasicString<Char_> >::decode(BasicNode<Char_> const& node) {
			if(auto str_data{std::get_if<BasicStringData<Char_> >(&node.data_.data_)}) {
				return {*str_data};
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicString<Char_> const&> DecodeImpl<Char_, BasicString<Char_> const&>::decode(BasicNode<Char_> const& node) {
			if(auto str_data{std::get_if<BasicStringData<Char_> >(&node.data_.data_)}) {
				return {*str_data};
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicListData<Char_> > DecodeImpl<Char_, BasicListData<Char_> >::decode(BasicNode<Char_> const& node) {
			if(auto list_data{std::get_if<BasicListData<Char_> >(&node.data_.data_)}) {
				return {*list_data};
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicListData<Char_> const&> DecodeImpl<Char_, BasicListData<Char_> const&>::decode(BasicNode<Char_> const& node) {
			if(auto list_data{std::get_if<BasicListData<Char_> >(&node.data_.data_)}) {
				return {*list_data};
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicMapData<Char_> > DecodeImpl<Char_, BasicMapData<Char_> >::decode(BasicNode<Char_> const& node) {
			if(auto map_data{std::get_if<BasicMapData<Char_> >(&node.data_.data_)}) {
				return {*map_data};
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicMapData<Char_> const&> DecodeImpl<Char_, BasicMapData<Char_> const&>::decode(BasicNode<Char_> const& node) {
			if(auto map_data{std::get_if<BasicMapData<Char_> >(&node.data_.data_)}) {
				return {*map_data};
			}
			return {};
		}
	}
}