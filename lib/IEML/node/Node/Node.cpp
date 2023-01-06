#include <algorithm>
#include "Node.hpp"
#include "../NodeData/null/NullNodeData.hpp"
#include "../NodeData/file/FileNodeData.hpp"
#include "../NodeData/exception/NodeAnotherTypeException.hpp"
#include "../../readFile/readFile.hpp"
#include "../../preprocess/preprocess.hpp"
#include "../../parse/parse.hpp"

namespace ieml {
	Node Node::undefined = Node{std::unique_ptr<NullNodeData>{}, Mark{0, 0}};
	
	Node::Node(const std::string &config) : data(parse(preprocess(config), mark)), mark({0, 0}) {}
	
	Node::Node(PData data, Mark mark) : data(std::move(data)), mark(mark) {}
	
	Node::Node(const Node &node) : data(node.data->copy()), mark(node.mark) {}
	
	Node &Node::getUndefined() {
		return undefined;
	}
	
	bool Node::isDefined() const {
		return this != &undefined;
	}
	
	Mark Node::getMark() {
		return mark;
	}
	
	NodeType Node::getType() const {
		return data->getNodeType();
	}
	
	bool Node::isNull() const {
		return getType() == NodeType::Null;
	}
	
	bool Node::isScalar() const {
		return getType() == NodeType::Scalar;
	}
	
	bool Node::isList() const {
		return getType() == NodeType::List;
	}
	
	bool Node::isMap() const {
		return getType() == NodeType::Map;
	}
	
	bool Node::isWithTag() {
		return data->isWithTag();
	}
	
	std::string Node::getTag() {
		return data->getTag();
	}
	
	bool Node::isFile() {
		return data->isFile();
	}
	
	fs::path Node::getFilePath() {
		return data->getFilePath();
	}
	
	std::size_t Node::getSize() {
		return data->getSize();
	}
	
	std::map<std::string, Node> Node::getMap() {
		return data->getMap();
	}
	
	Node &Node::at(std::size_t index) {
		return data->at(index);
	}
	
	Node &Node::at(std::string key) {
		return data->at(key);
	}
	
	Node::operator bool() const {
		return isDefined();
	}
	
	Node &Node::operator[](std::size_t index) {
		return at(index);
	}
	
	Node &Node::operator[](std::string key) {
		return at(key);
	}
	
	namespace detail {
		bool DecodeImpl<std::string>::func(const Node &node, std::string &object) {
			if(node.getType() == NodeType::Scalar) {
				object = node.data->getString();
				return true;
			}
			return false;
		}
		
		bool DecodeImpl<std::vector<Node>>::func(const Node &node, std::vector<Node> &object) {
			if(node.getType() == NodeType::List) {
				object = node.data->getList();
				return true;
			}
			return false;
		}
		
		bool DecodeImpl<std::map<std::string, Node>>::func(const Node &node, std::map<std::string, Node> &object) {
			if(node.getType() == NodeType::Map) {
				object = node.data->getMap();
				return true;
			}
			return false;
		}
	}
	
	Node file(const fs::path &filePath) {
		Mark mark{0, 0};
		INodeData *data{parse(preprocess(readFile<char>(filePath)), mark, filePath)};
		return Node{std::make_unique<FileNodeData>(std::unique_ptr<INodeData>{data}, filePath), mark};
	}
}