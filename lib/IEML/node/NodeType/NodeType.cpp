#include "NodeType.hpp"

namespace ieml {
	std::string getNodeTypeString(NodeType nodeType) {
		if(nodeType == NodeType::Bool) {
			return "Bool";
		} else if(nodeType == NodeType::Int) {
			return "Int";
		} else if(nodeType == NodeType::Double) {
			return "Double";
		} else if(nodeType == NodeType::String) {
			return "String";
		} else if(nodeType == NodeType::List) {
			return "List";
		} else if(nodeType == NodeType::Map) {
			return "Map";
		} else if(nodeType == NodeType::File) {
			return "File";
		} else if(nodeType == NodeType::Typed) {
			return "Typed";
		} else {
			return "Null";
		}
	}
}