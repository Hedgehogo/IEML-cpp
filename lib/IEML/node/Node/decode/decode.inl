//included into Node.hpp
#include "../../../helpers/toValue//toValue.hpp"
#include "../../../helpers/isValue/isValue.hpp"

namespace ieml {
	namespace detail {
		template<typename Char_, typename T>
		bool DecodeImpl<Char_, T>::decode(const BasicNode<Char_>& node, T& object) {
			if constexpr(std::is_arithmetic_v<T>) {
				if(node.isRaw()) {
					BasicString<Char_> str{node.template as<BasicRawData<Char_>>()};
					if(auto number{toNumber<T, Char_>(str.cbegin(), str.cend())}) {
						object = *number;
						return true;
					}
				}
			} else {
				return Decode<Char_, T>::decode(node, object);
			}
			return false;
		}
		
		template<typename Char_>
		bool DecodeImpl<Char_, BasicRawData<Char_>>::decode(const BasicNode<Char_>& node, BasicRawData<Char_>& object) {
			auto& clearData = BasicNode<Char_>::getDataFrom(node.data);
			if(auto strData = std::get_if<BasicRawData<Char_>>(&clearData.data)) {
				object = *strData;
				return true;
			}
			return false;
		}
		
		template<typename Char_>
		bool DecodeImpl<Char_, BasicString<Char_>>::decode(const BasicNode<Char_>& node, BasicString<Char_>& object) {
			auto& clearData = BasicNode<Char_>::getDataFrom(node.data);
			if(auto strData = std::get_if<BasicStringData<Char_>>(&clearData.data)) {
				object = *strData;
				return true;
			}
			return false;
		}
		
		template<typename Char_>
		bool DecodeImpl<Char_, BasicListData<Char_>>::decode(const BasicNode<Char_>& node, BasicListData<Char_>& object) {
			auto& clearData = BasicNode<Char_>::getDataFrom(node.data);
			if(auto listData = std::get_if<BasicListData<Char_>>(&clearData.data)) {
				object = *listData;
				return true;
			}
			return false;
		}
		
		template<typename Char_>
		bool DecodeImpl<Char_, BasicMapData<Char_>>::decode(const BasicNode<Char_>& node, BasicMapData<Char_>& object) {
			auto& clearData = BasicNode<Char_>::getDataFrom(node.data);
			if(auto mapData = std::get_if<BasicMapData<Char_>>(&clearData.data)) {
				object = *mapData;
				return true;
			}
			return false;
		}
	}
}