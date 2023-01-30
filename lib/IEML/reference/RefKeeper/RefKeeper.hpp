#pragma once
#include <map>
#include "../../node/NodeData/NodeData.hpp"

namespace ieml {
	class RefKeeper {
	private:
		using NodeDataMap = std::map<std::string, NodeData>;
		
		NodeDataMap refs;
		RefKeeper* parent;
		
	public:
		RefKeeper();
		
		RefKeeper(RefKeeper& parent);
		
		void add(const std::string &key, NodeData value);
		
		void add(const std::string &key, Node value);
		
		NodeData *get(const std::string &key);
	};
}
