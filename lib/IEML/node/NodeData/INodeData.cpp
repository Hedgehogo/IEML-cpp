#include "INodeData.hpp"
#include "exception/NodeAnotherTypeException.hpp"

namespace ieml {
	bool INodeData::isScalar() {
		return false;
	}
	
	bool INodeData::isWithTag() {
		return false;
	}
	
	std::string INodeData::getTag() {
		throw NodeAnotherTypeException{NodeType::Null, getNodeType()};
	}
	
	bool INodeData::isFile() {
		return false;
	}
	
	std::string INodeData::getFilePath() {
		throw NodeAnotherTypeException{NodeType::File, getNodeType()};;
	}
	
	std::string INodeData::getString() {
		throw NodeAnotherTypeException{NodeType::Scalar, getNodeType()};
	}
	
	Node &INodeData::at(std::size_t index) {
		throw NodeAnotherTypeException{NodeType::List, getNodeType()};
	}
	
	Node &INodeData::at(std::string key) {
		throw NodeAnotherTypeException{NodeType::Map, getNodeType()};
	}
}