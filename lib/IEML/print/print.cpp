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
	
	void printNode(Size startIndent, std::ostream& stream, Node& node) {
		IndentOut indent{startIndent};
		auto type{node.getType()};
		stream << indent << "<" << node.getMark().line << ":" << node.getMark().symbol;
		stream << ", " << getNodeTypeString(type);
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
				stream << indent << "\"" << node.as<RawData>().str << "\"\n";
				break;
			case NodeType::String:
				stream << indent << "\"" << node.as<String>() << "\"\n";
				break;
			case NodeType::List:
				for(Size i{0}; i < node.getSize(); ++i) {
					stream << indent << "- \n";
					printNode(startIndent + 1, stream, node.at(i));
				}
				break;
			case NodeType::Map:
				for(auto& [key, value]: node.getMap()) {
					stream << indent << key << ": \n";
					printNode(startIndent + 1, stream, *value);
				}
				break;
		}
	}
	
	std::ostream& operator<<(std::ostream& stream, Node& node) {
		printNode(0, stream, node);
		return stream;
	}
}