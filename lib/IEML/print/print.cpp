#include "print.hpp"
#include <iostream>

namespace ieml {
	struct IndentOut { Size count; };
	
	std::ostream& operator<<(std::ostream& stream, const IndentOut& indent) {
		for(Size i{0}; i < indent.count; ++i) {
			stream << "  ";
		}
		return stream;
	}
	
	void printNode(Size indentSize, std::ostream& stream, const BasicNode<Char>& node) {
		IndentOut indent{indentSize};
		auto& clearNode{node.getClear()};
		auto type{clearNode.getType()};
		
		stream << indent << "<" << node.getMark().line << ":" << node.getMark().symbol;
		stream << ", " << getStringFromNodeType(type);
		if(auto tag{node.getTag()})
			stream << ", tag: " << tag.value();
		if(auto filePath{node.getFilePath()})
			stream << ", file-path: " << filePath.value();
		if(auto getAnchorName{node.getGetAnchorName()})
			stream << ", get-anchor-name: " << getAnchorName.value();
		if(auto takeAnchorName{node.getTakeAnchorName()})
			stream << ", take-anchor-name: " << takeAnchorName.value();
		stream << ">\n";
		
		switch(type) {
			case NodeType::Null:
				stream << indent << "null\n";
				break;
			case NodeType::Raw:
				stream << indent << "\"" << clearNode.as<BasicRawData<Char>>().str << "\"\n";
				break;
			case NodeType::String:
				stream << indent << "\"" << clearNode.as<String>() << "\"\n";
				break;
			case NodeType::List:
				for(Size i{0}; i < clearNode.getListSize(); ++i) {
					stream << indent << "- \n";
					printNode(indentSize + 1, stream, clearNode.at(i));
				}
				break;
			case NodeType::Map:
				for(auto& [key, value]: clearNode.getMap()) {
					stream << indent << key << ": \n";
					printNode(indentSize + 1, stream, value);
				}
				break;
			default:
				break;
		}
	}
	
	std::ostream& operator<<(std::ostream& stream, BasicNode<Char>& node) {
		printNode(0, stream, node);
		return stream;
	}
}