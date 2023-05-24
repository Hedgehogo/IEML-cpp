//included into Node.hpp
#include "../../../helpers/toValue//toValue.hpp"

namespace ieml {
	namespace detail {
		template<typename Char_, typename T>
		Option<T> DecodeImpl<Char_, T>::decode(const BasicNode<Char_>& node) {
			if constexpr(std::is_arithmetic_v<T>) {
				if(auto rawData{node.template as<BasicRawData<Char_>>()}) {
					return toNumber<T, Char_>(rawData.ok().str.cbegin(), rawData.ok().str.cend());
				}
			} else {
				return Decode<Char_, T>::decode(node);
			}
			return {};
		}
		
		template<typename Char_>
		Option<bool> DecodeImpl<Char_, bool>::decode(const BasicNode<Char_>& node) {
			if(auto rawData{std::get_if<BasicRawData<Char_>>(&node.data_.data_)}) {
				return toBool<Char_>(rawData->str.cbegin(), rawData->str.cend());
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicRawData<Char_>> DecodeImpl<Char_, BasicRawData<Char_>>::decode(const BasicNode<Char_>& node) {
			if(auto rawData{std::get_if<BasicRawData<Char_>>(&node.data_.data_)}) {
				return {*rawData};
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicString<Char_>> DecodeImpl<Char_, BasicString<Char_>>::decode(const BasicNode<Char_>& node) {
			if(auto strData{std::get_if<BasicStringData<Char_>>(&node.data_.data_)}) {
				return {*strData};
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicListData<Char_>> DecodeImpl<Char_, BasicListData<Char_>>::decode(const BasicNode<Char_>& node) {
			if(auto listData{std::get_if<BasicListData<Char_>>(&node.data_.data_)}) {
				return {*listData};
			}
			return {};
		}
		
		template<typename Char_>
		Option<BasicMapData<Char_>> DecodeImpl<Char_, BasicMapData<Char_>>::decode(const BasicNode<Char_>& node) {
			if(auto mapData{std::get_if<BasicMapData<Char_>>(&node.data_.data_)}) {
				return {*mapData};
			}
			return {};
		}
	}
}