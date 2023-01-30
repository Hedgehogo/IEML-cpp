#include <algorithm>
#include "Node.hpp"
#include "../../readFile/readFile.hpp"
#include "../../preprocess/preprocess.hpp"
#include "../../parse/parse.hpp"

namespace ieml {
	TagNodeData::TagNodeData(PNodeData data, Tag tag) : data(data), tag(tag) {}
	
	TagNodeData::TagNodeData(const TagNodeData &other) : data(new NodeData{*other.data}), tag(other.tag) {}
	
	TagNodeData::~TagNodeData() { delete data; }
	
	FileNodeData::FileNodeData(PNodeData data, FilePath filePath) : data(data), filePath(filePath) {}
	
	FileNodeData::FileNodeData(const FileNodeData &other) : data(new NodeData{*other.data}), filePath(other.filePath) {}
	
	FileNodeData::~FileNodeData() { delete data; }
	
	Node Node::undefined = Node{NullNodeData{}, Mark{0, 0}};
	
	Node::Node(const std::string &config) : data(parse(preprocess(config), mark)), mark({0, 0}) {}
	
	Node::Node(NodeData data, Mark mark) : data(std::move(data)), mark(mark) {}
	
	const NodeData &Node::getDataFrom(const NodeData &data) {
		if(auto tagData = std::get_if<TagNodeData>(&data))
			return getDataFrom(*tagData->data);
		if(auto fileData = std::get_if<FileNodeData>(&data))
			return getDataFrom(*fileData->data);
		return data;
	}
	
	NodeData &Node::getDataFrom(NodeData &data) {
		if(auto tagData = std::get_if<TagNodeData>(&data))
			return getDataFrom(*tagData->data);
		if(auto fileData = std::get_if<FileNodeData>(&data))
			return getDataFrom(*fileData->data);
		return data;
	}
	
	const FileNodeData *Node::getFileFrom(const NodeData &data) {
		if(auto tagData = std::get_if<TagNodeData>(&data))
			return getFileFrom(*tagData->data);
		if(auto fileData = std::get_if<FileNodeData>(&data))
			return fileData;
		return nullptr;
	}
	
	FileNodeData *Node::getFileFrom(NodeData &data) {
		if(auto tagData = std::get_if<TagNodeData>(&data))
			return getFileFrom(*tagData->data);
		if(auto fileData = std::get_if<FileNodeData>(&data))
			return fileData;
		return nullptr;
	}
	
	const TagNodeData *Node::getTagFrom(const NodeData &data) {
		if(auto fileData = std::get_if<FileNodeData>(&data))
			return getTagFrom(*fileData->data);
		if(auto tagData = std::get_if<TagNodeData>(&data))
			return tagData;
		return nullptr;
	}
	
	TagNodeData *Node::getTagFrom(NodeData &data) {
		if(auto fileData = std::get_if<FileNodeData>(&data))
			return getTagFrom(*fileData->data);
		if(auto tagData = std::get_if<TagNodeData>(&data))
			return tagData;
		return nullptr;
	}
	
	bool Node::isDefined(const Node &node) {
		return &node != &undefined;
	}
	
	bool Node::isDefined() const {
		return this != &undefined;
	}
	
	Mark Node::getMark() {
		return mark;
	}
	
	NodeType Node::getType() const {
		auto& clearData = getDataFrom(data);
		if(std::holds_alternative<ScalarNodeData>(clearData))
			return NodeType::Scalar;
		if(std::holds_alternative<ListNodeData>(clearData))
			return NodeType::List;
		if(std::holds_alternative<MapNodeData>(clearData))
			return NodeType::Map;
		return NodeType::Null;
	}
	
	bool Node::isNull() const {
		auto& clearData = getDataFrom(data);
		return std::holds_alternative<NullNodeData>(clearData);
	}
	
	bool Node::isScalar() const {
		auto& clearData = getDataFrom(data);
		return std::holds_alternative<ScalarNodeData>(clearData);
	}
	
	bool Node::isList() const {
		auto& clearData = getDataFrom(data);
		return std::holds_alternative<ListNodeData>(clearData);
	}
	
	bool Node::isMap() const {
		auto& clearData = getDataFrom(data);
		return std::holds_alternative<MapNodeData>(clearData);
	}
	
	bool Node::isWithTag() {
		return getTagFrom(data) != nullptr;
	}
	
	std::string Node::getTag() {
		if(auto tagData = getTagFrom(data))
			return tagData->tag;
		throw NodeAnotherTypeException{NodeType::Null, getType()};
	}
	
	bool Node::isFile() {
		return getFileFrom(data) != nullptr;
	}
	
	fs::path Node::getFilePath() {
		if(auto fileData = getFileFrom(data))
			return fileData->filePath;
		throw NodeAnotherTypeException{NodeType::Null, getType()};
	}
	
	std::size_t Node::getSize() {
		auto& clearData = getDataFrom(data);
		if(auto listData = std::get_if<ListNodeData>(&clearData))
			return listData->size();
		if(auto mapData = std::get_if<MapNodeData>(&clearData))
			return mapData->size();
		throw NodeAnotherTypeException{NodeType::List, getType()};
	}
	
	ListNodeData Node::getList() const {
		return getT<ListNodeData>(NodeAnotherTypeException{NodeType::List, getType()});
	}
	
	MapNodeData Node::getMap() {
		return getT<MapNodeData>(NodeAnotherTypeException{NodeType::Map, getType()});
	}
	
	Node &Node::at(std::size_t index) {
		auto& list = getT<ListNodeData>(NodeAnotherTypeException{NodeType::List, getType()});
		if(index < list.size())
			return list.at(index);
		return undefined;
	}
	
	Node &Node::at(std::string key) {
		auto& map = getT<MapNodeData>(NodeAnotherTypeException{NodeType::Map, getType()});
		if(auto find{map.find(key)}; find != map.end())
			return find->second;
		return undefined;
	}
	
	Node::operator bool() const {
		return this->isDefined();
	}
	
	Node &Node::operator[](std::size_t index) {
		return this->at(index);
	}
	
	Node &Node::operator[](std::string key) {
		return this->at(key);
	}
	
	namespace detail {
		bool DecodeImpl<std::string>::func(const Node &node, std::string &object) {
			auto& clearData = Node::getDataFrom(node.data);
			if(auto strData = std::get_if<ScalarNodeData>(&clearData)) {
				object = *strData;
				return true;
			}
			return false;
		}
		
		bool DecodeImpl<std::vector<Node>>::func(const Node &node, std::vector<Node> &object) {
			auto& clearData = Node::getDataFrom(node.data);
			if(auto vecData = std::get_if<ListNodeData>(&clearData)) {
				object = *vecData;
				return true;
			}
			return false;
		}
		
		bool DecodeImpl<std::map<std::string, Node>>::func(const Node &node, std::map<std::string, Node> &object) {
			auto& clearData = Node::getDataFrom(node.data);
			if(auto mapData = std::get_if<MapNodeData>(&clearData)) {
				object = *mapData;
				return true;
			}
			return false;
		}
	}
	
	Node file(const fs::path &filePath) {
		Mark mark{0, 0};
		NodeData data{parse(preprocess(readFile<char>(filePath)), mark, filePath)};
		return Node{std::move(data), filePath, mark};
	}
}