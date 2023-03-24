#pragma once

#include <map>
#include "../../node/NodeData/NodeData.hpp"
#include "../../usings/usings.hpp"

namespace ieml {
	class AnchorKeeper {
	private:
		using NodeDataMap = std::map<String, NodeData>;
		
		NodeDataMap anchors_;
		Rc<AnchorKeeper> parent_;
	
	public:
		AnchorKeeper();
		
		AnchorKeeper(Rc<AnchorKeeper> parent);
		
		bool add(const String& key, NodeData value);
		
		bool add(const String& key, Node value);
		
		NodeData* get(const String& key);
	};
}
