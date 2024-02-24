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
	
	void debug(Node const& node, std::ostream& stream, Size indent_size) {
		IndentOut indent{indent_size};
		auto& clear_node{node.get_clear()};
		auto type{clear_node.get_type()};
		
		stream << indent << "<" << node.get_mark().line << ":" << node.get_mark().symbol;
		stream << ", " << get_string_from_node_type(type);
		for(auto& tag: node.get_tag()) {
			stream << ", tag: " << tag;
		}
		for(auto& file_path: node.get_file_path()) {
			stream << ", file-path: " << file_path;
		}
		for(auto& get_anchor_name: node.get_get_anchor_name()) {
			stream << ", get-anchor-name: " << get_anchor_name;
		}
		for(auto& take_anchor_name: node.get_take_anchor_name()) {
			stream << ", take-anchor-name: " << take_anchor_name;
		}
		stream << ">\n";
		
		switch(type) {
			case NodeType::Null:
				stream << indent << "null\n";
				break;
			case NodeType::Raw:
				stream << indent << "\"" << clear_node.as<RawData>().ok().str << "\"\n";
				break;
			case NodeType::String:
				stream << indent << "\"" << clear_node.as<String>().ok() << "\"\n";
				break;
			case NodeType::List:
				for(Size i{0}; i < clear_node.get_list_size().ok(); ++i) {
					stream << indent << "- \n";
					debug(clear_node.at(i).ok(), stream, indent_size + 1);
				}
				break;
			case NodeType::Map:
				for(auto& [key, value]: clear_node.get_map().ok()) {
					stream << indent << key << ": \n";
					debug(value, stream, indent_size + 1);
				}
				break;
			default:
				break;
		}
	}
}