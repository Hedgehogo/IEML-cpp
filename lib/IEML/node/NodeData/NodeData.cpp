#include "NodeData.hpp"

#include "../Node/Node.hpp"

namespace ieml {
	TagData::TagData(Box<NodeData> data, const Tag& tag) : data(std::move(data)), tag(tag) {
	}
	
	TagData::TagData(const NodeData& data, const Tag& tag) : data(makeBox<NodeData>(data)), tag(tag) {
	}
	
	TagData::TagData(const TagData& other) : data(makeBox<NodeData>(*other.data)), tag(other.tag) {
	}
	
	TagData& TagData::operator=(const TagData& other) {
		data = makeBox<NodeData>(*other.data);
		tag = other.tag;
		return *this;
	}
	
	FileData::FileData(Box<NodeData> data, const FilePath& filePath) : data(std::move(data)), filePath(filePath) {
	}
	
	FileData::FileData(const NodeData& data, const FilePath& filePath) : data(makeBox<NodeData>(data)), filePath(filePath) {
	}
	
	FileData::FileData(const FileData& other) : data(makeBox<NodeData>(*other.data)), filePath(other.filePath) {
	}
	
	FileData& FileData::operator=(const FileData& other) {
		data = makeBox<NodeData>(*other.data);
		filePath = other.filePath;
		return *this;
	}
	
	RawData::operator String() const {
		return str;
	}
	
	PNode::PNode(const Node& node) : node(makeBox<Node>(node)) {
	}
	
	PNode::PNode(PNode&& other) : node(std::move(other.node)) {
	}
	
	PNode::PNode(const PNode& other) : node(makeBox<Node>(*other)) {
	}
	
	Node& PNode::operator*() const {
		return *node;
	}
	
	Node* PNode::operator->() const {
		return node.get();
	}
	
	PNode& PNode::operator=(const PNode& other) {
		node = makeBox<Node>(*other);
		return *this;
	}
	
	PNode::operator const Ptr&() const {
		return node;
	}
	
	PNode::operator Ptr&() {
		return node;
	}
}
