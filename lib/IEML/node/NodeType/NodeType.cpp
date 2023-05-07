#include "NodeType.hpp"

namespace ieml {
	String getStringFromNodeType(NodeType nodeType) {
		if(nodeType == NodeType::String) {
			return "String";
		} else if(nodeType == NodeType::Raw) {
			return "Raw";
		} else if(nodeType == NodeType::List) {
			return "List";
		} else if(nodeType == NodeType::Map) {
			return "Map";
		} else if(nodeType == NodeType::Tag) {
			return "Tag";
		} else if(nodeType == NodeType::File) {
			return "File";
		} else if(nodeType == NodeType::TakeAnchor) {
			return "Take Anchor";
		} else if(nodeType == NodeType::GetAnchor) {
			return "Get Anchor";
		} else {
			return "Null";
		}
	}
}