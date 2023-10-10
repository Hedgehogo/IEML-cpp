#include "NodeType.hpp"

namespace ieml {
	String get_string_from_node_type(NodeType node_type) {
		if(node_type == NodeType::String) {
			return "String";
		} else if(node_type == NodeType::Raw) {
			return "Raw";
		} else if(node_type == NodeType::List) {
			return "List";
		} else if(node_type == NodeType::Map) {
			return "Map";
		} else if(node_type == NodeType::Tag) {
			return "Tag";
		} else if(node_type == NodeType::File) {
			return "File";
		} else if(node_type == NodeType::TakeAnchor) {
			return "Take Anchor";
		} else if(node_type == NodeType::GetAnchor) {
			return "Get Anchor";
		} else {
			return "Null";
		}
	}
}