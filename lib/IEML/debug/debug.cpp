#include "debug.hpp"
#include <iostream>

namespace ieml {
	struct IndentOut { Size count; };
	
	std::ostream& operator<<(std::ostream& stream, const IndentOut& indent) {
		for(Size i{0}; i < indent.count; ++i) {
			stream << "  ";
		}
		return stream;
	}
	
	void debug(Node const& node, std::ostream& stream, Size indentSize) {
		IndentOut indent{indentSize};
		auto& clearNode{node.getClear()};
		auto type{clearNode.getType()};
		
		stream << indent << "<" << node.getMark().line << ":" << node.getMark().symbol;
		stream << ", " << getStringFromNodeType(type);
		if(auto tag{node.getTag()})
			stream << ", tag: " << tag.some();
		if(auto filePath{node.getFilePath()})
			stream << ", file-path: " << filePath.some();
		if(auto getAnchorName{node.getGetAnchorName()})
			stream << ", get-anchor-name: " << getAnchorName.some();
		if(auto takeAnchorName{node.getTakeAnchorName()})
			stream << ", take-anchor-name: " << takeAnchorName.some();
		stream << ">\n";
		
		switch(type) {
			case NodeType::Null:
				stream << indent << "null\n";
				break;
			case NodeType::Raw:
				stream << indent << "\"" << clearNode.as<RawData>().ok().str << "\"\n";
				break;
			case NodeType::String:
				stream << indent << "\"" << clearNode.as<String>().ok() << "\"\n";
				break;
			case NodeType::List:
				for(Size i{0}; i < clearNode.getListSize().ok(); ++i) {
					stream << indent << "- \n";
					debug(clearNode.at(i).ok(), stream, indentSize + 1);
				}
				break;
			case NodeType::Map:
				for(auto& [key, value]: clearNode.getMap().ok()) {
					stream << indent << key << ": \n";
					debug(value, stream, indentSize + 1);
				}
				break;
			default:
				break;
		}
	}
}