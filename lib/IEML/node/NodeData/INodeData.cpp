#include <filesystem>
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
	
	fs::path INodeData::getFilePath() {
		throw NodeAnotherTypeException{NodeType::Null, getNodeType()};
	}
	
	std::size_t INodeData::getSize() {
		throw NodeAnotherTypeException{NodeType::List, getNodeType()};
	}
	
	std::string INodeData::getString() {
		throw NodeAnotherTypeException{NodeType::Scalar, getNodeType()};
	}
	
	std::map<std::string, Node> &INodeData::getMap() {
		throw NodeAnotherTypeException{NodeType::Map, getNodeType()};
	}
	
	Node &INodeData::at(std::size_t index) {
		throw NodeAnotherTypeException{NodeType::List, getNodeType()};
	}
	
	Node &INodeData::at(std::string key) {
		throw NodeAnotherTypeException{NodeType::Map, getNodeType()};
	}
}