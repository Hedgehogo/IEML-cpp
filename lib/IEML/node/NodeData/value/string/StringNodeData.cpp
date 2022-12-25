#include "StringNodeData.hpp"

namespace ieml {
	StringNodeData::StringNodeData(std::string string) : ValueNodeData(string) {}
	
	NodeType StringNodeData::getNodeType() {
		return NodeType::String;
	}
}