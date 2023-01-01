#include "NodeType.hpp"

namespace ieml {
	std::string getNodeTypeString(NodeType nodeType) {
		if(nodeType == NodeType::Scalar) {
			return "Scalar";
		} else if(nodeType == NodeType::List) {
			return "List";
		} else if(nodeType == NodeType::Map) {
			return "Map";
		} else if(nodeType == NodeType::File) {
			return "File";
		} else {
			return "Null";
		}
	}
}