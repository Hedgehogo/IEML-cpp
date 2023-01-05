#pragma once
#include <map>
#include "../../node/NodeData/INodeData.hpp"

namespace ieml {
	class RefKeeper {
	private:
		using PNodeData = std::unique_ptr<INodeData>;
		using NodeDataMap = std::map<std::string, PNodeData>;
		
		NodeDataMap refs;
		RefKeeper* parent;
		
	public:
		RefKeeper();
		
		RefKeeper(RefKeeper& parent);
		
		void add(const std::string &key, INodeData* value);
		
		INodeData *get(const std::string &key);
	};
}
