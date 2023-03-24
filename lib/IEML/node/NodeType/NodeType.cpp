#include "NodeType.hpp"

namespace ieml {
	String getNodeTypeString(NodeType nodeType) {
		if(nodeType == NodeType::String) {
			return "String";
		} else if(nodeType == NodeType::Raw) {
			return "Raw";
		} else if(nodeType == NodeType::List) {
			return "List";
		} else if(nodeType == NodeType::Map) {
			return "Map";
		} else {
			return "Null";
		}
	}
}