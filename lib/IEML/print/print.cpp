#include "print.hpp"
#include <iostream>

namespace ieml {
	struct Indent {size_t count; };
	
	std::ostream &operator<<(std::ostream &stream, const Indent &indent) {
		for(size_t i{0}; i < indent.count; ++i) {
			stream << "  ";
		}
		return stream;
	}
	
	void printNode(std::size_t startIndent, std::ostream &stream, Node &node) {
		Indent indent{startIndent};
		auto type{node.getType()};
		stream << indent << "<" << node.getMark().line << ":" << node.getMark().symbol;
		stream << ", " << getNodeTypeString(type);
		if(node.isWithTag()) stream << ", tag: " << node.getTag();
		if(node.isFile()) stream << ", file-path: " << node.getFilePath();
		stream << ">\n";
		
		switch(type) {
			case NodeType::Null: stream << indent << "null\n"; break;
			case NodeType::Raw: stream << indent << "\"" << node.as<RawNodeData>().str << "\"\n"; break;
			case NodeType::String: stream << indent << "\"" << node.as<std::string>() << "\"\n"; break;
			case NodeType::List:
				for(std::size_t i{0}; i < node.getSize(); ++i) {
					stream << Indent{startIndent + 1} << "- \n";
					printNode(startIndent + 2, stream, node.at(i));
				}
				break;
			case NodeType::Map:
				for(auto& [key, value]: node.getMap()) {
					stream << indent << key << ": \n";
					printNode(startIndent + 1, stream, value);;
				}
				break;
		}
	}
	
	std::ostream &operator<<(std::ostream &stream, Node &node) {
		printNode(0, stream, node);
		return stream;
	}
}