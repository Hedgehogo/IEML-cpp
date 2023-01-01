#include <algorithm>
#include "Node.hpp"
#include "../NodeData/scalar/ScalarNodeData.hpp"
#include "../NodeData/null/NullNodeData.hpp"
#include "../NodeData/list/ListNodeData.hpp"
#include "../NodeData/map/MapNodeData.hpp"
#include "../NodeData/file/FileNodeData.hpp"
#include "../NodeData/tag/TagNodeData.hpp"
#include "../../isValue/isValue.hpp"
#include "../../toValue/toValue.hpp"

namespace ieml {
	Node::Node(std::string config) : data(parse(config)), mark({0, 0}) {}
	
	Node::Node(Node::PData data, Mark mark) : data(std::move(data)), mark(mark) {}
	
	Mark Node::getMark() {
		return mark;
	}
	
	NodeType Node::getNodeType() {
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
	
	std::string Node::getFilePath() {
		return data->getFilePath();
	}
	
	Node &Node::at(std::size_t index) {
		return data->at(index);
	}
	
	Node &Node::at(std::string key) {
		return data->at(key);
	}
	
	INodeData* parse(std::string_view config) {
		auto first{config.begin()};
		auto last{config.end()};
		auto line{std::find(first, last, '\n')};
		
		
		
		if(isEnter(config.begin(), config.end())) {
		
		} else if(isShortList(config.begin(), config.end())) {
		
		} else if(isFile(config.begin(), config.end())) {
		
		} else if(isNull(config.begin(), config.end())) {
			return new NullNodeData{{config.begin(), config.end()}};
		} else {
			return new ScalarNodeData{{config.begin(), config.end()}};
		}
		return new NullNodeData(std::string{});
	}
	
	AsIf<std::string>::AsIf(const Node &node) : node(&node) {}
	
	std::string AsIf<std::string>::operator()() {
		return node->data->getString();
	}
}