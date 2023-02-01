#pragma once
#include <map>

namespace ieml {
	class Node;
	
	/// @brief Structure to implement the conversion functions from a node to T
	template<typename T>
	struct Decode;
	
	namespace detail {
		/// @brief Help structure to implement the conversion functions from a node to T
		template<typename T>
		struct DecodeImpl {
			static bool func(const Node &node, T &object);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to raw data
		template<>
		struct DecodeImpl<RawNodeData> {
			static bool func(const Node &node, RawNodeData &object);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to string
		template<>
		struct DecodeImpl<std::string> {
			static bool func(const Node &node, std::string &object);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to list
		template<>
		struct DecodeImpl<std::vector<Node>> {
			static bool func(const Node &node, std::vector<Node> &object);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to map
		template<>
		struct DecodeImpl<std::map<std::string, Node>> {
			static bool func(const Node &node, std::map<std::string, Node> &object);
		};
	}
}
