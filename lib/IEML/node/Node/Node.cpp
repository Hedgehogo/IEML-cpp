#include <algorithm>
#include "Node.hpp"
#include "../../readFile/readFile.hpp"
#include "../../preprocess/preprocess.hpp"
#include "../../parse/parse.hpp"

namespace ieml {
	Node Node::undefined = Node{NullData{}, Mark{0, 0}};
	
	Node::Node(const std::string& config) : data(parse(preprocess(config), mark)), mark({0, 0}) {
	}
	
	Node::Node(NodeData data, Mark mark) : data(std::move(data)), mark(mark) {
	}
	
	const NodeData& Node::getDataFrom(const NodeData& data) {
		if(auto tagData = std::get_if<TagData>(&data))
			return getDataFrom(*tagData->data);
		if(auto fileData = std::get_if<FileData>(&data))
			return getDataFrom(*fileData->data);
		return data;
	}
	
	NodeData& Node::getDataFrom(NodeData& data) {
		if(auto tagData = std::get_if<TagData>(&data))
			return getDataFrom(*tagData->data);
		if(auto fileData = std::get_if<FileData>(&data))
			return getDataFrom(*fileData->data);
		return data;
	}
	
	const FileData* Node::getFileFrom(const NodeData& data) {
		if(auto tagData = std::get_if<TagData>(&data))
			return getFileFrom(*tagData->data);
		if(auto fileData = std::get_if<FileData>(&data))
			return fileData;
		return nullptr;
	}
	
	FileData* Node::getFileFrom(NodeData& data) {
		if(auto tagData = std::get_if<TagData>(&data))
			return getFileFrom(*tagData->data);
		if(auto fileData = std::get_if<FileData>(&data))
			return fileData;
		return nullptr;
	}
	
	const TagData* Node::getTagFrom(const NodeData& data) {
		if(auto fileData = std::get_if<FileData>(&data))
			return getTagFrom(*fileData->data);
		if(auto tagData = std::get_if<TagData>(&data))
			return tagData;
		return nullptr;
	}
	
	TagData* Node::getTagFrom(NodeData& data) {
		if(auto fileData = std::get_if<FileData>(&data))
			return getTagFrom(*fileData->data);
		if(auto tagData = std::get_if<TagData>(&data))
			return tagData;
		return nullptr;
	}
	
	bool Node::isDefined(const Node& node) {
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
		return getNodeTypeFromIndex(clearData.index());
	}
	
	bool Node::isNull() const {
		return this->is<NodeType::Null>();
	}
	
	bool Node::isRaw() const {
		return this->is<NodeType::Raw>();
	}
	
	bool Node::isString() const {
		return this->is<NodeType::String>();
	}
	
	bool Node::isList() const {
		return this->is<NodeType::List>();
	}
	
	bool Node::isMap() const {
		return this->is<NodeType::Map>();
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
	
	FilePath Node::getFilePath() {
		if(auto fileData = getFileFrom(data))
			return fileData->filePath;
		throw NodeAnotherTypeException{NodeType::Null, getType()};
	}
	
	std::size_t Node::getSize() {
		auto& clearData = getDataFrom(data);
		if(auto listData = std::get_if<ListData>(&clearData))
			return listData->size();
		if(auto mapData = std::get_if<MapData>(&clearData))
			return mapData->size();
		throw NodeAnotherTypeException{NodeType::List, getType()};
	}
	
	ListData Node::getList() const {
		return getT<ListData>(NodeAnotherTypeException{NodeType::List, getType()});
	}
	
	MapData Node::getMap() {
		return getT<MapData>(NodeAnotherTypeException{NodeType::Map, getType()});
	}
	
	Node& Node::at(std::size_t index) {
		auto& list = getT<ListData>(NodeAnotherTypeException{NodeType::List, getType()});
		if(index < list.size())
			return list.at(index);
		return undefined;
	}
	
	Node& Node::at(std::string key) {
		auto& map = getT<MapData>(NodeAnotherTypeException{NodeType::Map, getType()});
		if(auto find{map.find(key)}; find != map.end())
			return *find->second;
		return undefined;
	}
	
	Node::operator bool() const {
		return this->isDefined();
	}
	
	Node& Node::operator[](std::size_t index) {
		return this->at(index);
	}
	
	Node& Node::operator[](std::string key) {
		return this->at(key);
	}
	
	namespace detail {
		bool DecodeImpl<RawData>::func(const Node& node, RawData& object) {
			auto& clearData = Node::getDataFrom(node.data);
			if(auto strData = std::get_if<RawData>(&clearData)) {
				object = *strData;
				return true;
			}
			return false;
		}
		
		bool DecodeImpl<std::string>::func(const Node& node, std::string& object) {
			auto& clearData = Node::getDataFrom(node.data);
			if(auto strData = std::get_if<StringData>(&clearData)) {
				object = *strData;
				return true;
			}
			return false;
		}
		
		bool DecodeImpl<ListData>::func(const Node& node, ListData& object) {
			auto& clearData = Node::getDataFrom(node.data);
			if(auto listData = std::get_if<ListData>(&clearData)) {
				object = *listData;
				return true;
			}
			return false;
		}
		
		bool DecodeImpl<MapData>::func(const Node& node, MapData& object) {
			auto& clearData = Node::getDataFrom(node.data);
			if(auto mapData = std::get_if<MapData>(&clearData)) {
				object = *mapData;
				return true;
			}
			return false;
		}
	}
	
	Node file(const FilePath& filePath) {
		Mark mark{0, 0};
		FilePath normalFilePath{filePath.lexically_normal().make_preferred()};
		NodeData data{parse(preprocess(readFile<char>(normalFilePath)), mark, normalFilePath)};
		return Node{std::move(data), normalFilePath, mark};
	}
}