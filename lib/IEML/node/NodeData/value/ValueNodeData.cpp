#include "ValueNodeData.hpp"

namespace ieml {
	ValueNodeData::ValueNodeData(std::string string) : string(string) {}
	
	std::string ValueNodeData::getString() { return string; }
}