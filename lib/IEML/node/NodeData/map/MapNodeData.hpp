#pragma once
#include "../INodeData.hpp"
#include "../../Node/Node.hpp"
#include <map>
#include <memory>

namespace ieml {
	class MapNodeData : public INodeData {
	private:
		std::map<std::string, Node> map;
	
	public:
		MapNodeData(std::map<std::string, Node> map);
		
		NodeType getNodeType() const override;
		
		std::size_t getSize() const override;
		
		std::map<std::string, Node> getMap() const override;
		
		Node &at(std::string key) override;
		
		MapNodeData *copy() const override;
	};
}
