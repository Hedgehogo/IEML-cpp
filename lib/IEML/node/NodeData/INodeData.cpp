#include <filesystem>
#include "INodeData.hpp"
#include "exception/NodeAnotherTypeException.hpp"

namespace ieml {
	bool INodeData::isScalar() const {
		return false;
	}
	
	bool INodeData::isWithTag() const {
		return false;
	}
	
	std::string INodeData::getTag() const {
		throw NodeAnotherTypeException{NodeType::Null, getNodeType()};
	}
	
	bool INodeData::isFile() const {
		return false;
	}
	
	fs::path INodeData::getFilePath() const {
		throw NodeAnotherTypeException{NodeType::Null, getNodeType()};
	}
	
	std::size_t INodeData::getSize() const {
		throw NodeAnotherTypeException{NodeType::List, getNodeType()};
	}
	
	std::string INodeData::getString() const {
		throw NodeAnotherTypeException{NodeType::Scalar, getNodeType()};
	}
	
	std::vector<Node> INodeData::getList() const {
		throw NodeAnotherTypeException{NodeType::Map, getNodeType()};
	}
	
	std::map<std::string, Node> INodeData::getMap() const {
		throw NodeAnotherTypeException{NodeType::Map, getNodeType()};
	}
	
	Node &INodeData::at(std::size_t index) {
		throw NodeAnotherTypeException{NodeType::List, getNodeType()};
	}
	
	Node &INodeData::at(std::string key) {
		throw NodeAnotherTypeException{NodeType::Map, getNodeType()};
	}
}