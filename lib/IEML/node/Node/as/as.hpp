#pragma once

#include <map>

namespace ieml {
	class Node;
	
	/// @brief Structure to implement the conversion functions from a node to T
	template <typename T>
	struct Decode;
	
	namespace detail {
		/// @brief Help structure to implement the conversion functions from a node to T
		template <typename T>
		struct DecodeImpl {
			static bool func(const Node& node, T& object);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to raw data
		template <>
		struct DecodeImpl<RawData> {
			static bool func(const Node& node, RawData& object);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to string
		template <>
		struct DecodeImpl<StringData> {
			static bool func(const Node& node, StringData& object);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to list
		template <>
		struct DecodeImpl<ListData> {
			static bool func(const Node& node, ListData& object);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to map
		template <>
		struct DecodeImpl<MapData> {
			static bool func(const Node& node, MapData& object);
		};
	}
}
