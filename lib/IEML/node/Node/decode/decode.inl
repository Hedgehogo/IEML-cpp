//included into Node.hpp
#include "../../../helpers/toValue//toValue.hpp"
#include "../../../helpers/isValue/isValue.hpp"

namespace ieml {
	namespace detail {
		template<typename Char_, typename T>
		Option<T> DecodeImpl<Char_, T>::decode(const BasicNode<Char_>& node) {
			if constexpr(std::is_arithmetic_v<T>) {
				if(node.isRaw()) {
					BasicString<Char_> str{node.template as<BasicRawData<Char_>>().ok()};
					return toNumber<T, Char_>(str.cbegin(), str.cend());
				}
			} else {
				return Decode<Char_, T>::decode(node);
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicRawData<Char_>> DecodeImpl<Char_, BasicRawData<Char_>>::decode(const BasicNode<Char_>& node) {
			if(auto strData = std::get_if<BasicRawData<Char_>>(&node.data_.data_)) {
				return {*strData};
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicString<Char_>> DecodeImpl<Char_, BasicString<Char_>>::decode(const BasicNode<Char_>& node) {
			if(auto strData = std::get_if<BasicStringData<Char_>>(&node.data_.data_)) {
				return {*strData};
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicListData<Char_>> DecodeImpl<Char_, BasicListData<Char_>>::decode(const BasicNode<Char_>& node) {
			if(auto listData = std::get_if<BasicListData<Char_>>(&node.data_.data_)) {
				return {*listData};
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicMapData<Char_>> DecodeImpl<Char_, BasicMapData<Char_>>::decode(const BasicNode<Char_>& node) {
			if(auto mapData = std::get_if<BasicMapData<Char_>>(&node.data_.data_)) {
				return {*mapData};
			}
			return {};
		}
	}
}