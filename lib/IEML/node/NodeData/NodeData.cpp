#include "NodeData.hpp"

#include "../Node/Node.hpp"

namespace ieml {
	TagData::TagData(Box<NodeData> data, const Tag& tag) : data(std::move(data)), tag(tag) {
	}
	
	TagData::TagData(const NodeData& data, const Tag& tag) : data(std::make_unique<NodeData>(data)), tag(tag) {
	}
	
	TagData::TagData(const TagData& other) : data(std::make_unique<NodeData>(*other.data)), tag(other.tag) {
	}
	
	TagData& TagData::operator=(const TagData& other) {
		data = std::make_unique<NodeData>(*other.data);
		tag = other.tag;
		return *this;
	}
	
	FileData::FileData(Box<NodeData> data, const FilePath& filePath) : data(std::move(data)), filePath(filePath) {
	}
	
	FileData::FileData(const NodeData& data, const FilePath& filePath) : data(std::make_unique<NodeData>(data)), filePath(filePath) {
	}
	
	FileData::FileData(const FileData& other) : data(std::make_unique<NodeData>(*other.data)), filePath(other.filePath) {
	}
	
	FileData& FileData::operator=(const FileData& other) {
		data = std::make_unique<NodeData>(*other.data);
		filePath = other.filePath;
		return *this;
	}
	
	RawData::operator String() const {
		return str;
	}
	
	PNode::PNode(const Node& node) : node(std::make_unique<Node>(node)) {
	}
	
	PNode::PNode(PNode&& other) : node(std::move(other.node)) {
	}
	
	PNode::PNode(const PNode& other) : node(std::make_unique<Node>(*other)) {
	}
	
	Node& PNode::operator*() const {
		return *node;
	}
	
	Node* PNode::operator->() const {
		return node.get();
	}
	
	PNode& PNode::operator=(const PNode& other) {
		node = std::make_unique<Node>(*other);
		return *this;
	}
	
	PNode::operator const Ptr&() const {
		return node;
	}
	
	PNode::operator Ptr&() {
		return node;
	}
}
