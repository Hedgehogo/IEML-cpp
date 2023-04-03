#include <algorithm>
#include "Node.hpp"
#include "../../helpers/readFile/readFile.hpp"
#include "../../parser/Parser/Parser.hpp"
#include "getFrom.inl"

namespace ieml {
	Node Node::undefined = Node{NullData{}, Mark{0, 0}};
	
	Node::Node(NodeData data, Mark mark) : data(std::move(data)), mark(mark) {
	}
	
	const NodeData& Node::getDataFrom(const NodeData& data) {
		return getFrom<const NodeData, TagData, FileData, TakeAnchorData, GetAnchorData>(data);
	}
	
	NodeData& Node::getDataFrom(NodeData& data) {
		return getFrom<NodeData, TagData, FileData, TakeAnchorData, GetAnchorData>(data);
	}
	
	const FileData* Node::getFileFrom(const NodeData& data) {
		auto& getData{getFrom<const NodeData, TagData, TakeAnchorData, GetAnchorData>(data)};
		return std::get_if<FileData>(&getData);
	}
	
	FileData* Node::getFileFrom(NodeData& data) {
		auto& getData{getFrom<NodeData, TagData, TakeAnchorData, GetAnchorData>(data)};
		return std::get_if<FileData>(&getData);
	}
	
	const TagData* Node::getTagFrom(const NodeData& data) {
		auto& getData{getFrom<const NodeData, FileData, TakeAnchorData, GetAnchorData>(data)};
		return std::get_if<TagData>(&getData);
	}
	
	TagData* Node::getTagFrom(NodeData& data) {
		auto& getData{getFrom<NodeData, FileData, TakeAnchorData, GetAnchorData>(data)};
		return std::get_if<TagData>(&getData);
	}
	
	const TakeAnchorData* Node::getTakeAnchorFrom(const NodeData& data) {
		auto& getData{getFrom<const NodeData, TagData, FileData, GetAnchorData>(data)};
		return std::get_if<TakeAnchorData>(&getData);
	}
	
	TakeAnchorData* Node::getTakeAnchorFrom(NodeData& data) {
		auto& getData{getFrom<NodeData, TagData, FileData, GetAnchorData>(data)};
		return std::get_if<TakeAnchorData>(&getData);
	}
	
	const GetAnchorData* Node::getGetAnchorFrom(const NodeData& data) {
		auto& getData{getFrom<const NodeData, TagData, FileData, TakeAnchorData>(data)};
		return std::get_if<GetAnchorData>(&getData);
	}
	
	GetAnchorData* Node::getGetAnchorFrom(NodeData& data) {
		auto& getData{getFrom<NodeData, TagData, FileData, TakeAnchorData>(data)};
		return std::get_if<GetAnchorData>(&getData);
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
	
	bool Node::isTakeAnchor() const {
		return getTakeAnchorFrom(data) != nullptr;
	}
	
	Option<String> Node::getTakeAnchorName() const {
		if(auto tagData = getTakeAnchorFrom(data))
			return tagData->name;
		return {};
	}
	
	bool Node::isGetAnchor() const {
		return getGetAnchorFrom(data) != nullptr;
	}
	
	Option<String> Node::getGetAnchorName() const {
		if(auto tagData = getGetAnchorFrom(data))
			return tagData->name;
		return {};
	}
	
	Option<String> Node::getAnchorName() const {
		auto getData{getFrom<const NodeData, TagData, FileData>(data)};
		if(auto takeAnchorData{std::get_if<TakeAnchorData>(&getData)})
			return takeAnchorData->name;
		if(auto getAnchorData{std::get_if<TakeAnchorData>(&getData)})
			return getAnchorData->name;
		return {};
	}
	
	bool Node::isWithTag() {
		return getTagFrom(data) != nullptr;
	}
	
	Option<Tag> Node::getTag() {
		if(auto tagData = getTagFrom(data))
			return tagData->tag;
		return {};
	}
	
	bool Node::isFile() {
		return getFileFrom(data) != nullptr;
	}
	
	Option<FilePath> Node::getFilePath() {
		if(auto fileData = getFileFrom(data))
			return fileData->filePath;
		return {};
	}
	
	Size Node::getSize() const {
		auto& clearData = getDataFrom(data);
		if(auto listData = std::get_if<ListData>(&clearData))
			return listData->size();
		if(auto mapData = std::get_if<MapData>(&clearData))
			return mapData->size();
		throw NodeAnotherTypeException{NodeType::List, getType()};
	}
	
	const ListData& Node::getList() const {
		return getType<ListData>(NodeAnotherTypeException{NodeType::List, getType()});
	}
	
	const MapData& Node::getMap() const {
		return getType<MapData>(NodeAnotherTypeException{NodeType::Map, getType()});
	}
	
	Node& Node::at(Size index) {
		auto& list = getType<ListData>(NodeAnotherTypeException{NodeType::List, getType()});
		if(index < list.size())
			return list.at(index);
		return undefined;
	}
	
	const Node& Node::at(Size index) const {
		auto& list = getType<ListData>(NodeAnotherTypeException{NodeType::List, getType()});
		if(index < list.size())
			return list.at(index);
		return undefined;
	}
	
	Node& Node::at(String key) {
		auto& map = getType<MapData>(NodeAnotherTypeException{NodeType::Map, getType()});
		if(auto find{map.find(key)}; find != map.end())
			return *find->second;
		return undefined;
	}
	
	const Node& Node::at(String key) const {
		auto& map = getType<MapData>(NodeAnotherTypeException{NodeType::Map, getType()});
		if(auto find{map.find(key)}; find != map.end())
			return *find->second;
		return undefined;
	}
	
	Node::operator bool() const {
		return this->isDefined();
	}
	
	Node& Node::operator[](Size index) {
		return this->at(index);
	}
	
	const Node& Node::operator[](Size index) const {
		return this->at(index);
	}
	
	Node& Node::operator[](String key) {
		return this->at(key);
	}
	
	const Node& Node::operator[](String key) const {
		return this->at(key);
	}
	
	namespace detail {
		bool DecodeImpl<RawData>::decode(const Node& node, RawData& object) {
			auto& clearData = Node::getDataFrom(node.data);
			if(auto strData = std::get_if<RawData>(&clearData)) {
				object = *strData;
				return true;
			}
			return false;
		}
		
		bool DecodeImpl<String>::decode(const Node& node, String& object) {
			auto& clearData = Node::getDataFrom(node.data);
			if(auto strData = std::get_if<StringData>(&clearData)) {
				object = *strData;
				return true;
			}
			return false;
		}
		
		bool DecodeImpl<ListData>::decode(const Node& node, ListData& object) {
			auto& clearData = Node::getDataFrom(node.data);
			if(auto listData = std::get_if<ListData>(&clearData)) {
				object = *listData;
				return true;
			}
			return false;
		}
		
		bool DecodeImpl<MapData>::decode(const Node& node, MapData& object) {
			auto& clearData = Node::getDataFrom(node.data);
			if(auto mapData = std::get_if<MapData>(&clearData)) {
				object = *mapData;
				return true;
			}
			return false;
		}
	}
	
	Node fromFile(const FilePath& filePath, Rc<AnchorKeeper> anchorKeeper) {
		FilePath normalFilePath{filePath.lexically_normal().make_preferred()};
		Parser parser{readFile<char>(normalFilePath), normalFilePath, anchorKeeper};
		return Node{parser.parse()};
	}
	
	Node from(const String& inputStr, Rc<AnchorKeeper> anchorKeeper) {
		Parser parser{inputStr, anchorKeeper};
		return Node(parser.parse());
	}
}