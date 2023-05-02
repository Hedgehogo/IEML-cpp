#pragma once

#include <map>

namespace ieml {
	template<typename Char_>
	class BasicNode;
	
	/// @brief Structure to implement the conversion functions from a node to T
	template<typename Char_, typename T>
	struct Decode;
	
	namespace detail {
		/// @brief Help structure to implement the conversion functions from a node to T
		template<typename Char_, typename T>
		struct DecodeImpl {
			static bool decode(const BasicNode<Char_>& node, T& object);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to raw data
		template<typename Char_>
		struct DecodeImpl<Char_, BasicRawData<Char_>> {
			static bool decode(const BasicNode<Char_>& node, BasicRawData<Char_>& object);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to string
		template<typename Char_>
		struct DecodeImpl<Char_, BasicStringData<Char_>> {
			static bool decode(const BasicNode<Char_>& node, BasicStringData<Char_>& object);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to list
		template<typename Char_>
		struct DecodeImpl<Char_, BasicListData<Char_>> {
			static bool decode(const BasicNode<Char_>& node, BasicListData<Char_>& object);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to map
		template<typename Char_>
		struct DecodeImpl<Char_, BasicMapData<Char_>> {
			static bool decode(const BasicNode<Char_>& node, BasicMapData<Char_>& object);
		};
	}
}
