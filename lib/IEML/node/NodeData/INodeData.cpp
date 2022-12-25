#include "INodeData.hpp"
#include "exception/NotRequestedTypeException.hpp"

namespace ieml {
	std::string INodeData::getString() {
		throw NotRequestedTypeException{"string", getNodeType()};
	}
	
	bool INodeData::getBool() {
		throw NotRequestedTypeException{"bool", getNodeType()};
	}
	
	llint INodeData::getInt() {
		throw NotRequestedTypeException{"int", getNodeType()};
	}
	
	double INodeData::getDouble() {
		throw NotRequestedTypeException{"double", getNodeType()};
	}
}