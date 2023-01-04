#include <algorithm>
#include "Node.hpp"
#include "../NodeData/file/FileNodeData.hpp"
#include "../../readFile/readFile.hpp"
#include "../../preprocess/preprocess.hpp"
#include "../../parse/parse.hpp"

namespace ieml {
	Node::Node(const std::string &config) : data(parse(preprocess(config), mark)), mark({0, 0}) {}
	
	Node::Node(PData data, Mark mark) : data(std::move(data)), mark(mark) {}
	
	Node::Node(const Node &node) : data(node.data->copy()), mark(node.mark) {}
	
	Mark Node::getMark() {
		return mark;
	}
	
	NodeType Node::getType() {
		return data->getNodeType();
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
	
	Node &Node::at(std::size_t index) {
		return data->at(index);
	}
	
	Node &Node::at(std::string key) {
		return data->at(key);
	}
	
	std::map<std::string, Node> &Node::getMap() {
		return data->getMap();
	}
	
	AsIf<std::string>::AsIf(const Node &node) : node(&node) {}
	
	std::string AsIf<std::string>::operator()() {
		return node->data->getString();
	}
	
	Node file(const fs::path &filePath) {
		Mark mark{0, 0};
		INodeData *data{parse(preprocess(readFile<char>(filePath)), mark)};
		return Node{std::make_unique<FileNodeData>(std::unique_ptr<INodeData>{data}, filePath), mark};
	}
}