#pragma once

#include <map>
#include "../../node/NodeData/NodeData.hpp"
#include "../../usings/usings.hpp"

namespace ieml {
	template<typename Char_>
	class BasicAnchorKeeper {
	private:
		using NodeDataMap = std::unordered_map<BasicString<Char_>, BasicNodeData<Char_>>;
		
		NodeDataMap anchors_;
		Rc<BasicAnchorKeeper<Char_>> parent_;
		
	public:
		BasicAnchorKeeper();
		
		BasicAnchorKeeper(Rc<BasicAnchorKeeper> parent);
		
		bool add(const BasicString<Char_>& key, BasicNodeData<Char_> value);
		
		bool add(const BasicString<Char_>& key, BasicNode<Char_> value);
		
		BasicNodeData<Char_>* get(const BasicString<Char_>& key);
	};
	
	using AnchorKeeper = BasicAnchorKeeper<Char>;
}
